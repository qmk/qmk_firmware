/*
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H


// Layer shorthand
enum layer {
  BASE,
  SYMB,
  NUMB,
  ONE_HAND,
  ONE_HAND_ALT,
  _FN,
  _HHKB,
  _7U,
  _2UARROW,
  _625UARROW,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* 1uGrid
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | FN     | LALT   | SPACE  |   Symb  | SPACE  | SPACE  | SPACE  | SPACE  | RIGHT  | DOWN   | UP     | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [BASE] = LAYOUT_ortho_5x14(
  KC_ESC,                KC_1,    KC_2,    KC_3,    KC_4,                  KC_5,              TO(ONE_HAND),     KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  MT(MOD_LALT, KC_TAB),  KC_Q,    KC_W,    KC_E,    KC_R,                  KC_T,              LCTL(LSFT(KC_4)), KC_PGUP, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE, \
  MT(MOD_LGUI, KC_BSPC), KC_A,    KC_S,    KC_D,    KC_F,                  KC_G,              KC_HOME,          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  KC_ENT,                KC_Z,    KC_X,    KC_C,    KC_V,                  KC_B,              LCTL(LSFT(KC_3)), KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
  KC_LEFT,               KC_DOWN, KC_UP,   KC_RGHT, MT(MOD_LCTL, KC_DEL),  LT(SYMB, KC_SPC),  KC_SPC,           LT(NUMB, KC_SPC), KC_SPC,  KC_LSFT, KC_TAB,  KC_UP,   KC_RGHT, KC_RCTL  \
 ),

 [SYMB] = LAYOUT_ortho_5x14(
  KC_ESC,                KC_1,             KC_2,    KC_3,    KC_4,                  KC_5,              TO(ONE_HAND),     KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  TO(ONE_HAND),          KC_EXLM,          KC_AT,   KC_LCBR, KC_RCBR,               KC_PIPE,           LCTL(LSFT(KC_4)), KC_PGUP, KC_AMPR, KC_EQL, LCTL(LSFT(KC_3)), LCTL(LSFT(KC_4)), KC_BSLS, \
  KC_TRNS,               KC_HASH,          KC_DLR,  KC_LPRN, KC_RPRN,               KC_GRV,            KC_HOME,          KC_PGUP, KC_TRNS, KC_PLUS, KC_MINS, KC_SLSH, KC_ASTR, KC_PERC, KC_QUOT,  \
  KC_TRNS,               KC_PERC,          KC_CIRC, KC_LBRC, KC_RBRC,               KC_TILD,              LCTL(LSFT(KC_3)), KC_PGDN, KC_AMPR, KC_EQL,  KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
  KC_LEFT,               KC_DOWN, KC_UP,   KC_RGHT, MT(MOD_LCTL, KC_DEL),  LT(SYMB, KC_SPC),  KC_SPC,           LT(NUMB, KC_SPC), KC_SPC,  KC_LSFT, KC_TAB,  KC_UP,   KC_RGHT, KC_RCTL  \
 ),

 [NUMB] = LAYOUT_ortho_5x14(
  KC_ESC,                KC_1,             KC_2,    KC_3,    KC_4,                  KC_5,              TO(ONE_HAND),     KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  MT(MOD_LALT, KC_TAB),  KC_1, 	           KC_2,    KC_3,    KC_4,                  KC_5,              LCTL(LSFT(KC_4)), KC_RBRC, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_VOLU, \
  MT(MOD_LGUI, KC_BSPC), KC_F1,            KC_F2,   KC_F3,   KC_F4,                 KC_F5,             KC_HOME,          KC_PGUP, KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_VOLD,  \
  KC_ENT,                KC_F6,             KC_F7,   KC_F8,   KC_F9,   KC_F10,              LCTL(LSFT(KC_3)), KC_PGDN, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_MPLY, KC_MNXT, \
  KC_LEFT,               KC_DOWN, KC_UP,   KC_RGHT, MT(MOD_LCTL, KC_DEL),  LT(SYMB, KC_SPC),  KC_SPC,           LT(NUMB, KC_SPC), KC_SPC,  KC_LSFT, KC_TAB,  KC_UP,   KC_RGHT, KC_RCTL  \
 ),

 [ONE_HAND] = LAYOUT_ortho_5x14(
  KC_ESC,                KC_1,             KC_2,    KC_3,    KC_4,                  KC_5,              TO(BASE),     KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  TO(BASE), KC_7, 	  KC_8,    KC_9,    KC_MINS,    KC_SLSH,              LCTL(LSFT(KC_4)), KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE, \
  KC_TRNS, KC_4,   KC_5,   KC_6,   KC_PLUS,   KC_BSLS,              KC_HOME,          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  LT(ONE_HAND_ALT, KC_DEL), KC_1, KC_2, KC_3, KC_DOT,  KC_PIPE,              LCTL(LSFT(KC_3)), KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
  KC_LEFT,               KC_DOWN, KC_UP,   KC_RGHT, KC_0,  LT(SYMB, KC_SPC),  KC_SPC,           LT(NUMB, KC_SPC), KC_SPC,  KC_LSFT, KC_TAB,  KC_UP,   KC_RGHT, KC_RCTL  \
 ),

 [ONE_HAND_ALT] = LAYOUT_ortho_5x14(
  KC_ESC,                KC_1,             KC_2,    KC_3,    KC_4,                  KC_5,              TO(ONE_HAND),     KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  MT(MOD_LALT, KC_TAB),  KC_Q,             KC_W,    KC_E,    KC_R,                  KC_T,              LCTL(LSFT(KC_4)), KC_RBRC, KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_PIPE, \
  MT(MOD_LGUI, KC_BSPC), KC_A,             KC_S,    KC_D,    KC_F,                  KC_G,              KC_HOME,          KC_PGUP, KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,  \
  KC_ENT,                KC_Z,             KC_X,    KC_C,    KC_V,                  KC_B,              LCTL(LSFT(KC_3)), KC_PGDN, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_MINS, \
  KC_LCTL,               LGUI(LCTL(KC_Q)), MO(1),   KC_ESC,  MT(MOD_LCTL, KC_DEL),  LT(SYMB, KC_SPC),  KC_SPC,           LT(NUMB, KC_SPC), KC_SPC,  KC_LSFT, KC_TAB,  KC_UP,   KC_RGHT, KC_RCTL  \
 ),

 /* HHKB
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * |        | LCTRL  | FN     | LALT   | LGUI   |      SPACE      |      SPACE      | LEFT   | DOWN  | UP      | RIGHT  |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [_HHKB] = LAYOUT_ortho_hhkb(
  KC_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
           KC_LCTL, MO(1),   KC_LALT, KC_LGUI,       KC_SPC,         KC_SPC,      KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT           \
 ),

  /* 7u HHKB
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | 6      | 7      | 8      | 9      | 0      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | [      | ]      | Y      | U      | I      | O      | P      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | HOME   | PG UP  | H      | J      | K      | L      | ;      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | END    | PG DN  | N      | M      | ,      | .      | /      | RSHIFT |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * |        | LCTRL  | LALT       |                             SPACE                            | RALT        | FN     |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [_7U] = LAYOUT_ortho_7u(
  KC_ESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    _______, _______, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_BSLS, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    _______, _______, KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    _______, _______, KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______, _______, KC_N,   KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, \
           KC_LCTL, KC_LALT,                                KC_SPC,                                 KC_RALT, MO(1)             \
 ),

 /* 2x2u Space with Arrows
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | "      | ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | SHIFT  | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | FN     | LALT   |      SPACE      |      SPACE      | RALT   | RGUI   | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [_2UARROW] = LAYOUT_2u_arrow(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_QUOT, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSLS, KC_ENT,  KC_PGUP, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
  KC_LCTL, KC_LGUI, MO(1),   KC_LALT,     KC_SPC,          KC_SPC,        KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT \
 ),

  /* 6.25u Space with Arrows
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | 6      | 7      | 8      | 9      | 0      | -      | =      | BACKSP |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | Y      | U      | I      | O      | P      | [      | ]      | \      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | CAP LK | A      | S      | D      | F      | G      | H      | J      | K      | L      | ;      | "      | ENTER  | PG UP  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | N      | M      | ,      | .      | /      | SHIFT  | UP     | PG DN  |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   |                        SPACE                        | FN     | RCTRL  | LEFT   | DOWN   | RIGHT  |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */

 [_625UARROW] = LAYOUT_625u_arrow(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC, \
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_QUOT, \
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_BSLS, KC_ENT,  KC_PGUP, \
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_UP,   KC_PGDN, \
  KC_LCTL, KC_LGUI, KC_LALT,                          KC_SPC,                      MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT \
 ),

/* FUNCTION
 * .-----------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '-----------------------------------------------------------------------------------------------------------------------------'
 */


 [_FN] = LAYOUT_ortho_5x14(
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
rgblight_sethsv(120, 100, 85);
  }
  return true;
}
