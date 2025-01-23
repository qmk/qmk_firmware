// Copyright 2025 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(20250122);

static uint32_t init_timestamp = 0;

void keyboard_post_init_hello_world(void) {
    keyboard_post_init_hello_world_kb();

    init_timestamp = timer_read32();
}

void housekeeping_task_hello_world(void) {
    housekeeping_task_hello_world_kb();

    static bool welcomed = false;
    if(!welcomed && timer_elapsed32(init_timestamp) > 10000) {
        welcomed = true;
        print("Hello, world! I'm a QMK based keyboard!\n");
    }
}
