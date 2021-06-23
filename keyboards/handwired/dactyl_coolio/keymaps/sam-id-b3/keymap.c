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
#include "sam-id-b3.h"

// Enumerate the tap dances
enum taps {
	//TD_PRNS = 0,
	//TD_BRCS, //Brackets
	TD_EXLM, //! and ?
	TD_PCAS, //% and *
	TD_PLMN, //+ and -
	TD_ASDI, //* and /
	TD_TABC  //Tab and Ctrl TAB
};
// TAP DANCING

qk_tap_dance_action_t tap_dance_actions[] = {
  //[TD_PRNS] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN, KC_RPRN),
  //[TD_BRCS] = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_RBRC),
  [TD_EXLM] = ACTION_TAP_DANCE_DOUBLE(KC_EXLM, KC_QUES),
  [TD_PCAS] = ACTION_TAP_DANCE_DOUBLE(KC_PERC, KC_ASTR),
  [TD_PLMN] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_PMNS),
  [TD_ASDI] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_PSLS),
  [TD_TABC] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, S(KC_TAB))
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*Base Layerer*/
    [_QWERTY] = LAYOUT_wrapper(
      _____________________QWERTY_L1______________________,      _____________________QWERTY_R1______________________,
      _____________________QWERTY_L2______________________,      _____________________QWERTY_R2______________________,
      _____________________QWERTY_L3______________________,	     _____________________QWERTY_R3______________________,
      _____________________THUMBS_LF1_____________________,      _____________________THUMBS_RG1_____________________,
	  _____________________THUMBS_LF2_____________________,      _____________________THUMBS_RG2_____________________
    ),
	[_GAMING] = LAYOUT_wrapper(
      _____________________GAMING_LF1_____________________,       _____________________GAMING_RT1_____________________,
      _____________________GAMING_LF2_____________________,       _____________________GAMING_RT2_____________________,
      _____________________GAMING_LF3_____________________,       _____________________GAMING_RT3_____________________,
      _____________________GAME_TMB_L_____________________,       _____________________GAME_TMB_R_____________________,
	  _____________________GAME_TM_L2_____________________,       _____________________GAME_TM_R2_____________________       
    ),
	[_SHORTCUT] = LAYOUT_wrapper(
      _____________________SHORTCT_L1_____________________,       _____________________SHORTCT_R1_____________________,
      _____________________SHORTCT_L2_____________________,       _____________________SHORTCT_R2_____________________,
      _____________________SHORTCT_L3_____________________,       _____________________SHORTCT_R3_____________________,
      _____________________SHRT_TH_L1_____________________,       _____________________SHRT_TH_R1_____________________, 
	  _____________________SHRT_TH_L2_____________________,       _____________________SHRT_TH_R2_____________________
    ),

	[_SYMNUM] = LAYOUT_wrapper(
      _____________________SYMNUM_RT1_____________________,       _____________________SYMNUM_LF1_____________________,
      _____________________SYMNUM_RT2_____________________,       _____________________SYMNUM_LF2_____________________,
      _____________________SYMNUM_RT3_____________________,	 	  _____________________SYMNUM_LF3_____________________,
      _______, KC_0, _______, _______, _______,       _______, _______, _______, _______, _______,
	  _______, _______,                                  _______,_______
    ),
	[_NAVIGATION] = LAYOUT_wrapper(
      _____________________NAVIGT_R1______________________,        _____________________NAVIGT_L1______________________,
      _____________________NAVIGT_R2______________________,        _____________________NAVIGT_L2______________________,
      _____________________NAVIGT_R3______________________,	       _____________________NAVIGT_L3______________________,
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
