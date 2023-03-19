/* Copyright 2021 Regan Palmer
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

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

/* key matrix pins */
#define MATRIX_ROW_PINS { D1, D7, F7, C6 }
#define MATRIX_COL_PINS { F6, D4, F5, D0, F4, B6 }
#define MATRIX_ROW_PINS_RIGHT { D1, D7, F7, C6 }
#define MATRIX_COL_PINS_RIGHT { F6, D4, F5, D0, F4, B6 }
// #define UNUSED_PINS

#define ENCODERS_PAD_A { B2 }
#define ENCODERS_PAD_B { B4 }
#define ENCODERS_PAD_A_RIGHT { B2 }
#define ENCODERS_PAD_B_RIGHT { B4 }

/* usb handedness? */
#define SPLIT_USB_DETECT

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* number of backlight levels */

#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 3
#endif

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)


/* define serial pin */
#define SOFT_SERIAL_PIN D3

#ifdef RGB_DI_PIN
#define RGBLED_NUM 0
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif
