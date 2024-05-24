// Copyright 2024 Sinisha Stojchevski (@sini6a)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┐             ┌───┬───┬───┬───┬───┬───┐
     * │   │ 1 │ 2 │ 3 │ 4 │ 5 │             │ 6 │ 7 │ 8 │ 9 │ 0 │   │
     * ├───┼───┼───┼───┼───┼───│             ├───┼───┼───┼───┴───┴───│
     * │   │ Q │ W │ E │ R │ T │             │ Y │ U │ I │ O │ P │   │
     * ├───┼───┼───┼───┼───┼───│             ├───┼───┼───┼───┴───┴───│
     * │   │ A │ S │ D │ F │ G │             │ H │ J │ K │ L │ ; │   │
     * ├───┼───┼───┼───┼───┼───│             ├───┼───┼───┼───┼───┼───│
     * │   │ Z │ X │ C │ V │ B │             │ N │ M │ , │ . │ / │   │
     * └───┴───┴───┴───┼───┼───┼───┐     ┌───┼───┼───┼───┴───┴───┴───┘
     *                 │   │   │   │     │   │   │   │
     *                 └───┴───┴───┘     └───┴───┴───┘
     */
    [0] = LAYOUT( // base layer
         KC_TILDE,      KC_1,   KC_2,   KC_3,   KC_4,   KC_5,         KC_6,   KC_7,   KC_8,   KC_9,   KC_0,    KC_PSCR,
        KC_LPRN,         KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,         KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,             KC_RPRN,
        KC_LT,  LGUI_T(KC_A),   LALT_T(KC_S),   LCTL_T(KC_D),   LSFT_T(KC_F),   KC_G,         KC_H,   RSFT_T(KC_J),   RCTL_T(KC_K),   ALGR_T(KC_L),   RGUI_T(KC_SEMICOLON),     KC_GT,
        KC_LCBR,   KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,         KC_N,   KC_M,   KC_COMMA,   KC_DOT,   KC_SLSH,    KC_RCBR,
                                   LT(5, KC_ESCAPE), LT(1, KC_SPC), LT(6, KC_TAB),         LT(4, KC_ENTER), LT(3, KC_BACKSPACE), LT(2, KC_DELETE)
    ),
    [1] = LAYOUT( // nav layer
        KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_AGIN,   KC_PASTE,   KC_COPY,   KC_CUT,   KC_UNDO,             KC_NO,
        KC_NO,  KC_LGUI,   KC_LALT,   KC_LCTL,   KC_LSFT,   KC_NO,         KC_CAPS,   KC_LEFT,   KC_DOWN,   KC_UP,   KC_RIGHT,     KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_INS,   KC_HOME,   KC_PAGE_DOWN,   KC_PAGE_UP,   KC_END,    KC_NO,
                                   KC_NO, KC_TRNS, KC_NO,         KC_ENTER, KC_BACKSPACE, KC_DELETE
    ),
    [2] = LAYOUT( // function layer
        QK_BOOT,      KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,             KC_NO,
        KC_NO,     KC_F12,   KC_F7,   KC_F8,   KC_F9,   KC_PSCR,         KC_NO,   KC_NO,   KC_NO,   KC_F11,   KC_F12,             KC_NO,
        KC_NO,     KC_F11,   KC_F4,   KC_F5,   KC_F6,   KC_SCRL,         KC_NO,   KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI,     KC_NO,
        KC_NO,     KC_F10,   KC_F1,   KC_F2,   KC_F3,   KC_PAUS,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
                                         KC_APP, KC_SPC, KC_TAB,         KC_NO, KC_NO, KC_TRNS
    ),
    [3] = LAYOUT( // number layer
        KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,     KC_LBRC,   KC_7,   KC_8,   KC_9,   KC_RCBR,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,     KC_SCLN,   KC_4,   KC_5,   KC_6,   KC_EQL,         KC_NO,   KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI,     KC_NO,
        KC_NO,     KC_COMM,   KC_1,   KC_2,   KC_3,   KC_BSLS,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
                                         KC_DOT, KC_0, KC_MINUS,         KC_NO, KC_TRNS, KC_NO
    ),
    [4] = LAYOUT( // symbol layer
        KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,     KC_LCBR,   KC_AMPR,   KC_ASTR,   KC_LPRN,   KC_RCBR,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,     KC_COLN,   KC_DLR,   KC_PERC,   KC_CIRC,   KC_PLUS,         KC_NO,   KC_RSFT,   KC_RCTL,   KC_RALT,   KC_RGUI,     KC_NO,
        KC_NO,     KC_TILD,   KC_EXLM,   KC_AT,   KC_HASH,   KC_PIPE,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,
                                         KC_LPRN, KC_RPRN, KC_UNDS,         KC_TRNS, KC_NO, KC_NO
    ),
    [5] = LAYOUT( // media layer
        KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         RGB_TOG,   RGB_MOD,   RGB_HUI,   RGB_SAI,   RGB_VAI,             KC_NO,
        KC_NO,     KC_LGUI,   KC_LALT,   KC_LCTL,   KC_LSFT,   KC_NO,         KC_NO,   KC_MPRV,   KC_VOLD,   KC_VOLU,   KC_MNXT,     KC_NO,
        KC_NO,     KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
                                         KC_TRNS, KC_NO, KC_NO,         KC_MSTP, KC_MPLY, KC_MUTE
    ),
    [6] = LAYOUT( // mouse layer
        KC_NO,      KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,             KC_NO,
        KC_NO,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_AGIN,   KC_PASTE,   KC_COPY,   KC_CUT,   KC_UNDO,             KC_NO,
        KC_NO,  KC_LGUI,   KC_LALT,   KC_LCTL,   KC_LSFT,   KC_NO,         KC_NO,   KC_MS_L,   KC_MS_D,   KC_MS_U,   KC_MS_R,     KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_NO,   KC_WH_L,   KC_WH_D,   KC_WH_U,   KC_WH_R,    KC_NO,
                                   KC_NO, KC_NO, KC_TRNS,         KC_BTN2, KC_BTN1, KC_BTN3
    )
};