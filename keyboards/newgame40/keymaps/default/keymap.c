/* Copyright 2018 GoTakigawa
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

 
enum layers {
  _QWERTY,
  _COLEMAK,
  _DVORAK,
  _EUCALYN,
  _LOWER,
  _RAISE,
  _ADJUST,
};

 enum custom_keycodes {
   QWERTY = SAFE_RANGE,
   COLEMAK,
   DVORAK,
   LOWER,
   RAISE,
   EUCALYN,
   ADJUST,
 };

 #define LOWER MO(_LOWER)
 #define RAISE MO(_RAISE)

 const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 /* Qwerty
  * ,---------------------------------------------------------------------.
  * |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  |
  * |------+------+------+------+------+------|------+------+------+------|
  * |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   -  |
  * |------+------+------+------+------+------+-------------+------+------|
  * |   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |
  * |-------------+------+------+------+------+------+------+------+------'
  * |Shift |  GUI |Lower | Ctrl |Space | Bksp |Enter |Raise | Left |Right |
  * `---------------------------------------------------------------------'
  */
 [_QWERTY] = LAYOUT_ortho_4x10(
   KC_Q,     KC_W,     KC_E,      KC_R,      KC_T,      KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,
   KC_A,     KC_S,     KC_D,      KC_F,      KC_G,      KC_H,      KC_J,      KC_K,      KC_L,      KC_MINS,
   KC_Z,     KC_X,     KC_C,      KC_V,      KC_B,      KC_N,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,
   KC_LSFT, KC_LGUI, LT(_LOWER,KC_LNG2),  KC_LCTL, KC_SPC,  KC_BSPC, KC_ENT, LT(_RAISE,KC_LNG1),  KC_LEFT, KC_RGHT
 ),

 /* Colemak
  * ,---------------------------------------------------------------------.
  * |   Q  |   W  |   F  |   P  |   G  |   J  |   L  |   U  |   Y  |   -  |
  * |------+------+------+------+------+------|------+------+------+------|
  * |   A  |   R  |   S  |   T  |   D  |   H  |   N  |   E  |   I  |   O  |
  * |------+------+------+------+------+------+-------------+------+------|
  * |   Z  |   X  |   C  |   V  |   B  |   K  |   M  |   ,  |   .  |   /  |
  * |-------------+------+------+------+------+------+------+------+------'
  * |Shift |  GUI |Lower | Ctrl |Space | Bksp |Enter |Raise | Left |Right |
  * `---------------------------------------------------------------------'
  */
 [_COLEMAK] = LAYOUT_ortho_4x10(
   KC_Q,     KC_W,     KC_F,      KC_P,      KC_G,      KC_J,      KC_L,      KC_U,      KC_Y,      KC_MINS,
   KC_A,     KC_R,     KC_S,      KC_T,      KC_D,      KC_H,      KC_N,      KC_E,      KC_I,      KC_O,
   KC_Z,     KC_X,     KC_C,      KC_V,      KC_B,      KC_K,      KC_M,      KC_COMM,   KC_DOT,    KC_SLSH,
   KC_LSFT, KC_LGUI, LT(_LOWER,KC_LNG2),  KC_LCTL, KC_SPC,  KC_BSPC, KC_ENT, LT(_RAISE,KC_LNG1),  KC_LEFT, KC_RGHT
 ),

 /* Dvorak
  * ,---------------------------------------------------------------------.
  * |   "  |   ,  |   .  |   P  |   Y  |   F  |   G  |   C  |   R  |   L  |
  * |------+------+------+------+------+------|------+------+------+------|
  * |   A  |   O  |   E  |   U  |   I  |   D  |   H  |   T  |   N  |   S  |
  * |------+------+------+------+------+------+-------------+------+------|
  * |   ;  |   Q  |   J  |   K  |   X  |   B  |   M  |   W  |   V  |   Z  |
  * |-------------+------+------+------+------+------+------+------+------'
  * |Shift |  GUI |Lower | Ctrl |Space | Bksp |Enter |Raise | Left |Right |
  * `---------------------------------------------------------------------'
  */
 [_DVORAK] = LAYOUT_ortho_4x10(
   KC_QUOT,   KC_COMM,  KC_DOT,    KC_P,      KC_Y,       KC_F,     KC_G,      KC_C,     KC_R,      KC_L,
   KC_A,      KC_O,     KC_E,      KC_U,      KC_I,       KC_D,     KC_H,      KC_T,     KC_N,      KC_S,
   KC_SCLN,   KC_Q,     KC_J,      KC_K,      KC_X,       KC_B,     KC_M,      KC_W,     KC_V,      KC_Z,
   KC_LSFT, KC_LGUI, LT(_LOWER,KC_LNG2),  KC_LCTL, KC_SPC,  KC_BSPC, KC_ENT, LT(_RAISE,KC_LNG1),  KC_LEFT, KC_RGHT
 ),

 /* Lower
  * ,---------------------------------------------------------------------.
  * |  Esc |      |      |      |      |      |      |      |      |      |
  * |------+------+------+------+------+------|------+------+------+------|
  * |      |      |      |      |      |      |      |      |      |      |
  * |------+------+------+------+------+------+-------------+------+------|
  * |  F13 |  F14 |  F15 |  F16 |  F17 |  F18 | F19  | F20  | F21  | F22  |
  * |-------------+------+------+------+------+------+------+------+------'
  * |  F1  | F2   |      | F3   |  F4  |  F5  |  F6  |      |  F7 |   F8  |
  * `---------------------------------------------------------------------'
  */
 [_LOWER] = LAYOUT_ortho_4x10(
   KC_ESC,  _______, _______, _______, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,
   KC_F13,  KC_F14,  KC_F15,  KC_F16,  KC_F17,  KC_F18,  KC_F19,  KC_F20,  KC_F21,  KC_F22,
   KC_F1,   KC_F2,   _______, KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, KC_F7,   KC_F8
 ),

 /* Raise
  * ,---------------------------------------------------------------------.
  * |   1  |   2  |　 3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |
  * |------+------+------+------+------+------|------+------+------+------|
  * |   !  |   "  |   #  |   $  |   %  |   &  |   '  |  (　 |   )  |   _  |
  * |------+------+------+------+------+------+-------------+------+------|
  * |   =  |   ¥  |  {   |   }  |   *  |   ~  |   |  |  <   |   >  |   ?  |
  * |-------------+------+------+------+------+------+------+------+------'
  * |  F1  |  Alt |      |   [  |   ]  |   ;  |   :  |      |   \  |   /  |
  * `---------------------------------------------------------------------'
  */
 [_RAISE] = LAYOUT_ortho_4x10(
   KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
   KC_EXLM, KC_DQT,  KC_HASH, KC_DLR,  KC_PERC, KC_AMPR, KC_QUOT, KC_LPRN, KC_RPRN, KC_UNDS,
   KC_EQL,  KC_INT3, KC_LCBR, KC_RCBR, KC_ASTR, KC_TILD, KC_PIPE, KC_LABK, KC_RABK, KC_QUES,
   KC_F1,   KC_LALT, _______, KC_LBRC, KC_RBRC, KC_SCLN, KC_COLN, _______, KC_BSLS, KC_SLSH
 ),

 /* EUCALYN
  * ,---------------------------------------------------------------------.
  * |   Q  |   W  |   ,  |   .  |   ;  |   M  |   R  |   D  |   Y  |   P  |
  * |------+------+------+------+------+------|------+------+------+------|
  * |   A  |   O  |   E  |   I  |   U  |   G  |   T  |   K  |   S  |   N  |
  * |------+------+------+------+------+------+-------------+------+------|
  * |   Z  |   X  |   C  |   V  |   F  |   B  |   H  |   J  |   L  |   /  |
  * `-------------+------+------+------+------+------+------+-------------'
  * |Shift |  GUI |Lower | Ctrl |Space | Bksp |Enter |Raise | Left |Right |
  * `---------------------------------------------------------------------'
  */
 [_EUCALYN] = LAYOUT_ortho_4x10(
   KC_Q,     KC_W,      KC_COMM,   KC_DOT,    KC_SCLN,     KC_M,     KC_R,     KC_D,     KC_Y,      KC_P,
   KC_A,     KC_O,      KC_E,      KC_I,      KC_U,        KC_G,     KC_T,     KC_K,     KC_S,      KC_N,
   KC_Z,     KC_X,      KC_C,      KC_V,      KC_F,        KC_B,     KC_H,     KC_J,     KC_L,      KC_SLSH,
   KC_LSFT, KC_LGUI, LT(_LOWER,KC_LNG2),  KC_LCTL, KC_SPC,  KC_BSPC, KC_ENT, LT(_RAISE,KC_LNG1),  KC_LEFT, KC_RGHT
 ),

 /* Adjust (Lower + Raise)
  * ,---------------------------------------------------------------------.
  * |      |RGB Tg|RGB Md|Hue Up|Hue Dn|Sat Up|Sat Dn|Val Up|Val Dn|      |
  * |------+------+------+------+------+------.------+------+------+------|
  * |      |      |      |Aud on|Audoff|AGnorm|AGswap|      |BL TOG|BL STP|
  * |------+------+------+------+------+------+------+------+------+------|
  * |Qwerty|Colemk|Dvorak|Eucalyn|     |      |      |      |      |      |
  * |------+------+------+------+------+------+------+------+------+------|
  * |      |      |      |      |      |      |      |      |      |      |
  * `---------------------------------------------------------------------'
  */
 [_ADJUST] =  LAYOUT_ortho_4x10(
   _______,  UG_TOGG, UG_NEXT, UG_HUED, UG_HUEU, UG_SATD, UG_SATU, UG_VALD, UG_VALU, _______,
   _______, _______,  _______,  AU_ON,    AU_OFF, AG_NORM, AG_SWAP, _______, BL_TOGG, BL_STEP,
   QWERTY,  COLEMAK, DVORAK,  EUCALYN, _______, _______, _______, _______, _______, _______,
   _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
 )


 };

 layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
 }

 bool process_record_user(uint16_t keycode, keyrecord_t *record) {
   switch (keycode) {
     case QWERTY:
       if (record->event.pressed) {
         set_single_persistent_default_layer(_QWERTY);
       }
       return false;
       break;
     case COLEMAK:
       if (record->event.pressed) {
         set_single_persistent_default_layer(_COLEMAK);
       }
       return false;
       break;
     case DVORAK:
       if (record->event.pressed) {
         set_single_persistent_default_layer(_DVORAK);
       }
       return false;
       break;
     case EUCALYN:
       if (record->event.pressed) {
         set_single_persistent_default_layer(_EUCALYN);
       }
       return false;
       break;
   }
   return true;
 }
