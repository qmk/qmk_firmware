/**
 * Copyright (C) 2021 Jerrell, Jacob <@jjerrell>
 * 
 * This file is part of qmk_firmware.
 * 
 * qmk_firmware is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * qmk_firmware is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with qmk_firmware.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "jjerrell.h"
#include "version.h"

bool did_leader_succeed;
#ifdef AUDIO_ENABLE
float leader_begin[][2] = SONG(ONE_UP_SOUND);
float leader_succeed[][2] = SONG(ALL_STAR);
float leader_fail[][2] = SONG(RICK_ROLL);
#endif

__attribute__((weak)) bool leader_scan_secrets(uint8_t mods) { return true; }
__attribute__((weak)) void matrix_scan_keymap(void) {}
__attribute__((weak)) void matrix_scan_rgb_matrix(void) {}

LEADER_EXTERNS();
void matrix_scan_leader(void) {
    uint8_t mods = get_mods(); // Store modifiers
    clear_mods(); // Clear them so they don't mess with strings sent below

    if (leader_scan_secrets(mods)) {
        LEADER_DICTIONARY() {
            leading = false;

            // Website Refresh / XCode "Run"
            SEQ_ONE_KEY(KC_R) {
                SEND_STRING(SS_LGUI("r"));
                did_leader_succeed = true;
            } else

            SEQ_TWO_KEYS(KC_B, KC_D) {
                SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " Built at: " QMK_BUILDDATE);
                did_leader_succeed = true;
            }
            leader_end();
        }
    } else {
        did_leader_succeed = true;
        leader_end();
    }
}

void matrix_scan_user(void) {
    /**
     * Any shared matrix_scan code would go here if it doesn't
     * fit into the RGB, Leader-key, or Secrets features
     */
    matrix_scan_leader();
    matrix_scan_rgb_matrix();
    matrix_scan_keymap();
}

void leader_start(void) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_begin);
#endif
}

void leader_end(void) {
  if (did_leader_succeed) {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_succeed);
#endif
  } else {
#ifdef AUDIO_ENABLE
    PLAY_SONG(leader_fail);
#endif
  }
}