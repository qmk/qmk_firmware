// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Layer 0: Base keys
 *
 * ,-----.-----.-----.-----.-----.                      ,-----.-----.-----.-----.-----.
 * | Q   | W   | E   | R   | T   |                      | Y   | U   | I   | O   | P   |
 * |-----+-----+-----+-----+-----|                      |-----+-----+-----+-----+-----|
 * | A   | S   | D   | F   | G   |                      | H   | J   | K   | L   | ; : |
 * |-----+-----+-----+-----+-----+                      |-----+-----+-----+-----+-----|
 * |SHF/Z| X   | C   | V   | B   |                      | N   | M   | < , | > . |SHF/?|
 * `-----'-----'-----'-----'-----'                      `-----'-----'-----'-----'-----'
 *               .-------.-------.-------.      .-------.-------.-------.
 *               |OPT/ESC|  CMD  |CTR/TAB|      | ENTER |L1/SPC |L2/BSP |
 *               '-------'-------'-------'      '-------'-------'-------'
 */

  [0] = LAYOUT(
    KC_Q, KC_W, KC_E, KC_R, KC_T,                                     KC_Y, KC_U, KC_I, KC_O, KC_P,
    KC_A, KC_S, KC_D, KC_F, KC_G,                                     KC_H, KC_J, KC_K, KC_L, KC_SCLN,
    LSFT_T(KC_Z), KC_X, KC_C, KC_V, KC_B,                             KC_N, KC_M, KC_COMM, KC_DOT, RSFT_T(KC_SLSH),
                      LALT_T(KC_ESC), KC_LGUI, LCTL_T(KC_TAB),      KC_ENT, LT(1,KC_SPC), LT(2,KC_BSPC)
  ),

 /* Layer 1: Symbols
 * ,-----.-----.-----.-----.-----.                      ,-----.-----.-----.-----.-----.
 * | 1!  | 2@  | 3#  | 4$  | 5%  |                      | 6^  | 7&  | 8*  | 9(  | 0)  |
 * |-----+-----+-----+-----+-----|                      |-----+-----+-----+-----+-----|
 * | `~  |HOME |PGUP |PGDN | END |                      |LEFT |DOWN | UP  |RGHT | ' " |
 * |-----+-----+-----+-----+-----+                      |-----+-----+-----+-----+-----|
 * |SHFT |     |     |     |     |                      | -_  | =+  | [{  | ]}  |SHF\||
 * `-----'-----'-----'-----'-----'                      `-----'-----'-----'-----'-----'
 *               .-------.-------.-------.      .-------.-------.-------.
 *               |       |       |       |      |       |(hold) |       |
 *               '-------'-------'-------'      '-------'-------'-------'
 */

  [1] = LAYOUT(
    KC_1, KC_2, KC_3, KC_4, KC_5,                          KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_GRV, KC_HOME, KC_PGUP, KC_PGDN, KC_END,             KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_QUOT,
    KC_LSFT, KC_DEL, KC_NO, KC_NO, KC_NO,                  KC_MINS, KC_EQL, KC_LBRC, KC_RBRC, RSFT_T(KC_BSLS),
                      KC_NO, KC_NO, KC_NO,          KC_NO, KC_TRNS, KC_NO
  ),

  /* Layer 2: Function keys
* ,-----.-----.-----.-----.-----.                      ,-----.-----.-----.-----.-----.
* | F1  | F2  | F3  | F4  | F5  |                      | F6  | F7  | F8  | F9  | F10 |
* |-----+-----+-----+-----+-----|                      |-----+-----+-----+-----+-----|
* | F11 | F12 |PREV |PLAY |NEXT |                      |MUTE |Vol- |Vol+ | Br- | Br+ |
* |-----+-----+-----+-----+-----+                      |-----+-----+-----+-----+-----|
* |     |     |     |     |     |                      |     |     |     |     |     |
* `-----'-----'-----'-----'-----'                      `-----'-----'-----'-----'-----'
*               .-------.-------.-------.      .-------.-------.-------.
*               |       |       |       |      |       |       |(hold) |
*               '-----------------------'      '-------'-------'-------'
*/

  [2] = LAYOUT(
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5,                            KC_F6, KC_F7, KC_F8, KC_F9, KC_F10,
    KC_F11, KC_F12, KC_MPRV, KC_MPLY, KC_MNXT,                    KC_MUTE, KC_VOLD, KC_VOLU, KC_BRID, KC_BRIU,
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,                            KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
                            KC_NO, KC_NO, KC_NO,           KC_NO, KC_NO, KC_TRNS
  )
};
