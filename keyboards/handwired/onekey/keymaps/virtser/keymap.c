// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H
#include "virtser.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

static uint32_t counter = 0;

void virtser_recv(const uint8_t ch) {
    static const char *lut = "0123456789ABCDEF";

    counter++;

    virtser_send(lut[(ch & 0xF0) >> 4]);
    virtser_send(lut[ch & 0xF]);
}

#ifdef CONSOLE_ENABLE

void keyboard_post_init_user(void) {
    // Customise these values to desired behaviour
    debug_enable = true;
    // debug_matrix=true;
    // debug_keyboard=true;
    // debug_mouse=true;
}

void housekeeping_task_user(void) {
    static uint32_t last = 0;
    if (timer_elapsed32(last) > 1000) {
        uprintf("recv: %ld!\n", counter);

        last = timer_read32();
    }
}

#endif
