/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "ugfx/gfx.h"


#if GFX_USE_GINPUT && GINPUT_NEED_MOUSE

#define GMOUSE_DRIVER_VMT		GMOUSEVMT_QWidget
#include "../../../../src/ginput/ginput_driver_mouse.h"

GMouse* qwidgetMouse;
gCoord qwidgetMouseX;
gCoord qwidgetMouseY;
gCoord qwidgetMouseZ;
gU16 qwidgetMouseButtons;

static gBool _init(GMouse* m, unsigned driverinstance)
{
    (void)driverinstance;

    qwidgetMouse = m;

	return gTrue;
}

static gBool _read(GMouse* m, GMouseReading* pdr)
{
    (void)m;

    pdr->x = qwidgetMouseX;
    pdr->y = qwidgetMouseY;
    pdr->z = qwidgetMouseZ;
    pdr->buttons = qwidgetMouseButtons;

	return gTrue;
}

const GMouseVMT GMOUSE_DRIVER_VMT[1] = {{
	{
        GDRIVER_TYPE_MOUSE,
        0,
        sizeof(GMouse),
		_gmouseInitDriver,
		_gmousePostInitDriver,
		_gmouseDeInitDriver
	},
    1,				// z_max
    0,  			// z_min
    1,              // z_touchon
    0,              // z_touchoff
	{				// pen_jitter
        1,          // calibrate
        1,			// click
        1           // move
	},
	{				// finger_jitter
        1,          // calibrate
        1,			// click
        1			// move
	},
    _init,          // init
	0,				// deinit
    _read,          // get
	0,				// calsave
	0				// calload
}};

#endif /* GFX_USE_GINPUT && GINPUT_NEED_MOUSE */

