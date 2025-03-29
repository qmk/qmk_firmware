// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H
#include <stdint.h>

enum layer_names { _BASE, _NUM, _FN, _MOUSE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT_basic(
        // clang-format off

        // channel 1
        //// key5 * 5, key4 * 2
        KC_ESC, KC_TAB, KC_LEFT_CTRL, KC_LEFT_SHIFT, LT(_NUM, KC_GRAVE),
        KC_1, KC_Q, KC_A, KC_Z, KC_LEFT_PAREN,
        KC_2,KC_W, KC_S, KC_X, KC_RIGHT_PAREN,
        KC_3, KC_E, KC_D, KC_C, KC_LEFT_ALT,
        KC_4, KC_R, KC_F, KC_V, LGUI_T(KC_LANGUAGE_2),
        KC_5, KC_T, KC_G, KC_B,
        KC_SPACE, KC_BACKSPACE, _______, _______,
        //// rotary encoders * 1
        KC_TAB,

        // channel 2
        //// key4 * 2, key5 * 5
        KC_ENTER, KC_TAB, _______, LCTL(KC_LEFT_BRACKET),
        KC_6, KC_Y, KC_H, KC_N,
        KC_7, KC_U, KC_J, KC_M, KC_LANGUAGE_1,
        KC_8, KC_I, KC_K, KC_COMMA, _______,
        KC_9, KC_O, KC_L, KC_DOT, KC_LEFT_BRACKET,
        KC_0, KC_P, KC_SEMICOLON, KC_SLASH, KC_RIGHT_BRACKET,
        KC_MINUS, KC_BACKSLASH, KC_QUOTE, _______, KC_EQUAL

        // clang-format on
        ),
    [_NUM] = LAYOUT_basic(
        // clang-format off

        // channel 1
        //// key5 * 5, key4 * 2
        _______, _______, _______, _______, _______,
        _______, _______, KC_EXCLAIM, KC_CIRCUMFLEX, MO(_FN),
        _______, _______, KC_AT, KC_AMPERSAND, _______,
        _______, _______, KC_HASH, KC_ASTERISK, _______,
        _______, _______, KC_DOLLAR, _______, _______,
        _______, _______, KC_PERCENT, _______,
        _______, _______, _______, _______,
        //// rotary encoders * 1
        _______,

        // channel 2
        //// key4 * 2, key5 * 5
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, KC_7, KC_4, KC_1, _______,
        _______, KC_8, KC_5, KC_2, KC_0,
        _______, KC_9, KC_6, KC_3, KC_LEFT,
        _______, KC_MINUS, KC_PPLS, KC_UP, KC_DOWN,
        _______, _______, _______, _______, KC_RIGHT

        // clang-format on
        ),
    [_FN] = LAYOUT_basic(
        // clang-format off

        // channel 1
        //// key5 * 5, key4 * 2
        QK_BOOT, QK_CLEAR_EEPROM, _______, _______, _______,
        _______, QK_KB_10, QK_KB_5, QK_KB_0, _______,
        _______, QK_KB_11, QK_KB_6, QK_KB_1, _______,
        _______, QK_KB_12, QK_KB_7, QK_KB_2, _______,
        _______, QK_KB_13, QK_KB_8, QK_KB_3, _______,
        _______, QK_KB_14, QK_KB_9, QK_KB_4,
        _______, _______, _______, _______,

        //// rotary encoders * 1
        _______,

        // channel 2
        //// key4 * 2, key5 * 5
        _______, _______, _______, _______,
        _______, _______, _______, _______,
        _______, KC_F7, KC_F4, KC_F1, _______,
        _______, KC_F8, KC_F5, KC_F2, KC_F10,
        _______, KC_F9, KC_F6, KC_F3, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______

        // clang-format on
        ),
    [_MOUSE] = LAYOUT_basic(
        // clang-format off

        // channel 1
        //// key5 * 5, key4 * 2
        _______, _______, _______, _______, _______,
        _______, _______, DRAG_SCROLL, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, QK_MOUSE_WHEEL_UP, _______, _______,
        _______, _______, QK_MOUSE_WHEEL_DOWN, _______, _______,
        _______, _______, _______, _______,
        _______, _______, _______, _______,

        //// rotary encoders * 1
        _______,

        // channel 2
        //// key4 * 2, key5 * 5
        QK_MOUSE_BUTTON_4, QK_MOUSE_BUTTON_3, QK_MOUSE_BUTTON_2, QK_MOUSE_BUTTON_1,
        _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______

        // clang-format on
        ),
};

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM
    encoder_map[][NUM_ENCODERS]
               [NUM_DIRECTIONS] = {

                   [_BASE] =
                       {
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                           ENCODER_CCW_CW(KC_PGDN, KC_PGUP),
                       },
                   [_NUM] =
                       {
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                       },
                   [_FN] =
                       {
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                       },
                   [_MOUSE] =
                       {
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                           ENCODER_CCW_CW(_______, _______),
                       },

};
#endif

#ifdef POINTING_DEVICE_ENABLE
void pointing_device_init_user(void) {
    set_auto_mouse_layer(_MOUSE);
}
#endif
