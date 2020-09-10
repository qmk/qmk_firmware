/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2013 Oleg Kostyuk <cub.uanic@gmail.com>
Copyright 2017 Erin Call <hello@erincall.com>

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

#ifndef FLAT_ALBATROSS_CONFIG_H
#define FLAT_ALBATROSS_CONFIG_H

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1308
#define DEVICE_VER      0x0001
#define MANUFACTURER    CaraDeGil
#define PRODUCT         Flat Albatross
#define DESCRIPTION     An ortholinear, split, flat keyboard with tiered thumb clusters that is freaking huge.

#define DIODE_DIRECTION ROW2COL
#define MATRIX_ROWS 7
#define MATRIX_COLS 16
#define COL_EXPANDED { true, true, true, true, true, true, true, true, false, false, false, false, false, false, false, false}
#define MATRIX_ONBOARD_ROW_PINS { F0, F1, F4, F5, F6, F7, B6 }
#define MATRIX_ONBOARD_COL_PINS { 0, 0, 0, 0, 0, 0, 0, 0, B0, B1, B2, B3, B7, D2, D3, C6 }
#define EXPANDER_COL_REGISTER GPIOA
#define EXPANDER_ROW_REGISTER GPIOB
#define MATRIX_EXPANDER_COL_PINS {0, 1, 2, 3, 4, 5, 6, 7}
#define MATRIX_EXPANDER_ROW_PINS {0, 1, 2, 3, 4, 5, 6}

#define RGB_DI_PIN B5
#define RGBLED_NUM 102
#define RGBLIGHT_SLEEP
#define LED_LAYOUT( \
                                                                        \
    L00,L01,L02,L03,L04,L05,L06,L07,                                            \
    L10,L11,L12,L13,L14,L15,L16,L17,                                            \
    L20,L21,L22,L23,L24,L25,L26,L27,                                            \
    L30,L31,L32,L33,L34,L35,L36,L37,                                            \
    L40,L41,L42,L43,L44,L45,L46,                                                \
    L50,L51,L52,L53,L54,L55,                                                \
                            L56,L47,                                    \
                                L57,                                    \
                        L65,L66,L67,                                    \
                                                                        \
            L08,L09,L0A,L0B,L0C,L0D,L0E,L0F,                                    \
            L18,L19,L1A,L1B,L1C,L1D,L1E,L1F,                                    \
            L28,L29,L2A,L2B,L2C,L2D,L2E,L2F,                                    \
            L38,L39,L3A,L3B,L3C,L3D,L3E,L3F,                                    \
                L49,L4A,L4B,L4C,L4D,L4E,L4F,                                    \
                    L5A,L5B,L5C,L5D,L5E,L5F,                                    \
    L48,L59,                                                            \
    L58,                                                                \
    L68,L69,L6A ) \
    { \
        L08,L09,L0A,L0B,L0C,L0D,L0E,L0F, \
        L18,L19,L1A,L1B,L1C,L1D,L1E,L1F, \
        L28,L29,L2A,L2B,L2C,L2D,L2E,L2F, \
        L38,L39,L3A,L3B,L3C,L3D,L3E,L3F, \
        L48,L59,L49,L4A,L4B,L4C,L4D,L4E,L4F, \
        L58,L68,L69,L6A,L5A,L5B,L5C,L5D,L5E,L5F, \
        L07,
    } \

#define MOUSEKEY_INTERVAL     20
#define MOUSEKEY_DELAY        0
#define MOUSEKEY_TIME_TO_MAX  60
#define MOUSEKEY_MAX_SPEED    7
#define MOUSEKEY_WHEEL_DELAY  0

#define TAPPING_TOGGLE  1

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* fix space cadet rollover issue */
#define DISABLE_SPACE_CADET_ROLLOVER

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    15

#define USB_MAX_POWER_CONSUMPTION 500

#endif
