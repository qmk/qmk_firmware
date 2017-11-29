/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.org/license.html
 */

#ifndef _GDISP_LLD_BOARD_H
#define _GDISP_LLD_BOARD_H

//#define SSD1306_PAGE_PREFIX           0x40

// Hardware pin definitions
#define SSD1306_GPIOPORT	GPIOC
#define SSD1306_PORT		PORTC
#define SSD1306_A0_PIN		7
#define SSD1306_RST_PIN		8
#define SSD1306_MOSI_PIN	6
#define SSD1306_SLCK_PIN	5
#define SSD1306_SS_PIN		4

#define palSetPadModeRaw(portname, bits) \
    SSD1306_PORT->PCR[SSD1306_##portname##_PIN] = bits

#define palSetPadModeNamed(portname, portmode) \
    palSetPadMode(SSD1306_GPIOPORT, SSD1306_##portname##_PIN, portmode)

#define SSD1306_SPI_MODE PORTx_PCRn_DSE | PORTx_PCRn_MUX(2)
// DSPI Clock and Transfer Attributes
// Frame Size: 8 bits
// MSB First
// CLK Low by default
static const SPIConfig spi1config = {
   // Operation complete callback or @p NULL.
  .end_cb = NULL,
   //The chip select line port - when not using pcs.
  .ssport = SSD1306_GPIOPORT,
   // brief The chip select line pad number - when not using pcs.
  .sspad=SSD1306_SS_PIN,
   // SPI initialization data.
  .tar0 =
    SPIx_CTARn_FMSZ(7) // Frame size = 8 bytes
    | SPIx_CTARn_ASC(1) // After SCK Delay Scaler (min 50 ns) = 55.56ns
    | SPIx_CTARn_DT(0) // Delay After Transfer Scaler (no minimum)= 27.78ns
    | SPIx_CTARn_CSSCK(0) // PCS to SCK Delay Scaler (min 20 ns) = 27.78ns
    | SPIx_CTARn_PBR(0) // Baud Rate Prescaler = 2
    | SPIx_CTARn_BR(0) // Baud rate (min 50ns) = 55.56ns
};


static GFXINLINE void init_board(GDisplay *g) {
    (void) g;
    palSetPadModeNamed(A0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(SSD1306_GPIOPORT, SSD1306_A0_PIN);
    palSetPadModeNamed(RST, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPad(SSD1306_GPIOPORT, SSD1306_RST_PIN);
    palSetPadModeRaw(MOSI, SSD1306_SPI_MODE);
    palSetPadModeRaw(SLCK, SSD1306_SPI_MODE);
    palSetPadModeNamed(SS, PAL_MODE_OUTPUT_PUSHPULL);

    spiInit();
    spiStart(&SPID1, &spi1config);
    //release_bus(g);
    spiUnselect(&SPID1);
}

static GFXINLINE void post_init_board(GDisplay *g) {
        (void) g;
}

static GFXINLINE void setpin_reset(GDisplay *g, bool_t state) {
    (void) g;
    if (state) {
        palClearPad(SSD1306_GPIOPORT, SSD1306_RST_PIN);
    }
    else {
        palSetPad(SSD1306_GPIOPORT, SSD1306_RST_PIN);
    }
}

static GFXINLINE void acquire_bus(GDisplay *g) {
    (void) g;
    // Only the LCD is using the SPI bus, so no need to acquire
    // spiAcquireBus(&SPID1);
    spiSelect(&SPID1);
}

static GFXINLINE void release_bus(GDisplay *g) {
    (void) g;
    // Only the LCD is using the SPI bus, so no need to release
    //spiReleaseBus(&SPID1);
    spiUnselect(&SPID1);
}

static GFXINLINE void write_cmd(GDisplay *g, uint8_t cmd) {
	(void) g;
	palClearPad(SSD1306_GPIOPORT, SSD1306_A0_PIN);
	spiSend(&SPID1, 1, &cmd);
}

static GFXINLINE void write_data(GDisplay *g, uint8_t* data, uint16_t length) {
	(void) g;
	palSetPad(SSD1306_GPIOPORT, SSD1306_A0_PIN);
	spiSend(&SPID1, length, data);
}

#endif /* _GDISP_LLD_BOARD_H */

