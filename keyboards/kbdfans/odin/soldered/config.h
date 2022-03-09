/* Copyright 2021 Dztech
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
#include "config_common.h"

#define VENDOR_ID       0x4B42
#define PRODUCT_ID      0x0101
#define DEVICE_VER      0x0001
#define MANUFACTURER    KBDFANS
#define PRODUCT         ODIN_SOLDERED


#define MATRIX_ROWS 6
#define MATRIX_COLS 20

#define MATRIX_ROW_PINS { A10, A9, A8, B14, B13, A2 }
#define MATRIX_COL_PINS { A3, A4, A5, A6, A7, B0, B1, B2, B12, A15, B3, B4, B5, B6, B7, B8, C13, C14, C15, A0}
#define UNUSED_PINS

#define LED_NUM_LOCK_PIN B9
#define LED_CAPS_LOCK_PIN B10
#define LED_PIN_ON_STATE 0

#define DIODE_DIRECTION COL2ROW
#define DEBOUNCE 15
#define NO_ACTION_MACRO
#define NO_ACTION_FUNCTION
#define RGB_DI_PIN B15
#ifdef RGB_DI_PIN
#define RGBLED_NUM 4
#define RGBLIGHT_ANIMATIONS
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_DEFAULT_MODE (RGBLIGHT_EFFECT_RAINBOW_MOOD + 8) 
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 180
#define RGBLIGHT_SLEEP
#endif
#define VIA_EEPROM_LAYOUT_OPTIONS_SIZE 2
