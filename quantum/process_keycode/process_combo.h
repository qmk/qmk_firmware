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

#ifndef PROCESS_COMBO_H
#define PROCESS_COMBO_H

#include "progmem.h"
#include "quantum.h"
#include <stdint.h>

#if defined(EXTRA_EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 32
#elif defined(EXTRA_LONG_COMBOS)
#    define MAX_COMBO_LENGTH 16
#else
#    define MAX_COMBO_LENGTH 8
#endif

typedef struct {
    const uint16_t *keys;
    uint16_t        keycode;
    bool            disabled : 1;
    bool            active : 1;
#if defined(EXTRA_EXTRA_LONG_COMBOS)
    uint32_t state;
#elif defined(EXTRA_LONG_COMBOS)
    uint16_t state;
#else
    uint8_t state;
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
#ifndef COMBO_MOD_TERM
#    define COMBO_MOD_TERM 200
#endif

/* check if keycode is only modifiers */
#define KEYCODE_IS_MOD(code) (IS_MOD(code) || ((code & 0xFF00) >= QK_MODS && (code & 0xFF00) <= QK_MODS_MAX && !(code & 0xFF)))

bool process_combo(uint16_t keycode, keyrecord_t *record);
void matrix_scan_combo(void);
void process_combo_event(uint16_t combo_index, bool pressed);

void combo_enable(void);
void combo_disable(void);
void combo_toggle(void);
bool is_combo_enabled(void);

#endif
