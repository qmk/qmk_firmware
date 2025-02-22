// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │
     * ├───┼───┼───┴───┴───┼───┴───┴───┼───┼───┤
     * │ 1 │ ' │ Backspace │   Space   │ ` │ 2 │
     * └───┴───┴───────────┴───────────┴───┴───┘
     */
    [0] = LAYOUT(
        KC_Q,       KC_W,       KC_E, KC_R,         KC_T,       KC_Y,       KC_U,       KC_I,       KC_O,       KC_P,
        KC_A,       KC_S,       LT(1, KC_D),        LSFT_T(KC_F),       KC_G, KC_H,       LSFT_T(KC_J),         LT(2, KC_K),        KC_L,      KC_SCLN,
        KC_Z,       LCTL_T(KC_X), LALT_T(KC_C),         KC_V,       KC_B,       KC_N,       KC_M,       LALT_T(KC_COMM),      LCTL_T(KC_DOT),         KC_SLSH,
        TG(7),    LT(3, KC_QUOT),         KC_BSPC,        LT(5, KC_SPC),      LT(4, KC_GRV),      TG(6)
    ),
    [1] = LAYOUT(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_SLSH, KC_ASTR, KC_7, KC_8, KC_9,
        KC_NO, KC_RALT, KC_NO, KC_LSFT, KC_NO, KC_CALC, KC_MINS, KC_4, KC_5, KC_6,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_PLUS, KC_1, KC_2, KC_3,
        KC_NO, KC_NO, KC_NO, KC_EQUAL, KC_0, KC_DOT
),
    [2] = LAYOUT(
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL,
        KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_F11, KC_F12, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_MPRV, KC_MPLY, KC_MNXT, KC_VOLD, KC_MUTE, KC_VOLU,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_U, KC_BTN1, KC_UP, KC_BTN2,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_WH_D, KC_LEFT, KC_DOWN, KC_RGHT,
        KC_NO, KC_NO, KC_NO, KC_LGUI, KC_NO, KC_NO
),
    [4] = LAYOUT(
        KC_NO, QK_BOOT, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),
    [5] = LAYOUT(
        KC_ESC, KC_NO, KC_NO, KC_NO, KC_MYCM, KC_PSCR, KC_NO, KC_NO, KC_NO, KC_DEL,
        KC_NO, KC_NO, KC_NO, KC_ENT, KC_TAB, KC_CAPS, KC_ENT, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO
),
    [6] = LAYOUT(
        KC_TAB, KC_Q, KC_W,  KC_E, KC_R, KC_Y, KC_F1, KC_NO, LGUI(KC_G), KC_ESC,
        KC_LSFT, KC_A, KC_S, KC_D, KC_F, KC_CAPS, KC_F2, KC_NO, KC_MNXT, KC_VOLU,
        KC_LCTL, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_F3, KC_NO, KC_MPLY, KC_VOLD,
        KC_NO, KC_NO, KC_SPC, KC_F3, KC_F2, TG(6)
),
    [7] = LAYOUT(
        RGB_M_P,    RGB_M_B,    RGB_M_R,    RGB_M_TW,    KC_NO,    KC_NO,    UG_VALU,    UG_SATU,    UG_HUEU,    UG_TOGG,
        RGB_M_SW,    RGB_M_SN,    RGB_M_K,    KC_NO,    KC_NO,    KC_NO,    UG_VALD,    UG_SATD,    UG_HUED,    UG_NEXT,
        RGB_M_X,    RGB_M_G,    RGB_M_T,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    UG_PREV,
        TG(7),    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO
)
};