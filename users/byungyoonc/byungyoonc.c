/* Copyright 2021 Choi Byungyoon <byungyoonc@gmail.com>
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

#include QMK_KEYBOARD_H
#include "byungyoonc.h"

#if (__has_include("secrets.h") && !defined(NO_SECRETS))
#    include "secrets.h"
#else
static const char *const secrets[] = {"test1", "test2"};
#endif

#if !defined(MACRO_TIMER)
#   define MACRO_TIMER 20
#endif

/* replicaJunction's process_record_user_kb */
__attribute__ ((weak))
bool process_record_user_kb(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case KC_SEC1 ... KC_SEC2: /* Secrets!  Externally defined strings, not stored in repo */
        if (!record->event.pressed) {
            clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
            send_string_with_delay(secrets[keycode - KC_SEC1], MACRO_TIMER);
        }
        return false;
        break;
    }
    return process_record_user_kb(keycode, record);
};

