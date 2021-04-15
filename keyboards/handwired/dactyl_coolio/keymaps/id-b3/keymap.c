/*
Copyright 2021 id-b3
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
#include "id-b3.h"

// Enumerate the tap dances
enum taps {
	//TD_PRNS = 0,
	//TD_BRCS, //Brackets
	TD_EXLM = 0, //! and ?
	TD_PCAS, //% and *
	TD_PLMN, //+ and -
	TD_ASDI, //* and /
	TD_TABC, //Tab and Ctrl TAB
	TD_0,
	TD_1,
	TD_2,
	TD_3,
	TD_4,
	TD_5,
	TD_6,
	TD_7,
	TD_8,
	TD_9
};
// TAP DANCING

qk_tap_dance_action_t tap_dance_actions[] = {
  //[TD_PRNS] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  //[TD_BRCS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_EXLM] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, KC_QUES),
  [TD_PCAS] = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_ASTR),
  [TD_PLMN] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_PMNS),
  [TD_ASDI] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_PSLS),
  [TD_TABC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, S(KC_TAB)),
//  [TD_0] = ACTION_TAP_DANCE_DOUBLE(KC_0, C(KC_0)),
//  [TD_1] = ACTION_TAP_DANCE_DOUBLE(KC_1, C(KC_1)),
//  [TD_2] = ACTION_TAP_DANCE_DOUBLE(KC_2, C(KC_2)),
//  [TD_3] = ACTION_TAP_DANCE_DOUBLE(KC_3, C(KC_3)),
//  [TD_4] = ACTION_TAP_DANCE_DOUBLE(KC_4, C(KC_4)),
//  [TD_5] = ACTION_TAP_DANCE_DOUBLE(KC_5, C(KC_5)),
//  [TD_6] = ACTION_TAP_DANCE_DOUBLE(KC_6, C(KC_6)),
//  [TD_7] = ACTION_TAP_DANCE_DOUBLE(KC_7, C(KC_7)),
//  [TD_8] = ACTION_TAP_DANCE_DOUBLE(KC_8, C(KC_8)),
//  [TD_9] = ACTION_TAP_DANCE_DOUBLE(KC_9, C(KC_9))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*Base Layerer*/
    [_COLEMAK] = LAYOUT_wrapper(
      _____________________COLEMAK_L1_____________________,       _____________________COLEMAK_R1_____________________,
      _____________________COLEMAK_L2_____________________,       _____________________COLEMAK_R2_____________________,
      _____________________COLEMAK_L3_____________________,	      _____________________COLEMAK_R3_____________________,
      _____________________THUMBS_LF1_____________________,       _____________________THUMBS_RG1_____________________,
	  _____________________THUMBS_LF2_____________________,       _____________________THUMBS_RG2_____________________
    ),
	[_QWERTY] = LAYOUT_wrapper(
      _____________________QWERTY_L1______________________,       _____________________QWERTY_R1______________________,
      _____________________QWERTY_L2______________________,       _____________________QWERTY_R2______________________,
      _____________________QWERTY_L3______________________,	      _____________________QWERTY_R3______________________,
      _____________________THUMBS_LF1_____________________,       KC_LEFT, TD(TD_TABC), KC_BSPC, KC_RIGHT, TO(_COLEMAK),
	  _____________________THUMBS_LF2_____________________,       _____________________THUMBS_RG2_____________________
    ),
	[_GAMING] = LAYOUT_wrapper(
      _____________________GAMING_LF1_____________________,       _____________________GAMING_RT1_____________________,
      _____________________GAMING_LF2_____________________,       _____________________GAMING_RT2_____________________,
      _____________________GAMING_LF3_____________________,       _____________________GAMING_RT3_____________________,
      _____________________GAME_TMB_L_____________________,       _____________________GAME_TMB_R_____________________,
	  _____________________GAME_TM_L2_____________________,       _____________________GAME_TM_R2_____________________       
    ),
//	[_WARHAMMER] = LAYOUT_wrapper(
  //    _____________________WARHAMMER_LF1_____________________,       _____________________WARHAMMER_RT1_____________________,
    //  _____________________WARHAMMER_LF2_____________________,       _____________________WARHAMMER_RT2_____________________,
      //_____________________WARHAMMER_LF3_____________________,       _____________________WARHAMMER_RT3_____________________,
//      _____________________WARHAMMER_TMB_L_____________________,       _____________________WARHAMMER_TMB_R_____________________,
	//  _____________________WARHAMMER_TM_L2_____________________,       _____________________WARHAMMER_TM_R2_____________________       
 //   ),
	[_SHORTCUT] = LAYOUT_wrapper(
      _____________________SHORTCT_L1_____________________,       _____________________SHORTCT_R1_____________________,
      _____________________SHORTCT_L2_____________________,       _____________________SHORTCT_R2_____________________,
      _____________________SHORTCT_L3_____________________,       _____________________SHORTCT_R3_____________________,
      _____________________SHRT_TH_L1_____________________,       _____________________SHRT_TH_R1_____________________, 
	  _____________________SHRT_TH_L2_____________________,       _____________________SHRT_TH_R2_____________________
    ),

	[_SYMNUM] = LAYOUT_wrapper(
      _____________________SYMNUM_LF1_____________________,       _____________________SYMNUM_RT1_____________________,
      _____________________SYMNUM_LF2_____________________,       _____________________SYMNUM_RT2_____________________,
      _____________________SYMNUM_LF3_____________________,	 	  _____________________SYMNUM_RT3_____________________,
      _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______,
	  _______, _______,                                  _______,_______
    ),
	[_NAVIGATION] = LAYOUT(
      _______, _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP,        _______,   KC_F7,   KC_F8,   KC_F9,  KC_F10, KC_CAPS,
      _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,        _______,   KC_F4,   KC_F5,   KC_F6,  KC_F11, KC_SLCK,
      _______, _______,_______,C(KC_MINS),C(KC_EQL), _______,	       _______,   KC_F1,   KC_F2,   KC_F3,  KC_F12, KC_NLCK,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
	  _______,                                                                                                  _______
    ),

	
	#ifdef DICE_ROLLER_ENABLE
	[_RPG] = LAYOUT(
      KC_GRAVE, _______, _______, _______, _______, ROLL_D100,        _______, _______, _______, _______, _______, _______,
      ROLL_D3, ROLL_D4, ROLL_D6, ROLL_D10, ROLL_D12, ROLL_D20,        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,	       _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
	  _______,                                                                                                  _______
    )
	#endif
	
	/*[_BLANK] = LAYOUT(
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,	       _______, _______, _______, _______, _______, _______,
      _______, _______, _______, _______, _______, _______,        _______, _______, _______, _______, _______, _______,
	  _______,                                                                                                  _______
    )
	*/

};
