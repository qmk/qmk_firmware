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

#include "quantum.h"

#ifndef AUTO_MOD_TIMEOUT
#    define AUTO_MOD_TIMEOUT 175
#endif

#define AUTO_MOD_SHIFT 1
#define AUTO_MOD_CTRL  2
#define AUTO_MOD_ALT   3
#define AUTO_MOD_GUI   4

#define IS_LT(kc) ((kc) >= QK_LAYER_TAP && (kc) <= QK_LAYER_TAP_MAX)
#define IS_MT(kc) ((kc) >= QK_MOD_TAP && (kc) <= QK_MOD_TAP_MAX)
#define IS_RETRO(kc) (IS_MT(kc) || IS_LT(kc))
#define DO_GET_AUTOMOD_TIMEOUT(keycode, record, ...) record
// clang-format off
#define AUTO_MOD_ALPHA KC_A ... KC_Z
#define AUTO_MOD_NUMERIC KC_1 ... KC_0
#define AUTO_MOD_SPECIAL          \
             KC_TAB:                \
        case KC_MINUS ... KC_SLASH: \
        case KC_NONUS_BSLASH
// clang-format on

bool process_auto_mod(uint16_t keycode, keyrecord_t *record);
void retromod_poll_time(keyevent_t *event);
void retromod_swap_times(void);

void     automod_enable(void);
void     automod_disable(void);
void     automod_toggle(void);
bool     get_automod_state(void);
uint16_t get_generic_automod_timeout(void);
// clang-format off
uint16_t (get_automod_timeout)(uint16_t keycode, keyrecord_t *record);
void     set_automod_timeout(uint16_t timeout);
void     automod_matrix_scan(void);
bool     get_custom_auto_modded_key(uint16_t keycode, keyrecord_t *record);
// clang-format on
