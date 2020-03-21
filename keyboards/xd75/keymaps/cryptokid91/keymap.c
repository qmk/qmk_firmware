/* Copyright 2020 Marco Stålfors
 *
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

// Custom keycodes for longer things
#define MS_LW LT(_LOWER, KC_BSPC)
#define MS_RS LT(_RAISE, KC_DEL)
#define MS_US MT(MOD_RSFT, KC_UP)

// Layer shorthand
enum layer_names {
    _QWERTY,
    _LOWER,
    _RAISE,
    _RESET
};

enum custom_keycodes {
  MS_P00 = SAFE_RANGE,
  NEWTAB,
  ROLL,
  IOTECH,
	TERM
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* SPLIT QWERTY
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | PRTSCR | SLCK   | LOCK   | 6      | 7      | 8      | 9      | 0      | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | E      | R      | T      | NUM7   | NUM8   | NUM9   | Y      | U      | I      | O      | P      | Å      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | LCTRL  | A      | S      | D      | F      | G      | NUM4   | NUM5   | NUM6   | H      | J      | K      | L      | ;      | Ä      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      | NUM1   | NUM2   | NUM3   | N      | M      | <      | >      | UP     | -      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | MENU   | <      | LGUI   | LALT   | LOWER  | SPACE  | NUM00  | NUM0   | NUM.   | ENTER  | RAISE  | RALT   | LEFT   | DOWN   | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

 [_QWERTY] = LAYOUT_ortho_5x15( /* SPLIT QWERTY */
   KC_GESC, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_PSCR, KC_SLCK, KC_LOCK, KC_6,   KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
   KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_P7,   KC_P8,   KC_P9,   KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,
   KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_P4,   KC_P5,   KC_P6,   KC_H,   KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
   KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_N,   KC_M,    KC_COMM, KC_DOT,  MS_US,   KC_SLSH,
   KC_APP,  KC_NUBS, KC_LGUI, KC_LALT, MS_LW,   KC_SPC,  MS_P00,  KC_P0,   KC_PDOT, KC_ENT, MS_RS,   KC_RALT, KC_LEFT, KC_DOWN, KC_RGHT
 ),

/* LOWERED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | GRV    | F1     | F2     | F3     | F4     | F5     | F11    |        | F12    | F6     | F7     | F8     | F9     | F10    | ´      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | PREV   | NEXT   | VOLUP  |        |        | RGBTOG |        | PRTSCR |        | PG_DN  | UP     | PG_UP  |        | ¨      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | PLAY   | STOP   | VOLDWN |        |        | RGBMOD |        | BL+    | HOME   | LEFT   | DOWN   | RIGHT  |        | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        | MUTE   |        |        | DMPLY1 | DMPLY2 | BL-    | END    |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        | NEWTAB |ROLL100 |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_LOWER] = LAYOUT_ortho_5x15( /* LOWERED */
   KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  _______, KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_EQL,
   _______, KC_MPRV, KC_MNXT, KC_VOLU, _______, _______, RGB_TOG, _______, KC_PSCR, _______, KC_PGDN, KC_UP,   KC_PGUP, _______, KC_RBRC,
   _______, KC_MPLY, KC_MSTP, KC_VOLD, _______, _______, RGB_MOD, _______, BL_INC, KC_HOME,  KC_LEFT, KC_DOWN, KC_RGHT, _______, KC_BSLS,
   _______, _______, _______, KC_MUTE, _______, _______, DM_PLY1, DM_PLY2, BL_DEC, KC_END,   _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, NEWTAB,  ROLL,    _______, _______, _______, _______, _______, _______, _______, _______
 ),

/* RAISED
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | GRV    | F1     | F2     | F3     | F4     | F5     | F11    |        | F12    | F6     | F7     | F8     | F9     | F10    | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        | PREV   | NEXT   | VOLUP  |        |TERM    | RGBTOG |        | PRTSCR |        | PG_DN  | UP     | PG_UP  |        | ^      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        | PLAY   | STOP   | VOLDWN |        |        | RGBMOD |        | BL+    | HOME   | LEFT   | DOWN   | RIGHT  |        | *      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        | MUTE   |        |        | DMREC1 | DMREC2 | BL-    | END    |IOTECH  |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        | DMRSTP |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_RAISE] = LAYOUT_ortho_5x15( /* RAISED */
   S(KC_GRV), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  _______, KC_F12,  KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  S(KC_EQL),
   _______,   KC_MPRV, KC_MNXT, KC_VOLU, _______, TERM,    RGB_TOG, _______, KC_PSCR, _______, KC_PGDN, KC_UP,   KC_PGUP, _______, S(KC_RBRC),
   _______,   KC_MPLY, KC_MSTP, KC_VOLD, _______, _______, RGB_MOD, _______, BL_INC,  KC_HOME, KC_LEFT, KC_DOWN, KC_RGHT, _______, S(KC_BSLS),
   _______,   _______, _______, KC_MUTE, _______, _______, DM_REC1, DM_REC2, BL_DEC,  KC_END,  IOTECH,  _______, _______, _______, _______,
   _______,   _______, _______, _______, _______, _______, _______, DM_RSTP, _______, _______, _______, _______, _______, _______, _______
 ),

/* RESET
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |        |        |        |        |        |        | RESET  |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
 
 [_RESET] = LAYOUT_ortho_5x15( /* RESET */
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, RESET,   _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case MS_P00:
    if (record->event.pressed) {
      SEND_STRING("00");
    }
    return false;
  case NEWTAB:
    if(record->event.pressed) {
      SEND_STRING(SS_LCTRL("c") SS_LCTRL("t"));
      wait_ms(100);
      tap_code16(C(KC_V));
      wait_ms(100);
      tap_code(KC_ENT);
    }
    return false;
  case ROLL:
    if(record->event.pressed) {
      SEND_STRING(SS_LSFT("1") "roll 1d100" SS_TAP(X_ENTER));
    }
    return false;
  case IOTECH:
    if(record->event.pressed) {
      SEND_STRING(SS_LCTRL("t"));
      _delay_ms(100);
      SEND_STRING("www.io/tech.fi");
      _delay_ms(100);
      SEND_STRING(SS_TAP(X_ENTER));
    }
    return false;
  case TERM:
    if(record->event.pressed) {
      SEND_STRING(SS_LGUI("r"));
      wait_ms(300);
      SEND_STRING("powershell");
      wait_ms(100);
      SEND_STRING(SS_TAP(X_ENTER));
    }
    return false;
  default:
    return true;
  }
};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _RESET);
}
