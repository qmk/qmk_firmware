// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "introspection.h"

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

uint32_t delayed_hello_world(uint32_t trigger_time, void *cb_arg) {
    printf("Hello, world! I'm a QMK based keyboard! The keymap array size is %d bytes.\n", (int)hello_world_introspection().total_size);
    return 0;
}

void keyboard_post_init_hello_world(void) {
    keyboard_post_init_hello_world_kb();
    defer_exec(10000, delayed_hello_world, NULL);
}

bool process_record_hello_world(uint16_t keycode, keyrecord_t *record) {
    if (!process_record_hello_world_kb(keycode, record)) {
        return false;
    }

    switch (keycode) {
        case COMMUNITY_MODULE_HELLO:
            if (record->event.pressed) {
                SEND_STRING("Hello there.");
                break;
            }
    }

    return true;
}
