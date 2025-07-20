/* Copyright 2022 Alexander (Sasha) Karmanov 
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

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _QWERTY,
    _CURSORLEFT,
    _CURSORRGHT,
    _NUMBERS,
    _EXTRARIGHT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty                                 
 * ,-----------------------------------------+		+-----------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |		|   Y  |   U  |   I  |   O  |   P  |BSpc  |
 * |------+------+------+------+------+------+		+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |		|   H  |   J  |   K  |   L  |   ;  |Enter |
Hold:
   Extra-Rt 
 * |------+------+------+------+------+------|		|------+------+------+------+------+------|
 * | Ctrl |   Z  |   X  |   C  |   V  |   B  |		|   N  |   M  |   ,  |   .  |   /  |RCtrl |
 * +------+------+------+------+------+------+		+------+------+------+------+------+------+
	     .   |  GUI | Alt  |      |      |		|      |      | RAlt | Menu |   .
	     |   +------+------+      |      |		|      |      +------+------+   |            
Hold:  	     |	               | LSft |CursLt|		|CursRt| RSft |                 |
Single hit:  |		       |      |Space |		|Space |      |                 |
	     |                 +------+------|		|------+------+                 |
	     +------------------------------> SPACE SPACE <-----------------------------+

 */
[_QWERTY] = LAYOUT(
  KC_ESC,                  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,       KC_Y,       KC_U,    KC_I,    KC_O,   KC_P,    KC_BSPC,
  LT(_EXTRARIGHT,KC_TAB),  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,       KC_H,       KC_J,    KC_K,    KC_L,   KC_SCLN, KC_PENT,
  KC_LCTL,                 KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,       KC_N,       KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_RCTL,
      KC_SPC,  KC_LGUI, KC_LALT, KC_LSFT, LT(_CURSORLEFT,KC_SPC), LT(_CURSORRGHT ,KC_SPC), KC_RSFT, KC_RALT, KC_APP, KC_SPC
),


/*

Layers below are used on top of QWERTY layer defined above.
(Except the PLOVER/STENO layers.)
                                           +-------+
The keys which are shown empty, like this: |       |, represent a transparent key,
                                           +-------+
meaning the key from the underlaying layer (i.e. QWERTY) will be used.
In the keymaps those keys are defined as "_______".

                                           +-------+         +-------+
The keys which are shown solid, like this: | XXXXX | or this |  ...  |, represent an opaque/blocking key?
                                           +-------+         +-------+
Such key is not doing anything in that layer nor allowing the key from the underlaying layer
to be invoked.
In the keymaps those keys are defined as "XXXXXXX".

Most of the modifiers are the same in all layers.
So in most layers they are defined as transparent keys,
letting the keys from QWERTY layer to do the work.

With that idea all the layers below leave the unmodified keys as transparent keys.
In the same time - the layers block the keys that have no sense to be used 
in that given layer. For instance in the cursor control layers 
some of the keys are not used in the layer, but they are blocked to avoid
alpha-keys from QWERTY layer to appear.

For the same reason the keymaps below are shown simplified,
without separate thumbcluster.

*/



/* Cursor Control on the right (Right Space)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |Break |WheelD|MousUp|WheelU| Del  |  Ins | Home |  Up  | End  |   `  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |SelAll|MousLt|MousDn|MousRt| ...  | PgUp | Left | Down |Right | ...  |      |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      | Undo | Cut  | Copy | Paste| ...  | PgDn |MsBtLe|MsBtMi|MsBtRt| ...  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |      |   X  |      |      |      |
 *               `-------------------------------------------------------'
 */
[_CURSORRGHT] = LAYOUT(
  _______, KC_BRK,           KC_WH_D,      KC_MS_U,      KC_WH_U,      KC_DEL,              KC_PGUP,  KC_HOME, KC_UP,   KC_END,  KC_GRV,  KC_DEL,
  KC_ENT,  LCTL(KC_A),       KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX,             KC_PGDN,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, _______,
  _______, LCTL(KC_Z),       LSFT(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX,             KC_INS,   KC_BTN1, KC_BTN3, KC_BTN2, XXXXXXX, _______,
	   _______,	     _______,      _______,      _______,      _______,             _______,  _______, _______, _______, _______
),



 /* Cursor Control on the left (Left Space)
 * ,-----------------------------------------------------------------------------------.
 * |      |Break | Home |  Up  | End  |  Ins | Del  |WheelU|MousUp|WheelD|   `  | Del  |
 * |------+------+------+------+------+------+-------------+------+------+------+------|
 * | Enter|SelAll|Right | Down | Left | PgUp | xxx  |MousLt|MousDn|MousRt| xxx  |Enter |
 * |------+------+------+------+------+------+------|------+------+------+------+------|
 * |      | xxx  |MsBtRt|MsBtMi|MsBtLe| PgDn | xxx  | Cut  | Copy | Paste| xxx  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |   X  |      |      |      |      |
 *               `-------------------------------------------------------'
 */
[_CURSORLEFT] = LAYOUT(
  _______, KC_BRK,          KC_HOME, KC_UP,   KC_END,  KC_PGUP,       KC_DEL,  KC_WH_U,      KC_MS_U,      KC_WH_D,      KC_GRV,  KC_DEL,
  KC_ENT,  LCTL(KC_A),      KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,       XXXXXXX, KC_MS_L,      KC_MS_D,      KC_MS_R,      XXXXXXX, _______,
  _______, XXXXXXX,         KC_BTN2, KC_BTN3, KC_BTN1, KC_INS,        XXXXXXX, LCTL(KC_DEL), LCTL(KC_INS), LSFT(KC_INS), XXXXXXX, _______,
	   _______,	    _______, _______, _______, _______,       _______, _______, _______, _______, _______
),


 /* Numbers on the home row, FNs on the top row, symbols in the second row
 * (Lower or Raise)
 * ,-----------------------------------------------------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |BackSp|
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |   F1 |   F2 |   F3 |   F4 |   F5 |   F6 |   F7 |   F8 |   F9 |   F10| Enter|
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |  F11 |  F12 | LAlt |LShift| LAlt | RAlt |RShift|   ,  |   .  |   /  |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |      |      |      |      |      |
 *               `-------------------------------------------------------'
 */
[_NUMBERS] = LAYOUT(
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  LT(_EXTRARIGHT,KC_TAB), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______,
  _______, KC_F11,  KC_F12,  KC_LALT, KC_LSFT, KC_LALT, KC_RALT, KC_RSFT, KC_COMM, KC_DOT,  KC_SLSH, _______,
	   _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______
),

/* ExtraRightSide (the keys from the right side which did not fit into the matrix)
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |BREAK |PLOVR2|PLOVER|TxBOLT|TxBlt2|   `  |   =  |   (  |   )  |   -  |      |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |******|      |      |      |      |      |PrtScr|      |      |      |  '   |      |
   This is the
   key turning
   this layer on
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * |      |      |      |NumPad|Qwerty|      |      |      |   [  |   ]  |  \   |      |
 * `------+------+------+------+------+------+------+------+------+------+------+------.
 *               |      |      |      |      |      |      |      |      |
 *               `-------------------------------------------------------'
 */
[_EXTRARIGHT] = LAYOUT(
  _______, KC_BRK,  XXXXXXX, XXXXXXX,      XXXXXXX, 	 XXXXXXX, 	KC_GRV,  KC_EQL,  KC_LPRN, KC_RPRN, KC_MINS, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       KC_PSCR, XXXXXXX, XXXXXXX, XXXXXXX, KC_QUOT, _______,
  _______, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX,      XXXXXXX,       XXXXXXX, XXXXXXX, KC_LBRC, KC_RBRC, KC_BSLS, _______,
	   _______, _______, _______,      _______,      _______,       _______,  _______, _______, _______, _______
)
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _CURSORLEFT, _CURSORRGHT, _NUMBERS);
}
