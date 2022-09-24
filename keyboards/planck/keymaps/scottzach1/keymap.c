// Copyright 2022 Zac Scott (@scottzach1)
// SPDX-License-Identifier: GPL-2.0

#include QMK_KEYBOARD_H

enum planck_layers {
    _COLEMAK,
    _LOWER,
    _RAISE,
    _FUNCTION,
    _DEBUG
};

#define xxxxxxx KC_NO
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define FUNCT MO(_FUNCTION)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Colemak Mod-DH
 * ,-----------------------------------------------------------------------------------------------------------.
 * | Tab    |   Q    |   W    |   F    |   P    |   B    |   J    |   L    |   U    |   Y    |   ;    |  '     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Func   |   A    |   R    |   S    |   T    |   G    |   M    |   N    |   E    |   I    |   O    | Enter  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Shift  |   Z    |   X    |   C    |   D    |   V    |   K    |   H    |   ,    |   .    |   /    |  \     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Ctrl   |  GUI   |  Alt   | Shift  | Space  | Lower  | Raise  | Bkspc  | Shift  |   -    |   =    | Ctrl   |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_COLEMAK] = LAYOUT_ortho_4x12(
    KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT,
    FUNCT,   KC_A,    KC_R,    KC_S,    KC_T,    KC_G,    KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,    KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
    KC_LCTL, KC_LGUI, KC_LALT, KC_LSFT, KC_SPC,  LOWER,   RAISE,   KC_BSPC, KC_RSFT, KC_MINS, KC_EQL,  KC_RCTL
),

/* Lower
 * ,-----------------------------------------------------------------------------------------------------------.
 * | Tab    |        |   {    |   }    |        |        |   `    |   7    |   8    |   9    |   0    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Func   |        |   (    |   )    |        |        |   *    |   4    |   5    |   6    |   -    | Enter  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Shift  |        |   [    |   ]    |        |        |   /    |   1    |   2    |   3    |   +    |   =    |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Ctrl   |  GUI   | Alt    | Shift  | Space  | Lower  | Func   | Bkspc  |   0    |   .    |   =    | Ctrl   |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_ortho_4x12(
    _______, xxxxxxx, KC_LCBR, KC_RCBR, xxxxxxx,  xxxxxxx, KC_GRV,  KC_7,    KC_8,    KC_9,    KC_0,    _______,
    _______, xxxxxxx, KC_LPRN, KC_RPRN, xxxxxxx,  xxxxxxx, KC_ASTR, KC_4,    KC_5,    KC_6,    KC_MINS, _______,
    _______, xxxxxxx, KC_LBRC, KC_RBRC, xxxxxxx,  xxxxxxx, KC_SLSH, KC_1,    KC_2,    KC_3,    KC_PLUS, KC_EQL,
    _______, _______, _______, _______, _______,  _______, FUNCT,   _______, KC_0,    KC_DOT,  _______,  _______
),

/* Raise
 * ,-----------------------------------------------------------------------------------------------------------.
 * | Tab    |        |   {    |   }    |        |        |        | Pg_Up  |  Up    | Pg_Dn  |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Func   |        |   (    |   )    |        |        | Home   | Left   | Down   | Right  |  Del   | Ent er |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Shift  |        |   [    |   ]    |        |        |        |  End   |  Ins   | Caps   |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * | Ctrl   |  GUI   | Alt    | Shift  | Space  | Func   | Raise  | Bkspc  |        |        |        | Ctr l  |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_RAISE] = LAYOUT_ortho_4x12(
    _______, xxxxxxx,  KC_LCBR, KC_RCBR, xxxxxxx,  xxxxxxx, xxxxxxx, KC_PGUP, KC_UP,   KC_PGDN, _______, _______,
    _______, xxxxxxx,  KC_LPRN, KC_RPRN, xxxxxxx,  xxxxxxx, KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, KC_DEL , _______,
    _______, xxxxxxx,  KC_LBRC, KC_RBRC, xxxxxxx,  xxxxxxx, KC_SLSH, KC_END,  KC_INS,  KC_CAPS, xxxxxxx, xxxxxxx,
    _______, _______,  _______, _______, _______,  FUNCT,   _______, _______, _______, _______, _______, _______
),

/* Function
 * ,-----------------------------------------------------------------------------------------------------------.
 * |  Esc   |        | Prev   | Play   | Next   |        |        |  F7    |  F8    |  F9    | F10    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        | Vol-   | Vol+   | Mute   |        |        |  F4    |  F5    |  F6    | F11    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |  F1    |  F2    |  F3    | F12    |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        | Funct  | Funct  |        |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_FUNCTION] = LAYOUT_ortho_4x12(
    KC_ESC,  xxxxxxx, KC_MPRV, KC_MPLY, KC_MNXT, xxxxxxx, xxxxxxx, KC_F7,   KC_F8,   KC_F9,   KC_F10,  xxxxxxx,
    _______, xxxxxxx, KC_VOLD, KC_VOLU, KC_MUTE, xxxxxxx, xxxxxxx, KC_F4,   KC_F5,   KC_F6,   KC_F11,  _______,
    _______, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, KC_F1,   KC_F2,   KC_F3,   KC_F12,  _______,
    _______, _______, _______, _______, _______, DEBUG,   DEBUG,   _______, _______, _______, _______, _______
),

/* Debug
 * ,-----------------------------------------------------------------------------------------------------------.
 * | Reset  | Debug  |        |        |        |        |        |        |        |        |        |  EEP   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |
 * `-----------------------------------------------------------------------------------------------------------'
 */
[_DEBUG] = LAYOUT_ortho_4x12(
    QK_BOOT, DEBUG,   xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, EEP_RST,
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx,
    xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx, xxxxxxx
)
};
