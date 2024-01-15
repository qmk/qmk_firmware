// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

// MacOS based definitions.
#define K_SPCFN LT(2, KC_SPACE) // Tap for space, hold for symbols layer
#define K_PRVWD LALT(KC_LEFT)      // Previous word
#define K_NXTWD LALT(KC_RIGHT)     // Next word
#define K_LSTRT LGUI(KC_LEFT)      // Start of line
#define K_LEND  LGUI(KC_RIGHT)     // End of line
#define UNDO    LGUI(KC_Z)         // UNDO
#define CUT     LGUI(KC_X)         // CUT
#define COPY    LGUI(KC_C)         // COPY
#define PASTE   LGUI(KC_V)         // PASTE

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
     * │Esc│ ` │ 1 │ 2 │ 3 │ 4 │ 5 │D1 │ 6 │ 7 │ 8 │ 9 │ 0 │ ; │BSp│
     * ├───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┼───┤
     * │Tab│Cap│ Q │ W │ F │ P │ B │Del│ J │ L │ U │ Y │ ' │ [ │ ] │
     * ├───┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴───┤
     * │  M3  │ A │ R │ S │ T │ G │  \  │ M │ N │ E │ I │ O │ Enter│
     * ├─────┬┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬─────┤
     * │Shift│ Z │ X │ C │ D │ V │ - │ = │ K │ H │ , │ . │ / │Shift│
     * ├───┬─┴─┬─┴─┬─┴─┬─┴──┬┴───┼───┼───┼───┴┬──┴─┬─┴─┬─┴─┬─┴─┬───┤
     * │CAP│   │Ctl│Opt│Cmd │ Sp │Ent│Cmd│ Sp │ M2 │ ← │ ↓ │ ↑ │ → │
     * └───┴───┴───┴───┴────┴────┴───┴───┴────┴────┴───┴───┴───┴───┘
     */
    [0] = LAYOUT(
        KC_ESC,  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    DF(1),   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_SCLN,  KC_BSPC,
        KC_TAB,  KC_CAPS, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_DEL,  KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT, KC_LBRC, KC_RBRC,
            MO(3),   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,         KC_BSLS,     KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
            KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_MINS, KC_EQL,  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
            KC_CAPS, KC_LCTL, KC_LCTL, KC_LALT, KC_LGUI, KC_SPACE,KC_ENT,  KC_LGUI, K_SPCFN, MO(2),   KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),
    [1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, DF(0),   _______, _______, KC_PEQL, KC_PSLS, KC_PAST, _______, _______,
        _______, _______, _______, _______, KC_MS_U, _______, _______, _______, _______, KC_P7,   KC_P8,   KC_P9,   KC_PMNS, _______, _______,
            _______, KC_BTN2, KC_MS_L, KC_MS_D, KC_MS_R, _______,      _______,     _______, KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______,
            _______, _______, KC_ACL0, KC_ACL1, KC_ACL2, _______, _______, _______, _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
            _______, _______, _______, _______, _______, KC_BTN1, _______, _______, KC_P0,   _______, KC_PDOT, KC_PENT, _______, _______
    ),
    [2] = LAYOUT(
        QK_BOOT, _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_VOLU, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        _______, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_VOLD, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_DEL, _______,
            _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_MPLY,     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
            _______, KC_PLUS, KC_MINS, KC_EQL,  KC_LCBR, KC_RCBR, KC_MPRV, KC_MNXT, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, KC_BSLS, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    ),
    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, K_PRVWD, KC_UP,   K_NXTWD, _______, _______, _______,
            _______, KC_LGUI, KC_LCTL, KC_LALT, KC_LSFT, _______,      _______,     KC_BSPC, KC_LEFT, KC_DOWN, KC_RIGHT,KC_DEL,  _______,
            _______, UNDO,    CUT,     COPY,    PASTE,   _______, _______, _______, _______, K_LSTRT, _______, K_LEND,  _______, _______,
            _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
    )
};
