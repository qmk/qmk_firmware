// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
    [1] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU)  },
};
#endif


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4,                                                                          KC_END, KC_INSERT, KC_DELETE, KC_KB_MUTE,
        KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6,                                                KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_BACKSPACE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T,                                KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_ENTER,
        OSM(MOD_LCTL), KC_A, KC_S, KC_D, KC_F, KC_G,                                             KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_BACKSLASH,
        OSM(MOD_LSFT), KC_LEFT_ANGLE_BRACKET, KC_Z, KC_X, KC_C, KC_V, KC_B,                              KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH, OSM(MOD_RSFT),
        CW_TOGG, OSM(MOD_LGUI), KC_LEFT_ALT, MO(1), OSM(MOD_LALT),                        KC_SPACE, OSM(MOD_RALT), KC_RIGHT_CTRL, KC_NO, KC_NO
    ),

    [1] = LAYOUT(
        QK_REBOOT, _______, _______, _______, _______,                                                                         KC_PSCR, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______,                            _______, _______, _______, _______, _______, _______,  _______,
        KC_TAB,     KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                               KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______, _______, _______,
        _______, _______, _______, _______, _______, _______,                                     KC_LEFT, KC_DOWN,   KC_UP, KC_RIGHT, _______, _______, _______,
        _______, _______, _______,  _______, _______, _______, _______,                                     _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,                                                                KC_PGDN, _______, _______, _______, _______
    )
};
