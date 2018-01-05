/* Copyright 2018  Andrew Heaston  @rooski15
 *
 * Developed by /u/holtenc at www.primekb.com
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
 */// Prime_R Rev 1.0

#include "prime_r.h"
#include "action_layer.h"
#include "backlight.h"

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

//Arrow Cluster Toggle
static bool arrow_toggle = false;

//Arrow Keys
enum custom_keycodes{
	AR_TOG = SAFE_RANGE, //Toggle Arrow Keys
	AR_LT,	//Num0 or Left Arrow
	AR_RT,	//NumEnt or Right Arrow
	AR_DN,	//NumDot or Down Arrow
	AR_UP,	//Num2 or Up Arrow
};
		
// Tap/Hold Space Layer
#define SPC_LT LT(1, KC_SPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  /* (Base Layer) Default Layer
   * ,---------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|BSP|DEL|HOM|END|
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|  '|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1|ARU|  3|  AR - U/D/L/R & Toggle
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |Alt|TO1| 1/SP |  1/SP  |ART|App|Alt|Ctrl |ARL|ARD|ARR|  Arrow keys operate on AR Toggle to be numpad keys
   * `---------------------------------------------------------------'
   */
  // 0: Base Layer
	KEYMAP(
		KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_BSPC, KC_DEL,  KC_HOME, KC_END,   \
		KC_GRV,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_P7,   KC_P8,   KC_P9,    \
		KC_TAB,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,          KC_ENT,  KC_P4,   KC_P5,   KC_P6,    \
		KC_LSPO,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC, KC_P1,   AR_UP,   KC_P3,    \
		KC_LCTL,          KC_LGUI, KC_LALT, TO(1),   SPC_LT,           SPC_LT,           AR_TOG,  KC_APP,  KC_RALT, KC_RCTL, AR_LT,   AR_DN,   AR_RT),   \

  /* (Function Layer)
   * ,---------------------------------------------------------------.
   * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9| F0|  =|BSP|HOM|END|DEL|
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  \|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |BL  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  '|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1|VUP|  3|
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |Alt|TO0| 1/SP |  1/SP  |ART|TO2|Alt|Ctrl |MUT|VDN|STP|
   * `---------------------------------------------------------------'
   */  
  // 1: Function Layer
	KEYMAP(
		_______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_EQL,  _______, KC_PSLS, KC_PAST, KC_PPLS, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BSLS, _______, _______, _______, 
		BL_TOGG, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_QUOT,          _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, _______, 
		_______,          _______, _______, TO(0),   _______,          _______,          _______, TO(2),   _______, _______, KC_MUTE, KC_VOLD, KC_MSTP),	

  /* (Numpad Mods)
   * ,---------------------------------------------------------------.
   * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|BSP|  /|  *|  +| Mirrors base layer, but with numpad mods
   * |---------------------------------------------------------------|
   * |Grv|  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  7|  8|  9|
   * |---------------------------------------------------------------|
   * |Tab |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|Return|  4|  5|  6|
   * |---------------------------------------------------------------|
   * |Shift|  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  ?|Shift|  1|ARU|  3|
   * |---------------------------------------------------------------|
   * |Ctrl|Gui |Alt|TO0| 1/SP |  1/SP  |ART|App|Alt|Ctrl |ARL|ARD|ARR|
   * `---------------------------------------------------------------'
   */
    // 2: Numpad Mods
	KEYMAP(
		_______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, _______, KC_PSLS, KC_PAST, KC_PPLS, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_RBRC, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_SCLN,          _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, AR_UP,   _______, 
		_______,          _______, _______, TO(0),   _______,          _______,          _______, KC_APP,  _______, _______, AR_LT,   AR_DN,   AR_RT ),
		
  // 3: Extra
	KEYMAP(
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, 
		_______,          _______, _______, _______, _______,          _______,          _______, _______, _______, _______, _______, _______, _______),

};

void matrix_init_user(void) {
	if (get_backlight_level() != 0){
		backlight_toggle();
	}
};

void matrix_scan_user(void) {
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	if(record->event.pressed){
		switch(keycode) {
			case AR_TOG:
				arrow_toggle = !arrow_toggle;
				backlight_toggle();	
				return false; break;
			
			case AR_UP:
				if(arrow_toggle == 1){
					SEND_STRING(SS_DOWN(X_UP));
				} else {
					SEND_STRING(SS_DOWN(X_KP_2));
				}
				return false; break;
			
			case AR_DN:
				if(arrow_toggle == 1){
					SEND_STRING(SS_DOWN(X_DOWN));
				} else {
					SEND_STRING(SS_DOWN(X_KP_DOT));
				}
				return false; break;
			
			case AR_LT:
				if(arrow_toggle == 1){
					SEND_STRING(SS_DOWN(X_LEFT));
				} else {
					SEND_STRING(SS_DOWN(X_KP_0));
				}
				return false; break;
			
			case AR_RT:
				if(arrow_toggle == 1){
					SEND_STRING(SS_DOWN(X_RIGHT));
				} else {
					SEND_STRING(SS_DOWN(X_KP_ENTER));
				}
				return false; break;
		}
	}
	if(!record->event.pressed){
		switch(keycode) {
			case AR_UP:
				if(arrow_toggle == 1){
					SEND_STRING(SS_UP(X_UP));
				} else {
					SEND_STRING(SS_UP(X_KP_2));
				}
				return false; break;
			case AR_DN:
				if(arrow_toggle == 1){
					SEND_STRING(SS_UP(X_DOWN));
				} else {
					SEND_STRING(SS_UP(X_KP_DOT));
				}
				return false; break;
			case AR_LT:
				if(arrow_toggle == 1){
					SEND_STRING(SS_UP(X_LEFT));
				} else {
					SEND_STRING(SS_UP(X_KP_0));
				}
				return false; break;
			case AR_RT:
				if(arrow_toggle == 1){
					SEND_STRING(SS_UP(X_RIGHT));
				} else {
					SEND_STRING(SS_UP(X_KP_ENTER));
				}
				return false; break;
		}
	}
	return true;
};