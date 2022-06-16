/*
 * This file is subject to the terms of the GFX License. If a copy of
 * the license was not distributed with this file, you can obtain one at:
 *
 *              http://ugfx.io/license.html
 */

#ifndef _GINPUT_LLD_MOUSE_BOARD_H
#define _GINPUT_LLD_MOUSE_BOARD_H

// Resolution and Accuracy Settings
#define GMOUSE_LINUX_EVENT_PEN_CALIBRATE_ERROR		8
#define GMOUSE_LINUX_EVENT_PEN_CLICK_ERROR			6
#define GMOUSE_LINUX_EVENT_PEN_MOVE_ERROR			4
#define GMOUSE_LINUX_EVENT_FINGER_CALIBRATE_ERROR	14
#define GMOUSE_LINUX_EVENT_FINGER_CLICK_ERROR		18
#define GMOUSE_LINUX_EVENT_FINGER_MOVE_ERROR		14

#define GMOUSE_LINUX_EVENT_NUM_EVENT				64

// The linux device input used for touchscreen
#define GMOUSE_LINUX_EVENT_DEVICE					"/dev/input/event0"

// Set this to GFXON if you want self-calibration.
//	NOTE:	This is not as accurate as real calibration.
//			It requires the orientation of the touch panel to match the display.
//			It requires the active area of the touch panel to exactly match the display size.
#define GMOUSE_LINUX_EVENT_SELF_CALIBRATE			GFXOFF

#define GMOUSE_LINUX_EVENT_FINGERMODE				GFXON

#endif /* _GINPUT_LLD_MOUSE_BOARD_H */
