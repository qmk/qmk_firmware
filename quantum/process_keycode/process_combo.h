/* Copyright 2016 Jack Humbert
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
#include "keycodes.h"
#include "quantum_keycodes.h"

/* COMBO_BUFFER_LENGTH defines the maximum number of simulatenously active combos. */
#ifndef COMBO_BUFFER_LENGTH
#    define COMBO_BUFFER_LENGTH 4
#endif

#if defined(EXTRA_EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 32
#    define COMBO_STATE_BITS 5
typedef uint32_t combo_active_state_t;
#elif defined(EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 16
#    define COMBO_STATE_BITS 4
typedef uint16_t combo_active_state_t;
#elif defined(EXTRA_SMALL_COMBOS)
#    define MAX_COMBO_LENGTH 4
#    define COMBO_STATE_BITS 2
typedef uint8_t combo_active_state_t;
#else
#    define MAX_COMBO_LENGTH 8
#    define COMBO_STATE_BITS 3
typedef uint8_t combo_active_state_t;
#endif

#ifdef COMBO_COMPRESSED
/* If combo_count() < (256/MAX_COMBO_LENGTH) - 1, this can be defined to save some space */
typedef uint8_t combo_state_t;
#else
typedef uint16_t combo_state_t;
#endif

#ifndef COMBO_KEY_BUFFER_LENGTH
#    define COMBO_KEY_BUFFER_LENGTH (MAX_COMBO_LENGTH + 4)
#endif

typedef struct combo_t {
    const uint16_t *keys;
    uint16_t        keycode;
    combo_state_t   state;
} combo_t;

#define COMBO(ck, ca) {.keys = &(ck)[0], .keycode = (ca)}
#define COMBO_ACTION(ck) {.keys = &(ck)[0]}

#define COMBO_END 0
#ifndef COMBO_TERM
#    define COMBO_TERM TAPPING_TERM
#endif
#ifndef COMBO_HOLD_TERM
#    define COMBO_HOLD_TERM TAPPING_TERM
#endif

#ifdef COMBO_NO_TIMER
#    pragma message "COMBO_NO_TIMER is deprecated and will be removed in a future version. Please define an explicit COMBO_TERM"
#    undef COMBO_TERM
#    define COMBO_TERM 32000
#endif

/* check if keycode is only modifiers */
#define KEYCODE_IS_MOD(code) (IS_MODIFIER_KEYCODE(code) || (IS_QK_MODS(code) && !QK_MODS_GET_BASIC_KEYCODE(code)))

bool process_combo(uint16_t keycode, keyrecord_t *record);
void combo_task(void);
void process_combo_event(uint16_t combo_index, bool pressed);

void combo_enable(void);
void combo_disable(void);
void combo_toggle(void);
bool is_combo_enabled(void);
