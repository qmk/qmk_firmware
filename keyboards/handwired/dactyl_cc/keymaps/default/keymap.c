// Copyright 2022 mjohns
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum layers {
    BASE,
    NAV
};

#define CTL_ESC LCTL_T(KC_ESC)
#define CTL_CAP LCTL_T(KC_CAPS)
#define ALT_BSP LALT_T(KC_BSPC)
#define LT_SCLN LT(NAV, KC_SCLN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [BASE] = LAYOUT(
        KC_GRV,  KC_1,    KC_2,   KC_3,    KC_4,    KC_5,                                         KC_6, KC_7,    KC_8,    KC_9,   KC_0,    KC_HOME,
        KC_TAB,  KC_Q,    KC_W,   KC_E,    KC_R,    KC_T,                                         KC_Y, KC_U,    KC_I,    KC_O,   KC_P,    KC_BSLS,
        CTL_CAP, KC_A,    KC_S,   KC_D,    KC_F,    KC_G,                                         KC_H, KC_J,    KC_K,    KC_L,   LT_SCLN, KC_QUOT,
        KC_LSFT, KC_Z,    KC_X,   KC_C,    KC_V,    KC_B,                                         KC_N, KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RSFT,
                 KC_MINS, KC_EQL, KC_LBRC, KC_RBRC,                                                     KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT,
                                                          TT(NAV),  KC_DEL,     KC_PGUP, KC_RCTL,
                                                 KC_BSPC, CTL_ESC, KC_LGUI,     KC_PGDN, KC_ENT,  KC_SPC,
                                                                   KC_LALT,     KC_RALT  
    ),
    [NAV] = LAYOUT(
        QK_BOOT, KC_NO,   KC_MPRV, KC_MPLY, KC_MNXT, KC_NO,                                           KC_BRIU, KC_P7,   KC_P8,  KC_P9,   KC_NO,   QK_BOOT,
        _______, KC_VOLU, KC_WBAK, KC_MS_U, KC_WFWD, KC_WH_U,                                         KC_BRID, KC_P4,   KC_P5,  KC_P6,   KC_PMNS, _______,
        _______, KC_VOLD, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,                                         KC_PPLS, KC_P1,   KC_P2,  KC_P3,   KC_PSLS, _______,
        KC_NO,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_NO,                                           KC_PAST, KC_PCMM, KC_P0,  KC_PDOT, KC_PENT, _______,
                 KC_F5,   KC_F6,   KC_F7,   KC_F8,                                                             KC_F9,   KC_F10, KC_F11,  KC_F12,
                                                              _______, _______,     KC_HOME, _______,
                                                     KC_BTN1, KC_BTN2, _______,     KC_END,  _______, _______,
                                                                       _______,     ALT_BSP 
    )
};
