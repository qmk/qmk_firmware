/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#include "gfx.h"

#include <linux/input.h>

#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

#if GFX_USE_GINPUT && GINPUT_NEED_MOUSE

#define GMOUSE_DRIVER_VMT GMOUSEVMT_LINUX_EVENT
#include "src/ginput/ginput_driver_mouse.h"

// Include the board file
#include "gmouse_lld_linux_event_board.h"

// Private area definition
// We need to store the last reading ourselves because we only get events
// from the Linux system. When touching the touchscreen and then moving around,
// we only get one z = 1 event. However, the GINPUT module expects z = 1 to be
// true for the entire touch duration.
typedef struct privStruct {
	int fd;
	GMouseReading lastReading;
} privStruct;

static gBool _init(GMouse* m, unsigned driverInstance)
{
	(void)driverInstance;

	// Retrive the private area struct
    privStruct* priv = (privStruct*)(m+1);

	// Open the device
	priv->fd = open(GMOUSE_LINUX_EVENT_DEVICE, O_RDONLY | O_NONBLOCK);
	if (priv->fd < 0) {
		fprintf(stderr, "GINPUT Mouse: Cannot open input device (%s)\n", GMOUSE_LINUX_EVENT_DEVICE);
		return gFalse;
	}

	// Initialize
	priv->lastReading.buttons = 0;
	priv->lastReading.x = 0;
	priv->lastReading.y = 0;
	priv->lastReading.z = 0;

	return gTrue;
}

static gBool _read(GMouse* m, GMouseReading* pdr)
{
	int i;
	int rb;
	struct input_event ev[64];
	privStruct* priv;

	// Retrive the private area struct
    priv = (privStruct*)(m+1);

	// Assume not touched
	pdr->buttons = 0;
	pdr->z = priv->lastReading.z;
	pdr->x = priv->lastReading.x;
	pdr->y = priv->lastReading.y;

	// Read
	rb = read(priv->fd, ev, sizeof(struct input_event)*64);

	// Parse	
	if (rb > 0) {
		for (i = 0;  i < (int)(rb / sizeof(struct input_event)); i++) {
			if (ev[i].type == EV_KEY && ev[i].code == 330 && ev[i].value == 1) {
				pdr->z = 1;
			}
			else if (ev[i].type == EV_KEY && ev[i].code == 330 && ev[i].value == 0) {
				pdr->z = 0;
			}
			else if (ev[i].type == EV_ABS && ev[i].code == 0 && ev[i].value > 0) {
				pdr->x = ev[i].value;
			}
			else if (ev[i].type == EV_ABS  && ev[i].code == 1 && ev[i].value > 0) {
				pdr->y = ev[i].value;
			}
		}
	}

	// Store the current reading
	priv->lastReading.x = pdr->x;
	priv->lastReading.y = pdr->y;
	priv->lastReading.z = pdr->z;
	priv->lastReading.buttons = pdr->buttons;
	
	return gTrue;
}

const GMouseVMT const GMOUSE_DRIVER_VMT[1] = {{
	{
		GDRIVER_TYPE_TOUCH,
		#if GMOUSE_LINUX_EVENT_FINGERMODE
			GMOUSE_VFLG_DEFAULTFINGER |
		#endif
		
		#if GMOUSE_LINUX_EVENT_SELF_CALIBRATE
			GMOUSE_VFLG_TOUCH | GMOUSE_VFLG_ONLY_DOWN | GMOUSE_VFLG_POORUPDOWN , 
		#else
			GMOUSE_VFLG_TOUCH | GMOUSE_VFLG_ONLY_DOWN | GMOUSE_VFLG_POORUPDOWN |GMOUSE_VFLG_CALIBRATE,
		#endif
		sizeof(GMouse) + sizeof(privStruct),
		_gmouseInitDriver,
		_gmousePostInitDriver,
		_gmouseDeInitDriver
	},
	1,				// z_max - (currently?) not supported
	0,				// z_min - (currently?) not supported
	1,				// z_touchon
	0,				// z_touchoff
	{				// pen_jitter
		0,			// calibrate
		0,			// click
		0			// move
	},
	{				// finger_jitter
		0,			// calibrate
		0,			// click
		0			// move
	},
	_init, 			// init
	0,				// deinit
	_read,			// get
	0,				// calsave
	0				// calload
}};

#endif /* GFX_USE_GINPUT && GINPUT_NEED_MOUSE */

