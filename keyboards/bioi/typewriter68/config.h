/* Copyright 2023 Basic I/O Instruments (@scottywei)
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

#define MATRIX_ROW_PINS { D1, D2, B1, D5, B2 }
#define MATRIX_COL_PINS { C7, C6, B6, B5, B4, D7, D6, D4, F7, F6, F5, F4, F1, E6, F0 }

#define DIODE_DIRECTION COL2ROW

#define LED_CAPS_LOCK_PIN D3
#define LED_PIN_ON_STATE 1

#define FORCE_NKRO
#define USB_POLLING_INTERVAL_MS 1

#define AUDIO_PIN B7
#define AUDIO_CLICKY

#define RGB_DI_PIN D0
#define RGBLED_NUM 30
#define RGBLIGHT_LIMIT_VAL 215
#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_RGB_TEST

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define RGBLIGHT_EFFECT_ALTERNATING
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_CHRISTMAS
#define RGBLIGHT_EFFECT_KNIGHT
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RGB_TEST
#define RGBLIGHT_EFFECT_SNAKE
#define RGBLIGHT_EFFECT_STATIC_GRADIENT
#define RGBLIGHT_EFFECT_TWINKLE


#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))