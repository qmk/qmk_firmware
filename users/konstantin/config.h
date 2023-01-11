/* Copyright 2019-2021 Konstantin Đorđević <vomindoraan@gmail.com>
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

// Keyboard reports
#define FORCE_NKRO
#define USB_POLLING_INTERVAL_MS 1

// Mouse keys
#define MOUSEKEY_DELAY             0
#define MOUSEKEY_INTERVAL          10
#define MOUSEKEY_MAX_SPEED         4
#define MOUSEKEY_TIME_TO_MAX       100
#define MOUSEKEY_WHEEL_DELAY       0
#define MOUSEKEY_WHEEL_INTERVAL    50
#define MOUSEKEY_WHEEL_MAX_SPEED   4
#define MOUSEKEY_WHEEL_TIME_TO_MAX 50

// RGB lighting
#undef RGBLIGHT_EFFECT_BREATHING
#undef RGBLIGHT_EFFECT_RAINBOW_MOOD
#undef RGBLIGHT_EFFECT_RAINBOW_SWIRL
#undef RGBLIGHT_EFFECT_SNAKE
#undef RGBLIGHT_EFFECT_KNIGHT
#undef RGBLIGHT_EFFECT_CHRISTMAS
#undef RGBLIGHT_EFFECT_STATIC_GRADIENT
#undef RGBLIGHT_EFFECT_RGB_TEST
#undef RGBLIGHT_EFFECT_ALTERNATING
#undef RGBLIGHT_EFFECT_TWINKLE
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_EFFECT_RAINBOW_MOOD
#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
#define RGBLIGHT_EFFECT_SNAKE

// Tapping
#define PERMISSIVE_HOLD
#define TAPPING_TERM    200
#define TAPPING_TOGGLE  2

// Unicode
#define UNICODE_CYCLE_PERSIST  false
#define UNICODE_SELECTED_MODES UNICODE_MODE_WINCOMPOSE, UNICODE_MODE_WINDOWS, UNICODE_MODE_LINUX
#define UNICODE_KEY_WINC       KC_RGUI

// Firmware size reduction
#undef  LOCKING_SUPPORT_ENABLE
#define NO_ACTION_FUNCTION
#define NO_ACTION_MACRO
#define NO_ACTION_ONESHOT
