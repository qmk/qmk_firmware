/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#ifndef CONFIG_H
#define CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x6060
#define DEVICE_VER      0x0002
#define MANUFACTURER    Exclusive / E-Team
#define PRODUCT         E6-V2
#define DESCRIPTION     E6-V2 QMK PCB (Mid-Port)

/* key matrix size */
#define MATRIX_ROWS 5
#define MATRIX_COLS 15

/* QMK E6-V2 PCB default pin-out */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5 }
#define MATRIX_COL_PINS { C7, C6, B5, B4, D7, D6, D4, F6, F7, F5, F4, F1, F0, B0, B1 }
#define UNUSED_PINS { E6, B2, B3, B7 }

#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 8
#define RGBLIGHT_HUE_STEP 12
#define RGBLIGHT_SAT_STEP 12
#define RGBLIGHT_VAL_STEP 12
#endif

#define BACKLIGHT_PIN B6
#ifdef BACKLIGHT_PIN
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_BREAHTING
#define BREATHING_PERIOD 3
#endif

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCING_DELAY 5

#define IS_COMMAND() ( \
        keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
    )



#endif
