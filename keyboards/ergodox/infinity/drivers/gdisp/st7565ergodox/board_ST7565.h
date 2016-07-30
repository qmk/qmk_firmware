/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

#include "print.h"

#define ST7565_LCD_BIAS         ST7565_LCD_BIAS_9 // actually 6
#define ST7565_ADC              ST7565_ADC_NORMAL
#define ST7565_COM_SCAN         ST7565_COM_SCAN_DEC
#define ST7565_PAGE_ORDER       0,1,2,3
/*
 * Custom page order for several LCD boards, e.g. HEM12864-99
 * #define ST7565_PAGE_ORDER       4,5,6,7,0,1,2,3
 */

#define ST7565_GPIOPORT GPIOC
#define ST7565_PORT PORTC
#define ST7565_A0_PIN 7
#define ST7565_RST_PIN 8
#define ST7565_MOSI_PIN 6
#define ST7565_SLCK_PIN 5
#define ST7565_SS_PIN 4

#define palSetPadModeRaw(portname, bits) \
    ST7565_PORT->PCR[ST7565_##portname##_PIN] = bits

#define palSetPadModeNamed(portname, portmode) \
    palSetPadMode(ST7565_GPIOPORT, ST7565_##portname##_PIN, portmode)

#define ST7565_SPI_MODE PORTx_PCRn_DSE | PORTx_PCRn_MUX(2)
// DSPI Clock and Transfer Attributes
// Frame Size: 8 bits
// MSB First
// CLK Low by default
static const SPIConfig spi1config = {
	NULL,
	/* HW dependent part.*/
	ST7565_GPIOPORT,
    ST7565_SS_PIN,
    SPIx_CTARn_FMSZ(7)
    | SPIx_CTARn_ASC(7)
    | SPIx_CTARn_DT(7)
    | SPIx_CTARn_CSSCK(7)
    | SPIx_CTARn_PBR(0)
    | SPIx_CTARn_BR(7)
	//SPI_CR1_BR_0
};

static bool_t st7565_is_data_mode = 1;

static GFXINLINE void init_board(GDisplay *g) {
    (void) g;
    palSetPadModeNamed(A0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(ST7565_GPIOPORT, ST7565_A0_PIN);
    st7565_is_data_mode = 1;
    palSetPadModeNamed(RST, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(ST7565_GPIOPORT, ST7565_RST_PIN);
    palSetPadModeRaw(MOSI, ST7565_SPI_MODE);
    palSetPadModeRaw(SLCK, ST7565_SPI_MODE);
    palSetPadModeRaw(SS, ST7565_SPI_MODE);

    spiInit();
    spiStart(&SPID1, &spi1config);
    spiSelect(&SPID1);
}

static GFXINLINE void post_init_board(GDisplay *g) {
	(void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
    (void) g;
    if (state) {
        palClearPad(ST7565_GPIOPORT, ST7565_RST_PIN);
    }
    else {
        palSetPad(ST7565_GPIOPORT, ST7565_RST_PIN);
    }
}

static GFXINLINE void acquire_bus(GDisplay *g) {
    (void) g;
    // Only the LCD is using the SPI bus, so no need to acquire
    // spiAcquireBus(&SPID1);
}

static GFXINLINE void release_bus(GDisplay *g) {
    (void) g;
    // Only the LCD is using the SPI bus, so no need to release
    //spiReleaseBus(&SPID1);
}

static GFXINLINE void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	if (st7565_is_data_mode) {
	    // The sleeps need to be at lest 10 vs 25 ns respectively
	    // So let's sleep two ticks, one tick might not be enough
	    // if we are at the end of the tick
	    chThdSleep(2);
        palClearPad(ST7565_GPIOPORT, ST7565_A0_PIN);
        chThdSleep(2);
        st7565_is_data_mode = 0;
	}
	spiSend(&SPID1, 1, &cmd);
}

static GFXINLINE void write_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	if (!st7565_is_data_mode) {
	    // The sleeps need to be at lest 10 vs 25 ns respectively
	    // So let's sleep two ticks, one tick might not be enough
	    // if we are at the end of the tick
	    chThdSleep(2);
        palSetPad(ST7565_GPIOPORT, ST7565_A0_PIN);
	    chThdSleep(2);
        st7565_is_data_mode = 1;
	}
	spiSend(&SPID1, length, data);
}

#endif /* _GDISP_LLD_BOARD_H */
