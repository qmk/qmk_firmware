 /* Copyright 2020 Ian Sterling 
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

// This is the personal keymap of Ian Sterling (@xyverz). It is based on the keymap by
// Chris Gerber (@gerbercj), with the addition of persistent layers like the Planck and
// Preonic keyboards by Jack Humbert.

#include QMK_KEYBOARD_H

// Xyverz's Keyboardio Atreus keymap

enum layer_names {
  _DVORAK,
  _DVORMAC,
  _LOWER,
  _RAISE,
  _ADJUST
};

enum planck_keycodes {
  DVORAK = SAFE_RANGE,
  DVORMAC,
  LOWER,
  RAISE,
  ADJUST
};

// Adding macros to make the keymaps below much easier to read.
#define SFTSCLN SFT_T(KC_SCLN)
#define SFTSLSH SFT_T(KC_SLSH)
#define SFTZED SFT_T(KC_Z)
#define ALTENT ALT_T(KC_ENT)
#define ESCTRL CTL_T(KC_ESC)
#define TABALT ALT_T(KC_TAB)
#define DELGUI GUI_T(KC_DEL)
#define DELCTL CTL_T(KC_DEL)
#define MACLOCK LGUI(LCTL(KC_Q))
#define WINLOCK LGUI(KC_L)
#define ADJUST MO(_ADJUST)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* Dvorak Layer
	,----------------------------------.              ,----------------------------------.
	|   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |
	|------+------+------+------+------+------.,------+------+------+------+------+------|
	|SFT/ ;|   Q  |   J  |   K  |   X  | Home || End  |   B  |   M  |   W  |   V  |SFT/ Z|
	|------+------+------+------+------+------||------+------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp |DELCTL||ALTENT|  Spc | RAISE|   -  |   /  |   \  |
	`-----------------------------------------'`-----------------------------------------' */
  [_DVORAK] = LAYOUT(
    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L   ,
    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S   ,
    SFTSCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_HOME, KC_END,  KC_B,    KC_M,    KC_W,    KC_V,    SFTZED ,
    ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, DELCTL,  ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_SLSH, KC_BSLS
  ),

  /* Dvorak Layer with Command key on left thumb instead of Control
	,----------------------------------.              ,----------------------------------.
	|   '  |   ,  |   .  |   P  |   Y  |              |   F  |   G  |   C  |   R  |   L  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|   A  |   O  |   E  |   U  |   I  |              |   D  |   H  |   T  |   N  |   S  |
	|------+------+------+------+------+------.,------+------+------+------+------+------|
	|SFT/ ;|   Q  |   J  |   K  |   X  | Home || End  |   B  |   M  |   W  |   V  |SFT/ Z|
	|------+------+------+------+------+------||------+------+------+------+------+------|
	|  Esc |  Tab |  GUI | LOWER| BkSp | LGUI ||ALTENT|  Spc | RAISE|   -  |   /  |   \  |
	`-----------------------------------------'`-----------------------------------------' */
  [_DVORMAC] = LAYOUT(
    KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                      KC_F,    KC_G,    KC_C,    KC_R,    KC_L   ,
    KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                      KC_D,    KC_H,    KC_T,    KC_N,    KC_S   ,
    SFTSCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_HOME, KC_END,  KC_B,    KC_M,    KC_W,    KC_V,    SFTZED ,
    ESCTRL,  TABALT,  KC_LGUI, LOWER,   KC_BSPC, DELGUI,  ALTENT,  KC_SPC,  RAISE,   KC_MINS, KC_SLSH, KC_BSLS
  ),

  /* LOWER Layer
	,----------------------------------.              ,----------------------------------.
	|   !  |   @  |   #  |   $  |   %  |              |   ^  |   &  |   *  |   (  |   )  |
	|------+------+------+------+------|              |------+------+------+------+------|
	| CAPS |      |  UP  |      | Home |              | PgDn |      |   +  |   {  |   }  |
	|------+------+------+------+------+------.,------+------+------+------+------+------|
	|      | Left | Down | Right| End  |MacLck||WinLck| PgUp | Mute | Vol- | Vol+ |      |
	|------+------+------+------+------+------||------+------+------+------+------+------|
	|   ~  |      |      |      | Del  |      ||      | Ins  |      |      |      |      |
	`-----------------------------------------'`-----------------------------------------'*/
  [_LOWER] = LAYOUT(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_CAPS, _______, KC_UP,   _______, KC_HOME,                   KC_PGUP, _______, KC_PLUS, KC_LCBR, KC_RCBR,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  MACLOCK, WINLOCK, KC_PGDN, KC_MUTE, KC_VOLD, KC_VOLU, _______,
    KC_TILD, KC_LEFT, KC_RGHT, _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_UP,   KC_DOWN, _______
  ),

  /* RAISE Layer
	,----------------------------------.              ,----------------------------------.
	|   1  |   2  |   3  |   4  |   5  |              |   6  |   7  |   8  |   9  |   0  |
	|------+------+------+------+------|              |------+------+------+------+------|
	| CAPS |      |  UP  |      | Home |              | PgDn |      |   =  |   [  |   ]  |
	|------+------+------+------+------+------.,------+------+------+------+------+------|
	|      | Left | Down | Right| End  |MacLck||WinLck| PgUp | Prev | Play | Next |      |
	|------+------+------+------+------+------||------+------+------+------+------+------|
	|   `  |      |      |      | Del  |      ||      | Ins  |      |      |      |      |
	`-----------------------------------------'`-----------------------------------------'*/
  [_RAISE] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0   ,
    KC_CAPS, _______, KC_UP,   _______, KC_HOME,                   KC_PGUP, _______, KC_EQL,  KC_LBRC, KC_RBRC,
    _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_END,  MACLOCK, WINLOCK, KC_PGDN, KC_MPRV, KC_MPLY, KC_MNXT, _______,
    KC_GRV,  KC_LEFT, KC_RGHT, _______, KC_DEL,  _______, _______, KC_INS,  _______, KC_UP,   KC_DOWN, _______
  ),

  /* ADJUST Layer
	,----------------------------------.              ,----------------------------------.
	|  F1  |  F2  |  F3  |  F4  |  F5  |              |  F6  |  F7  |  F8  |  F9  | F10  |
	|------+------+------+------+------|              |------+------+------+------+------|
	|  F11 |      |      |DVORAK|DVORMC|              |      | PrSc | ScLk | Paus | F12  |
	|------+------+------+------+------+------.,------+------+------+------+------+------|
	|      |      |      |      |      |      ||      |      |      |      |      |      |
	|------+------+------+------+------+------||------+------+------+------+------+------|
	|      |      |      |      |      |      ||      |      |      |      |      | QK_BOOT|
	`-----------------------------------------'`-----------------------------------------'*/
  [_ADJUST] = LAYOUT(
    KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10 ,
    KC_F11,  _______, DVORAK,  DVORMAC, _______,                   _______, KC_PSCR, KC_SCRL, KC_PAUS, KC_F12 ,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, QK_BOOT  
  ),
};

layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case DVORAK:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORAK);
      }
      return false;
    case DVORMAC:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_DVORMAC);
      }
      return false;
  }
  return true;
}