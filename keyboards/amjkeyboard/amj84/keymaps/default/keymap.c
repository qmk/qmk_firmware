// Copyright 2022 peepeetee (@peepeetee)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    /* Keymap 0: Default Layer
     * ,----------------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Home    |Del|
     * |------------------------------------------------------------|---|
     * |`  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp  |PgU|
     * |------------------------------------------------------------|---|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \ |PgD|
     * |------------------------------------------------------------|---|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return   |Ins|
     * |------------------------------------------------------------|---|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift  |Up |Fn0|
     * |------------------------------------------------------------|---|
     * |Ctrl|Win |Alt |       Space        |END|Alt |Ctrl|Left |Down|Rig|
     * `----------------------------------------------------------------'
     */
    [0] = LAYOUT_all(
        KC_ESC, KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_HOME,KC_DEL,
        KC_GRV, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,KC_PGUP,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,KC_PGDN,
        KC_CAPS,KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_NO,  KC_ENT, KC_INS,
        KC_LSFT,KC_NO,  KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,KC_RSFT,KC_UP,  MO(1),
        KC_LCTL,KC_LGUI,KC_LALT,          KC_SPC,           KC_END, KC_NO,  KC_RALT,KC_RCTL,KC_LEFT,KC_DOWN,KC_RIGHT),
    /* Keymap 1: Fn Layer
     * ,-----------------------------------------------------------.
     * |  `| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delete |
     * |-----------------------------------------------------------|
     * |     |   |Up |   |   |   |Cal|   |Ins|   |Psc|Slk|Pau|     |
     * |-----------------------------------------------------------|
     * |      |Lef|Dow|Rig|   |   |   |   |   |   |Hom|PgU|        |
     * |-----------------------------------------------------------|
     * |        |   |App|   |   |   |VoD|VoU|Mut|End|PgD|      |   |
     * |-----------------------------------------------------------|
     * |    |    |    |                        |    |    |    |    |
     * `-----------------------------------------------------------'
     */
    [1] = LAYOUT_all(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_UP,  KC_TRNS,KC_TRNS,KC_TRNS,KC_CALC,KC_TRNS,KC_INS, KC_TRNS,KC_PSCR,KC_SCRL,KC_PAUS,KC_TRNS,KC_TRNS,
        BL_BRTG,KC_LEFT,KC_DOWN,KC_RGHT,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_HOME,KC_PGUP,KC_TRNS,KC_TRNS,KC_TRNS,
        BL_STEP,KC_NO,  KC_TRNS,KC_APP, KC_TRNS,KC_TRNS,KC_TRNS,KC_VOLD,KC_VOLU,KC_MUTE,KC_END, KC_PGDN,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_SLEP,KC_TRNS,KC_TRNS,          KC_TRNS,          KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS)

};
