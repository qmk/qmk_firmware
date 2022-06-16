/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#if GFX_USE_GINPUT && GINPUT_NEED_MOUSE

#define GMOUSE_DRIVER_VMT		GMOUSEVMT_EXC7200
#include "../../../../src/ginput/ginput_driver_mouse.h"

// Get the hardware interface
#include "gmouse_lld_EXC7200_board.h"

#define EXC7200_READ_CMD 0x09

static gBool MouseInit(GMouse* m, unsigned driverinstance)
{
	if (!init_board(m, driverinstance)) {
		return gFalse;
	}
	
	return gTrue;
}

static gBool read_xyz(GMouse* m, GMouseReading* pdr)
{
	gU8 rxbuf[10];
	
	// We don't support buttons. This is a regular touchscreen
	pdr->buttons = 0;

	// Read
	if (!read_bytes(m, EXC7200_READ_CMD, rxbuf, 10)) {
		return gFalse;
	}
	
	// Check if touched
	if (rxbuf[1] == 0x83) {
		pdr->x = (((rxbuf[3] & 0x00ff) << 4) | ((rxbuf[2] & 0x00f0) >> 4)) << 1;
		pdr->y = (((rxbuf[5] & 0x00ff) << 4) | ((rxbuf[4] & 0x00f0) >> 4)) << 1;
		pdr->z = 1;
	} else {
		pdr->z = 0;
	}	

	return gTrue;
}

const GMouseVMT const GMOUSE_DRIVER_VMT[1] = {{
	{
		GDRIVER_TYPE_TOUCH,
		GMOUSE_VFLG_TOUCH | GMOUSE_VFLG_ONLY_DOWN | GMOUSE_VFLG_POORUPDOWN | GMOUSE_VFLG_CALIBRATE | GMOUSE_VFLG_CAL_TEST,
		sizeof(GMouse) + GMOUSE_EXC7200_BOARD_DATA_SIZE,
		_gmouseInitDriver,
		_gmousePostInitDriver,
		_gmouseDeInitDriver
	},
	1,				// z_max - not supported
	0,				// z_min - not supported
	1,				// z_touchon
	0,				// z_touchoff
	{				// pen_jitter
		GMOUSE_EXC7200_PEN_CALIBRATE_ERROR,			// calibrate
		GMOUSE_EXC7200_PEN_CLICK_ERROR,				// click
		GMOUSE_EXC7200_PEN_MOVE_ERROR				// move
	},
	{				// finger_jitter
		GMOUSE_EXC7200_FINGER_CALIBRATE_ERROR,		// calibrate
		GMOUSE_EXC7200_FINGER_CLICK_ERROR,			// click
		GMOUSE_EXC7200_FINGER_MOVE_ERROR			// move
	},
	MouseInit, 		// init
	0,				// deinit
	read_xyz,		// get
	0,				// calsave
	0				// calload
}};

#endif /* GFX_USE_GINPUT && GINPUT_NEED_MOUSE */
