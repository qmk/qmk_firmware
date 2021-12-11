/*
Copyright 2021 John Mueller

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#pragma once

#include "config_common.h"

// USB VID/PID
#define PRODUCT      2key/rgb

/* Keyboard Matrix Assignments */
#define MATRIX_ROW_PINS { F6 }
#define MATRIX_COL_PINS { F4, D7 }
#define UNUSED_PINS

// LED on kbmount base board is on B7
#define LED_CAPS_LOCK_PIN B7 // onboard LED for testing

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* RGB matrix key backlighting */
#ifdef RGB_MATRIX_ENABLE
#define RGB_DI_PIN B2
#define DRIVER_LED_TOTAL 2
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE
#define RGB_MATRIX_STARTUP_HUE 90
#define RGB_MATRIX_STARTUP_SPD 20
#define RGB_MATRIX_STARTUP_VAL 128
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_WHEN_USB_SUSPENDED

#define ENABLE_RGB_MATRIX_BREATHING
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* disable these deprecated features by default */
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
