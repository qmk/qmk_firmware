/*
Copyright 2021 Álvaro "Gondolindrim" Volpato  <gondolindrim@acheronproject.com>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x8384 //SR for Smith and Rune
#define PRODUCT_ID      0x1180
#define DEVICE_VER      0x0001
#define MANUFACTURER    SmithRune
#define PRODUCT         IRON180

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

#define MATRIX_COL_PINS { B7 , B6 , B5 , B4 , B3 , A10, A9 , A8 , B15, B14, B13, B12, B11, B2 , A4 , B1 , A3 }
#define MATRIX_ROW_PINS { B9 , B8 , A15, B0 , A7 , A5 }
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN           A6
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      1
#define BACKLIGHT_LEVELS 20
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD 5

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
