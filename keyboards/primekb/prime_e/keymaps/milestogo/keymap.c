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

enum mlayers {
_QWERTY=0, 
_CDH, 
_SYM,
_NUM,
_MOV,
};


#define MLAYOUT( \
	K000, K001, K002, K003, K004, K005,  		K006, K007, K008, K009, K010, K011, K012, \
	K100, K101, K102, K103, K104, K105,  		K106, K107, K108, K109, K110, K112, \
	K200, K201, K202, K203, K204, K205,  		K206, K207, K208, K209, K210, K211, K212, \
	K300, K301,  			K303, K304,  		K306, K308, 				K311, K312,\
                                    K413, K414 \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012, KC_NO, KC_NO }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  KC_NO, K112, KC_NO, KC_NO }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212, KC_NO, KC_NO }, \
	{ K300,  K301,  KC_NO, K303,  K304,  KC_NO, K306,  KC_NO, K308,  KC_NO, KC_NO, K311,  K312, KC_NO, KC_NO }, \
  { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,K413,  K414  }\
}


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
   [_QWERTY]=MLAYOUT(
		KC_GRAVE, KC_Q,     KC_W,     KC_E,   KC_R,    KC_T,          KC_Y,   KC_U,     KC_I, KC_O,    KC_P,    KC_MINS, KC_EQL,
		KC_TAB,   KC_A,     KC_S,     KC_D,   KC_F,    KC_G,          KC_H,   KC_J,     KC_K, KC_L,    KC_SCLN, KC_1,
		KC_LSFT,  KC_Z,     KC_X,     KC_C,   KC_V,    KC_B,          KC_RCTL,KC_N,     KC_M, KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
		KC_LALT,  MO(_MOV),                LT(_NUM,KC_DEL), LT(_SYM,KC_BSPC),	          KC_SPC, LT(_NUM,KC_ESC), MO(_MOV),KC_RALT,
    KC_LGUI,  KC_ENTER
    ),

 [_CDH]=MLAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_F,   KC_P,    KC_B,          KC_J,   KC_L,     KC_U, KC_Y,    KC_SCLN,  KC_TRNS, KC_TRNS,
    KC_TAB,   KC_A,     KC_R,     KC_S,   KC_T,    KC_G,          KC_M,   KC_N,     KC_E, KC_I,    KC_O,     KC_TRNS,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,   KC_D,    KC_V,          KC_TRNS,KC_K,     KC_H, KC_COMM, KC_DOT,   KC_SLSH, KC_TRNS,
    KC_TRNS,  KC_TRNS,                    KC_TRNS, KC_TRNS,       KC_TRNS,         KC_TRNS,                  KC_TRNS, KC_TRNS,
    KC_TRNS,  KC_TRNS
    ),


[_SYM]=  MLAYOUT(
    KC_GRV,    KC_EXLM,   KC_AT,   KC_HASH,   KC_DLR,    KC_PERC,          KC_CIRC,   KC_AMPR,    KC_ASTR,     KC_LPRN,   KC_RPRN,   KC_UNDS,   KC_PLUS,
    KC_CAPS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,          KC_LBRC,  KC_LCBR,   KC_PIPE,     KC_RCBR,  KC_RBRC,   KC_BSLS,
    KC_TRNS,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,          KC_NO,  KC_BSLS,   KC_NO,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    BL_TOGG,   BL_STEP,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TILDE,                                     KC_TRNS,   KC_TRNS,
    KC_TRNS, KC_TRNS
    ),

[_NUM]=  MLAYOUT( 
    TG(_CDH),  KC_1,      KC_2,      KC_3,      KC_4,       KC_5,             KC_6,      KC_7,     KC_8,    KC_9,    KC_0,      KC_VOLD, KC_VOLU,
    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P4,    KC_P5,   KC_P6,   KC_LBRC,   KC_RBRC,
    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P1,    KC_P2,   KC_P3,   KC_TRNS,   KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,                         KC_LSFT,    KC_TRNS,          KC_TRNS,   KC_TRNS,                        KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS
    ),

[_MOV]=MLAYOUT(
    KC_GRV,    KC_TRNS,   KC_MS_BTN1,KC_MS_U,   KC_MS_BTN2, KC_MS_BTN3,          KC_TRNS,   KC_TRNS,    KC_UP,     KC_TRNS,   KC_MUTE,   KC_VOLD,   KC_VOLU,
    KC_CAPS,   KC_WH_D,   KC_MS_L,   KC_MS_D,   KC_MS_R,    KC_WH_U,          KC_TRNS,   KC_LEFT,    KC_DOWN,   KC_RIGHT,  KC_SCLN,   KC_BSLS,
    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,    KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
    BL_TOGG,   BL_STEP,                         KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_TRNS,                             KC_TRNS,   KC_TRNS,
    KC_TRNS, KC_TRNS
    ),
};
/*
    LAYOUT(
    KC_TRNS,  KC_1,      KC_2,      KC_3,      KC_4,       KC_5,             KC_6,      KC_7,     KC_8,    KC_9,    KC_0,      KC_MINS,  KC_EQL,
    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P4,    KC_P5,   KC_P6,   KC_LBRC,   KC_RBRC,
    KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,    KC_TRNS,          KC_TRNS,   KC_P1,    KC_P2,   KC_P3,   KC_TRNS,   KC_TRNS,  KC_TRNS,
    KC_TRNS,  KC_TRNS,                         KC_TRNS,    KC_TRNS,          KC_PENT,   KC_PDOT,                               KC_TRNS,  KC_TRNS
    ),

*/ 
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
