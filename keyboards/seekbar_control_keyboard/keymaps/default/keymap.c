// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x2(
        KC_MEDIA_PREV_TRACK,   KC_MEDIA_PLAY_PAUSE,   KC_MEDIA_NEXT_TRACK,
        KC_D,   KC_MEDIA_REWIND,   KC_MEDIA_FAST_FORWARD
    )
};
