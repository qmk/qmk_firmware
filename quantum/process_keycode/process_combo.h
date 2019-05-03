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

#include <stdint.h>
#include "progmem.h"
#include "quantum.h"

typedef struct
{
    const uint16_t *keys;
    uint16_t keycode;        
#ifdef EXTRA_EXTRA_LONG_COMBOS
    uint32_t state;
#elif EXTRA_LONG_COMBOS
    uint16_t state;
#else
    uint8_t state;
#endif
    uint16_t timer;
#ifdef COMBO_ALLOW_ACTION_KEYS
    keyrecord_t prev_record;
#else
    uint16_t prev_key;
#endif
} combo_t;


#define COMBO(ck, ca)       {.keys = &(ck)[0], .keycode = (ca)}
#define COMBO_ACTION(ck)    {.keys = &(ck)[0]}

#define COMBO_END 0
#ifndef COMBO_COUNT
#define COMBO_COUNT 0
#endif
#ifndef COMBO_TERM
#define COMBO_TERM TAPPING_TERM
#endif

bool process_combo(uint16_t keycode, keyrecord_t *record);
void matrix_scan_combo(void);
void process_combo_event(uint8_t combo_index, bool pressed);

#endif
