// Copyright 2020 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT_ortho_1x1(QK_BACKLIGHT_STEP)
};

// https://github.com/qmk/qmk_firmware/blob/master/docs/feature_rgblight.md
void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(HSV_CYAN);
    // rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
}