// Copyright 2026 Anefecious
// SPDX-License-Identifier: GPL-2.0-or-later
//
// Alphabet wiring test (COL2ROW). Flash with: qmk flash -kb key_craft_pro -km test
//
// Front view:
//   EncL click = A     EncR click = B
//   C D E
//   F G H
//   I J K
//   L M N
//   Left rotate = O/P    Right rotate = Q/R
//
// See readme.md §6 for the debug checklist.

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_C, KC_D, KC_E,
        KC_F, KC_G, KC_H,
        KC_I, KC_J, KC_K,
        KC_L, KC_M, KC_N
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0] = {ENCODER_CCW_CW(KC_O, KC_P), ENCODER_CCW_CW(KC_Q, KC_R)}
};
#endif

// Active-low encoder buttons -> GND
void matrix_scan_user(void) {
    static bool left_prev  = false;
    static bool right_prev = false;

    bool left  = !gpio_read_pin(ENC_L_BTN_PIN);
    bool right = !gpio_read_pin(ENC_R_BTN_PIN);

    if (left != left_prev) {
        if (left) {
            register_code(KC_A);
        } else {
            unregister_code(KC_A);
        }
        left_prev = left;
    }

    if (right != right_prev) {
        if (right) {
            register_code(KC_B);
        } else {
            unregister_code(KC_B);
        }
        right_prev = right;
    }
}

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    oled_write_ln_P(PSTR("TEST"), false);
    oled_write_ln_P(PSTR("v2"), false);
    oled_write_ln_P(PSTR("A-N"), false);
    oled_write_ln_P(PSTR(""), false);
    oled_write_ln_P(PSTR("OP L"), false);
    oled_write_ln_P(PSTR("QR R"), false);
    return false;
}
#endif
