// Copyright 2024 SM Boards (@sm_boards)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Four layers matching the product's default functionality. SW9 (the 7th
// key) cycles to the next layer using TO(): L1 -> L2 -> L3 -> L4 -> L1.
enum layers {
    _L1,    // Volume / media
    _L2,    // Editing shortcuts
    _L3,    // Zoom / find / print
    _L4     // Navigation
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* L1 — Volume / media */
    [_L1] = LAYOUT(
        KC_MUTE,        KC_VOLU,        KC_MPLY,
        KC_VOLD,        KC_MPRV,        KC_MNXT,    TO(_L2)
    ),
    /* L2 — Editing: Copy/Paste/Find · Undo/Redo/Save */
    [_L2] = LAYOUT(
        LCTL(KC_C),     LCTL(KC_V),     LCTL(KC_F),
        LCTL(KC_Z),     LCTL(KC_Y),     LCTL(KC_S), TO(_L3)
    ),
    /* L3 — Zoom / find / print */
    [_L3] = LAYOUT(
        LCTL(KC_0),     LCTL(KC_EQUAL), LCTL(KC_P),
        LCTL(KC_MINUS), LCTL(KC_F),     LCTL(KC_S), TO(_L4)
    ),
    /* L4 — Navigation */
    [_L4] = LAYOUT(
        KC_PGUP,        KC_UP,          KC_HOME,
        KC_PGDN,        KC_DOWN,        KC_END,     TO(_L1)
    ),
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_L1] = { ENCODER_CCW_CW(KC_VOLD,        KC_VOLU)        },  // volume
    [_L2] = { ENCODER_CCW_CW(LCTL(KC_Z),     LCTL(KC_Y))     },  // undo / redo
    [_L3] = { ENCODER_CCW_CW(LCTL(KC_MINUS), LCTL(KC_EQUAL)) },  // zoom
    [_L4] = { ENCODER_CCW_CW(MS_WHLD,        MS_WHLU)        },  // scroll
};
#endif
