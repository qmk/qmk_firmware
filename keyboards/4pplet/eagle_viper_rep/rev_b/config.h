/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

#define MATRIX_COL_PINS { A0, A3, A4, A7, B5, B4, B3 }
#define MATRIX_ROW_PINS { A2, A1, B8, A10, C15, A15, B7, B6, C14, C13}
#define DIODE_DIRECTION COL2ROW

/* In switch leds */
#define BACKLIGHT_PIN           A6
#define BACKLIGHT_PWM_DRIVER    PWMD3
#define BACKLIGHT_PWM_CHANNEL   1
#define BACKLIGHT_PAL_MODE      1
#define BACKLIGHT_LEVELS        6
#define BACKLIGHT_BREATHING
#define BREATHING_PERIOD        6
#define BACKLIGHT_ON_STATE      1

/* Underglow */
#define RGBLED_NUM 16
#define WS2812_EXTERNAL_PULLUP
#define RGB_DI_PIN A8

#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
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

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Indicator leds */
#define LED_CAPS_LOCK_PIN   B1
#define LED_NUM_LOCK_PIN    B12
#define LED_SCROLL_LOCK_PIN B13
#define LAYER_1             B14
#define LAYER_2             B15
#define LAYER_3             B0
#define LAYER_4             B9
#define LAYER_5             A9

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Added extra layer for use of layer leds */
#define DYNAMIC_KEYMAP_LAYER_COUNT 5
