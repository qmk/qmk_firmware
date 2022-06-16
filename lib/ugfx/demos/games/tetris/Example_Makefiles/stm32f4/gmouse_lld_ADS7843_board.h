/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

/**
 * @file    boards/addons/ginput/touch/ADS7843/ginput_lld_mouse_board_st_stm32f4_discovery.h
 * @brief   GINPUT Touch low level driver source for the ADS7843 on an st_stm32f4_discovery.
 *
 * @note	This file contains a mix of hardware specific and operating system specific
 *			code. You will need to change it for your CPU and/or operating system.
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

/*
 * uGFX port used:  ChibiOS/RT
 *
 * SCK:             GPIOB, 13
 * MISO:            GPIOB, 14
 * MOSI:            GPIOB, 15
 * CS:              GPIOC, 4
 * IRC:             GPIOC, 5
 *
 * Note that you can tweak the SPI bus speed
 */
static const SPIConfig spicfg = { 
    0,
	GPIOC,
    4,
    /* SPI_CR1_BR_2 |*/ SPI_CR1_BR_1 | SPI_CR1_BR_0,
};

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		8
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			6
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			4
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		18
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		14

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

static gBool init_board(GMouse* m, unsigned driverinstance) {
    (void)m;

    // Only one touch interface on this board
    if (driverinstance)
		return gFalse;

    // Set the GPIO modes
        palSetPadMode(GPIOC, 6, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPadMode(GPIOC, 4, PAL_MODE_INPUT);
        palSetPadMode(GPIOA, 5, PAL_MODE_ALTERNATE(5));
        palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(5));
        palSetPadMode(GPIOA, 7, PAL_MODE_ALTERNATE(5));

    // Start the SPI peripheral
    	spiStart(&SPID1, &spicfg);

    return gTrue;
}

static GFXINLINE gBool getpin_pressed(GMouse* m) {
	(void)		m;

	return (!palReadPad(GPIOC, 4));
}

static GFXINLINE void aquire_bus(GMouse* m) {
	(void)		m;

	spiAcquireBus(&SPID1);
	palClearPad(GPIOC, 6);
}

static GFXINLINE void release_bus(GMouse* m) {
	(void)		m;

	palSetPad(GPIOC, 6);
	spiReleaseBus(&SPID1);
}

static GFXINLINE gU16 read_value(GMouse* m, gU16 port) {
	static gU8 txbuf[3] = {0};
	static gU8 rxbuf[3] = {0};
	(void)		m;

	txbuf[0] = port;
	spiExchange(&SPID1, 3, txbuf, rxbuf);

	return ((gU16)rxbuf[1] << 5) | (rxbuf[2] >> 3);
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
