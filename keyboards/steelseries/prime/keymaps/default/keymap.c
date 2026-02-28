// Copyright 2024 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Left, Middle, Right,
    // Forward
    // Back
    // Underneath
    [0] = LAYOUT(
        MS_BTN1, MS_BTN3, MS_BTN2,
        MS_BTN5,
        MS_BTN4,
        QK_BOOT
    )
};
// clang-format on

void pointing_device_init_user(void) {
    pointing_device_set_cpi(1600);
}

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
};
#endif
