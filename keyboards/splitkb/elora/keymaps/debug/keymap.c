// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    _DEFAULT = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_DEFAULT] = LAYOUT_myr(
      KC_A, KC_E, KC_I, KC_M, KC_Q, KC_U,       KC_9,    KC_9,       S(KC_U), S(KC_Q), S(KC_M), S(KC_I), S(KC_E), S(KC_A),
      KC_B, KC_F, KC_J, KC_N, KC_R, KC_V,       KC_8,    KC_8,       S(KC_V), S(KC_R), S(KC_N), S(KC_J), S(KC_F), S(KC_B),
      KC_C, KC_G, KC_K, KC_O, KC_S, KC_W,       KC_7,    KC_7,       S(KC_W), S(KC_S), S(KC_O), S(KC_K), S(KC_G), S(KC_C),
      KC_D, KC_H, KC_L, KC_P, KC_T, KC_X, KC_5, KC_6,    KC_6, KC_5, S(KC_X), S(KC_T), S(KC_P), S(KC_L), S(KC_H), S(KC_D),
                        KC_0, KC_1, KC_2, KC_3, KC_4,    KC_4, KC_3,   KC_2,    KC_1,    KC_0,

      KC_A, KC_B, KC_C, KC_D,       KC_E,                KC_A, KC_B,   KC_C,    KC_D,             KC_E
    ),
};

void keyboard_post_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
    rgblight_enable_noeeprom(); // enables RGB, without saving settings
    rgblight_sethsv_noeeprom(HSV_RED); // sets the color to red without saving
    rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING + 3); // sets mode to Fast breathing without saving
    #endif
}

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    // 0-3 left-half encoders
    // 4-7 are right-half encoders
    if (index == 0) {
        tap_code(KC_0);
    } else if (index == 1) {
        tap_code(KC_1);
    } else if (index == 2) {
        tap_code(KC_2);
    } else if (index == 3) {
        // Myriad
        tap_code(KC_3);
    } else if (index == 4) {
        tap_code(KC_4);
    } else if (index == 5) {
        tap_code(KC_5);
    } else if (index == 6) {
        tap_code(KC_6);
    } else if (index == 7) {
        // Myriad
        tap_code(KC_7);
    }

    if (clockwise) {
        tap_code16(KC_PLUS);
    } else {
        tap_code(KC_MINUS);
    }

    return false;
}
#endif

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    // A 128x32 OLED rotated 90 degrees is 5 characters wide and 16 characters tall
    // This example string should fill that neatly
    oled_write_P(PSTR("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ123456789!@#$%^&*()[]{}-=_+?"), is_keyboard_master());
    return false;
}
#endif
