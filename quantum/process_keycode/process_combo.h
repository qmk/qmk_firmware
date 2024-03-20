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

#include "progmem.h"
#include "quantum.h"
#include <stdint.h>

#ifdef EXTRA_SHORT_COMBOS
#    define MAX_COMBO_LENGTH 6
#elif defined(EXTRA_EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 32
#elif defined(EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 16
#else
#    define MAX_COMBO_LENGTH 8
#endif

#ifndef COMBO_KEY_BUFFER_LENGTH
#    define COMBO_KEY_BUFFER_LENGTH MAX_COMBO_LENGTH
#endif
#ifndef COMBO_BUFFER_LENGTH
#    define COMBO_BUFFER_LENGTH 4
#endif

typedef struct {
    const uint16_t *keys;
    uint16_t        keycode;
#ifdef EXTRA_SHORT_COMBOS
    uint8_t state;
#else
    bool     disabled;
    bool     active;
#    if defined(EXTRA_EXTRA_LONG_COMBOS)
    uint32_t state;
#    elif defined(EXTRA_LONG_COMBOS)
    uint16_t state;
#    else
    uint8_t state;
#    endif
#endif
} combo_t;

#define COMBO(ck, ca) \
    { .keys = &(ck)[0], .keycode = (ca) }
#define COMBO_ACTION(ck) \
    { .keys = &(ck)[0] }

#define COMBO_END 0
#ifndef COMBO_TERM
#    define COMBO_TERM 50
#endif
#ifndef COMBO_HOLD_TERM
#    define COMBO_HOLD_TERM TAPPING_TERM
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
