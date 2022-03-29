/* Copyright 2021 Joshua T.
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

// Before you can compile with this feature, you'll need to manually
// create a file in this directory called "secret_definitions.h"
// containing the data to be added.
//
// Example implementation:
//
// #pragma once
// static const char * const secrets[] = {
//   "secret1",
//   "secret2",
//   "secret3",
//   "secret4"
// }

#include QMK_KEYBOARD_H
#include "replicaJunction.h"
#include "secrets.h"
#include "secret_definitions.h"

#ifndef MACRO_TIMER
#   define MACRO_TIMER 5
#endif

bool process_record_secrets(uint16_t keycode, const keyrecord_t *record) {
    switch (keycode) {
        case K_SECR1 ... K_SECR4: // Secrets!  Externally defined strings, not stored in repo
            if (!record->event.pressed) {
                clear_oneshot_layer_state(ONESHOT_OTHER_KEY_PRESSED);
                send_string_with_delay(secrets[keycode - K_SECR1], MACRO_TIMER);
            }
            return false;
    }

    return true;
}
