/*
Copyright 2020 Team Mechlovin'

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

/* USB Device descriptor parameter */
#define VENDOR_ID    0x4D4C // ML-Mechlovin
#define PRODUCT_ID   0xAEC1
#define DEVICE_VER   0x0001
#define MANUFACTURER Team.Mechlovin
#define PRODUCT      Adelais En Ciel
#define DESCRIPTION  Team.Mechlovin Adelais En Ciel

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 */
#define MATRIX_ROW_PINS { B1, A0, C13, A1, A2}
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B8, B4, B5, B3, C14, A15 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW


#define RGB_DI_PIN A7
#define DRIVER_LED_TOTAL 91
#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
#define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
#define RGB_DISABLE_WHEN_USB_SUSPENDED false // turn off effects when suspended
#define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 220 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_PINWHEEL // Sets the default mode, if none has been set