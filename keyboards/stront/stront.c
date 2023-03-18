// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "stront.h"
#include "display.h"
#include "raw_hid.h"

static bool display_enabled;

void keyboard_post_init_kb(void) {
    debug_enable = true;

    if (is_keyboard_master()) {
        display_enabled = display_init();
    }

    keyboard_post_init_user();
}

void raw_hid_receive(uint8_t *data, uint8_t length) {
    dprintf("received %u bytes from HID \n", length);

    if (display_enabled) {
        display_process_raw_hid_data(data, length);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    dprintf("keycode %u %s %s %d\n", keycode, record->event.pressed ? "pressed" : "depressed", record->tap.interrupted ? "interrupted" : "not interrupted", record->tap.count);

    if (display_enabled) {
        display_process_record(keycode, record);
    }

    return process_record_user(keycode, record);
}

void housekeeping_task_kb(void) {
    if (display_enabled) {
        display_refresh_data();
    }

    housekeeping_task_user();
}
