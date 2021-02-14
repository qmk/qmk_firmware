/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
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

#define VENDOR_ID       0x4B50  // "KP"
#define PRODUCT_ID      0x0040
#define DEVICE_VER      0x0200
#define MANUFACTURER    KPrepublic
#define PRODUCT         JJ40

/* matrix size */
#define MATRIX_ROWS 4
#define MATRIX_COLS 12
#define MATRIX_ROW_PINS { B0, B1, B3, B4 }
#define MATRIX_COL_PINS { C4, C5, C6, C7, A4, A5, A6, A7, A3, A2, A1, A0 }

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

#define BACKLIGHT_PIN D4
#define BACKLIGHT_LEVELS 12
#define BACKLIGHT_BREATHING

/* RGB underglow */
// NOTE: for PS2AVRGB boards, underglow commands are sent via I2C to 0xB0.
#define RGBLED_NUM 5
#define RGBLIGHT_ANIMATIONS

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

#define USB_MAX_POWER_CONSUMPTION 100

/* key combination for magic key command */
/* defined by default; to change, uncomment and set to the combination you want */
// #define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

/* Bootmagic Lite key configuration */
// #define BOOTMAGIC_LITE_ROW 0
// #define BOOTMAGIC_LITE_COLUMN 0
