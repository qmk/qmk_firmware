// Copyright 2024 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(KC_A)
};

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
//   debug_matrix=false;
//   debug_keyboard=true;
//   debug_mouse=false;
}

void housekeeping_task_user(void) {
    static uint32_t last = 0;
    if (timer_elapsed32(last) > 2000) {
        uprintf("Bat: %d!\n", battery_get_percent());

        last = timer_read32();
    }
}
