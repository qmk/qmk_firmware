/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		2
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			2
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			2
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR	20
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		4
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		4

// How much extra data to allocate at the end of the GMouse structure for the board's use
#define GMOUSE_ADS7843_BOARD_DATA_SIZE			0

static const SPIConfig spicfg = { 
    0,
	GPIOC, 
    6,
    /* SPI_CR1_BR_2 |*/ SPI_CR1_BR_1 | SPI_CR1_BR_0,
};

static gBool init_board(GMouse* m, unsigned driverinstance)
{
	(void)m;

	// Only one touch interface on this board
	if (driverinstance)
		return gFalse;
	
	// Set the GPIO modes
	palSetPadMode(GPIOC, 4, PAL_MODE_INPUT_PULLUP);

	// Start the SPI peripheral
	spiStart(&SPID1, &spicfg);

	return gTrue;
}

static GFXINLINE gBool getpin_pressed(GMouse* m)
{
	(void)	m;

	return (!palReadPad(GPIOC, 4));
}

static GFXINLINE void aquire_bus(GMouse* m)
{
	(void)	m;

	spiAcquireBus(&SPID1);
    palClearPad(GPIOC, 6);
}

static GFXINLINE void release_bus(GMouse* m)
{
	(void)	m;

	palSetPad(GPIOC, 6);
	spiReleaseBus(&SPID1);
}

static GFXINLINE gU16 read_value(GMouse* m, gU16 port)
{
    static gU8 txbuf[3] = {0};
    static gU8 rxbuf[3] = {0};
    gU16 ret;
	(void)	m;

    txbuf[0] = port;

    spiExchange(&SPID1, 3, txbuf, rxbuf);

    ret = (rxbuf[1] << 5) | (rxbuf[2] >> 3); 
    
	return ret;
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */

