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

__attribute__((weak)) void matrix_scan_secrets(void) {}
__attribute__((weak)) void matrix_scan_keymap(void) {}
__attribute__((weak)) void matrix_scan_rgb_matrix(void) {}

LEADER_EXTERNS();
void matrix_scan_leader(void) {
    LEADER_DICTIONARY() {
        leading = false;
        leader_end();

        // Website Refresh / XCode "Run"
        SEQ_ONE_KEY(KC_R) {
            SEND_STRING(SS_LGUI("r"));
        } else

        SEQ_TWO_KEYS(KC_B, KC_D) {
            SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION " Built at: " QMK_BUILDDATE);
        }
    }
}

void matrix_scan_user(void) {
    /**
     * Any shared matrix_scan code would go here if it doesn't
     * fit into the RGB, Leader-key, or Secrets features
     */
    matrix_scan_leader();
    matrix_scan_rgb_matrix();
    matrix_scan_secrets();
    matrix_scan_keymap();
}