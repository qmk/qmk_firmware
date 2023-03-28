/* Copyright 2022 Basic I/O Instruments (@scottywei)
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

#define BIOI_MANTA
#define BLE_NAME        "BIOI MANTA Ortho BLE"
#define NO_BAT_LEVEL

#define USB_POLLING_INTERVAL_MS 1

#define MATRIX_ROW_PINS { B0, F7, D0, B5, D7, B4 }
#define MATRIX_COL_PINS { F5, F4, F1, F0, E2, C6, D5, D1, D4, B1, B2, B3, D6 }

#define LED_CAPS_LOCK_PIN F6
#define BLE_CONTROL_PIN E6
#define RGB_UG_CONTROL_PIN C7

#define NO_MUSIC_MODE
#ifdef AUDIO_ENABLE
    #define AUDIO_PIN B7
    #define AUDIO_CLICKY
    #define STARTUP_SONG SONG(STARTUP_SOUND)
#endif

#define RGBLIGHT_LAYERS
#define RGB_DI_PIN B6
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB
#define RGBLED_NUM 6  // Number of LEDs
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 175
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_TWINKLE

#define DIODE_DIRECTION COL2ROW

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define BOOTMAGIC_BLE_ROW 0
#define BOOTMAGIC_BLE_COLUMN 0

#define LOCKING_SUPPORT_ENABLE
#define LOCKING_RESYNC_ENABLE

#define KEYBOARD_LOCK_ENABLE
#define MAGIC_KEY_LOCK L
#define IS_COMMAND() (get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))