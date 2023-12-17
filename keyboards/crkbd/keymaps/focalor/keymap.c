#include QMK_KEYBOARD_H
#include "os_detection.h"
#include "quantum.h"
#include "./keymap_portuguese_mac_iso.h"
#include "gpio.h"

// clang-format off
enum layers {
	_COLEMAK_DH = 0,
	_NUMNAV,
  _SYM,
	_FUNCTION
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
*|	%	|	9	|	8	|	7	|	+	|					|		|		|	↑	|		|		|
*|------+-------+-------+-------+-------|					|-------+-------+-------+-------+-------|
*|	=	|	6	|	5	|	4	|	-	|					|		|	←	|	↓	|	→	|		|
*|------+-------+-------+-------+-------|                   |-------+-------+-------+-------+-------|
*|		|	3	|	2	|	1	|	*	|                   |		|		|		|		|		|
*'--------------+-------+-------+-------+-------.   .-------|-------+-------+-----------------------'
*						|	0	|	/	|_SYM	|	|_CK	|   	|ENT	|
*						'-----------------------'	'-----------------------'
*/
	[_NUMNAV]=LAYOUT_F_3x5(
	KC_EQL,	KC_9,  KC_8,KC_7,  KC_PLUS,                            			KC_NO,  KC_NO,			    TD(TD_UP_PGUP),		KC_NO,				KC_NO,
	KC_PERC,KC_6,  KC_5,KC_4,  KC_MINS,                            			KC_NO,  TD(TD_LEFT_HOME),	TD(TD_DOWN_PGDN),	TD(TD_RIGHT_END),	KC_NO,
	KC_NO,  KC_3,  KC_2,KC_1,  KC_SLSH,                            			KC_NO,  KC_NO,			    KC_NO,              KC_NO,		        KC_NO,
						KC_0,  KC_AMPR,TD(TD_BSPACE_2),  TD(TD_SPACE_2),	KC_NO,  KC_ENT
	),



// /*
// *SymLayer:Symbols
// *
// *,----------------------------------------------.									,-----------------------------------------------.
// *|		|	!	|	"	|	#	|	$	|	@	|									|	&	|	\	|	|	|	'	|	?	|		|
// *|-------+-------+-------+-------+-------+-------|									|-------+-------+-------+-------+-------+-------|
// *|		|		|		|		|		|		|									|		|		|		|		|		|		|
// *|-------+-------+-------+-------+-------+-------+---------------.	,---------------+-------+-------+-------+-------+-------+-------|
// *|		|		|		|		|		|		|		|		|	|		|		|		|		|		|		|		|		|
// *'-----------------------+-------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------+-----------------------'
// *						|		|		|		|	_FUN|		|	|		|	_CK	|		|		|		|
// *						'---------------------------------------'	'---------------------------------------'
// */
// 	[_SYM]=LAYOUT(
// 	KC_GRV,	KC_EXLM,KC_NO,KC_HASH,	KC_DLR,	KC_AT,														KC_NO,	KC_NO,	KC_PIPE,	KC_NO,	KC_QUES,KC_NO,
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

layer_state_t layer_state_set_user(layer_state_t state) {
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
    }
    return state;
}