/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

// wiring of each half
#define MATRIX_ROW_PINS { F4, D4, D7, E6, B4, C6 }
#define MATRIX_COL_PINS { F5, F6, F7, B1, B3, B2, B6, B5 }
#define MATRIX_ROW_PINS_RIGHT { F4, D4, D7, E6, B4, B5 }
#define MATRIX_COL_PINS_RIGHT { F5, F6, F7, B1, B3, B2, B6, C6 }
#define SPLIT_HAND_PIN D2

#define DIODE_DIRECTION COL2ROW

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* ws2812 RGB LED */
#define RGB_DI_PIN D3
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_TWINKLE
#define RGBLED_NUM 16    // Number of LEDs
#define RGBLED_SPLIT { 8, 8 }

// Set 65% column (option 1) and Macro (option 2) on by default
#define VIA_EEPROM_LAYOUT_OPTIONS_DEFAULT 0x60
