/* Copyright 2018 Holten Campbell
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
#include "milestogo.h"

/* customized matrix needs to be updated in local config.h
#define MATRIX_ROWS 5 
#define MATRIX_COLS 15
#define MATRIX_ROW_PINS { E6, C7, B5, B4, C6 }
#define MATRIX_COL_PINS { F0, F1, F4, F5, F6, F7, D6, D4, D5, D3, D2, D1, D0, B6, D7} 
*/


#define LAYOUT_m2primee( \
	K000, K001, K002, K003, K004, K005,  		K006, K007, K008, K009, K010, K011, K012, \
	K100, K101, K102, K103, K104, K105,  		K106, K107, K108, K109, K110,       K112, \
	K200, K201, K202, K203, K204, K205,  		K206, K207, K208, K209, K210, K211, K212, \
	K300, K301,  		        K303, K304,  		K306, K308, 		              K311, K312, \
                                K413,     K414 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012, KC_NO, KC_NO }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  KC_NO, K112, KC_NO, KC_NO }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212, KC_NO, KC_NO }, \
	{ K300,  K301,  KC_NO, K303,  K304,  KC_NO, K306,  KC_NO, K308,  KC_NO, KC_NO, K311,  K312, KC_NO, KC_NO }, \
	{ KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,K413,  K414  } \
}


#define LAYOUT_m2primee_trns( \
        K001, K002, K003, K004, K005,     K006, K007, K008, K009, K010, K011, K012, \
        K101, K102, K103, K104, K105,     K106, K107, K108, K109, K110,       K112, \
        K201, K202, K203, K204, K205,     K206, K207, K208, K209, K210, K211 \
) { \
  { KC_TAB,   K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012, KC_NO, KC_NO }, \
  { KC_LCTL,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  KC_NO, K112, KC_NO, KC_NO }, \
  { KC_LSFT,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  KC_TRNS, KC_NO, KC_NO }, \
  { KC_LALT,  KC_TRNS,  KC_NO, KC_TRNS,  KC_TRNS,  KC_NO, KC_TRNS,  KC_NO, KC_TRNS,  KC_NO, KC_NO, KC_TRNS,  KC_RSFT, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_TRNS,  KC_TRNS  } \
}


#define LAYOUT_wrap_m2primee(...)       LAYOUT_m2primee(__VA_ARGS__)
#define LAYOUT_wrap_m2primee_trns(...)       LAYOUT_m2primee_trns(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY]=LAYOUT_wrap_m2primee(
		KC_GRAVE, _________________QWERTY_L1_________________,       _________________QWERTY_R1_________________,   KC_MINS, KC_EQL,
		KC_TAB,   _________________QWERTY_L2_________________,       _________________QWERTY_R2_________________,   KC_QUOT,
		KC_LSFT,  _________________QWERTY_L3_________________,       _________________QWERTY_R3_________________,   KC_SLSH, KC_RSFT,
		KC_LALT,  MO(_MOV),          LT(_NUM,KC_DEL), LT(_SYM,KC_BSPC),	          KC_SPC, LT(_NUM,KC_ESC), MO(_MOV),KC_RALT,
    KC_LGUI,  KC_ENTER
    ),

 [_CDH]=LAYOUT_wrap_m2primee_trns(
    ______________COLEMAK_MOD_DH_L1____________,        ______________COLEMAK_MOD_DH_R1____________, KC_TRNS, KC_TRNS, \
    ______________COLEMAK_MOD_DH_L2____________,        ______________COLEMAK_MOD_DH_R2____________,  KC_QUOT, \
    ______________COLEMAK_MOD_DH_L3____________,        ______________COLEMAK_MOD_DH_R3____________, KC_TRNS
    ),

 [_SYM]=LAYOUT_wrap_m2primee_trns(
      ______________COLEMAK_MOD_DH_L1____________,        ______________COLEMAK_MOD_DH_R1____________, KC_TRNS, KC_TRNS, \
      ______________COLEMAK_MOD_DH_L2____________,        ______________COLEMAK_MOD_DH_R2____________,  KC_TRNS, \
      ______________COLEMAK_MOD_DH_L3____________,        ______________COLEMAK_MOD_DH_R3____________, KC_TRNS
    ),

[_NUM]=  LAYOUT_wrap_m2primee( 
    KC_TRNS, __________40_______NUM_L1__________________,                 __________40_______NUM_R1__________________,    KC_VOLD, KC_VOLU,
    KC_TRNS,  __________40_______NUM_L2__________________ ,                __________40_______NUM_R2__________________ ,   KC_ENT,
    KC_TRNS,  __________40_______NUM_L3__________________ ,                __________40_______NUM_R3__________________ ,  KC_SLSH,  KC_TRNS,
    KC_TRNS,  KC_TRNS,                         KC_LSFT,    KC_TRNS,        KC_TRNS,   KC_TRNS,                        KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS
    ),

[_MOV]=LAYOUT_wrap_m2primee_trns(
      __________40_______MOV_L1__________________,        __________40_______MOV_R1__________________, KC_TRNS, KC_CDH, \
      __________40_______MOV_L2__________________,        __________40_______MOV_R2__________________,  KC_TRNS, \
      __________40_______MOV_L3__________________,        __________40_______MOV_R3__________________, KC_TRNS
    ),
};


void matrix_init_user(void) {
  // set CapsLock LED to output and high by default, drop low when on. 
  setPinOutput(B1);
  writePinHigh(B1);
  // set NumLock LED to output and low
  setPinOutput(B2);
  writePinLow(B2);
  // set ScrollLock LED to output and low
  setPinOutput(B3);
  writePinLow(B3);


  backlight_enable();
  backlight_level(2);

}

void matrix_scan_user(void) {

}


void led_set_user(uint8_t usb_led) {
  if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
    writePinHigh(B2);
  } else {
    writePinLow(B2);
  }
  if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
    writePinLow(B1);
  } else {
    writePinHigh(B1);
  }
/*
  if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
    writePinHigh(B3);
  } else {
    writePinLow(B3);
  }*/

}

//function for layer indicator LED
layer_state_t layer_state_set_user(layer_state_t state)
{
    if (get_highest_layer(state) == 1) {
    writePinHigh(B3);
	} else {
		writePinLow(B3);
    }
    return state;
}
