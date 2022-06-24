/*
 * Copyright 2022 Uthol
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

#define DEVICE_VER 0x0003
#define PRODUCT_ID 0x67F3
#define PRODUCT UtholThree

/* key matrix size */
// A11 and A12 dont work. They are reserved for USB. B2 is reserved for BOOT1
#define MATRIX_COL_PINS \
    { B1, B10, B9, B8, B5, B4, B3, A15, B15, B14, B13, B12 }
#define MATRIX_ROW_PINS \
    { A4, A3, A2, A1, A0 }

#define UNUSED_PINS

// Encoder config
#define ENCODERS_PAD_A \
    { C15 }
#define ENCODERS_PAD_B \
    { C14 }
#define ENCODER_RESOLUTION 2

// OLED config
#define OLED_DISPLAY_128X64
#define OLED_DISPLAY_WIDTH 128
#define OLED_DISPLAY_HEIGHT 64
#define OLED_UPDATE_INTERVAL 0
#define OLED_BRIGHTNESS 255
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_RESET -1

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define TAPPING_TERM 500
#define PERMISSIVE_HOLD

// RGB Stuff
#define RGB_DI_PIN B0
#define RGBLED_NUM 39
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_DEFAULT_HUE 201
