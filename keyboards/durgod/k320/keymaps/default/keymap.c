/* Copyright 2021 kuenhlee and Don Kjer
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

// Layer shorthand
enum _layer {
    _BASE,
    _FUNC
};

static bool win_key_locked = false;

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    KC_TGUI = SAFE_RANGE   // Toggle between GUI Lock or Unlock
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Keymap _BASE: Base Layer (Default Layer)
   * ,-----------------------------------------------------------.  ,--------------.
   * |Esc  |f1| f2| f3| f4|  | f5| f6| f7| f8|   | f9|f10|f11|f12|  |Prnt|ScLk|Paus|
   * |-----------------------------------------------------------|  |--------------|
   * | ` | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 |  0| - | = |Backsp |  | Ins|Home|PgUp|
   * |-----------------------------------------------------------|  |--------------|
   * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  | Del| End|PgDn|
   * |-----------------------------------------------------------|  `--------------'
   * |CAPS   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return |
   * |-----------------------------------------------------------|        ,----.
   * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |        | Up |
   * |-----------------------------------------------------------|   ,-------------.
   * |Ctrl|Gui |Alt |      Space            |Alt |Func |App |Ctrl|   |Lft| Dn |Rig |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_BASE] = LAYOUT_tkl_ansi( /* Base Layer */
      KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,             KC_PSCR,  KC_SLCK,  KC_PAUS,
      KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC,  KC_INS,   KC_HOME,  KC_PGUP,
      KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS,  KC_DEL,   KC_END,   KC_PGDN,
      KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,  KC_ENT,
      KC_LSFT,            KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,                      KC_UP,
      KC_LCTL,  KC_LGUI,  KC_LALT,                                KC_SPC,                                 KC_RALT,  MO(_FUNC),KC_APP,   KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
  ),
  /* Keymap _FUNC: Function Layer
   * ,-----------------------------------------------------------.  ,--------------.
   * |   |Play|Stop|Prev|Next| |Mute|Vol+|Vol-|    | |  |  |  |  |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |   |   |   |   |   |   |   |   |   |   |   |   |   |       |  |    |    |    |
   * |-----------------------------------------------------------|  |--------------|
   * |     |   |   |   |   |   |   |   |   |   |   |   |   |     |  |    |    |    |
   * |-----------------------------------------------------------|  `--------------'
   * |       |   |   |   |   |   |   |   |   |   |   |   |       |
   * |-----------------------------------------------------------|        ,----.
   * |        |   |   |   |   |   |   |   |   |   |   |          |        |    |
   * |-----------------------------------------------------------|   ,-------------.
   * |    |Lock|    |                       |    |Func |    |    |   |   |    |    |
   * `-----------------------------------------------------------'   `-------------'
   */
  [_FUNC] = LAYOUT_tkl_ansi( /* Function Layer */
      _______,  KC_MPLY,  KC_MSTP,  KC_MRWD,  KC_MFFD,  KC_MUTE,  KC_VOLD,  KC_VOLU,  _______,  _______,  _______,  _______,  _______,            _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
      _______,            _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                      _______,
      _______,  KC_TGUI,  _______,                                _______,                                _______,  _______,  _______,  _______,  _______,  _______,   _______
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_TGUI:
            if (!record->event.pressed) {
                // Toggle GUI lock on key release
                win_key_locked = !win_key_locked;
                writePin(LED_WIN_LOCK_PIN, !win_key_locked);
            }
            break;
        case KC_LGUI:
            if (win_key_locked) { return false; }
            break;
    }
    return true;
}

