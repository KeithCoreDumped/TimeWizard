#include "NeueFrutigerProRegular.h"
#include "SSD1680.h"
#include "Vonwaon16pxLite.h"
#include "blewifi.h"
// #include "ble.h"
// #include "wifi.h"
#include "ds_digital.h"
#include "icon.h"
#include <BLECharacteristic.h>
#include <OpenFontRender.h>
#include <esp_log.h>
#include <memory.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

OpenFontRender render_cjk, render_digit, render_latin;

void render_init() {
	render_cjk.set_printFunc([](const char *s) { ESP_LOGI("RENDERCJK", "%s", s); });
	render_cjk.set_drawPixel(EPD_drawPixel);
	render_cjk.set_drawFastHLine(EPD_drawFastHLine);
	render_cjk.loadFont(Vonwaon16pxLite, sizeof(Vonwaon16pxLite));
	render_cjk.setFontSize(16);

	render_digit.set_printFunc([](const char *s) { ESP_LOGI("RENDERDIGIT", "%s", s); });
	render_digit.set_drawPixel(EPD_drawPixel);
	render_digit.set_drawFastHLine(EPD_drawFastHLine);
	render_digit.loadFont(DS_Digital, sizeof(DS_Digital));
	render_digit.setFontSize(54);
	render_digit.setFontColor(EPD_BLACK, EPD_WHITE);

	render_latin.set_printFunc([](const char *s) { ESP_LOGI("RENDERLATIN", "%s", s); });
	render_latin.set_drawPixel(EPD_drawPixel);
	render_latin.set_drawFastHLine(EPD_drawFastHLine);
	render_latin.loadFont(NeueFrutigerProRegular, sizeof(NeueFrutigerProRegular));
	render_latin.setFontSize(20);
	render_latin.setFontColor(EPD_BLACK, EPD_WHITE);
}

extern "C" void app_main(void) {
	EPD_init();
	EPD_reset();
	EPD_fillScreen(EPD_WHITE);
	ESP_LOGI("MAIN", "EPD_reset");
	render_init();
	FT_Error error;
	FT_BBox bbox;

	// EPD_fillRectangle(5, 0, 250, 21);
	//  top bar
	EPD_showImage(battery21, 296 - 21, 0, 21, 21);
	EPD_showImage(bluetooth11x10, 296 - 21 - 11 - 3, 0, 11, 10);
	EPD_showImage(wifi11x10, 296 - 21 - 11 - 3, 11, 11, 10);
	EPD_fillRectangle(296 - 21 + 2, 7, 10, 7);
	// marked scale
	render_digit.setFontSize(13);
	for (int i = 1; i <= 255; i += 10) {
		EPD_drawFastVLine(i, 17, 4, EPD_BLACK);
	}
	for (int i = 6; i <= 255; i += 10) {
		EPD_drawFastVLine(i, 19, 2, EPD_BLACK);
	}
	// nocture
	//for (int i = 0; i < 21; i += 3) {
	//	EPD_drawDashedHLine(0, i, 131, 1, 3);
	//}
	EPD_blendImage(people21, 40, 0, 21, 21);
	EPD_drawMask(peoplemask21, 40, 0, 21, 21, EPD_WHITE);
	EPD_blendImage(important21, 221, 0, 21, 21);
	EPD_blendImage(task21, 11, 0, 21, 21);
	EPD_blendImage(alarm21, 171, 0, 21, 21);
	EPD_drawMaskInvert(axismask42x21, 251 - 41, 0, 42, 21, EPD_WHITE);
	render_digit.setFontSize(54);
	// splitter
	EPD_fillRectangle(0, 21, 296, 2);
	EPD_fillRectangle(0, 128 - 23, 296, 2);
	EPD_drawDashedVLine(50, 21, 84, 2, 3);
	EPD_drawDashedVLine(169, 21, 84, 2, 3);

	// left sector
	EPD_fillRectangle(5, 54, 40, 20);
	render_cjk.drawHString("主页", 5 + 4, 54 + 2, EPD_WHITE, EPD_BLACK, Align::Left, Drawing::Execute, bbox, error);
	EPD_showImage(arrown21, 15, 30, 21, 21);
	EPD_showImage(arrows21, 15, 77, 21, 21);
	EPD_blendImage(leftsectorbg50x82, 0, 23, 50, 82, EPD_WHITE);
	// middle sector
	render_digit.drawHString("21:02", 4 + 51, 23 - 5, EPD_BLACK, EPD_WHITE, Align::Left, Drawing::Execute, bbox, error);
	render_latin.drawHString("2023/6/20", 111, 64, EPD_BLACK, EPD_WHITE, Align::Center, Drawing::Execute, bbox, error);
	render_cjk.drawHString("星期二", 111, 85, EPD_BLACK, EPD_WHITE, Align::Center, Drawing::Execute, bbox, error);

	// right sector
	EPD_showImage(sunny44, 170, 24, 44, 44);
	EPD_showImage(location21, 170, 24 + 44 - 1, 21, 21);
	render_cjk.drawHString("晴", 170 + 44 + 3, 24 + 3, EPD_BLACK, EPD_WHITE, Align::Left, Drawing::Execute, bbox, error);
	render_latin.setFontSize(18);
	render_latin.drawHString("21~35°C", 170 + 44 + 3, 24 + 3 + 16 + 6, EPD_BLACK, EPD_WHITE, Align::Left, Drawing::Execute, bbox, error);
	render_cjk.drawHString("北京 昌平区", 170 + 21 + 3, 24 + 44 + 3 - 1, EPD_BLACK, EPD_WHITE, Align::Left, Drawing::Execute, bbox, error);
	render_cjk.drawHString("还有一天端午节", 170 + 3, 24 + 44 + 21 - 1, EPD_BLACK, EPD_WHITE, Align::Left, Drawing::Execute, bbox, error);

	// bottom bar
	render_cjk.drawString("向阳生长，灿若花开。", 2, 128 - 21 + 2, EPD_BLACK, EPD_WHITE);
	render_cjk.drawHString("----Nick Wald", 296, 128 - 21 + 2, EPD_BLACK, EPD_WHITE, Align::Right, Drawing::Execute, bbox, error);

	EPD_endWrite();
}

extern "C" void app_main0(void) {
	startBLEServer();
	startWiFi();
	startSNTP();
}

void EPD_render_test() {
	render_cjk.drawString("hello world", 0, 0, EPD_BLACK, EPD_WHITE);
	render_cjk.drawString("中文测试", 0, 16, EPD_BLACK, EPD_WHITE);
	render_cjk.drawString("你好世界", 0, 32, EPD_BLACK, EPD_WHITE);
	render_cjk.drawString("1234567890", 0, 48, EPD_BLACK, EPD_WHITE);
	render_cjk.drawString("abcdefghijklmnopqrstuvwxyz", 0, 60, EPD_BLACK, EPD_WHITE);
	render_cjk.drawString("ABCDEFGHIJKLMNOPQRSTUVWXYZ", 0, 72, EPD_BLACK, EPD_WHITE);

	render_digit.drawString("12:34 Wed 2023/5/2", 0, 88, EPD_BLACK, EPD_WHITE);
}
