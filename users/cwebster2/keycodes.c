/* Copyright 2020 Casey Webster <casey@e1337.dev>
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
#include "keycodes.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_colon_timer;

    switch (keycode) {
        case KC_LCCL:
            if (record->event.pressed) {
                my_colon_timer = timer_read();
                register_code(KC_LCTL);
            } else {
                unregister_code(KC_LCTL);
                if (timer_elapsed(my_colon_timer) < TAPPING_TERM) {
                    SEND_STRING(":");
                }
            }
            return false;
    }
    return process_record_keymap(keycode, record);
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LGUI_T(KC_A):
        case LALT_T(KC_S):
        case LCTL_T(KC_D):
        case LSFT_T(KC_F):
        case RSFT_T(KC_J):
        case RCTL_T(KC_K):
        case RALT_T(KC_L):
        case RGUI_T(KC_SCLN):
            return TAPPING_TERM + 150;
        default:
            return TAPPING_TERM;
    }
}
