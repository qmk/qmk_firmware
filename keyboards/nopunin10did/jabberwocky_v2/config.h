/* Copyright 2022 W. Alex Ronke, a.k.a. NoPunIn10Did (w.alex.ronke@gmail.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS         12
#define MATRIX_COLS         10

/* key matrix pins */
#define MATRIX_ROW_PINS     { B8, C2, C3, C4, C5, B4, D2, B3, C12, C11, C10, C9 }
#define MATRIX_COL_PINS     { B9, A1, A2, A3, A4, A5, B0, C7, C6, B1 }
#define UNUSED_PINS

/* Indicator LEDs */
#define LED_NUM_LOCK_PIN    B12
#define LED_CAPS_LOCK_PIN   B10

/* In-switch LEDs */
#define BACKLIGHT_PIN  	        A6
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      1
#define BACKLIGHT_LEVELS        6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD        6

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION     COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE            5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Reducing layer count to 3 for via support */
#define DYNAMIC_KEYMAP_LAYER_COUNT  3
