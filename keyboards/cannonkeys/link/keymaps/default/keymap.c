// Copyright 2025 Andrew Kannan (awkannan)
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {  //Can skip these hard-coded layouts to save space when using only VIA (+700).
/* QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  -   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------|  Mute |    | Play  |------+------+------+------+------+------|
 * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/

[0] = LAYOUT(
  KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,  KC_5,                     KC_6,    KC_7,   KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,  KC_T,                     KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSPC,
  KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,  KC_G,                     KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,  KC_B,   KC_MUTE, KC_MPLY, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
           KC_LGUI, KC_LALT, KC_LCTL, MO(1), KC_ENT,                   KC_SPC,  MO(2),  KC_RCTL, KC_RALT, KC_RGUI
),
/* LAYER 1
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |  |   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   =  |   -  |   +  |   {  |   }  |-------|    |-------|   [  |   ]  |   .  |   :  |   \  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/
[1] = LAYOUT(
  KC_TRNS,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
  KC_GRV,   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,
  KC_WREF,  KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_PIPE,
  KC_TRNS,  KC_EQL,  KC_MINS, KC_PLUS, KC_LCBR, KC_RCBR, KC_TRNS, KC_TRNS, KC_LBRC, KC_RBRC, KC_DOT,  KC_COLN, KC_BSLS, KC_TRNS,
            KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,                   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
),
/* LAYER 2
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    | PREV | HOME |  UP  |  END | INS  | DEL  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| NEXT | LEFT | DOWN | RIGHT|      |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------| CAPS | PGUP |      | PGDN | PSCR |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            |      |      |      |      | /       /       \      \  |      |      |      |      |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
*/
[2] = LAYOUT(
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_MPRV,  KC_HOME,  KC_UP,    KC_END,   KC_INS,  KC_DEL,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_MNXT,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_TRNS, KC_TRNS,
  KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,  KC_TRNS, KC_CAPS,  KC_PGUP,  KC_TRNS,  KC_PGDN,  KC_PSCR, KC_TRNS,
           KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,                    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS
)
};
