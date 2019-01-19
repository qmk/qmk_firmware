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

#ifdef LEADER_ENABLE

#include "process_leader.h"

#ifndef LEADER_TIMEOUT
  #define LEADER_TIMEOUT 300
#endif

__attribute__ ((weak))
void leader_start(void) {}

__attribute__ ((weak))
void leader_end(void) {}

// Leader key stuff
bool leading = false;
uint16_t leader_time = 0;

uint16_t leader_sequence[5] = {0, 0, 0, 0, 0};
uint8_t leader_sequence_size = 0;

void qk_leader_start(void) {
  if (leading) { return; }
  leader_start();
  leading = true;
  leader_time = timer_read();
  leader_sequence_size = 0;
  leader_sequence[0] = 0;
  leader_sequence[1] = 0;
  leader_sequence[2] = 0;
  leader_sequence[3] = 0;
  leader_sequence[4] = 0;
}

bool process_leader(uint16_t keycode, keyrecord_t *record) {
  // Leader key set-up
  if (record->event.pressed) {
    if (leading) {
      if (timer_elapsed(leader_time) < LEADER_TIMEOUT) {
#ifndef LEADER_KEY_STRICT_KEY_PROCESSING
        if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) || (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
          keycode = keycode & 0xFF;
        }
#endif // LEADER_KEY_STRICT_KEY_PROCESSING
        leader_sequence[leader_sequence_size] = keycode;
        leader_sequence_size++;
#ifdef LEADER_PER_KEY_TIMING
        leader_time = timer_read();
#endif
        return false;
      }
    } else {
      if (keycode == KC_LEAD) {
        qk_leader_start();
      }
    }
  }
  return true;
}

#endif
