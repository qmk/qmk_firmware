// Copyright 2022 Josh Hinnebusch (@hineybush), QMK / James Young (@noroadsleft)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
    k00, k10, k01, k11, k02, k12, k03, k13, k04, k14, k05, k15, k06, k16, k17,   k37,     k08, k18, k09, k19, \
    k20, k30, k21, k31, k22, k32, k23, k33, k24, k34, k25, k35, k26,             k57,     k28, k38, k29, k39, \
    k40, k50, k41, k51, k42, k52, k43, k53, k44, k54, k45, k55, k46, k56,                 k48, k58, k49, k59, \
    k60, k70, k61, k71, k62, k72, k63, k73, k64, k74, k65, k75, k66, k76,        k77,     k68, k78, k69, k79, \
    k80, k90, k81,                k83,                k85, k95, k86,        k96, k97, k88,     k98, k89, k99  \ */

    [0] = LAYOUT_iso_all(
        KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_GRV,  KC_BSPC,    KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                      KC_PGDN,    KC_P7,   KC_P8,   KC_P9,   KC_PMNS,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,                          KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT, KC_TRNS,             KC_UP,      KC_P1,   KC_P2,   KC_P3,   KC_TRNS,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_SPC,                             KC_LALT, MO(1),   KC_RGUI,                      KC_LEFT, KC_DOWN, KC_RGHT,    KC_P0,   KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT_iso_all(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_TRNS, KC_TRNS,    KC_PGUP,    KC_NLCK, KC_PSLS, KC_PAST, KC_PAUS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, RESET,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                      KC_PGDN,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_NUHS, KC_TRNS,                         KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,             KC_VOLU,    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_LCTL, KC_LGUI, KC_LALT,                   KC_MPLY,                            KC_LALT, KC_TRNS, KC_RGUI,                      KC_MPRV, KC_VOLD, KC_MNXT,    KC_TRNS, KC_TRNS, KC_TRNS
    )
};
