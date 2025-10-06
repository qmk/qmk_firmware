// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


// ┌─────┬────┬────┬────┬────┬────┐                    ┌────┬────┬────┬────┬────┬─────┐
// │ ESC │ 1  │ 2  │ 3  │ 4  │ 5  │                    │ 6  │ 7  │ 8  │ 9  │ 0  │ BSPC│
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │ TAB │ Q  │ W  │ E  │ R  │ T  │                    │ Y  │ U  │ I  │ O  │ P  │ BSLS│
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │LSFT │ A  │ S  │ D  │ F  │ G  │                    │ H  │ J  │ K  │ L  │QUOT│ ENT │
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │LCTL │ Z  │ X  │ C  │ V  │ B  │                    │ N  │ M  │COMM│DOT │SLSH│RSFT │
// └─────┴────┴────┴────┴────┴────┘                    └────┴────┴────┴────┴────┴─────┘
//          ┌─────┬─────┬─────┬────┐                   ┌─────┬─────┬─────┬─────┐
//          │ LGUI│MO(1)│ SPC │LALT│                   │LEFT │DOWN │ UP  │RIGHT│
//          └─────┴─────┴─────┴────┘                   └─────┴─────┴─────┴─────┘
//
//
// ┌─────┬────┬────┬────┬────┬────┐                    ┌────┬────┬────┬────┬────┬─────┐
// │ GRV │ F1 │ F2 │ F3 │ F4 │ F5 │                    │ F6 │ F7 │ F8 │ F9 │ F10│ DEL │
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │CAPS │NO  │NO  │NO  │NO  │NO  │                    │MINS│ EQL│LBRC│RBRC│ F11│ F12 │
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │LSFT │NO  │NO  │NO  │NO  │NO  │                    │ NO │ NO │ NO │ NO │SCLN│ NO  │
// ├─────┼────┼────┼────┼────┼────┤                    ├────┼────┼────┼────┼────┼─────┤
// │LCTL │NO  │NO  │NO  │NO  │NO  │                    │ NO │ NO │ NO │ NO │ NO │RSFT │
// └─────┴────┴────┴────┴────┴────┘                    └────┴────┴────┴────┴────┴─────┘
//             ┌────┬────┬────┬────┐                   ┌────┬────┬────┬────┐
//             │ NO │ NO │ NO │LALT│                   │HOME│PGDN│PGUP│ END│
//             └────┴────┴────┴────┘                   └────┴────┴────┴────┘
                           

    [0] = LAYOUT_split_4x6_4(
  KC_ESC,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                           KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,   KC_Q,   KC_W,    KC_E,    KC_R,    KC_T,                           KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_LSFT,  KC_A,   KC_S,    KC_D,    KC_F,    KC_G,                           KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  KC_LCTL,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,                           KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
                    KC_LGUI, MO(1),   KC_SPC,  KC_LALT,                        KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT
    ),
    [1] = LAYOUT_split_4x6_4(
  KC_GRV,   KC_F1,   KC_F2,    KC_F3,    KC_F4,    KC_F5,                           KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_DEL,
  KC_CAPS,  KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,                           KC_MINS,  KC_EQL,   KC_LBRC,  KC_RBRC,  KC_F11,    KC_F12,
  KC_LSFT,  KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,                           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_SCLN,   KC_NO,
  KC_LCTL,  KC_NO,   KC_NO,    KC_NO,    KC_NO,    KC_NO,                           KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,     KC_RSFT,
                     KC_NO,    KC_TRNS,    KC_NO,    KC_LALT,                         KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END
    )
};
