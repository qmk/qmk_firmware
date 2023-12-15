/* Copyright 2017 Jeremy Cowgar
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

#include <stdint.h>
#include <stdbool.h>
#include "action.h"
#include "keyboard.h"
#include "keycodes.h"

#ifndef AUTO_SHIFT_TIMEOUT
#    define AUTO_SHIFT_TIMEOUT 175
#endif

#define IS_RETRO(kc) (IS_QK_MOD_TAP(kc) || IS_QK_LAYER_TAP(kc))

#define DO_GET_AUTOSHIFT_TIMEOUT(keycode, record, ...) record
// clang-format off
#define AUTO_SHIFT_ALPHA KC_A ... KC_Z
#define AUTO_SHIFT_NUMERIC KC_1 ... KC_0
#define AUTO_SHIFT_SYMBOLS          \
             KC_MINUS ... KC_SLASH: \
        case KC_NONUS_BACKSLASH

// Kept to avoid breaking existing keymaps.
#define AUTO_SHIFT_SPECIAL          \
             KC_TAB:                \
        case AUTO_SHIFT_SYMBOLS
// clang-format on

bool process_auto_shift(uint16_t keycode, keyrecord_t *record);
void retroshift_poll_time(keyevent_t *event);
void retroshift_swap_times(void);

void     autoshift_enable(void);
void     autoshift_disable(void);
void     autoshift_toggle(void);
bool     get_autoshift_state(void);
uint16_t get_generic_autoshift_timeout(void);
// clang-format off
uint16_t (get_autoshift_timeout)(uint16_t keycode, keyrecord_t *record);
void     set_autoshift_timeout(uint16_t timeout);
void     autoshift_matrix_scan(void);
bool     get_custom_auto_shifted_key(uint16_t keycode, keyrecord_t *record);
// clang-format on
