/* Copyright 2021 Nathan Blais
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


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	/*			For build guide: go to https://github.com/blewis308/BOP-Keyboard
	*	,-----------------------------------------------------------------------------------------------------------------------.
	*	| F1  | F5  | F9  |  ~  |  !  |  @  |  #  |  $  |  %  |  ^  |  &  |  *  |  (  |  )  |  _  |  +  | del |  {  |  }  |  |  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F2  | F6  | F10 | esc |  1  |  2  |  3  |  4  |  5  |  6  |  7  |  8  |  9  |  0  |  -  |  =  |bkspc| home| end |pg up|
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F3  | F7  | F11 | tab |  q  |  w  |  e  |  r  |  t  |  y  |  u  |  i  |  o  |  p  |  [  |  ]  |  \  |  :  |  "  |pg dn|
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| F4  | F8  | F12 |caplk|  a  |  s  |  d  |  f  |  g  |  h  |  j  |  k  |  l  |  ;  |  '  |enter|     |  7  |  8  |  9  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|  0  |-----+-----+-----|
	*	|ptscr|scrlk|psbrk|shift|  z  |  x  |  c  |  v  |  b  |  n  |  m  |  <  |  >  |  ?  |shift| up  |     |  4  |  5  |  6  |
	*	|-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----|
	*	| cut | copy|paste|Lctrl|L gui|L alt|   space   |MO(1)|   space   |  ,  |  .  |  /  | left| down|right|  1  |  2  |  3  |
	*	`-----------------------------------------------------------------------------------------------------------------------'
	*
	*	Notes: spaces and numpad 0 can be 1u instead of 2u also, this is already reflected in the keymap below
	*/
	/*																		SUDSACK KEYMAP
		KC_PSCR, KC_SCRL, KC_PAUS, KC_INS , KC_CALC, KC_CUT , KC_ESC , KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_HOME,
		KC_NUM , KC_PSLS, KC_PAST, KC_PMNS, KC_COPY, KC_PSTE, KC_GRV , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_UNDS, KC_BSLS, KC_PGUP,
		KC_P7  , KC_P8  , KC_P9  , KC_PPLS, KC_LBRC, KC_RBRC, KC_TAB , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, KC_DEL , KC_PGDN,
		KC_P4  , KC_P5  , KC_P6  , KC_PPLS, KC_VOLD, KC_VOLU, KC_CAPS, KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, KC_ENT , LCTL(KC_TAB),
		KC_P1  , KC_P2  , KC_P3  , KC_PENT, KC_MUTE, KC_MPLY, KC_LSFT, KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_RSFT, KC_UP  , KC_RGUI ,
		KC_P0  , KC_P0  , KC_PDOT, KC_MPRV, KC_MNXT, KC_LCTL, KC_LGUI, KC_LALT, XXXXXXX, KC_SPC , KC_SPC , KC_SPC , KC_SPC , KC_SPC , KC_RALT, XXXXXXX, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT )
	*/
    [0] = LAYOUT(
		KC_F1, 	 KC_F5,   KC_F9,   KC_TILD, KC_EXLM, KC_AT,   KC_HASH, KC_DLR, KC_PERC, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_UNDS, KC_PLUS, KC_DEL,  KC_LCBR, KC_RCBR, KC_PIPE,
		KC_F2, 	 KC_F6,   KC_F10,  KC_ESC,  KC_1, 	 KC_2,    KC_3,    KC_4,   KC_5, 	KC_6, 	 KC_7,    KC_8,    KC_9, 	KC_0, 	 KC_PMNS, KC_PEQL, KC_BSPC, KC_HOME, KC_END,  KC_PGUP,
		KC_F3,   KC_F7,   KC_F11,  KC_TAB,  KC_Q, 	 KC_W,    KC_E,    KC_R,   KC_T, 	KC_Y, 	 KC_U,    KC_I,    KC_O, 	KC_P, 	 KC_LBRC, KC_RBRC, KC_BSLS, KC_COLN, KC_DQUO, KC_PGDN,
		KC_F4,   KC_F8,   KC_F12,  KC_CAPS, KC_A, 	 KC_S,    KC_D,    KC_F,   KC_G, 	KC_H, 	 KC_J,    KC_K,    KC_L, 	KC_SCLN, KC_QUOT, KC_ENT,  KC_KP_0, KC_KP_7, KC_KP_8, KC_KP_9,
		KC_PSCR, KC_SCRL, KC_PAUS, KC_LSFT, KC_Z, 	 KC_X,    KC_C,    KC_V,   KC_B, 	KC_N, 	 KC_M,    KC_LABK, KC_RABK, KC_QUES, KC_RSFT, KC_UP,   KC_KP_0, KC_KP_4, KC_KP_5, KC_KP_6,
        KC_CUT,  KC_COPY, KC_PSTE, KC_LCTL, KC_LGUI, KC_LALT, KC_SPC,  KC_SPC, MO(1) ,  KC_SPC,  KC_SPC,  KC_PCMM, KC_PDOT, KC_SLSH, KC_LEFT, KC_DOWN, KC_RGHT, KC_KP_1, KC_KP_2, KC_KP_3),
    
    [1] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
    
    [2] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
    
    [3] = LAYOUT(
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO),
};
