/*
Copyright 2022
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "./keymap_portuguese.h"

enum layers {
	_LAYER0,
	_LAYER1,
	_LAYER2
};

enum {
	TD_LEFT_HOME,
	TD_RIGHT_END,
	TD_UP_PGUP,
	TD_DOWN_PGDN,
	TD_SPACE_L1,
	TD_BSPACE_L2,
	CT_LBRK,
	CT_RBRK
};

void left_brackets_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_LCBR);//{
	} else if (state->count == 2){
		register_code16(PT_LBRC);//[
	} else {
		register_code16(PT_LPRN);//(
	}
}

void left_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		unregister_code16(KC_LCBR);
	} else if (state->count == 2){
		unregister_code16(PT_LBRC);
	} else {
		unregister_code16(PT_LPRN);
	}
}

void right_brackets_finished(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		register_code16(KC_RCBR);//}
	} else if (state->count == 2){
		register_code16(PT_RBRC);//]
	} else {
		register_code16(PT_RPRN);//)
	}
}

void right_brackets_reset(qk_tap_dance_state_t *state, void *user_data) {
	if (state->count == 1) {
		unregister_code16(KC_RCBR);
	} else if (state->count == 2){
		unregister_code16(PT_RBRC);
	} else {
		unregister_code16(PT_RPRN);
	}
}

qk_tap_dance_action_t tap_dance_actions[] = {
	[TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME),
	[TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END),
	[TD_UP_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
	[TD_DOWN_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
	[TD_SPACE_L1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _LAYER1),
	[TD_BSPACE_L2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_BSPC, _LAYER2),
	[CT_LBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets_finished, left_brackets_reset),
	[CT_RBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets_finished, right_brackets_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_LAYER0] = LAYOUT_split_3x5_3(
		KC_Q,		KC_D,		KC_R,		KC_W,			KC_B,					KC_J,				KC_F,			KC_U,		KC_P,			KC_NO,
		KC_A,		KC_S,		KC_H,		KC_T,			KC_G,					KC_Y,				KC_N,			KC_E,		KC_O,			KC_I,
		KC_Z,		KC_X,		KC_M,		KC_C,			KC_V,					KC_K,				KC_L,			KC_NO,		KC_NO,			KC_NO,
								KC_TAB,		TD(CT_LBRK),	TD(TD_SPACE_L1),		TD(TD_BSPACE_L2),	TD(CT_RBRK),	KC_ENT
	),

	[_LAYER1] = LAYOUT_split_3x5_3(
		KC_ESC,		PT_AT,		PT_HASH,	PT_DLR,		PT_AMPR,				KC_PAST,		KC_7,			KC_8,		KC_9,		KC_PMNS,
		KC_QUES,	KC_EXLM,	KC_NO,		KC_NO,		KC_NO,					KC_PSLS,		KC_4,			KC_5,		KC_6,		KC_PPLS,
		KC_NO,		KC_NO,		KC_NO,		KC_NO,		KC_NO,					KC_PERC,		KC_1,			KC_2,		KC_3,		KC_PEQL,
								KC_NO,		KC_NO,		TO(_LAYER0),			TO(_LAYER2),	KC_NO,			KC_0
	),

	[_LAYER2] = LAYOUT_split_3x5_3(
		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,					KC_NO,			KC_NO,			 KC_NO,			  KC_NO,		   	KC_NO,
		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,					KC_NO,			KC_NO,			 TD(TD_UP_PGUP),  KC_NO,		   	KC_NO,
		KC_F11,		KC_F12,		KC_NO,		KC_NO,		KC_NO,					KC_NO,			TD(TD_LEFT_HOME),TD(TD_DOWN_PGDN),TD(TD_RIGHT_END),KC_NO,
								KC_NO,		KC_NO,		TO(_LAYER0),			TO(_LAYER1),	KC_NO,			 KC_NO
	)
};
