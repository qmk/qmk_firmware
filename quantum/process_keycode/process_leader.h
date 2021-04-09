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

#include "quantum.h"

bool process_leader(uint16_t keycode, keyrecord_t *record);

void leader_start(void);
void leader_end(void);
void qk_leader_start(void);

#define SEQ_ONE_KEY(key) if (leader_sequence[0] == (key) && leader_sequence[1] == 0 && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_TWO_KEYS(key1, key2) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == 0 && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_THREE_KEYS(key1, key2, key3) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == 0 && leader_sequence[4] == 0)
#define SEQ_FOUR_KEYS(key1, key2, key3, key4) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == 0)
#define SEQ_FIVE_KEYS(key1, key2, key3, key4, key5) if (leader_sequence[0] == (key1) && leader_sequence[1] == (key2) && leader_sequence[2] == (key3) && leader_sequence[3] == (key4) && leader_sequence[4] == (key5))

#define LEADER_EXTERNS()                \
    extern bool     leading;            \
    extern uint16_t leader_time;        \
    extern uint16_t leader_sequence[5]; \
    extern uint8_t  leader_sequence_size
#define LEADER_DICTIONARY() if (leading && timer_elapsed(leader_time) > LEADER_TIMEOUT)
