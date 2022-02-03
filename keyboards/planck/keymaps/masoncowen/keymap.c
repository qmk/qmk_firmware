/* Copyright 2021 masoncowen
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
  _ZWFP,
  _NUMNAV
};

enum planck_keycodes {
  ZWFP = SAFE_RANGE,
  NUMNAV
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_ZWFP] = LAYOUT_planck_grid(
  KC_Z , KC_W , KC_F , KC_P , KC_Q , KC_NO , KC_NO , KC_J , KC_L , KC_U , KC_Y , OSL(_NUMNAV) ,
  KC_A , KC_R , KC_S , KC_T , KC_G , KC_NO , KC_NO , KC_M , KC_N , KC_E , KC_I , KC_O ,
  KC_X , KC_V , KC_C , KC_D , KC_B , KC_NO , KC_NO , KC_K , KC_H , KC_DOT , KC_COMM , KC_SCLN ,
  KC_NO , KC_NO , KC_ESC , KC_SPC , OSM(MOD_LCTL) , KC_NO , KC_NO , KC_BSPC , OSM(MOD_LSFT) , OSM(MOD_LALT) , KC_NO , KC_NO
),

//TRANSPARENT keys are to be decided on
[_NUMNAV] = LAYOUT_planck_grid(
  KC_PPLS , KC_4 , KC_5 , KC_6 , KC_PAST , KC_NO , KC_NO , KC_BSLS , KC_HOME , KC_PGDN , KC_PGUP , KC_END ,
  KC_0 , KC_1 , KC_2 , KC_3 , KC_PENT , KC_NO , KC_NO , KC_NUHS , KC_LEFT , KC_DOWN , KC_UP , KC_RIGHT ,
  KC_PMNS , KC_7 , KC_8 , KC_9 , KC_PSLS , KC_NO , KC_NO , KC_QUOT , , _______ , _______ , _______ ,
  KC_NO , KC_NO , _______ , _______ , _______ , KC_NO , KC_NO , _______ , _______ , _______ , KC_NO , KC_NO
)

};

const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t enter_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_ESC, KC_ENTER);
const key_override_t tab_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);

const key_override_t **key_overrides = (const key_override_t *[]){
  &delete_key_override,
  &enter_key_override,
  &tab_key_override,
  NULL
};
