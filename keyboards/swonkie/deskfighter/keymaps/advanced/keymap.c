// Copyright 2026 Swonkie swonkie@pm.me
// SPDX-License-Identifier: GPL-3.0-or-later

#include QMK_KEYBOARD_H

#define CAPS_LED_PIN B9

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    // Base layer
    LAYOUT(
        KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_AUDIO_MUTE, KC_MEDIA_PREV_TRACK, KC_MEDIA_NEXT_TRACK, KC_MEDIA_PLAY_PAUSE,
        KC_SYSTEM_POWER, KC_HOME, KC_PAGE_UP, KC_GRAVE, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINUS, KC_EQUAL, KC_DEL,
        KC_PRINT_SCREEN, KC_END, KC_PAGE_DOWN, KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LEFT_BRACKET, KC_RIGHT_BRACKET, KC_BACKSLASH,
        MO(2), TG(1), KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SEMICOLON, KC_QUOTE, KC_ENTER,
        KC_UP, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMMA, KC_DOT, KC_SLASH,
        KC_LEFT, KC_DOWN, KC_RIGHT, KC_LEFT_SHIFT, KC_LEFT_CTRL, KC_LEFT_GUI, KC_LEFT_ALT, KC_SPACE, KC_BACKSPACE, KC_SPACE, KC_RIGHT_ALT, KC_RIGHT_GUI, KC_RIGHT_CTRL, KC_RIGHT_SHIFT
    ),
    // Numeric keypad at right hand position
    LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_SLASH, KC_KP_ASTERISK, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_7, KC_KP_8, KC_KP_9, KC_KP_MINUS, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, KC_KP_4, KC_KP_5, KC_KP_6, KC_KP_PLUS, _______, _______,
                 _______,                   _______, _______, _______, _______, _______, _______, KC_KP_1, KC_KP_2, KC_KP_3, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, KC_KP_0, KC_KP_DOT, _______, _______, _______
    ),
    // "fn" layer
    LAYOUT(
        QK_BOOTLOADER, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
                 _______,                   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};

// Make the caps LED reflect the state of "caps word".
void caps_word_set_user(bool active) {
    gpio_write_pin(CAPS_LED_PIN, active);
}
