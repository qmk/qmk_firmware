// Copyright (C) 2023 @kraken-jokes
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

#define COPY C(KC_C)
#define L1_GUI LT(1,KC_LGUI)
#define L1_DEL LT(1,KC_DEL)
#define L2_APP LT(2,KC_APP)
#define L2_ALT LT(2,KC_LALT)
#define PRTSC LGUI(LSFT(KC_S))
#define CUT C(KC_X)
#define PASTE C(KC_V)
#define ALTF4 A(KC_F4)
#define ALT_ESC A(KC_ESC)
#define UNDO C(KC_Z)
#define CTL_TAB C(KC_TAB)

enum my_keycodes {
    PASS = QK_USER
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_1,    KC_2,     KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, 
        KC_TAB,  KC_Q,    KC_W,     KC_E,    KC_R,    KC_T,            KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
        KC_LCTL, KC_A,    KC_S,     KC_D,    KC_F,    KC_G,            KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, 
        KC_LSFT, KC_Z,    KC_X,     KC_C,    KC_V,    KC_B,            KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, 
                          PASS,     KC_CAPS, KC_SPC,  KC_ENT,          TG(1),   KC_SPC,  KC_RALT, KC_RGUI
    ),

    [1] = LAYOUT(
        CUT,     KC_EXLM, KC_AT,    KC_HASH, KC_DLR,  KC_PERC,         KC_CIRC, KC_AMPR, KC_PSLS, KC_PAST, KC_INS,  KC_BSPC, 
        KC_TAB,  KC_LBRC, KC_UP,    KC_RBRC, KC_LCBR, KC_RCBR,         KC_NUM,  KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_DEL, 
        PASTE,   KC_LEFT, KC_DOWN,  KC_RGHT, UNDO,    CTL_TAB,         KC_PGUP, KC_P4,   KC_P5,   KC_P6,   KC_PMNS, TO(2), 
        COPY,    ALTF4,   ALT_ESC,  KC_MUTE, KC_MSTP, KC_MPLY,         KC_PGDN, KC_P1,   KC_P2,   KC_P3,   KC_BSLS, TO(0), 
                          KC_TRNS,  KC_LCTL, KC_LSFT, KC_LALT,         KC_TRNS, KC_TRNS, KC_TRNS, KC_P0
    ),

    [2] = LAYOUT(
        QK_BOOT, KC_SLEP, KC_WAKE, KC_TRNS, KC_PWR,   KC_TRNS,         KC_TRNS, KC_PSLS, KC_PAST, KC_PMNS, KC_TRNS, KC_BSPC, 
        KC_GRV,  KC_WBAK, KC_WFWD, KC_WSCH, KC_FIND,  KC_TRNS,         KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_PSLS, KC_PAST, 
        KC_DEL,  KC_CALC, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,         KC_P4,   KC_P5,   KC_P6,   KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LBRC, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,  KC_TRNS,         KC_P1,   KC_P2,   KC_P3,   KC_PDOT, KC_TRNS, KC_TRNS,
                          KC_TRNS, KC_TRNS, PRTSC,    KC_TRNS,         KC_TRNS, KC_TRNS, KC_TRNS, KC_P0
    ),
};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case PASS:
        if (record->event.pressed) {
            // when keycode M4 is pressed	
            SEND_STRING("XXXXXXXXXX");
        }
        break;
    }
    return true;
}
