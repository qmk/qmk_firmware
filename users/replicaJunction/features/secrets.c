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
