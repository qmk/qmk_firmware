/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

#define GMOUSE_ADS7843_PEN_CALIBRATE_ERROR		2
#define GMOUSE_ADS7843_PEN_CLICK_ERROR			2
#define GMOUSE_ADS7843_PEN_MOVE_ERROR			2
#define GMOUSE_ADS7843_FINGER_CALIBRATE_ERROR		4
#define GMOUSE_ADS7843_FINGER_CLICK_ERROR		4
#define GMOUSE_ADS7843_FINGER_MOVE_ERROR		40

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
        palSetPadMode(GPIOC, 6, PAL_MODE_OUTPUT_PUSHPULL);
        palSetPadMode(GPIOC, 4, PAL_MODE_INPUT);
        palSetPadMode(GPIOA, 5, PAL_MODE_ALTERNATE(5));
        palSetPadMode(GPIOA, 6, PAL_MODE_ALTERNATE(5));
        palSetPadMode(GPIOA, 7, PAL_MODE_ALTERNATE(5));

    // Start the SPI peripheral
    spiStart(&SPID1, &spicfg);

    return gTrue;
}

GFXINLINE gBool getpin_pressed(void) {
  return (!palReadPad(GPIOC, 4));
}

static GFXINLINE void aquire_bus(void) {
  spiAcquireBus(&SPID1);
  palClearPad(GPIOC, 6);
}

static GFXINLINE void release_bus(void) {
  palSetPad(GPIOC, 6);
  spiReleaseBus(&SPID1);
}

static GFXINLINE gU16 read_value(gU16 port) {
    static gU8 txbuf[3] = {0};
    static gU8 rxbuf[3] = {0};
    gU16 ret;

    txbuf[0] = port;

    spiExchange(&SPID1, 3, txbuf, rxbuf);

    ret = (rxbuf[1] << 5) | (rxbuf[2] >> 3);

  return ret;
}

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
