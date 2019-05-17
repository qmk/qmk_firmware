/* Copyright 2016 Alex Olkhovskiy
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

#ifndef PROCESS_LEADERS_H
#define PROCESS_LEADERS_H

#include "quantum.h"
#include "leaders/press_state.h"

#define LEADERS_LAYER_MAX 32
#ifndef LEADERS_SEQ_MAX
#define LEADERS_SEQ_MAX 10
#endif

#define KEYSEQ_END  0x0000
void keyseq_init(void);
void keyseq_push(uint16_t keycode);
void keyseq_reset_oneshot(void);
void keyseq_set_oneshot(void);
void keyseq_reset_momentary(uint8_t pos);

uint16_t* keyseq_codes_get(void);
uint8_t keyseq_index_get(void);

bool process_leaders(uint16_t keycode, keyrecord_t *record);
void leaders_init(void);
void set_keyseq_definitions(uint16_t** kd);

void keyseq_set_definitions(uint16_t* k[]);

#ifdef __cplusplus
#define LEADERMANAGER_EXTERNS()  \
  extern uint16_t  momentary_sentinels;   \
  extern bool oneshot_sentinel; \
  extern uint16_t keyseq_codes[LEADERS_SEQ_MAX]; \
  extern bool keyseq_index;
#endif

#endif
