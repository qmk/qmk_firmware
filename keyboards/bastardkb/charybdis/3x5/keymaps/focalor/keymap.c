/* Copyright 2019 Thomas Baart <thomas@splitkb.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.	If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "quantum.h"
#include "./keymap_portuguese_mac_iso.h"
#include "gpio.h"

#define PROCESSOR "RP2040"

// clang-format off
enum layers {
	_COLEMAK_DH = 0,
	_NUMNAV,
    _SYM,
	_FUNCTION,
	_MOUSE
};

#define _SYM 30

enum {
	TD_LEFT_HOME,
	TD_RIGHT_END,
	TD_UP_PGUP,
	TD_DOWN_PGDN,
	TD_SPACE_1,
	TD_SPACE_2,
	TD_BSPACE_1,
	TD_BSPACE_2,
	CT_LBRK,
	CT_RBRK,
	O_A,
	MIN_UND
};
// clang-format on
#define CHARYBDIS_AUTO_SNIPING_ON_LAYER _MOUSE
static uint16_t auto_pointer_layer_timer = 0;
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS 2500
#define CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD 3

// Aliases for readability
#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

#define USR_PST S(KC_INS)
#define USR_CPY C(KC_INS)
#define USR_CUT S(KC_DEL)

#define ___ KC_NO

void left_brackets_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(PT_LCBR); //{
    } else if (state->count == 2) {
        register_code16(PT_LBRC); //[
    } else {
        register_code16(PT_LPRN); //(
    }
}

void left_brackets_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(PT_LCBR);
    } else if (state->count == 2) {
        unregister_code16(PT_LBRC);
    } else {
        unregister_code16(PT_LPRN);
    }
}

void right_brackets_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(PT_RCBR); //}
    } else if (state->count == 2) {
        register_code16(PT_RBRC); //]
    } else {
        register_code16(PT_RPRN); //)
    }
}

void right_brackets_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code16(PT_RCBR);
    } else if (state->count == 2) {
        unregister_code16(PT_RBRC);
    } else {
        unregister_code16(PT_RPRN);
    }
}
// clang-format off
tap_dance_action_t tap_dance_actions[] = {
	[TD_LEFT_HOME] = ACTION_TAP_DANCE_DOUBLE(KC_LEFT, KC_HOME), 
	[TD_RIGHT_END] = ACTION_TAP_DANCE_DOUBLE(KC_RGHT, KC_END), 
	[TD_UP_PGUP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP), 
	[TD_DOWN_PGDN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN), 
	
	[TD_SPACE_1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _SYM), 
	[TD_BSPACE_1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_BSPC, _NUMNAV),
	[TD_SPACE_2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _SYM), 
	[TD_BSPACE_2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_BSPC, _COLEMAK_DH),

	[CT_LBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets_finished, left_brackets_reset), 
	[CT_RBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets_finished, right_brackets_reset), 
	[O_A] = ACTION_TAP_DANCE_DOUBLE(PT_MORD, PT_FORD), 
	[MIN_UND] = ACTION_TAP_DANCE_DOUBLE(PT_UNDS, PT_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
/*
*BaseLayer:ColemakDH
*,--------------------------------------.					.---------------------------------------.
*|	Q	|	W	|	F	|	P	|	B	|					|	J	|	L	|	U	|	Y	|	ºª	|
*|------+-------+-------+-------+-------|					|-------+-------+-------+-------+-------|
*|	A	|	R	|	S	|	T	|	G	|					|	M	|	N	|	E	|	I	|	O	|
*|------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------|
*|	Z	|	X	|	C	|	D	|	V	|                   |	K	|	H	|,	;	|.	:	|	-_	|
*'----------------------+-------+-------|-------.	.-------+-------+-------+-----------------------'
*						|	    |([{    |Back	|	|Space  |}])	|ENT	|
*						'-----------------------'	'-----------------------'
*/
	[_COLEMAK_DH]=LAYOUT_F_3x5(
	KC_Q,   KC_W,	KC_F,	KC_P,   KC_B,												KC_J,		KC_L,	KC_U,	KC_Y,	TD(O_A),	
	KC_A,   KC_R,	KC_S,	KC_T,   KC_G,												KC_M,		KC_N,	KC_E,	KC_I,	KC_O,		
	KC_Z,   KC_X,	KC_C,	KC_D,   KC_V,												KC_K,		KC_H,	KC_COMM,KC_DOT,	TD(MIN_UND),
							KC_NO,  TD(CT_LBRK),TD(TD_BSPACE_1),        TD(TD_SPACE_1),	TD(CT_RBRK),KC_ENT
	),

/*
*NumNav:Numeration,navigation
*
*,--------------------------------------.					,---------------------------------------.
*|	=	|	9	|	8	|	7	|	+	|					|		|		|	↑	|		|		|
*|------+-------+-------+-------+-------|					|-------+-------+-------+-------+-------|
*|	%	|	6	|	5	|	4	|	-	|					|		|	←	|	↓	|	→	|		|
*|------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------|
*|		|	3	|	2	|	1	|	/	|                   |		|		|		|		|		|
*'--------------+-------+-------+-------+-------.   .-------|-------+-------+-----------------------'
*						|	0	|	*	|_SYM	|	|_CK	|   	|ENT	|
*						'-----------------------'	'-----------------------'
*/
	[_NUMNAV]=LAYOUT_F_3x5(
	KC_EQL,	KC_9,  KC_8,KC_7,  KC_PLUS,                            			KC_NO,  KC_NO,			    TD(TD_UP_PGUP),		KC_NO,				KC_NO,
	KC_PERC,KC_6,  KC_5,KC_4,  KC_MINS,                            			KC_NO,  TD(TD_LEFT_HOME),	TD(TD_DOWN_PGDN),	TD(TD_RIGHT_END),	KC_NO,
	KC_NO,  KC_3,  KC_2,KC_1,  KC_SLSH,                            			KC_NO,  KC_NO,			    KC_NO,              KC_NO,		        KC_NO,
						KC_0,  KC_AMPR,TD(TD_BSPACE_2),  TD(TD_SPACE_2),	KC_NO,  KC_ENT
	),



// /*
// *SymLayer:NumbersAndSymbols
// *
// *,----------------------------------------------.									,-----------------------------------------------.
// *|	'	|		|		|		|		|		|									|		|		|		|		|		|		|
// *|-------+-------+-------+-------+-------+-------|									|-------+-------+-------+-------+-------+-------|
// *|	~	|	!	|	@	|	#	|	$	|		|									|	^	|	&	|	*	|		|		|		|
// *|-------+-------+-------+-------+-------+-------+---------------.	,---------------+-------+-------+-------+-------+-------+-------|
// *|	|	|	\	|		|		|		|		|		|		|	|		|		|		|		|		|		|		|	?	|
// *'-----------------------+-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------+-----------------------'
// *						|		|		|		|	_FUN|		|	|		|	_CK	|		|		|		|
// *						'---------------------------------------'	'---------------------------------------'
// */
// 	[_SYM]=LAYOUT(
// 	KC_GRV,	KC_NO,	KC_NO,KC_NO,	KC_NO,	KC_NO,														KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,KC_NO,
// 	KC_TILD,KC_EXLM,KC_AT,KC_HASH,	KC_DLR,	KC_NO,													KC_CIRC,KC_AMPR,KC_ASTR,KC_NO,	KC_NO,KC_NO,
// 	KC_PIPE,KC_BSLS,KC_NO,KC_NO,	KC_NO,	KC_NO,	KC_NO,        	KC_NO,		KC_NO,KC_NO,			KC_NO,	KC_NO,	KC_NO,	KC_NO,	KC_NO,KC_QUES,
// 							KC_NO,	KC_NO,	KC_NO,	TO(_FUNCTION),	KC_NO,		KC_NO,TO(_COLEMAK_DH),	KC_NO,	KC_NO,	KC_NO
// 	),

/*
*FunctionLayer:Functionkeys
*
*,--------------------------------------.					,---------------------------------------.
*|	F9	|	F10	|	F11	|	F12	|		|					|		|		|		|		|		|
*|------+-------+-------+-------+-------|					|-------+-------+-------+-------+-------|
*|	F5	|	F6	|	F7	|	F8	|		|					|		|Shift	|Ctrl	|Alt	|GUI	|
*|------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------|
*|	F1	|	F2	|	F3	|	F4	|		|                   |		|		|		|		|		|
*'----------------------+-------+-------+-------.	.-------+-------+-------+-----------------------'
*						|		|		|		|	|		|_CK	|		|
*						'-----------------------'	'-----------------------'
*/
	[_FUNCTION]=LAYOUT_F_3x5(
	KC_F9,KC_F10,	KC_F11,	KC_F12,	KC_NO,					    KC_NO,              KC_NO,	    KC_NO,	KC_NO,	KC_NO,
	KC_F5,KC_F6,	KC_F7,	KC_F8,	KC_NO,						KC_NO,              KC_RSFT,	KC_RCTL,KC_LALT,KC_RGUI,
	KC_F1,KC_F2,	KC_F3,	KC_F4,	KC_NO,                      KC_NO,              KC_NO,	    KC_NO,	KC_NO,	KC_NO,
							KC_NO,	KC_NO,	KC_NO,		KC_NO,  TO(_COLEMAK_DH),	KC_NO
	),

/*
	*Mouse Layer
	*
	*,--------------------------------------.					,---------------------------------------.
	*|		|		|		|		|		|					|		|		|		|		|		|
	*|------+-------+-------+---------------|					|-------+-------+-------+-------+-------|
	*|		|		|		|		|		|					|		|		|		|		|		|
	*|------+-------+-------+-------+-------|       	        |-------+-------+-------+-------+-------|
	*|		|		|		|		|		|       	        |		|		|		|		|		|
	*'----------------------+-------+-------+-------.	.-------+-------+-------+-------+---------------'
	*				        |		|		|		|	|		|		|		|
	*				        '-----------------------'	'-----------------------'
	*/
		[_MOUSE]=LAYOUT_F_3x5(
		_______,_______,_______,USR_CPY,_______,	                _______,_______,_______,_______,_______,
		_______,_______,_______,USR_PST,_______,	                _______,_______,_______,_______,_______,
		_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,
								KC_BTN3,KC_BTN1,KC_BTN2,    KC_BTN2,KC_BTN1,KC_BTN3
		),

///*
//	*Layertemplate
//	*
//	*
//	*,--------------------------------------.					,---------------------------------------.
//	*|		|		|		|		|		|					|		|		|		|		|		|
//	*|------+-------+-------+---------------|					|-------+-------+-------+-------+-------|
//	*|		|		|		|		|		|					|		|		|		|		|		|
//	*|------+-------+-------+-------+-------|       	        |-------+-------+-------+-------+-------|
//	*|		|		|		|		|		|       	        |		|		|		|		|		|
//	*'----------------------+-------+-------+-------.	.-------+-------+-------+-------+---------------'
//	*				        |		|		|		|	|		|		|		|
//	*				        '-----------------------'	'-----------------------'
//	*/
//	*/
//		[_LAYERINDEX]=LAYOUT(
//		_______,_______,_______,_______,_______,					_______,_______,_______,_______,_______,
//		_______,_______,_______,_______,_______,					_______,_______,_______,_______,_______,
//		_______,_______,_______,_______,_______,                    _______,_______,_______,_______,_______,
//								_______,_______,_______,    _______,_______,_______
//		),
};
// clang-format on

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    if (abs(mouse_report.x) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD || abs(mouse_report.y) > CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_THRESHOLD) {
        if (auto_pointer_layer_timer == 0) {
            layer_on(CHARYBDIS_AUTO_SNIPING_ON_LAYER);
        }
        auto_pointer_layer_timer = timer_read();
    }
    return mouse_report;
}

void matrix_scan_user(void) {
    if (auto_pointer_layer_timer != 0 && TIMER_DIFF_16(timer_read(), auto_pointer_layer_timer) >= CHARYBDIS_AUTO_POINTER_LAYER_TRIGGER_TIMEOUT_MS) {
        auto_pointer_layer_timer = 0;
        layer_off(CHARYBDIS_AUTO_SNIPING_ON_LAYER);
    }
}

layer_state_t layer_state_set_user(layer_state_t state) {
    charybdis_set_pointer_sniping_enabled(layer_state_cmp(state, CHARYBDIS_AUTO_SNIPING_ON_LAYER));
    switch (get_highest_layer(state)) {
        case _COLEMAK_DH:
            rgb_matrix_sethsv(0, 255, 100);
            break;
        case _NUMNAV:
            rgb_matrix_sethsv(169, 255, 100);
            break;
        case _SYM:
            rgb_matrix_sethsv(180, 255, 100);
            break;
        case _FUNCTION:
            rgb_matrix_sethsv(85, 255, 100);
            break;
        case _MOUSE:
            rgb_matrix_sethsv(0, 0, 100);
            break;
    }
    return state;
}

void keyboard_post_init_user(void) {
    pointing_device_set_cpi(3000);

#ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_DEFAULT_MODE);
    rgb_matrix_set_speed(125);
    rgb_matrix_sethsv(0, 255, 100);
#endif
}