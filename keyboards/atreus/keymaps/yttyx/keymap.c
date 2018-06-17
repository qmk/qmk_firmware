/* Copyright 2018 yttyx 
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
 *
 */
 
#include QMK_KEYBOARD_H

enum layers {
  _BLNC12,      // Balance Twelve (mirror variant)  default
  _NUMPUN,      // Numeric/Punctuation              momentary
  _PUNCUR,      // Punctuation/Cursor               momentary
  _FUNVIM,      // Function/Vim                     toggle
  _MOUSE,       // Mouse control                    toggle
  _RESET        // Reset                            momentary
};

#define xxxxxx    KC_NO
#define ______    KC_TRNS


const uint16_t PROGMEM keymaps[][ MATRIX_ROWS ][ MATRIX_COLS ] = {

 /* ---- Balance Twelve mirror variant (left-handed) ------------------------------------------------------------------------
  
  .--------------------------------------.             .-------------------------------------.
  | P    | L    | C    | D       | W     |             | U    | O       | Y    | K    | Q    |
  |------+------+------+---------+-------|             |------+---------+------+------+------|
  | N    | R    | S    | T       | M     |             | A    | E       | I    | H    | V    |
  |------+------+------+---------+-------|             |------+---------+------+------+------|
  | Z    | J    | F    | G       | B     |             | ,    | .       | ;    | X    | -    |
  |------+------+------+---------+-------+-------------+------+---------+------+------+------|
  | LSft | LCtl | LWin | _PUNCUR | Space | Tab | Enter | BSpc | _NUMPUN | LAlt | RCtl | RSft |
  '------------------------------------------------------------------------------------------'
  */
  [_BLNC12] = LAYOUT(
    KC_P,    KC_L,    KC_C,    KC_D,        KC_W,                   KC_U,    KC_O,        KC_Y,    KC_K,    KC_Q,
    KC_N,    KC_R,    KC_S,    KC_T,        KC_M,                   KC_A,    KC_E,        KC_I,    KC_H,    KC_V,
    KC_Z,    KC_J,    KC_F,    KC_G,        KC_B,                   KC_COMM, KC_DOT,      KC_SCLN, KC_X,    KC_MINS,
    KC_LSFT, KC_LCTL, KC_LWIN, MO(_PUNCUR), KC_SPC, KC_TAB, KC_ENT, KC_BSPC, MO(_NUMPUN), KC_LALT, KC_RCTL, KC_RSFT
   ),

 /* ---- Numeric/punctuation - right thumb ----------------------------------------------------------------------------------
  
  .-------------------------------------.                .------------------------------------.
  | '    | "    | !    | ?    | *       |                | (    | )      | [    | ]    | #    |
  |------+------+------+------+---------|                |------+--------+------+------+------|
  | 1    | 2    | 3    | 4    | 5       |                | 6    | 7      | 8    | 9    | 0    |
  |------+------+------+------+---------|                |------+--------+------+------+------|
  | $    | £    | /    | \    |         |                | ,    | .      | ;    |      | -    |
  |------+------+------+------+---------+----------------+------+--------+------+------+------|
  | LSft | LCtl | LWin |      | _FUNVIM | _MOUSE | Enter | BSpc |        | LAlt | RCtl | RSft |
  '-------------------------------------------------------------------------------------------'
  */
  [_NUMPUN] = LAYOUT(
    KC_QUOT, LSFT(KC_2), KC_EXLM, KC_QUES, KC_ASTR,                         KC_LPRN, KC_RPRN, KC_LBRC, KC_RBRC, KC_NUHS,
    KC_1,    KC_2,       KC_3,    KC_4,    KC_5,                            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    KC_DLR,  KC_HASH,    KC_SLSH, KC_NUBS, xxxxxx,                          ______,  ______,  ______,  xxxxxx,  ______,
    ______,  ______,     ______,  xxxxxx,  TG(_FUNVIM), TG(_MOUSE), ______, ______,  ______,  ______,  ______,  ______
  ),

 /* ---- Punctuation/cursor control - left thumb ----------------------------------------------------------------------------
  
  .----------------------------------.              .------------------------------------.
  | `    | ~    | =    | +    | |    |              | {    | }    | <     | >    | &     |
  |------+------+------+------+------|              |------+------+-------+------+-------|
  | Esc  |      | ^    | @    | Ins  |              | Home | Up   | End   | PgUp |       |
  |------+------+------+------+------|              |------+------+-------+------+-------|
  |      |      | PScr | SLck | Caps |              | Left | Down | Right | PgDn |       |
  |------+------+------+------+------+--------------+------+------+-------+------+-------|
  | LSft | LCtl | LWin |      |      | Tab  | Enter | Del  |      | LAlt  | RCtl | RSft  |
  '--------------------------------------------------------------------------------------'
  */
  [_PUNCUR] = LAYOUT(
    KC_GRV,  KC_PIPE, KC_EQL,  KC_PLUS,       LSFT(KC_NUBS),                 KC_LCBR, KC_RCBR, KC_LABK,  KC_RABK,   KC_AMPR,
    KC_ESC,  xxxxxx,  KC_CIRC, LSFT(KC_QUOT), KC_INS,                        KC_HOME, KC_UP,   KC_END,   KC_PGUP,   xxxxxx,
    xxxxxx,  xxxxxx,  KC_PSCR, KC_SLCK,       KC_CAPS,                       KC_LEFT, KC_DOWN, KC_RIGHT, KC_PGDOWN, xxxxxx,
    ______,  ______,  ______,  ______,        ______,        ______, ______, KC_DEL,  xxxxxx,  ______,   ______,    ______
  ),

 /* ---- Function/Vim -------------------------------------------------------------------------------------------------------

  .-------------------------------------.                 .-------------------------------------.
  | F1   | F2   | F3   | F4    | F5     |                 | F6    | F7   | F8    | F9    | F10  |
  |------+------+------+-------+--------|                 |-------+------+-------+-------+------|
  | F11  | F12  |      |       |        |                 | Start | Up   | End   | PgUp  |      |
  |------+------+------+-------+--------|                 |-------+------+-------+-------+------|
  |      |      |      |       |        |                 | Left  | Down | Right | PgDn  |      |
  |------+------+------+-------+--------+-----------------+-------+------+-------+-------+------|
  | LSft | LCtl | LWin |       | Space  | _BLNC12 | Enter | BSpc  |      | LAlt  | RCtl  | RSft |
  '---------------------------------------------------------------------------------------------'
  */
  [_FUNVIM] = LAYOUT(
    KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,                       KC_F6,  KC_F7,  KC_F8,  KC_F9,      KC_F10,
    KC_F11, KC_F12, xxxxxx, xxxxxx, xxxxxx,                      KC_0,   KC_K,   KC_DLR, LCTL(KC_B), xxxxxx,
    xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx,                      KC_H,   KC_J,   KC_L,   LCTL(KC_F), xxxxxx,
    ______, ______, ______, xxxxxx, ______, TO(_BLNC12), ______, ______, xxxxxx, ______, ______,     ______
  ),

 /* ---- Mouse cursor -------------------------------------------------------------------------------------------------------
  
  .-----------------------------------------.                 .------------------------------------------.
  | Accel0 | Accel1 | Accel2 |       |      |                 |       |      |        |           |      |
  |--------+--------+--------+-------+------|                 |-------+------+--------+-----------+------|
  | Esc    |        |        |       |      |                 |       | Up   |        | WheelUp   |      |
  |--------+--------+--------+-------+------|                 |-------+------+--------+-----------+------|
  |        |        |        |       |      |                 | Left  | Down |  Right | WheelDown |      |
  |--------+--------+--------+-------+------+-----------------+-------+------+--------+-----------+------|
  | _RESET |        |        |       | Btn1 | _BLNC12 |       | Btn2  | Btn3 |        |           |      |
  '------------------------------------------------------------------------------------------------------'
  */
  [_MOUSE] = LAYOUT(
    KC_MS_ACCEL0, KC_MS_ACCEL1, KC_MS_ACCEL2, xxxxxx, xxxxxx,                       xxxxxx,  xxxxxx,  xxxxxx,  xxxxxx,        xxxxxx,
    KC_ESC,       xxxxxx,       xxxxxx,       xxxxxx, xxxxxx,                       xxxxxx,  KC_MS_U, xxxxxx,  KC_MS_WH_UP,   xxxxxx,
    xxxxxx,       xxxxxx,       xxxxxx,       xxxxxx, xxxxxx,                       KC_MS_L, KC_MS_D, KC_MS_R, KC_MS_WH_DOWN, xxxxxx,
    MO(_RESET),   xxxxxx,       xxxxxx,       xxxxxx, KC_BTN1, TO(_BLNC12), ______, KC_BTN2, KC_BTN3, xxxxxx,  xxxxxx,        xxxxxx
  ),

 /* ---- Reset - in its own layer to reduce the chance of accidentally selecting it -----------------------------------------
  
  .----------------------------------------.                .------------------------------------.
  |       |        |        |       |      |                |       |      |      |      | RESET |
  |-------+--------+--------+-------+------|                |-------+------+------+------+-------|
  |       |        |        |       |      |                |       |      |      |      |       |
  |-------+--------+--------+-------+------|                |-------+------+------+------+-------|
  |       |        |        |       |      |                |       |      |      |      |       |
  |-------+--------+--------+-------+------+----------------+-------+------+------+------+-------|
  |       |        |        |       |      |        |       |       |      |      |      |       |
  '----------------------------------------------------------------------------------------------'
  */
  [_RESET] = LAYOUT(
    xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx,                 xxxxxx,  xxxxxx,  xxxxxx,  xxxxxx, RESET,
    xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx,                 xxxxxx,  xxxxxx,  xxxxxx,  xxxxxx, xxxxxx,
    xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx,                 xxxxxx,  xxxxxx,  xxxxxx,  xxxxxx, xxxxxx,
    ______, xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx, xxxxxx,  xxxxxx,  xxxxxx,  xxxxxx, xxxxxx
  )

};

const uint16_t PROGMEM fn_actions[] = {};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
}

