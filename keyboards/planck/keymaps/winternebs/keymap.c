/* Copyright 2015-2017 Jack Humbert
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


enum planck_layers {
  _QWERTY,
  _WORKMAN,
  _LOWER,
  _ADJUST,
};

enum planck_keycodes {
  QWERTY = SAFE_RANGE,
  WORKMAN,
  LOWER,
};

#define ADJUST MO(_ADJUST)
//#define LOWER MO(_LOWER)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |      | Alt  |Lower |Space |Space |Adjust|      | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_planck_grid(
    KC_ESC,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSPC,
    KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT ,
    KC_LCTL, KC_LGUI, _______, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  ADJUST,  _______, KC_LEFT, KC_DOWN, KC_RGHT
),
/* Workman
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   Q  |   D  |   R  |   W  |   B  |   J  |   F  |   U  |   P  |   ;  | Bksp |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | Tab  |   A  |   S  |   H  |   T  |   G  |   Y  |   N  |   E  |   O  |   I  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   M  |   C  |   V  |   K  |   L  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | GUI  |      | Alt  |Lower |Space | Bksp |Adjust|      | Left | Down |Right |
 * `-----------------------------------------------------------------------------------'
 */
[_WORKMAN] = LAYOUT_planck_grid(
  KC_ESC,  KC_Q,    KC_D,    KC_R,    KC_W,    KC_B,    KC_J,    KC_F,    KC_U,    KC_P,    KC_SCLN, KC_BSPC, 
  KC_TAB,  KC_A,    KC_S,    KC_H,    KC_T,    KC_G,    KC_Y,    KC_N,    KC_E,    KC_O,    KC_I,	 KC_QUOT, 
  KC_LSFT, KC_Z,    KC_X,    KC_M,    KC_C,    KC_V,    KC_K,    KC_L,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT , 
  KC_LCTL, KC_LGUI, _______, KC_LALT, LOWER,   KC_SPC,  KC_BSPC, ADJUST,  _______, KC_LEFT, KC_DOWN, KC_RGHT 
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |   `  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Del  |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |   -  |   =  |   [  |   ]  |  \   |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |  F7  |  F8  |  F9  |  F10 |  F11 |  F12 |      |      |Pg Up |  UP  |Pg Dn |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |PrScr |      |      |             |      |      |      |      |      |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_planck_grid(
    KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______ ,
    KC_DEL,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_MINS, KC_EQL,  KC_LBRC, KC_RBRC, KC_BSLS,
    _______, KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, _______, KC_PGUP, KC_UP,   KC_PGDN,
    _______, _______, KC_PSCR, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

/* Adjust (Lower + Raise)
 * ,-----------------------------------------------------------------------------------
 * |RESET |DEBUG|       |Aud on|Audoff|      |      |      |      |      |      |Reset |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |QWERTY|WORKMAN|      |      | Help |      |      |      |      |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |      |      |      |      |      |      |      |      | Home |  End | VOL+ | Play |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | NKRO |      |      |      |      |             |      |      | Prev | VOL- | Next |
 * `-----------------------------------------------------------------------------------'
 */
[_ADJUST] = LAYOUT_planck_grid(
    RESET,   DEBUG,   _______, _______, AU_ON,    AU_OFF, _______, _______, _______, _______, _______, _______ ,
    _______, _______, _______, QWERTY, WORKMAN , _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_END,  KC_VOLU, KC_MPLY,
    MAGIC_TOGGLE_NKRO, _______, _______, _______, _______, _______, _______, _______, _______, KC_MPRV, KC_VOLD, KC_MNXT
)
};




bool held[7][6] = {{false}};
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if(record->event.key.row != 3 && record->event.key.row != 7 ){
    held[record->event.key.row][record->event.key.col] = record->event.pressed;
  }
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case WORKMAN:
      if (record->event.pressed) {
       set_single_persistent_default_layer(_WORKMAN);
      }
      return false;
      break;
    case LOWER:
      if(record->event.pressed){
        print("registered\n");
        for(int i = 0; i < 7; i++){
          for(int j = 0; j < 6; j++){
            if(held[i][j]){
              tap_code(pgm_read_word(&keymaps[_LOWER][i][j]));
            }
          }
        }
        layer_on(_LOWER);
        return false;
      }

      layer_off(_LOWER);
      return false;
      break;
  }
  return true;
}

void dip_update(uint8_t index, bool active) {
  switch (index) {
    case 0:
      if (active) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      break;
   }
}
