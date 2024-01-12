// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// tap danceの宣言
enum {
    TD_FORWARD_NEXT,
    TD_BACK_PREV,
};

// tap danceの定義
tap_dance_action_t tap_dance_actions[] = {
    [TD_FORWARD_NEXT]  = ACTION_TAP_DANCE_DOUBLE(KC_MEDIA_FAST_FORWARD, KC_MEDIA_NEXT_TRACK),
    [TD_BACK_PREV]  = ACTION_TAP_DANCE_DOUBLE(KC_MEDIA_REWIND, KC_MEDIA_PREV_TRACK),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┐
     * │ A │ B │ C │
     * ├───┼───┼───┤
     * │ D │ E │ F │
     * └───┴───┴───┘
     */
    [0] = LAYOUT_ortho_3x2(
        TD(TD_BACK_PREV),   KC_MEDIA_PLAY_PAUSE,   TD(TD_FORWARD_NEXT),
        KC_NO,   KC_NO,   KC_NO
    )
};
