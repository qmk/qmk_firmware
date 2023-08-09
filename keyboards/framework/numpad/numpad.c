// Copyright 2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "numpad.h"

void keyboard_post_init_user(void) {
    // Sync initial numlock state from the host
    if (host_keyboard_led_state().num_lock) {
        layer_on(_NUMLOCK);
    } else {
        layer_off(_FN);
    }
}
