 /*Copyright 2017 Wunder
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


/* Keymap by:
 *        _           _               _  _  ____  
 *  _ __ | |__   ___ | |__   ___  ___| || ||___ \
 * | '_ \| '_ \ / _ \| '_ \ / _ \/ __| || |_ __) |
 * | |_) | | | | (_) | |_) | (_) \__ \__   _/ __/ 
 * | .__/|_| |_|\___/|_.__/ \___/|___/  |_||_____|
 * |_|
 */

#include QMK_KEYBOARD_H


enum xd75_layers{
  _QWERTY,
  _DVORAK,
  _LOWER,
  _RAISE,
  _KEEB
};


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  DVORAK,
  LOWER,
  RAISE,
  BSPCDEL,
  HOLDKEEB
};
#define KC_BSDEL BSPCDEL

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* QWERTY
 * .-------------------------------------------------------------------------------------------------------------------------------------.
 * |   `    |    1   |    2   |    3   |    4   |    5   |   6    |    7   |    8   |    9   |   0    | BACKSP|        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------+--------|
 * | TAB    | Q      | W      | E      | R      | T      |  Y     | U      | I      | O      | P      | BACKSP|   7    |  8     | 9      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+-------+--------+--------+--------|
 * | ESC    | A      | S      | D      | F      | G      |  H     | J      | K      | L      | ;      | ENTER |   4    |  5     | 6      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+-------+--------+--------+--------|
 * | LSHIFT | Z      | X      | C      | V      | B      |  N     | M      | ,      | .      | /      |   '   |   1    |  2     | 3      |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-------+--------+--------+--------|
 * | LCTRL  | LGUI   |        | LALT   | LOWER  | SPACE  | SPACE  | RAISE  |  RALT  |        | RGUI   | RCTRL |   0    |  .     | ENTER  |
 * '-------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_QWERTY] = LAYOUT_ortho_5x15( /* QWERTY */
    KC_GRV,  KC_1,    KC_2,  KC_3,       KC_4,    KC_5,     KC_6,    KC_7,    KC_8,    KC_9,   KC_0,    KC_BSPC,  XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  KC_Q,    KC_W,  KC_E,       KC_R,    KC_T,     KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,  KC_7,    KC_8,    KC_9,   
    KC_ESC,  KC_A,    KC_S,  KC_D,       KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_ENT,   KC_4,    KC_5,    KC_6,   
    KC_LSFT, KC_Z,    KC_X,  KC_C,       KC_V,    KC_B,     KC_N,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_QUOT,  KC_1,    KC_2,    KC_3,   
    KC_LCTL, KC_LGUI, KC_NO, KC_LALT,    LOWER,   KC_SPC,   KC_SPC,  RAISE,   KC_RALT, KC_NO,  KC_RGUI, KC_RCTL,  KC_0,    KC_DOT,  KC_ENT
  ),

/* Dvorak
 * .-------------------------------------------------------------------------------------------------------------------------------------.
 * |  `     |    1   |    2   |    3   |    4   |    5   |   6    |    7   |    8   |    9   |   0    | BACKSP|        |        |        |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-------+--------+--------+--------|
 * | Tab    |    "   |    ,   |    .   |    P   |    Y   |   F    |    G   |    C   |    R   |   L    | Bksp  |  7     |   8    |  9     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------+--------|
 * |  Esc   |    A   |    O   |    E   |    U   |    I   |   D    |    H   |    T   |    N   |   S    | Enter |  4     |   5    |  6     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------+--------|
 * | Shift  |    ;   |    Q   |    J   |    K   |    X   |   B    |    M   |    W   |    V   |   Z    |   /   |  1     |   2    |  3     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-------+--------+--------+--------|
 * | Ctrl   |   GUI  |  App   |  Alt   | Lower  | Space  | Space  |  Raise |  nump  |   ALT  |  CAPS  |  Ctrl |  0     |   .    | ENTER  |
 * '-------------------------------------------------------------------------------------------------------------------------------------'
 */
[_DVORAK] = LAYOUT_ortho_5x15(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,   KC_6,    KC_7,    KC_8,      KC_9,    KC_0,    KC_BSPC, XXXXXXX, XXXXXXX, XXXXXXX,
    KC_TAB,  KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,   KC_F,    KC_G,    KC_C,      KC_R,    KC_L,    KC_BSPC, KC_7,    KC_8,    KC_9,   
    KC_ESC,  KC_A,    KC_O,    KC_E,    KC_U,    KC_I,   KC_D,    KC_H,    KC_T,      KC_N,    KC_S,    KC_ENT,  KC_4,    KC_5,    KC_6,   
    KC_LSFT, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,   KC_B,    KC_M,    KC_W,      KC_V,    KC_Z,    KC_SLSH, KC_1,    KC_2,    KC_3,   
    KC_LCTL, KC_LGUI, KC_NO,   KC_LALT, LOWER,   KC_SPC, KC_SPC,  RAISE,   KC_RALT,   KC_NO,   KC_RGUI, KC_RCTL, KC_0,    KC_DOT,  KC_ENT
 
),

 /* LOWER
  * .--------------------------------------------------------------------------------------------------------------------------------------.
  * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | NUM LK | P/     | P*     |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * | PR SCR |   !    |   @    |    #   |    $   |   %    |    ^   |    &   |    *   |    (   |    )   |  F12   | P7     | P8     | P9     |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |        |  PLAY  |  VOL-  | BACKSP | DELETE |        |    +   |   -    |   [    |   ]    |   ~    | P4     | P5     | P6     |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |        |  PAUSE |  APP   | MYCOMP |        |        |    =   |   _    |   |    |   \    |   `    | P1     | P2     | P3     |
  * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
  * |        |        |        |        |        |        |        |        |        |        |        |        |        |        |        |
  * '--------------------------------------------------------------------------------------------------------------------------------------'
  */
     [_LOWER] = LAYOUT_ortho_5x15( /* FUNCTION */
      _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,     KC_F5,   KC_F6,    KC_F7,     KC_F8,      KC_F9,    KC_F10,   KC_F11,  _______, _______, _______, 
      KC_PSCR, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,    KC_PERC, KC_CIRC,  KC_AMPR,   KC_ASTR,    KC_LPRN,  KC_RPRN,  KC_F12,  _______, _______, _______, 
      _______, _______, KC_MPLY, KC_VOLD, KC_BSPC,   KC_DEL,  _______,  S(KC_EQL), KC_MINS,	   KC_LBRC,  KC_RBRC,  KC_TILD, _______, _______, _______, 
      _______, _______, KC_PAUS, KC_APP,  KC_MYCM,   _______, KC_PLUS,  KC_EQL,    S(KC_MINS), KC_PIPE,  KC_BSLS,  KC_GRV,  _______, _______, _______, 
      _______, _______, _______, _______, _______,   _______, _______,  _______,   _______,    _______,  _______,  _______, _______, _______, _______
    ),  

/* RAISE
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * |        | F1     | F2     | F3     | F4     | F5     | F6     | F7     | F8     | F9     | F10    | F11    | NUM LK | P/     | P*     | 
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        | !      | @      | #      | $      | %      | ^      | &      | *      | (      | )      | F12    | P7     | P8     | P9     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | +      |        |        |        |        |        | P4     | P5     | P6     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        | PENT   |        |        |        |        |        | P1     | P2     | P3     |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------|
 * |        |        |        |        |        |        |        |        |  Vol-  |  Vol+  | MUTE   |        |        |        |        |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */
  [_RAISE] = LAYOUT_ortho_5x15( /* FUNCTION */
    _______, KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,   KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  _______, _______, _______,
    _______, KC_1,   KC_2,     KC_3,     KC_4,     KC_5,    KC_6,     KC_7,    KC_8,    KC_9,    KC_0,    KC_F12,  _______, _______, _______,
    KC_CAPS, _______,_______,  _______,  _______,  _______, KC_LEFT,  KC_DOWN, KC_UP,   KC_RGHT, _______, _______, _______, _______, _______,
    _______, _______,_______,  _______,  _______,  _______, _______,  KC_PGDN, KC_PGUP, _______, _______, _______, _______, _______, _______,
    _______, _______,_______,  _______,  _______,  _______, _______,_______,   KC_VOLD, KC_VOLU, KC_MUTE, _______, _______, _______, _______
  ),


 // RGB_HUD, RGB_HUI
 // RGB_SAD, RGB_SAI
 // RGB_VAD, RGB_VAI
 // RGB_RMOD,RGB_MOD
[_KEEB] = LAYOUT_ortho_5x15( /* NUM */
  QK_BOOT, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RGB_SAD, RGB_SAI, _______, _______, _______, _______, _______, QWERTY,  DVORAK,  _______, _______, _______, _______, _______, _______,
  RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
  RGB_RMOD,RGB_MOD, RGB_TOG, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
)
};


unsigned int layer_state_set_user(unsigned int state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _KEEB);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  static bool bsdel_mods = false;
  switch (keycode) {
    
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
    break;
    case DVORAK:
      if (record -> event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    break;    

    case BSPCDEL:
      if (record -> event.pressed){ // KC_BKSP pressed
        if (get_mods() & MOD_BIT(KC_LSFT)) { // KC_LSFT is pressed
          unregister_code(KC_LSFT);
          register_code(KC_DEL);
          bsdel_mods = true;
        }else{ // KC_LSFT not pressed
            register_code(KC_BSPC);
          }
      } else {// KC_BKSP released
          if (bsdel_mods) {
            unregister_code(KC_DEL);
            register_code(KC_LSFT);
            bsdel_mods = false;
          } else {
            unregister_code(KC_BSPC);
          }
      }
      return false;
    break;
  }
  return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}
