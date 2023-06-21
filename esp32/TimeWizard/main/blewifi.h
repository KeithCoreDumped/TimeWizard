#pragma once

#include "BLE2902.h"
#include "BLEDevice.h"
#include "BLEServer.h"
#include "BLEUtils.h"
#include "Wifi.h"
#include "esp_event.h"
#include "esp_log.h"
#include "esp_netif.h"
#include "esp_system.h"
#include "esp_tls.h"
#include "esp_wifi.h"
#include "freertos/FreeRTOS.h"
#include "freertos/event_groups.h"
#include "freertos/task.h"
#include "lwip/dns.h"
#include "lwip/err.h"
#include "lwip/netdb.h"
#include "lwip/sockets.h"
#include "lwip/sys.h"
#include "nvs_flash.h"
#include <Task.h>
#include <esp_log.h>
#include <esp_sntp.h>
#include <lwip/apps/sntp.h>
#include <string>
#include <time.h>

#include "sdkconfig.h"

static char TAG[] = "BLEWIFI";
#define WIFI_CONNECTED_BIT BIT0
#define WIFI_FAIL_BIT BIT1
struct Data {
	std::string SSID      = "myssid";
	std::string pass      = "mypassword";
	bool scan_requested   = false;
	bool scan_done        = false;
	bool wifi_connected   = false;
	bool wifi_reconnect   = false;
	int wifi_retry        = 0;
	char scan_result[420] = "?not ready";
	EventGroupHandle_t wifi_event_group;
} g_data;

void WiFiEventHandler(void *arg,
                      esp_event_base_t event_base,
                      int32_t event_id,
                      void *event_data) {
	if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_STA_START) {
		esp_wifi_connect();
	} else if (event_base == WIFI_EVENT &&
	           event_id == WIFI_EVENT_STA_DISCONNECTED) {
		g_data.wifi_connected = false;
		if (g_data.wifi_retry < 2) {
			esp_wifi_connect();
			++g_data.wifi_retry;
			// ESP_LOGI(TAG, "retrying...(%d,%d)", s_retry_num, WIFI_MAX_RETRY);
		} else {
			xEventGroupSetBits(g_data.wifi_event_group, WIFI_FAIL_BIT);
		}
		// ESP_LOGI(TAG, "connection failed");
	} else if (event_base == IP_EVENT && event_id == IP_EVENT_STA_GOT_IP) {
		g_data.wifi_connected    = true;
		ip_event_got_ip_t *event = (ip_event_got_ip_t *)event_data;
		ESP_LOGI(TAG, "got ip:" IPSTR, IP2STR(&event->ip_info.ip));
		g_data.wifi_retry = 0;
		xEventGroupSetBits(g_data.wifi_event_group, WIFI_CONNECTED_BIT);
	} else if (event_base == WIFI_EVENT && event_id == WIFI_EVENT_SCAN_DONE) {
		ESP_LOGI(TAG, "Wifi Scan done");
		g_data.scan_done = true;
	}
}

esp_err_t connectWiFi(const char *ssid, const char *pass);

void startWiFi() {
	ESP_ERROR_CHECK(esp_netif_init());

	ESP_ERROR_CHECK(esp_event_loop_create_default());
	esp_netif_create_default_wifi_sta();

	wifi_init_config_t cfg = WIFI_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_wifi_init(&cfg));
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_start());
	g_data.wifi_event_group = xEventGroupCreate();
	esp_event_handler_instance_t instance_any_id;
	esp_event_handler_instance_t instance_got_ip;
	ESP_ERROR_CHECK(esp_event_handler_instance_register(
	    WIFI_EVENT, ESP_EVENT_ANY_ID, &WiFiEventHandler, NULL, &instance_any_id));
	ESP_ERROR_CHECK(esp_event_handler_instance_register(
	    IP_EVENT, IP_EVENT_STA_GOT_IP, &WiFiEventHandler, NULL, &instance_got_ip));
	/* The event will not be processed after unregister */
	/*ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
	    IP_EVENT, IP_EVENT_STA_GOT_IP, instance_got_ip));
	ESP_ERROR_CHECK(esp_event_handler_instance_unregister(
	    WIFI_EVENT, ESP_EVENT_ANY_ID, instance_any_id));*/
	// vEventGroupDelete(g_data.wifi_event_group);
}

esp_err_t connectWiFi(const char *ssid, const char *pass) {
	wifi_config_t wifi_config = {};
	strcpy((char *)wifi_config.sta.ssid, ssid);
	strcpy((char *)wifi_config.sta.password, pass);

	ESP_ERROR_CHECK(esp_wifi_stop());
	ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA));
	ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config));
	ESP_ERROR_CHECK(esp_wifi_start());

	/* Waiting until either the connection is established (WIFI_CONNECTED_BIT) or
	 * connection failed for the maximum number of re-tries (WIFI_FAIL_BIT). The
	 * bits are set by event_handler() (see above) */
	EventBits_t bits = xEventGroupWaitBits(g_data.wifi_event_group,
	                                       WIFI_CONNECTED_BIT | WIFI_FAIL_BIT,
	                                       pdFALSE, pdFALSE, portMAX_DELAY);
	bool ret         = false;
	/* xEventGroupWaitBits() returns the bits before the call returned, hence we
	 * can test which event actually happened. */
	if (bits & WIFI_CONNECTED_BIT) {
		ESP_LOGI(TAG, "connection to wifi succeeded with [ssid=%s, pass=%s]", ssid, pass);
		ret = true;
	} else if (bits & WIFI_FAIL_BIT) {
		ESP_LOGI(TAG, "connection to wifi failed with [ssid=%s, pass=%s]", ssid, pass);
	} else {
		ESP_LOGE(TAG, "UNEXPECTED EVENT");
	}
	g_data.wifi_connected = ret;
	return ret;
}

void scanWiFi() {
	if (!g_data.scan_requested) {
		g_data.scan_requested = true;
		g_data.scan_done      = false;
		auto ret              = esp_wifi_scan_start(NULL, false);
		if (ESP_ERR_WIFI_STATE == ret) {
			esp_wifi_disconnect();
			ESP_LOGW(TAG, "stopped connecting to wifi, making way for wifi scanning.");
		} else {
			ESP_ERROR_CHECK(ret);
		}
	} else {
		if (g_data.scan_done) {
			constexpr int DEFAULT_SCAN_LIST_SIZE = 10;
			uint16_t number                      = DEFAULT_SCAN_LIST_SIZE;
			wifi_ap_record_t ap_info[DEFAULT_SCAN_LIST_SIZE];
			uint16_t ap_count = 0;
			memset(ap_info, 0, sizeof(ap_info));
			ESP_ERROR_CHECK(esp_wifi_scan_get_ap_records(&number, ap_info));
			ESP_ERROR_CHECK(esp_wifi_scan_get_ap_num(&ap_count));

			ESP_LOGI(TAG, "esp_wifi_scan_get_ap_num: %d", ap_count);

			ESP_LOGI(TAG, "Total APs scanned = %u", ap_count);
			for (int i = 0; (i < DEFAULT_SCAN_LIST_SIZE) && (i < ap_count); ++i) {
				ESP_LOGI(TAG, "SSID \t\t%s", ap_info[i].ssid);
				ESP_LOGI(TAG, "RSSI \t\t%d", ap_info[i].rssi);
				ESP_LOGI(TAG, "Channel \t\t%d\n", ap_info[i].primary);
			}

			uint8_t map[DEFAULT_SCAN_LIST_SIZE] = {};
			for (int i = 0; i < ap_count - 1; ++i) {
				while (map[i]) {
					++i;
				}
				for (int j = i + 1; j < ap_count; ++j) {
					if (strncmp((const char *)ap_info[i].ssid, (const char *)ap_info[j].ssid, 32) == 0) {
						if (ap_info[i].rssi < ap_info[j].rssi) {
							ap_info[i].rssi = ap_info[j].rssi;
						}
						map[j] = 1;
					}
				}
			}

			memset(g_data.scan_result, 0, sizeof(g_data.scan_result));
			strcpy(g_data.scan_result, ".");
			char line[64];
			for (int i = 0; i < ap_count; ++i) {
				if (map[i] == 0) {
					sprintf(line, "%s\n%d\n", ap_info[i].ssid, ap_info[i].rssi);
					strcat(g_data.scan_result, line);
				}
			}
			ESP_LOGI(TAG, "scan result: %s", g_data.scan_result);
			g_data.scan_requested = false;
			g_data.scan_done      = false;
		} else {
			ESP_LOGW(TAG, "scan result requested before it's ready");
			strcpy(g_data.scan_result, "!scan not finnished");
		}
	}
	ESP_LOGI(TAG, "scanWiFi() exits");
}

class WiFiScanCharCb : public BLECharacteristicCallbacks {
public:
	~WiFiScanCharCb(){};
	void onRead(BLECharacteristic *pCharacteristic) {
		ESP_LOGI(TAG, "read scan");
		scanWiFi();
		pCharacteristic->setValue((uint8_t *)g_data.scan_result, strnlen(g_data.scan_result, 420));
		strcpy(g_data.scan_result, "?not ready");
	}
	void onWrite(BLECharacteristic *pCharacteristic) {
	}
} wscb;

class WiFiSSIDCharCb : public BLECharacteristicCallbacks {
public:
	~WiFiSSIDCharCb(){};
	void onRead(BLECharacteristic *pCharacteristic) {
		ESP_LOGI(TAG, "read ssid");
	}
	void onWrite(BLECharacteristic *pCharacteristic) {
		g_data.SSID = pCharacteristic->getValue();
	}
} wicb;

class WiFiPassCharCb : public BLECharacteristicCallbacks {
public:
	~WiFiPassCharCb(){};
	void onRead(BLECharacteristic *pCharacteristic) {
		ESP_LOGI(TAG, "read pass");
	}
	void onWrite(BLECharacteristic *pCharacteristic) {
		g_data.pass = pCharacteristic->getValue();
	}
} wpcb;

void startBLEServer() {
	BLEDevice::init("TimeWizard");
	BLEServer *pServer   = BLEDevice::createServer();
	BLEService *pService = pServer->createService("F39E932E-4AED-B103-9A1B-CBC672F4A58E");

	BLECharacteristic *pWiFiSSID = pService->createCharacteristic(
	    BLEUUID("639F27BB-AB86-8490-C30A-EA863AA2E78B"),
	    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
	BLECharacteristic *pWiFiPass = pService->createCharacteristic(
	    BLEUUID("91D08FB7-BF53-C18D-551D-B7B3704D39EE"),
	    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE);
	BLECharacteristic *pWiFiScan = pService->createCharacteristic(
	    BLEUUID("A2914308-84F0-7F49-2579-886EA4713127"),
	    BLECharacteristic::PROPERTY_READ);

	pWiFiScan->setValue(g_data.scan_result);
	pWiFiSSID->setValue("myssid");
	pWiFiPass->setValue("mypassword");

	pWiFiScan->setCallbacks(&wscb);
	pWiFiPass->setCallbacks(&wpcb);
	pWiFiSSID->setCallbacks(&wicb);

	pService->start();

	BLEAdvertising *pAdvertising = pServer->getAdvertising();
	pAdvertising->addServiceUUID(BLEUUID(pService->getUUID()));
	pAdvertising->start();

	ESP_LOGI(TAG, "Advertising started!");
}

void timeSyncCb(struct timeval *tv) {
	ESP_LOGI(TAG, "time synchronized");
}
void startSNTP() {
	ESP_LOGI(TAG, "Initializing SNTP");
	sntp_setoperatingmode(SNTP_OPMODE_POLL);
	sntp_setservername(0, "ntp.aliyun.com");
	sntp_setservername(1, "ntp.tuna.tsinghua.edu.cn");
	sntp_setservername(2, "pool.ntp.org");
	sntp_set_time_sync_notification_cb(timeSyncCb);
}

void startTimeSync(){
	sntp_init();
}

void syncTime() {
	int retry               = 0;
	const int retry_count   = 10;
	sntp_sync_status_t stat = sntp_get_sync_status();
	while (stat == SNTP_SYNC_STATUS_RESET && ++retry < retry_count) {
		ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
		vTaskDelay(2000 / portTICK_PERIOD_MS);
	}
	if (stat == SNTP_SYNC_STATUS_RESET) {
		ESP_LOGW(TAG, "Time synchronization failed");
	}
	time_t now;
	struct tm timeinfo;
	setenv("TZ", "CST-8", 1);
	tzset();
    time(&now);
    localtime_r(&now, &timeinfo);
    char strftime_buf[64];
	strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
	ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
}
