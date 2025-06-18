// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum {
    TD_FORWARD_NEXT,
    TD_BACK_PREV,
};

tap_dance_action_t tap_dance_actions[] = {
    [TD_FORWARD_NEXT]  = ACTION_TAP_DANCE_DOUBLE(KC_MEDIA_FAST_FORWARD, KC_MEDIA_NEXT_TRACK),
    [TD_BACK_PREV]  = ACTION_TAP_DANCE_DOUBLE(KC_MEDIA_REWIND, KC_MEDIA_PREV_TRACK),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) }
};
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_ortho_2x3(
        TD(TD_BACK_PREV), KC_MPLY,   TD(TD_FORWARD_NEXT),
        KC_NO,   KC_NO,   KC_SLEP
    )
};

