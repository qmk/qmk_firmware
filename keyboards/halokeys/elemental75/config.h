 /* Copyright 2022 Halokeys
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

#define MATRIX_ROW_PINS { A2, A3, A4, A5, A6, A7 }
#define MATRIX_COL_PINS { B2, B1, B0, B10, B11, B13, B14, B15, A8, A9, A14, A15, B3, B4, B7 }
#define DIODE_DIRECTION COL2ROW

#define TAP_CODE_DELAY 10 // tap_code function delay for register and unregister

#define RGB_DI_PIN A10
#define RGBLED_NUM 22
#define RGBLIGHT_LIMIT_VAL 225 // value set lower than 255 since current draw is too high
#define RGBLIGHT_SLEEP

/* animations enabled */
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

//#define RGBLIGHT_DISABLE_KEYCODES

// Tap dance term declaration
#define TAPPING_TERM 300

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
