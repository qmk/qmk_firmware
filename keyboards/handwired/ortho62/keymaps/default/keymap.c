/* Copyright 2017 REPLACE_WITH_YOUR_NAME
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
#include "ortho62.h"

// Each Layer gets it's own name
#define _BL	0
#define _FL	1

// Fillers to make layering more clear
#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BL] = KEYMAP( 
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     KC_GRV , KC_1  , KC_2  , KC_3  , KC_4  , KC_5  , KC_6  , KC_7  , KC_8  , KC_9  , KC_0  ,KC_MINS,KC_EQL ,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     KC_TAB , KC_Q  , KC_W  , KC_E  , KC_R  , KC_T  , KC_Y  , KC_U  , KC_I  , KC_O  , KC_P  ,KC_LBRC,KC_RBRC,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     KC_BSPC, KC_A  , KC_S  , KC_D  , KC_F  , KC_G  , KC_H  , KC_J  , KC_K  , KC_L  ,SKC_CLN,KC_QUOT,KC_ENT ,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     KC_ESC , KC_Z  , KC_X  , KC_C  , KC_V  , KC_B  , KC_N  , KC_M  ,KC_COMM,KC_DOT, KC_SLSH, KC_UP ,KC_DEL ,
  //,-------+-------+-------+---------------+---------------+---------------+-------+-------+-------+-------.
     KC_LCTL,KC_LGUI,KC_LALT,    MO(_FL)    ,     KC_SPC    ,    KC_LSFT    ,KC_BSLS,KC_LEFT,KC_DOWN,KC_RGHT
  //,-------+-------+-------+---------------+---------------+---------------+-------+-------+-------+-------.  
),
[_FL] = COMPACT_KEYMAP( 
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     _______, KC_F1 , KC_F2 , KC_F  , KC_F4 , KC_F5 , KC_F6 , KC_F7 , KC_F8 , KC_F9 ,KC_F10 ,KC_F11, KC_F12 ,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,_______, KC_7  , KC_8  , KC_9  , KC_0  ,_______,_______,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     _______,KC_STOP,KC_MUTE,KC_VOLD,KC_VOLU,_______,KC_GRV , KC_4  , KC_5  , KC_6  ,KC_MINS,_______,_______,
  //,-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,_______, KC_1  , KC_2  , KC_3  ,KC_EQL ,KC_PGUP,KC_INS ,
  //,-------+-------+-------+---------------+---------------+---------------+-------+-------+-------+-------.
     _______,_______,_______,    _______    ,    _______    ,    _______    ,_______,KC_HOME,KC_PGDN,KC_END
  //,-------+-------+-------+---------------+---------------+---------------+-------+-------+-------+-------.
),
};

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}
