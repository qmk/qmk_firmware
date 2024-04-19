// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "graphics/display.h"

void keyboard_post_init_kb(void) {
    display_init_kb();
    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        display_key_counter();
    }
    return process_record_user(keycode, record);
}
