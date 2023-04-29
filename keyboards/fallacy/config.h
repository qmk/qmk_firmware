/* Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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


/* key matrix pins
 */
#define MATRIX_ROW_PINS { B1, B2, B3, C6, C7 }
#define MATRIX_COL_PINS { E6, F0, F1, F4, F5, F6, F7, B6, B5, B4, D7, D6, D4, D5, D3 }

/* COL2ROW or ROW2COL
 */
#define DIODE_DIRECTION COL2ROW

/* IS31FL3731 driver address (for status LEDs)
 * Using the default defines here, but using a custom implementation
 */
#define LED_DRIVER_ADDR_1 0b1110100
#define LED_DRIVER_COUNT 1
#define LED_MATRIX_LED_COUNT 3

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap
 */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack
 */
#define LOCKING_RESYNC_ENABLE

#define RGB_DI_PIN D2
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
#define RGBLED_NUM 14
