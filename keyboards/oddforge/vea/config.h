/*
Copyright 2021 MajorKoos <github.com/majorkoos>

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
#define VENDOR_ID       0xFFFE
#define PRODUCT_ID      0x4155
#define DEVICE_VER      0x0100
#define MANUFACTURER    OddForge
#define PRODUCT         VE.A

/* matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 15

#define DEBOUNCE 5
#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define DYNAMIC_KEYMAP_LAYER_COUNT 3

#define RGBLED_NUM 18
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 9

#define LED_NUM_LOCK_PIN D0
#define LED_CAPS_LOCK_PIN D1
#define LED_SCROLL_LOCK_PIN D6
#define BACKLIGHT_PIN D4
