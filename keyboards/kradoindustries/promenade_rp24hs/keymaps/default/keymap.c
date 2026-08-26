// Copyright 2026 Matt F
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H


#define _FN      MO(3)
#define FN_BACK  LT(3, KC_BSPC)
#define ZOOMIN   C(KC_EQL)
#define ZOOMOUT  C(KC_MINS)
#define NTAB     C(KC_TAB)
#define BTAB     C(S(KC_TAB))



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT(

    /* Base Layer


 * .------------------------------------------------------------------------------------------------------------------------------------.
 * | Grave     | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | Backspace |
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |
 * |-----------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------|
 * | Tab       | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | Del       |
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |
 * |-----------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------+-----------------+-----------|
 * | FN_BACK   | A      | S      | D      | F      | G      | [      | ]      | H      | J      | K      | L      | "      | Enter     |
 * |           |        |        |        |        |        |        |        |        |        |        |        | '      |           |
 * |-----------+--------+--------+--------+--------+--------|--------+--------|--------+--------+--------------------------+-----------|
 * | LShift    | Z      | X      | C      | V      | B      | BTab   | NTab   | N      | M      | <      | >      | ?      | RShift    |
 * |           |        |        |        |        |        |        |        |        |        | ,      | .      | /      |           |
 * |-----------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+-----------|
 * | LCTRL     | LGUI   | LALT   | FN     | Space  | Space  | Space  | Space  | Space  | RALT   | Vol-   | Mute   | Vol+   | RCTRL     |
 * |           |        |        |        |        |        |        |        |        |        |        |        |        |           |
 * '-----------------------------------------------------------------------------------------------------------------------------------'
 */

  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  FN_BACK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  SC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    BTAB,    NTAB,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, SC_RSPC,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_VOLD, KC_MUTE, KC_VOLU, KC_RCTL
  ),

  [1] = LAYOUT( /* Layer One */

  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_LBRC, KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_PGUP, KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_VOLD, KC_MUTE, KC_VOLU, KC_RCTL
  ),


  [2] = LAYOUT( /* Layer Two */

  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    ZOOMIN,  KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  FN_BACK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_LBRC, KC_RBRC, KC_H,    KC_J,    KC_K,    KC_L,    KC_QUOT, KC_ENT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    ZOOMOUT, KC_LBRC, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LCTL, KC_LGUI, KC_LALT, _FN,     KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_SPC,  KC_RALT, KC_VOLD, KC_MUTE, KC_VOLU, KC_RCTL
  ),

  [3] = LAYOUT( /* Layer Three */

  KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL,
  _______, KC_HOME, KC_UP,   KC_END,  KC_PGUP, _______, DF(0)  , DF(1)  , _______, _______, _______, _______, KC_PSCR, KC_BSLS,
  _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______, _______, _______, _______, _______, _______, _______, KC_SCLN, KC_QUOT,
  _______, _______, _______, _______, _______, _______, DF(2)  , _______, _______, KC_MUTE, KC_VOLD, KC_VOLU, KC_BSLS, KC_CAPS,
  _______, _______, _______, _______, _______, _______, KC_ENT,  _______, _______, _______, _______, _______, _______, QK_BOOT
  )

};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [0]       = { ENCODER_CCW_CW(C(KC_MINS), C(KC_EQL)),  ENCODER_CCW_CW(C(KC_MINS), C(KC_EQL)),
                  ENCODER_CCW_CW(KC_LEFT, KC_RGHT),       ENCODER_CCW_CW(MS_WHLU, MS_WHLD)},
    [1 ... 3] = { ENCODER_CCW_CW(_______, _______),       ENCODER_CCW_CW(_______, _______),
                  ENCODER_CCW_CW(_______, _______),       ENCODER_CCW_CW(_______, _______)}
};
#endif
