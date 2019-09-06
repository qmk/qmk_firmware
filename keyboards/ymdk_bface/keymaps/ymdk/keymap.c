/*
Copyright 2017 Sebastian Kaim <sebastian.kaim@sebb767.de>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

#define LAYOUT_60_split_shift_ymdk(\
  K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, KA4, KB4, KC4, KE4, \
  K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3,  KC3,  KD3, \
  K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2,      KD2, \
  K01,    K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1,  KD1,  KE1, \
  K00,    K10,     K20,           K70,                K90, KA0, KC0, KD0  \
){ \
  { K00,   K10,   K20,   KC_NO, KC_NO, KC_NO, KC_NO, K70, KC_NO,     K90,    KA0,   KC_NO, KC0,   KD0,   KC_NO }, \
  { K01,   KC_NO,   K21,   K31,   K41,   K51,   K61,  K71,    K81,    K91,    KA1,   KB1,   KC_NO, KD1,   KE1 }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,  K72,    K82,    K92,    KA2,   KB2,   KC_NO, KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,  K73,    K83,    K93,    KA3,   KB3,   KC3,   KD3,   KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   K64,  K74,    K84,    K94,    KA4,   KB4,   KC4,   KC_NO, KE4   }, \
}
//   0      1      2      3      4      5       6      7      8     9       A      B      C      D     E
//   A0     A1     A2     A3     A4     A5     A6      A7     C7    C6      C5     C4     C3     C2    D7

#define LAYOUT_60_ansi_ymdk(\
  K04, K14, K24, K34, K44, K54, K64, K74, K84, K94, KA4, KB4, KC4, KE4, \
  K03, K13, K23, K33, K43, K53, K63, K73, K83, K93, KA3, KB3, KC3,    KD3, \
  K02, K12, K22, K32, K42, K52, K62, K72, K82, K92, KA2, KB2,     KD2, \
  K01,    K21, K31, K41, K51, K61, K71, K81, K91, KA1, KB1,  KD1,  \
  K00,    K10,     K20,           K70,                K90, KA0, KC0, KD0  \
){ \
  { K00,   K10,   K20,   KC_NO, KC_NO, KC_NO, KC_NO, K70, KC_NO,     K90,    KA0,   KC_NO, KC0,   KD0,   KC_NO }, \
  { K01,   KC_NO,   K21,   K31,   K41,   K51,   K61,  K71,    K81,    K91,    KA1,   KB1,   KC_NO, KD1 }, \
  { K02,   K12,   K22,   K32,   K42,   K52,   K62,  K72,    K82,    K92,    KA2,   KB2,   KC_NO, KD2,   KC_NO }, \
  { K03,   K13,   K23,   K33,   K43,   K53,   K63,  K73,    K83,    K93,    KA3,   KB3,   KC3,   KD3,   KC_NO }, \
  { K04,   K14,   K24,   K34,   K44,   K54,   K64,  K74,    K84,    K94,    KA4,   KB4,   KC4,   KC_NO, KE4   }, \
}
//   0      1      2      3      4      5       6      7      8     9       A      B      C      D     E
//   A0     A1     A2     A3     A4     A5     A6      A7     C7    C6      C5     C4     C3     C2    D7


#define _FL 1
#define _CL 2
#define KC_X0   LT(_CL, KC_CAPS)   

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT_60_ansi_ymdk(
        KC_GESC, KC_1,   KC_2,   KC_3,   KC_4,   KC_5,   KC_6,   KC_7,   KC_8,   KC_9,   KC_0,   KC_MINS,KC_EQL, KC_BSPC,
        KC_TAB, KC_Q,   KC_W,   KC_E,   KC_R,   KC_T,   KC_Y,   KC_U,   KC_I,   KC_O,   KC_P,   KC_LBRC,KC_RBRC,KC_BSLS,
        KC_X0,  KC_A,   KC_S,   KC_D,   KC_F,   KC_G,   KC_H,   KC_J,   KC_K,   KC_L,   KC_SCLN,KC_QUOT,KC_ENT,
        KC_LSFT,KC_Z,   KC_X,   KC_C,   KC_V,   KC_B,   KC_N,   KC_M,   KC_COMM,KC_DOT, KC_SLSH,        KC_RSFT,
        KC_LCTL,KC_LALT,KC_LGUI,                KC_SPC,                         MO(_FL),  KC_RALT, KC_RCTL,        KC_MENU
    ),
    [_FL] = LAYOUT_60_ansi_ymdk(
        KC_GRV,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS, KC_MPLY,KC_VOLD,KC_VOLU,KC_MUTE,KC_TRNS,        KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS
    ),
    [_CL] = LAYOUT_60_ansi_ymdk(
        KC_GRV,KC_F1,  KC_F2,  KC_F3,  KC_F4,  KC_F5,  KC_F6,  KC_F7,  KC_F8,  KC_F9,  KC_F10, KC_F11, KC_F12, KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_PSCR,KC_SLCK,KC_PAUS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS, KC_TRNS, KC_LEFT, KC_DOWN,  KC_UP,KC_RIGHT,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,  KC_TRNS, KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS, 
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS
    ),
    /* You can copy this layer as base for a new fn layer * /
	[n] = LAYOUT_60_split_shift_ymdk(
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,        KC_TRNS, KC_TRNS,
        KC_TRNS,KC_TRNS,KC_TRNS,                KC_TRNS,                        KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
    ), // */
};

void led_set_user(uint8_t usb_led){
    //control the caps lock LED
    if(IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)){
        //set led pin to high
        setPinOutput(D1);
        writePinHigh(D1);
    } else {
        //set to low
        writePinLow(D1);
    }
}
