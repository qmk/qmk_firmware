// Copyright 2026 ToYoNiX <toyonix.assemmohamed.2005@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// Home Row Mods - custom modifier order
#define HM_A LSFT_T(KC_A)           // Shift
#define HM_S LCTL_T(KC_S)           // Ctrl
#define HM_D LGUI_T(KC_D)           // Win/GUI
#define HM_F LALT_T(KC_F)           // Alt

#define HM_J LALT_T(KC_J)           // Alt
#define HM_K LGUI_T(KC_K)           // Win/GUI
#define HM_L LCTL_T(KC_L)           // Ctrl
#define HM_SCLN RSFT_T(KC_SCLN)     // Shift

// Keymap
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* BASE Layer: QWERTY */
    [0] = LAYOUT_split_3x5_3(
      //A8       B15      B14      B13      B12                                 B12      B13      B14      B15      A8 
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,             /*B0*/            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        HM_A,    HM_S,    HM_D,    HM_F,    KC_G,             /*A5*/            KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,             /*A4*/            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                          KC_ESC,  KC_SPC,  MO(1),            /*A3*/            MO(2),   KC_BSPC, KC_ENT
    ),
    [1] = LAYOUT_split_3x5_3(
        KC_TAB,   KC_7,    KC_8,    KC_9,    KC_0,                               KC_GRV,  KC_QUOT, KC_MINS, KC_EQL,  KC_NO,
        KC_LSFT,  KC_4,    KC_5,    KC_6,    KC_PSCR,                            KC_HOME, KC_LBRC, KC_RBRC, KC_BSLS, KC_RSFT,
        KC_LGUI,  KC_1,    KC_2,    KC_3,    KC_DEL,                             KC_END,  KC_COMM, KC_DOT,  KC_SLSH, KC_NO,
                          _______, _______, _______,                            _______, _______, _______
    ),
    [2] = LAYOUT_split_3x5_3(
        QK_BOOT,  KC_F7,  KC_F8,   KC_F9,   KC_F10,                             TO(3),   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_NO,    KC_F4,  KC_F5,   KC_F6,   KC_F11,                             KC_NO,   KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
        QK_RBT,   KC_F1,  KC_F2,   KC_F3,   KC_F12,                             KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          _______, _______, _______,                            _______, _______, _______
    ),
    // Gaming Layers
    [3] = LAYOUT_split_3x5_3(
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,                               TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LSFT, KC_A,    KC_S,    KC_D,    KC_F,                               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_LCTL, KC_Z,    KC_X,    KC_C,    KC_V,                               KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          KC_ESC,  KC_SPC,  LT(MO(4), KC_LGUI),                 KC_NO,   KC_NO,   KC_NO
    ),
    [4] = LAYOUT_split_3x5_3(
        KC_NO,    KC_7,   KC_8,    KC_9,    KC_0,                               TO(0),   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_M,     KC_4,   KC_5,    KC_6,    KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
        KC_B,     KC_1,   KC_2,    KC_3,    KC_F3,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
                          _______, _______, _______,                            KC_NO,   KC_NO,   KC_NO
    )
};

// Encoders
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [0] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(MS_WHLD, MS_WHLU)  },
    [1] =   { ENCODER_CCW_CW(KC_NO,   KC_NO),   ENCODER_CCW_CW(KC_BRIU, KC_BRID)  },
    [2] =   { ENCODER_CCW_CW(KC_PGUP, KC_PGDN), ENCODER_CCW_CW(KC_NO, KC_NO)      },
    [3] =   { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_NO, KC_NO)      },
    [4] =   { ENCODER_CCW_CW(KC_NO,   KC_NO),   ENCODER_CCW_CW(KC_NO, KC_NO)      },
    //                  Encoder 1                                     Encoder 2
};
#endif
