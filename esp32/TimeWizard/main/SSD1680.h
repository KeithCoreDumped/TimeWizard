#ifndef __SSD1680_H__
#define __SSD1680_H__

#include <OpenFontRender.h>
#include <driver/gpio.h>
#include <driver/spi_master.h>
#include <esp_log.h>
#include <esp_task_wdt.h>
#include <esp_timer.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
// setup:
#define PIN_CS GPIO_NUM_33
#define PIN_DC GPIO_NUM_27
#define PIN_RES GPIO_NUM_22
#define PIN_BUSY GPIO_NUM_32
#define PIN_SCL GPIO_NUM_18
#define PIN_SDA GPIO_NUM_23

#define EPD_WIDTH 128
#define EPD_HEIGHT 296

enum EPD_Color_t {
	EPD_WHITE = 1,
	EPD_BLACK = 0
};

spi_device_handle_t spi_dev_handle;
static uint8_t g_screenBuffer[EPD_WIDTH * EPD_HEIGHT / 8];

void msleep(unsigned long ms) {
	if (ms < portTICK_PERIOD_MS) {
		esp_rom_delay_us(ms * 1000);
		esp_task_wdt_reset();
	} else {
		vTaskDelay(ms / portTICK_PERIOD_MS);
	}
}

void EPD_init() {
	spi_bus_config_t spi_bus_cfg = {.mosi_io_num   = 23,
	                                .miso_io_num   = -1,
	                                .sclk_io_num   = 18,
	                                .quadwp_io_num = -1,
	                                .quadhd_io_num = -1,
	                                .max_transfer_sz =
	                                    SOC_SPI_MAXIMUM_BUFFER_SIZE,
	                                .flags = SPICOMMON_BUSFLAG_MASTER};

	spi_device_interface_config_t spi_dev_cfg = {.dummy_bits = 0,
	                                             .mode       = 0,
	                                             .clock_speed_hz =
	                                                 SPI_MASTER_FREQ_10M,
	                                             .spics_io_num = PIN_CS,
	                                             .queue_size   = 7};

	esp_err_t err;
	err = spi_bus_initialize(SPI3_HOST, &spi_bus_cfg, SPI_DMA_CH1);
	ESP_ERROR_CHECK(err);
	err = spi_bus_add_device(SPI3_HOST, &spi_dev_cfg, &spi_dev_handle);
	ESP_ERROR_CHECK(err);

	gpio_pad_select_gpio(PIN_CS);
	gpio_set_pull_mode(PIN_CS, GPIO_PULLUP_ONLY);
	gpio_set_direction(PIN_CS, GPIO_MODE_OUTPUT);

	gpio_pad_select_gpio(PIN_DC);
	gpio_set_pull_mode(PIN_DC, GPIO_PULLUP_ONLY);
	gpio_set_direction(PIN_DC, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_DC, 1);

	gpio_pad_select_gpio(PIN_RES);
	gpio_set_pull_mode(PIN_RES, GPIO_PULLUP_ONLY);
	gpio_set_direction(PIN_RES, GPIO_MODE_OUTPUT);
	gpio_set_level(PIN_RES, 1);

	gpio_pad_select_gpio(PIN_BUSY);
	gpio_set_pull_mode(PIN_BUSY, GPIO_PULLUP_ONLY);
	gpio_set_direction(PIN_BUSY, GPIO_MODE_INPUT);
}

bool EPD_isBusy() { return gpio_get_level(PIN_BUSY); }

void EPD_waitWhileBusy() {
	while (EPD_isBusy()) {
		msleep(10);
	}
}

void EPD_writeBuffer(uint8_t *data, uint8_t len) {
	esp_err_t err;
	spi_transaction_t tr;
	memset(&tr, 0, sizeof(tr));
	tr.length    = len * 8;
	tr.tx_buffer = data;
	tr.user      = (void *)1;
	err          = spi_device_polling_transmit(spi_dev_handle, &tr);
	ESP_ERROR_CHECK(err);
}

void EPD_writeCommand(uint8_t cmd) {
	gpio_set_level(PIN_DC, 0);
	EPD_writeBuffer(&cmd, 1);
	gpio_set_level(PIN_DC, 1);
}

void EPD_writeData(uint8_t dat) { EPD_writeBuffer(&dat, 1); }

void EPD_reset() {
	ESP_LOGW("EPDDRV", "initializing");
	auto start = esp_timer_get_time();
	gpio_set_level(PIN_RES, 0);
	msleep(20);
	gpio_set_level(PIN_RES, 1);
	msleep(20);

	EPD_waitWhileBusy();
	EPD_writeCommand(0x12); // resets the commands and parameters to default
	msleep(20);

	EPD_waitWhileBusy();
	EPD_writeCommand(0x01); // Driver Output control
	EPD_writeData(0x27);    // -+
	EPD_writeData(0x01);    // -+-> MUX Gate lines setting as 0x0127 + 1 = 296
	EPD_writeData(0x01);    // Gate scanning sequence and direction

	EPD_writeCommand(0x11); // Data Entry mode setting
	EPD_writeData(0x02);    // ID = 0b10, X decrement, Y increment
	                        // AM = 0b00, the address counter is updated in the X direction
	EPD_writeCommand(0x44); // set Ram-X address start/end position
	EPD_writeData(0x0F);    // Start = (15+1)*8=128
	EPD_writeData(0x00);    // End = 0

	EPD_writeCommand(0x45); // set Ram-Y address start/end position
	EPD_writeData(0x00);    // Start = 0
	EPD_writeData(0x00);
	EPD_writeData(0x27);    // End = 0x0127 = 295
	EPD_writeData(0x01);

	EPD_writeCommand(0x3C); // Border Waveform Control
	EPD_writeData(0x05);

	EPD_writeCommand(0x21); // Display update control
	EPD_writeData(0x00);    // Red/B/W RAM option: Normal
	EPD_writeData(0x80);    // Source Output Mode: Available Source from S8 to S167

	EPD_writeCommand(0x18); // Temperature Sensor Control
	EPD_writeData(0x80);    // Internal temperature sensor selected

	EPD_writeCommand(0x4E); // set RAM x address count to 0;
	EPD_writeData(0x00);
	EPD_writeCommand(0x4F); // set RAM y address count to 0X127;
	EPD_writeData(0x27);
	EPD_writeData(0x01);

	EPD_waitWhileBusy();

	memset(g_screenBuffer, 0xFF, sizeof(g_screenBuffer));

	ESP_LOGW("EPDDRV", "initialization complete after %lld ms", (esp_timer_get_time() - start) / 1000);
}

void EPD_update() {
	EPD_writeCommand(0x22); // Display Update Control
	// EPD_writeData(0xF7); // mode 1
	EPD_writeData(0xFF);    // mode 2
	EPD_writeCommand(0x20); // Activate Display Update Sequence
	EPD_waitWhileBusy();
}

void EPD_fillScreen(uint16_t c) {
	uint8_t color = c ? 0xff : 0x00;
	EPD_writeCommand(0x24);
	for (int i = 0; i < 296 * 128 / 8; ++i) {
		EPD_writeData(color);
	}
	memset(g_screenBuffer, color, sizeof(g_screenBuffer));
	EPD_update();
}

void EPD_fillBuffer(uint16_t c) {
	uint8_t color = c ? 0xff : 0x00;
	memset(g_screenBuffer, color, sizeof(g_screenBuffer));
}

void EPD_showImage(const uint8_t *img) {
	EPD_writeCommand(0x24);
	for (int i = 0; i < 296 * 128 / 8; ++i) {
		EPD_writeData(*img);
		++img;
	}
	EPD_update();
}

void EPD_showImageInverted(const uint8_t *img) {
	EPD_writeCommand(0x24);
	for (int i = 0; i < 296 * 128 / 8; ++i) {
		EPD_writeData(~*img);
		++img;
	}
	EPD_update();
}

void EPD_deepSleep() {
	EPD_writeCommand(0x10);
	EPD_writeData(0x01);
}

void EPD_startWrite() {
}

void EPD_endWrite() {
	EPD_showImage(g_screenBuffer);
}

/*
 * Graphic functions
 */

void EPD_drawPixel(int32_t x, int32_t y, uint16_t c) {
	if (x > EPD_HEIGHT || y > EPD_WIDTH) {
		return;
	}
	x = 295 - x;

	uint32_t index = (y + x * 128) / 8 + 1; // why + 1?
	uint8_t offset = y % 8;
	if (c) {
		// white
		g_screenBuffer[index] |= (0x80 >> offset);
	} else {
		// black
		g_screenBuffer[index] &= ~(0x80 >> offset);
	}
}

void EPD_blendPixel(int32_t x, int32_t y, uint16_t c, uint16_t transparent) {
	if (x > EPD_HEIGHT || y > EPD_WIDTH) {
		// ESP_LOGW("EPDDRV", "pixel %x(%d, %d) out of bound", c, x, y);
		return;
	}
	x = 295 - x;

	uint32_t index = (y + x * 128) / 8 + 1; // why + 1?
	uint8_t offset = y % 8;
	if (!(c && transparent)) {
		if (c) {
			// white
			g_screenBuffer[index] |= (0x80 >> offset);
		} else {
			// black
			g_screenBuffer[index] &= ~(0x80 >> offset);
		}
	}
}

void EPD_drawFastVLine(int32_t x, int32_t y, int32_t h, uint16_t c) {
	for (int i = 0; i < h; ++i) {
		EPD_drawPixel(x, y + i, c);
	}
}

void EPD_drawFastHLine(int32_t x, int32_t y, int32_t w, uint16_t c) {
	for (int i = 0; i < w; ++i) {
		EPD_drawPixel(x + i, y, c);
	}
}

void EPD_drawDashedVLine(int32_t x, int32_t y, int32_t h, uint32_t t1, uint32_t t2) {
	uint32_t tx = t1 ^ t2, t = t1;
	uint16_t c = 0;
	for (int i = 0, n = 0; i < h; ++i) {
		EPD_drawPixel(x, y + i, c);
		++n;
		if (n == t) {
			c = !c;
			t = tx ^ t;
			n = 0;
		}
	}
}

void EPD_drawDashedHLine(int32_t x, int32_t y, int32_t w, uint32_t t1, uint32_t t2) {
	uint32_t tx = t1 ^ t2, t = t1;
	uint16_t c = 0;
	for (int i = 0, n = 0; i < w; ++i) {
		EPD_drawPixel(x + i, y, c);
		++n;
		if (n == t) {
			c = !c;
			t = tx ^ t;
			n = 0;
		}
	}
}

void EPD_drawLine(int x0, int y0, int x1, int y1, uint16_t c = EPD_BLACK) {
	/* Bresenham algorithm */
	int dx  = x1 - x0 >= 0 ? x1 - x0 : x0 - x1;
	int sx  = x0 < x1 ? 1 : -1;
	int dy  = y1 - y0 <= 0 ? y1 - y0 : y0 - y1;
	int sy  = y0 < y1 ? 1 : -1;
	int err = dx + dy;

	while ((x0 != x1) && (y0 != y1)) {
		EPD_drawPixel(x0, y0, c);
		if (2 * err >= dy) {
			err += dy;
			x0 += sx;
		}
		if (2 * err <= dx) {
			err += dx;
			y0 += sy;
		}
	}
}

void EPD_fillRectangle(uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t c = EPD_BLACK) {
	for (uint32_t dy = 0; dy < h; ++dy) {
		EPD_drawFastHLine(x, y + dy, w, c);
	}
}

void EPD_drawCircle(int x, int y, int radius, uint16_t c) {
	/* Bresenham algorithm */
	int x_pos = -radius;
	int y_pos = 0;
	int err   = 2 - 2 * radius;
	int e2;

	do {
		EPD_drawPixel(x - x_pos, y + y_pos, c);
		EPD_drawPixel(x + x_pos, y + y_pos, c);
		EPD_drawPixel(x + x_pos, y - y_pos, c);
		EPD_drawPixel(x - x_pos, y - y_pos, c);
		e2 = err;
		if (e2 <= y_pos) {
			err += ++y_pos * 2 + 1;
			if (-x_pos == y_pos && e2 <= x_pos) {
				e2 = 0;
			}
		}
		if (e2 > x_pos) {
			err += ++x_pos * 2 + 1;
		}
	} while (x_pos <= 0);
}

void EPD_fillCircle(int x, int y, int radius, uint16_t c) {
	/* Bresenham algorithm */
	int x_pos = -radius;
	int y_pos = 0;
	int err   = 2 - 2 * radius;
	int e2;

	do {
		EPD_drawPixel(x - x_pos, y + y_pos, c);
		EPD_drawPixel(x + x_pos, y + y_pos, c);
		EPD_drawPixel(x + x_pos, y - y_pos, c);
		EPD_drawPixel(x - x_pos, y - y_pos, c);
		EPD_drawFastHLine(x + x_pos, y + y_pos, 2 * (-x_pos) + 1, c);
		EPD_drawFastHLine(x + x_pos, y - y_pos, 2 * (-x_pos) + 1, c);
		e2 = err;
		if (e2 <= y_pos) {
			err += ++y_pos * 2 + 1;
			if (-x_pos == y_pos && e2 <= x_pos) {
				e2 = 0;
			}
		}
		if (e2 > x_pos) {
			err += ++x_pos * 2 + 1;
		}
	} while (x_pos <= 0);
}

void EPD_updateWindow(uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	if (y + h > 128 || x + w > 296) {
		ESP_LOGE("EPDDRV", "EPD_updateWindow: geometry exceed bounds");
		return;
	}
	if (x % 8 != 0 || w % 8 != 0) {
		x = ((x >> 3) << 3);
		w = w & 0x07 ? w & (((w >> 3) + 1) << 3) : ((w >> 3) << 3);
	}
	// Set RAM X - address Start / End position
	EPD_writeCommand(0x44);
	EPD_writeData((x + w) >> 3); // Start
	EPD_writeData(x >> 3);       // End

	// Set Ram Y- address Start / End position
	EPD_writeCommand(0x45);
	EPD_writeData(0x00); // Start = 0
	EPD_writeData(0x00);
	EPD_writeData(0x27); // End = 0x0127 = 295
	EPD_writeData(0x01);

	// Set RAM X address counter
	EPD_writeCommand(0x4E);
	EPD_writeData(0x00);
	//  Set RAM Y address counter
	y = 127 - y;
	EPD_writeCommand(0x4F);
	EPD_writeData(y & 0xFF);
	EPD_writeData((y >> 3) & 0xFF);
}

void EPD_showImage(const char *img, uint32_t x, uint32_t y, uint32_t w, uint32_t h) {
	for (int i = 0; i < h; ++i) {
		int k = 0;
		for (int j = 0; j < w; ++j) {
			EPD_drawPixel(x + j, y + i, *img & (0x80 >> k));
			++k;
			if (k == 8) {
				k = 0;
				++img;
			}
		}
		++img;
	}
}

void EPD_blendImage(const char *img, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t transparent = EPD_WHITE) {
	for (int i = 0; i < h; ++i) {
		int k = 0;
		for (int j = 0; j < w; ++j) {
			EPD_blendPixel(x + j, y + i, *img & (0x80 >> k), transparent);
			++k;
			if (k == 8) {
				k = 0;
				++img;
			}
		}
		++img;
	}
}

void EPD_drawMask(const char *img, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t c) {
	for (int i = 0; i < h; ++i) {
		int k = 0;
		for (int j = 0; j < w; ++j) {
			if (*img & (0x80 >> k)) {
				EPD_drawPixel(x + j, y + i, c);
			}
			++k;
			if (k == 8) {
				k = 0;
				++img;
			}
		}
		++img;
	}
}

void EPD_drawMaskInvert(const char *img, uint32_t x, uint32_t y, uint32_t w, uint32_t h, uint16_t c) {
	for (int i = 0; i < h; ++i) {
		int k = 0;
		for (int j = 0; j < w; ++j) {
			if (!(*img & (0x80 >> k))) {
				EPD_drawPixel(x + j, y + i, c);
			}
			++k;
			if (k == 8) {
				k = 0;
				++img;
			}
		}
		++img;
	}
}
#endif