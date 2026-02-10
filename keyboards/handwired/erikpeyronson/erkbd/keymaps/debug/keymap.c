// Copyright 2025 Qmk, Erik Peyronson @erikpeyronson
// SPDX-License-Identifier: GPL-3.0-or-later

// NOTE: This keymap is for debugging purposes to have firmware to test the matrix when building the keyboard. If you intend to build this keyboard
// you should copy this to your fork or userspace repository and create your own.

#include QMK_KEYBOARD_H

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_split_3x6_5(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                               KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
        KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                               KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                               KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                        KC_LBRC, KC_RBRC, KC_LGUI, KC_BSPC, KC_SPC,           KC_SPC,  KC_ENT,  KC_RALT, KC_LPRN, KC_RPRN
    )
};
// clang-format on

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
    debug_enable = true;
    debug_matrix = true;
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // If console is enabled, it will print the matrix position and status of each key pressed
#ifdef CONSOLE_ENABLE
    uprintf("KL: kc: 0x%04X, col: %2u, row: %2u, pressed: %u, time: %5u, int: %u, count: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed, record->event.time, record->tap.interrupted, record->tap.count);
#endif
    return true;
}

// This function prints which half the keyboard considers itself to be which is
// useful for verify if the handedness pin and display is correctly set up when building
#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (is_keyboard_left()) {
        oled_write_P(PSTR("left"), false);
    } else {
        oled_write_P(PSTR("right"), false);
    }
    return false;
}
#endif

#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_UP, KC_DOWN), ENCODER_CCW_CW(KC_RIGHT, KC_LEFT)}
};
#endif
