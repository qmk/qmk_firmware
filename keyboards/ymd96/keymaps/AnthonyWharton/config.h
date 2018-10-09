/*
Base Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>
Modified 2017 Andrew Novak <ndrw.nvk@gmail.com>
Modified 2018 Anthony Wharton <th3ant@gmail.com>

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

#define VENDOR_ID       0x20A0
#define PRODUCT_ID      0x422D
// Edit usbconfig.h to change these.
#define MANUFACTURER    ymdkey
#define PRODUCT         ymd96

/* Matrix Size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15
#define DIODE_DIRECTION COL2ROW

/* Required for MX Locks installed */
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define PREVENT_STUCK_MODIFIERS
#define TAPPING_TOGGLE 3
#define NO_UART 1

#define BACKLIGHT_LEVELS 12

/* RGB Underglow  */
// The RGB_DI_PING value seems to be shared between all PS2AVRGB boards.
// The same pin is used on the JJ40, at least.
#define RGBLED_NUM 18
#define RGB_DI_PIN E2 // NOTE: for PS2AVRGB boards, underglow commands are send
                      //       via I2C to 0xB0

#define RGBLIGHT_ANIMATIONS

#define RGBLIGHT_EFFECT_BREATHE_CENTER 1.85 // 1.0-2.7
#define RGBLIGHT_EFFECT_BREATHE_MAX 255     // 1-255
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 7
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM RGBLED_NUM
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 1
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 500

/* key combination for command */
#define IS_COMMAND() (keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)))

