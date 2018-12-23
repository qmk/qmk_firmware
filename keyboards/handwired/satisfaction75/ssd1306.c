
#include <string.h>

#include "hal.h"
#include "ssd1306.h"
#include "print.h"

#include "ssd1306_font.c"


/* Steal from https://stm32f4-discovery.net/2015/05/library-61-ssd1306-oled-i2c-lcd-for-stm32f4xx/ */

/*===========================================================================*/
/* Driver local functions.                                                   */
/*===========================================================================*/

static msg_t wrCmd(void *ip, uint8_t cmd) {
	const SSD1306Driver *drvp = (const SSD1306Driver *)ip;
	msg_t ret;
	uint8_t txbuf[] = { 0x00, cmd };

	i2cAcquireBus(drvp->config->i2cp);
	i2cStart(drvp->config->i2cp, drvp->config->i2ccfg);

	ret = i2cMasterTransmitTimeout(drvp->config->i2cp, drvp->config->sad,
			txbuf, sizeof(txbuf), NULL, 0, TIME_INFINITE);

	i2cReleaseBus(drvp->config->i2cp);

	return ret;
}

static msg_t wrDat(void *ip, uint8_t *txbuf, uint16_t len) {
	const SSD1306Driver *drvp = (const SSD1306Driver *)ip;
	msg_t ret;

	i2cAcquireBus(drvp->config->i2cp);
	i2cStart(drvp->config->i2cp, drvp->config->i2ccfg);

	ret = i2cMasterTransmitTimeout(drvp->config->i2cp, drvp->config->sad,
			txbuf, len, NULL, 0, TIME_INFINITE);

	i2cReleaseBus(drvp->config->i2cp);

	return ret;
}

static void updateScreen(void *ip) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;
	uint8_t idx;

	for (idx = 0; idx < 8; idx++) {
		wrCmd(drvp, 0xB0 + idx);
		wrCmd(drvp, 0x00);
		wrCmd(drvp, 0x10);

		// Write multi data
		wrDat(drvp, &drvp->fb[SSD1306_WIDTH_FIXED * idx], SSD1306_WIDTH_FIXED);
	}
}

static void toggleInvert(void *ip) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;
	uint16_t idx;

	// Toggle invert
	drvp->inv = !drvp->inv;

	for (idx = 0; idx < sizeof(drvp->fb); idx++) {
		if (idx % SSD1306_WIDTH_FIXED == 0) continue;
		drvp->fb[idx] = ~drvp->fb[idx];
	}
}

static void fillScreen(void *ip, ssd1306_color_t color) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;
	uint8_t idx;

	for (idx = 0; idx < 8; idx++) {
		drvp->fb[SSD1306_WIDTH_FIXED * idx] = 0x40;
		memset(&drvp->fb[SSD1306_WIDTH_FIXED * idx + 1],
				color == SSD1306_COLOR_BLACK ? 0x00 : 0xff, SSD1306_WIDTH);
	}
}

static void drawPixel(void *ip, uint8_t x, uint8_t y, ssd1306_color_t color) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;
	if (x > SSD1306_WIDTH || y > SSD1306_HEIGHT) return;

	// Check if pixels are inverted
	if (drvp->inv) {
		color = (ssd1306_color_t)!color;
	}

	// Set color
	if (color == SSD1306_COLOR_WHITE) {
		drvp->fb[x + (y / 8) * SSD1306_WIDTH_FIXED + 1] |= 1 << (y % 8);
	} else {
		drvp->fb[x + (y / 8) * SSD1306_WIDTH_FIXED + 1] &= ~(1 << (y % 8));
	}
}

static void gotoXy(void *ip, uint8_t x, uint8_t y) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;

	drvp->x = x;
	drvp->y = y;
}

static char PUTC(void *ip, char ch, const ssd1306_font_t *font, ssd1306_color_t color) {
	SSD1306Driver *drvp = (SSD1306Driver *)ip;
	uint32_t i, b, j;

	// Check available space in OLED
	if (drvp->x + font->fw >= SSD1306_WIDTH ||
			drvp->y + font->fh >= SSD1306_HEIGHT) {
		return 0;
	}

	// Go through font
	for (i = 0; i < font->fh; i++) {
		b = font->dt[(ch - 32) * font->fh + i];
		for (j = 0; j < font->fw; j++) {
			if ((b << j) & 0x8000) {
				drawPixel(drvp, drvp->x + j, drvp->y + i, color);
			} else {
				drawPixel(drvp, drvp->x + j, drvp->y + i,(ssd1306_color_t)! color);
			}
		}
	}

	// Increase pointer
	drvp->x += font->fw;

	// Return character written
	return ch;
}

static char PUTS(void *ip, char *str, const ssd1306_font_t *font, ssd1306_color_t color) {
	// Write characters
	while (*str) {
		// Write character by character
		if (PUTC(ip, *str, font, color) != *str) {
			// Return error
			return *str;
		}

		// Increase string pointer
		str++;
	}

	// Everything OK, zero should be returned
	return *str;
}

static void setDisplay(void *ip, uint8_t on) {
	wrCmd(ip, 0x8D);
	wrCmd(ip, on ? 0x14 : 0x10);
	wrCmd(ip, 0xAE);
}

static const struct SSD1306VMT vmt_ssd1306 = {
	updateScreen, toggleInvert, fillScreen, drawPixel,
	gotoXy, PUTC, PUTS, setDisplay
};

/*===========================================================================*/
/* Driver exported functions.                                                */
/*===========================================================================*/

void ssd1306ObjectInit(SSD1306Driver *devp) {
	devp->vmt = &vmt_ssd1306;
	devp->config = NULL;

	devp->state = SSD1306_STOP;
}

void ssd1306Start(SSD1306Driver *devp, const SSD1306Config *config) {
	const uint8_t cmds[] = {
		0xAE,	// display off
		0x20,	// Set memory address
		0x10,	// 0x00: horizontal addressing mode, 0x01: vertical addressing mode
				// 0x10: Page addressing mode(RESET), 0x11: invalid
		0xB0,	// Set page start address for page addressing mode: 0 ~ 7
		0xC8,	// Set COM output scan direction
		0x00,	// Set low column address
		0x10,	// Set height column address
		0x40,	// Set start line address
		0x81,	// Set contrast control register
		0xFF,
		0xA1,	// Set segment re-map 0 to 127
		0xA6,	// Set normal display
		0xA8,	// Set multiplex ratio(1 to 64)
		0x3F,
		0xA4,	// 0xa4: ouput follows RAM content, 0xa5: ouput ignores RAM content
		0xD3,	// Set display offset
		0x00,	// Not offset
		0xD5,	// Set display clock divide ratio/oscillator frequency
		0xF0,	// Set divide ration
		0xD9,	// Set pre-charge period
		0x22,
		0xDA,	// Set COM pins hardware configuration
		0x12,
		0xDB,	// Set VCOMH
		0x20,	// 0x20: 0.77*Vcc
		0x8D,	// Set DC-DC enable
		0x14,
		0xAF,	// turn on SSD1306panel
	};
	uint8_t idx;

    chDbgCheck((devp != NULL) && (config != NULL));

    chDbgAssert((devp->state == SSD1306_STOP) || (devp->state == SSD1306_READY),
            "ssd1306Start(), invalid state");

    devp->config = config;

	// A little delay
	chThdSleepMilliseconds(100);

	// OLED initialize
	for (idx = 0; idx < sizeof(cmds) / sizeof(cmds[0]); idx++) {
		wrCmd(devp, cmds[idx]);
	}

	// Clear screen
	fillScreen(devp, SSD1306_COLOR_WHITE);

	// Update screen
	updateScreen(devp);

	// Set default value
	devp->x = 0;
	devp->y = 0;

    devp->state = SSD1306_READY;
}

void ssd1306Stop(SSD1306Driver *devp) {
    chDbgAssert((devp->state == SSD1306_STOP) || (devp->state == SSD1306_READY),
            "ssd1306Stop(), invalid state");

    if (devp->state == SSD1306_READY) {
		// Turn off display
		setDisplay(devp, 0);
    }

    devp->state = SSD1306_STOP;
}
