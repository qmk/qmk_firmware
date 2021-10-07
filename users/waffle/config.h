/* Copyright 2021 @waffle#0007
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

#define IGNORE_MOD_TAP_INTERRUPT
#define ONESHOT_TAP_TOGGLE 3
#define ONESHOT_TIMEOUT 5000
#define PERSMISSVE_HOLD
#define TAPPING_TERM 150
#define LAYER_STATE_8BIT
#define USB_POLLING_INTERVAL_MS 1
#define FORCE_NKRO
#define TAPPING_TERM_PER_KEY
#define MACRO_TIMER 5
#undef MANUFACTURER
#define MANUFACTURER Waffles

#ifdef RGBLIGHT_ENABLE
#    undef RGBLIGHT_HUE_STEP
#    define RGBLIGHT_HUE_STEP 10
#    undef RGBLIGHT_SAT_STEP
#    define RGBLIGHT_SAT_STEP 10
#    undef RGBLIGHT_VAL_STEP
#    define RGBLIGHT_VAL_STEP 10
#    define RGBLIGHT_SLEEP
#endif

#ifdef OLED_ENABLE
#    define OLED_TIMEOUT 50000
#    define OLED_FONT_H "users/waffle/oledfonts.c"
#    define OLED_UPDATE_INTERVAL 100
#endif

#ifdef UNICODEMAP_ENABLE
#    define UNICODE_SELECTED_MODES UC_LNX
#    define UNICODE_CYCLE_PERSIST false
#endif

#ifdef MOUSEKEY_ENABLE
#    define MOUSEKEY_DELAY 300
#    define MOUSEKEY_INTERVAL 16
#    define MOUSEKEY_MAX_SPEED 5
#endif

#ifdef AUTOSHIFT_ENABLE
#    define AUTO_SHIFT_MODIFIERS
#    define AUTO_SHIFT_TIMEOUT 170
#    define NO_AUTO_SHIFT_SPECIAL
#    define NO_AUTO_SHIFT_NUMERIC
#endif

#ifdef SPLIT_KEYBOARD
#    define MASTER_RIGHT
#    define SPLIT_MODS_ENABLE
#    define SPLIT_WPM_ENABLE
#    define SPLIT_LAYER_STATE_ENABLE
#    define SPLIT_OLED_ENABLE
#    define BOOTMAGIC_LITE_ROW 0
#    define BOOTMAGIC_LITE_COLUMN 0
#    define BOOTMAGIC_LITE_ROW_RIGHT 4
#    define BOOTMAGIC_LITE_COLUMN_RIGHT 0
#endif

#ifdef COMBO_ENABLE
#    ifdef OLED_ENABLE
#        define COMBO_COUNT 16
#    else
#        define COMBO_COUNT 15
#    endif
#    define COMBO_TERM 50
#endif
