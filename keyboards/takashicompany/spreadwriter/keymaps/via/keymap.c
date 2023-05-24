// Copyright 2022 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

enum custom_keycodes {
    SPREADWRITER = SAFE_RANGE,
    WEB,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    LAYOUT(
        KC_ESC, LT(2, KC_Q), KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_BSPC,
        KC_LCTL, KC_A, KC_S, LT(2, KC_D), KC_F, KC_G, SPREADWRITER, KC_H, KC_J, LT(2, KC_K), KC_L, KC_ENT, KC_ENT,
        KC_LSFT, SFT_T(KC_Z), GUI_T(KC_X), KC_C, KC_V, KC_B, MEH(KC_4), LSA(KC_5),  KC_N, KC_M, KC_COMM, CTL_T(KC_DOT), KC_BSPC, KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT, MO(5), MO(4), ALT_T(KC_LANG2), SFT_T(KC_TAB), WEB, LT(6, KC_SPC), LT(1, KC_LANG1), KC_RALT, KC_LEFT, KC_UP, KC_DOWN, KC_RGHT,
        KC_WH_U, KC_WH_D
    ),

    LAYOUT(
        KC_TRNS, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_TRNS,
        KC_LCTL, CTL_T(KC_EQL), KC_LBRC, KC_SLSH, KC_MINS, KC_RO, KC_TRNS, KC_SCLN, KC_QUOT, KC_RBRC, KC_NUHS, KC_JYEN, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_ESC, KC_TAB, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_UP, KC_NO, KC_NO, KC_NO,
        KC_TRNS, KC_LCTL, KC_TRNS, KC_QUES, KC_EXLM, KC_NO, KC_TRNS, KC_NO, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, MO(3), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_BSPC, KC_SPC
    ),

    LAYOUT(
        RGB_TOG, RGB_MOD, RGB_HUI, RGB_SAI, RGB_VAI, KC_NO, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6,
        KC_TRNS, RGB_M_P, RGB_M_B, RGB_M_R, RGB_M_SW, RGB_M_SN, KC_TRNS, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,
        KC_TRNS, RGB_M_K, RGB_M_X, RGB_M_G, RGB_M_T, RGB_M_T, KC_TRNS, QK_BOOT, KC_F11, KC_F12, KC_CAPS, KC_NO, KC_NO, KC_TRNS, 
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, KC_MINS, KC_EQL, KC_JYEN, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_SCLN, KC_QUOT, KC_NUHS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P0, KC_COMM, KC_DOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_COMM, KC_DOT, KC_SLSH, KC_RO, KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, KC_TRNS, KC_P7, KC_P8, KC_P9, KC_TRNS, KC_TRNS, S(KC_MINS), S(KC_EQL), S(KC_JYEN), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P4, KC_P5, KC_6, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_LBRC), S(KC_RBRC), KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P1, KC_P2, KC_P3, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_SCLN), S(KC_QUOT), S(KC_NUHS), KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_P0, KC_COMM, KC_DOT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, S(KC_COMM), S(KC_DOT), S(KC_SLSH), S(KC_RO), KC_TRNS,
        KC_TRNS, KC_TRNS
    ),

    LAYOUT(
        KC_TRNS, S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), S(KC_7), S(KC_8), S(KC_9), G(KC_JYEN), KC_TRNS,
        KC_LCTL, S(KC_EQL), S(KC_LBRC), S(KC_SLSH), S(KC_MINS), S(KC_RO), KC_TRNS, S(KC_SCLN), S(KC_QUOT), S(KC_RBRC), S(KC_NUHS), S(KC_JYEN), KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case SPREADWRITER:
            if (record->event.pressed) {
                SEND_STRING("Spreadwriter");
                rgblight_toggle();
            }
            return false;

        case WEB:
            if (record->event.pressed) {
                SEND_STRING("github.com/takashicompany/spreadwriter");
            }
            return false;
    }
    
    return true;
}

//------------------------------------------------------------------------------
// Rotary Encoder
//------------------------------------------------------------------------------
static uint8_t  encoder_state[ENCODERS] = {0};
static keypos_t encoder_cw[ENCODERS]    = ENCODERS_CW_KEY;
static keypos_t encoder_ccw[ENCODERS]   = ENCODERS_CCW_KEY;

void encoder_action_unregister(void) {
    for (int index = 0; index < ENCODERS; ++index) {
        if (encoder_state[index]) {
            keyevent_t encoder_event = (keyevent_t) {
                .key = encoder_state[index] >> 1 ? encoder_cw[index] : encoder_ccw[index],
                .pressed = false,
                .time = (timer_read() | 1)
            };
            encoder_state[index] = 0;
            action_exec(encoder_event);
        }
    }
}

void encoder_action_register(uint8_t index, bool clockwise) {
    keyevent_t encoder_event = (keyevent_t) {
        .key = clockwise ? encoder_cw[index] : encoder_ccw[index],
        .pressed = true,
        .time = (timer_read() | 1)
    };
    encoder_state[index] = (clockwise ^ 1) | (clockwise << 1);
    action_exec(encoder_event);
}

void matrix_scan_kb(void) {
    encoder_action_unregister();
    matrix_scan_user();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    encoder_action_register(index, clockwise);
    return true;
};