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

#include "process_leader.h"
#include <string.h>

#ifndef LEADER_TIMEOUT
#    define LEADER_TIMEOUT 300
#endif

__attribute__((weak)) void leader_start_user(void) {}

__attribute__((weak)) void leader_end_user(void) {}

// Leader key stuff
bool     leading     = false;
uint16_t leader_time = 0;

uint16_t leader_sequence[5]   = {0, 0, 0, 0, 0};
uint8_t  leader_sequence_size = 0;

void leader_start(void) {
    if (leading) {
        return;
    }
    leader_start_user();
    leading              = true;
    leader_time          = timer_read();
    leader_sequence_size = 0;
    memset(leader_sequence, 0, sizeof(leader_sequence));
}

void leader_end(void) {
    leader_end_user();
}

bool process_leader(uint16_t keycode, keyrecord_t *record) {
    // Leader key set-up
    if (record->event.pressed) {
        if (leading) {
#ifndef LEADER_NO_TIMEOUT
            if (timer_elapsed(leader_time) < LEADER_TIMEOUT)
#endif // LEADER_NO_TIMEOUT
            {
#ifndef LEADER_KEY_STRICT_KEY_PROCESSING
                if (IS_QK_MOD_TAP(keycode)) {
                    keycode = QK_MOD_TAP_GET_TAP_KEYCODE(keycode);
                } else if (IS_QK_LAYER_TAP(keycode)) {
                    keycode = QK_LAYER_TAP_GET_TAP_KEYCODE(keycode);
                }
#endif // LEADER_KEY_STRICT_KEY_PROCESSING
                if (leader_sequence_size < ARRAY_SIZE(leader_sequence)) {
                    leader_sequence[leader_sequence_size] = keycode;
                    leader_sequence_size++;
                } else {
                    leading = false;
                    leader_end_user();
                    return true;
                }
#ifdef LEADER_PER_KEY_TIMING
                leader_time = timer_read();
#endif
                return false;
            }
        } else {
            if (keycode == QK_LEADER) {
                leader_start();
            }
        }
    }
    return true;
}
