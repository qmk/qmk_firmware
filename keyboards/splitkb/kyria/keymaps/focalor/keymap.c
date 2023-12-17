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
#include "./keymap_portuguese_mac_iso.h"

// clang-format off
enum layers { 
	_COLEMAK_DH = 0,
	_NAV,
	_SYM,
	_FUNCTION
};

enum {
	TD_LEFT_HOME,
	TD_RIGHT_END,
	TD_UP_PGUP,
	TD_DOWN_PGDN,
	TD_SPACE_L1,
	TD_BSPACE_L2,
	CT_LBRK,
	CT_RBRK,
	O_A,
	MIN_UND
};
// clang-format on
// Aliases for readability
#define COLEMAK DF(_COLEMAK_DH)
#define SYM MO(_SYM)
#define NAV MO(_NAV)
#define FKEYS MO(_FUNCTION)

#define CTL_ESC MT(MOD_LCTL, KC_ESC)
#define CTL_QUOT MT(MOD_RCTL, KC_QUOTE)
#define CTL_MINS MT(MOD_RCTL, KC_MINUS)
#define ALT_ENT MT(MOD_LALT, KC_ENT)

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
		[TD_SPACE_L1] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_SPC, _NAV),
		[TD_BSPACE_L2] = ACTION_TAP_DANCE_LAYER_TOGGLE(KC_BSPC, _SYM),
		[CT_LBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, left_brackets_finished, left_brackets_reset),
		[CT_RBRK] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, right_brackets_finished, right_brackets_reset),
		[O_A] = ACTION_TAP_DANCE_DOUBLE(PT_MORD, PT_FORD),
		[MIN_UND] = ACTION_TAP_DANCE_DOUBLE(PT_UNDS, PT_MINS),
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     *BaseLayer:ColemakDH
     *
     *,-------------------------------------------------.									,-----------------------------------------------.
     *|	ESC     |	Q	|	W	|	F	|	P	|	B	|									|	J	|	L	|	U	|	Y	|	ºª  |KC_SPC |
     *|---------+-------+-------+-------+-------+-------|									|-------+-------+-------+-------+-------+-------|
     *|KC_TAB	|	A	|	R	|	S	|	T	|	G	|									|	M	|	N	|	E	|	I	|	O	|   `´	|
     *|---------+-------+-------+-------+-------+-------+-------------.		,---------------+-------+-------+-------+-------+-------+-------|
     *|			|	Z	|	X	|	C	|	D	|	V	|XXXXXXX|	  |		|	∆	|XX		|	K	|	H	|	,;  |	.:  |	-_	|   ^~  |
     *`---------+-------+-------+-------+-------+-------+-------+-----|		|-------+-------+-------+-------+-------+-----------------------'
     *						    |		|		|([{    |Space  |     |		|	µ	|	    ||}])   |   ENT |		|
     *							`-------------------------------------'		`---------------------------------------'
     */
    [_COLEMAK_DH] = LAYOUT(
			KC_ESC, KC_Q, KC_W, 	KC_F, KC_P, KC_B, 																														KC_J, 			KC_L, 	KC_U, 	KC_Y, 	TD(O_A),		KC_NO,
			KC_TAB, KC_A, KC_R, 	KC_S, KC_T, KC_G,																															KC_M, 			KC_N, 	KC_E, 	KC_I, 	KC_O, 			KC_NO,
			KC_NO, 	KC_Z, KC_X, 	KC_C, KC_D, KC_V, 		KC_NO,			PT_PIPE,		PT_INCR,KC_NO,						KC_K, 			KC_H, 	KC_COMM,KC_DOT, TD(MIN_UND),KC_NO,
									KC_NO,KC_NO,TD(CT_LBRK),TD(TD_SPACE_L1),KC_NO,			PT_MICR,TD(TD_BSPACE_L2),	TD(CT_RBRK),KC_ENT,	KC_NO),

    /*
     *NavLayer:Media,navigation
     *
     *,-----------------------.												,-----------------------.
     *|		|		|		|		|		|		|												|		|		|	↑	|		|		|		|
     *|---+---+---+---+---+---|												|---+---+---+---+---+---|
     *|		|		|		|		|		|		|												|		|	←	|	↓	|	→	|		|		|
     *|---+---+---+---+---+---+---------.		,---------+---+---+---+---+---+---|
     *|		|		|		|		|		|		|			|		|		|		|			|		|		|		|		|		|		|
     *`-------+---+---+---+---+-----+---|		|---+-----+---+---+---+-----------'
     *						|		|		|		|_SYM	|		|		|		|	_CK	|		|		|		|
     *						`---------------------'		`---------------------'
     */
    [_NAV] = LAYOUT(
			KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, 																					KC_NO, KC_NO, 						TD(TD_UP_PGUP), 	KC_NO, 						KC_NO, KC_NO,
			KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, 																					KC_NO, TD(TD_LEFT_HOME),	TD(TD_DOWN_PGDN), TD(TD_RIGHT_END), KC_NO, KC_NO, 
			KC_NO, KC_NO, KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,		KC_NO,		KC_NO,KC_NO,					KC_NO, KC_NO, 						KC_NO, 						KC_NO, 						KC_NO, KC_NO,
													KC_NO, KC_NO, KC_NO, TO(_SYM),KC_NO,		KC_NO,TO(_COLEMAK_DH),KC_NO, KC_NO, 						KC_NO),

    /*
     *SymLayer:Numbersandsymbols
     *
     *,-----------------------.									,-----------------------.
     *|	`	|	1	|	2	|	3	|	4	|	5	|									|	6	|	7	|	8	|	9	|	0	|	=	|
     *|---+---+---+---+---+---|									|---+---+---+---+---+---|
     *|	~	|	!	|	@	|	#	|	$	|	%	|									|	^	|	&	|	*	|	(	|	)	|	+	|
     *|---+---+---+---+---+---+-------.	,-------+---+---+---+---+---+---|
     *|	|	|	\	|	:	|	;	|	-	|	[	|	{	 |- |	|		|	}	|	]	|	_	|	,	|	.	|	/	|	?	|
     *`-------+---+---+---+---+----+--|	|---+---+---+---+---+---+-------'
     *						|		|		|   |_FUN|	|	|		|_CK|		|		|		|
     *						`---------------------'	`-----------------'
     */
    [_SYM] = LAYOUT(
			KC_GRV, KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 																										KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, 	KC_EQL,
			KC_TILD,KC_EXLM,KC_AT,	KC_HASH,KC_DLR, KC_PERC, 																									KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,KC_PLUS,
			KC_PIPE,KC_BSLS,KC_COLN,KC_SCLN,KC_MINS,PT_LBRC, 	KC_LCBR,			KC_NO, 		KC_NO, KC_RCBR, 				PT_RBRC,KC_UNDS,KC_COMM,KC_DOT, KC_SLSH,KC_QUES,
															KC_NO, 	KC_NO, 	KC_NO,		TO(_FUNCTION),KC_NO, 		KC_NO, TO(_COLEMAK_DH), KC_NO, 	KC_NO, 	KC_NO),

    /*
     *FunctionLayer:Functionkeys
     *
     *,---------------------------.										,---------------------------.
     *|		|	F9	|	F10	|F11|F12|		|										|		|			|			|		|		|		|
     *|---+-----+-----+---+---+---|										|---+-----+-----+---+---+---|
     *|		|	F5	|	F6	|	F7|	F8|		|										|		|Shift|Ctrl	|Alt|GUI|		|
     *|---+-----+-----+---+---+---+-------.		,-------+---+-----+-----+---+---+---|
     *|		|	F1	|	F2	|	F3|F4	|		|		|		|		|		|		|		|			|			|		|		|		|
     *`---------+-----+---+---+---+-------|		|---+---+---+-----+-----+---+-------'
     *								|		|		|		|		|		|		|		|_CK|		|			|			|
     *								`-------------------'		`-----------------------'
     */
    [_FUNCTION] = LAYOUT(
			KC_NO, KC_F9, KC_F10,	KC_F11,KC_F12,KC_NO, 																				KC_NO, KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 
			KC_NO, KC_F5, KC_F6,	KC_F7, KC_F8, KC_NO, 																				KC_NO, KC_RSFT, KC_RCTL,KC_LALT,KC_RGUI,KC_NO, 
			KC_NO, KC_F1, KC_F2,	KC_F3, KC_F4, KC_NO, KC_NO, KC_NO, 		KC_NO,KC_NO,					KC_NO, KC_NO, 	KC_NO,	KC_NO, 	KC_NO, 	KC_NO,
														KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 		KC_NO,TO(_COLEMAK_DH),KC_NO, KC_NO, 	KC_NO),

    ///*
    //	*Layertemplate
    //	*
    //	*,----------------------------------------------.									,-----------------------------------------------.
    //	*|		|		|		|		|		|		|									|		|		|		|		|		|		|
    //	*|------+-------+-------+-------+---------------|									|-------+-------+-------+-------+-------+-------|
    //	*|		|		|		|		|		|		|									|		|		|		|		|		|		|
    //	*|------+-------+-------+-------+-------+-------+---------------.	,---------------+-------+-------+-------+-------+-------+-------|
    //	*|		|		|		|		|		|		|		|		|	|		|		|		|		|		|		|		|		|
    //	*`------------------------------+-------+-------+-------+-------|	|-------+-------+-------+-------+-------+-----------------------'
    //	*						|		|		|		|		|		|	|		|		|		|		|		|
    //	*						`---------------------------------------'	`---------------------------------------'
    //	*/
    //		[_LAYERINDEX]=LAYOUT(
    //		_______,_______,_______,_______,_______,_______,																	_______,_______,_______,_______,_______,_______,
    //		_______,_______,_______,_______,_______,_______,																	_______,_______,_______,_______,_______,_______,
    //		_______,_______,_______,_______,_______,_______,_______,_______,	_______,_______,_______,_______,_______,_______,_______,_______,_______,_______,
    //										_______,_______,_______,_______,_______,_______,	_______,_______,_______,_______,_______,_______
    //		),
};

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _COLEMAK_DH:
            if (is_master) {
                static const char PROGMEM qmk_logo[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0};

                oled_write_P(qmk_logo, false);
                oled_write_P(PSTR("Kyria rev3.0\n\n"), false);
            } else {
                static const char PROGMEM kyria_logo[] = {0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   128, 128, 192, 224, 240, 112, 120, 56,  60,  28, 30, 14, 14, 14, 7,  7,   7,   7,   7,  7, 7,   7,   7, 7,  7,   7,   7,   7,  7,  7,  14, 14, 14,  30,  28,  60,  56,  120, 112, 240, 224, 192, 128, 128, 0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   192, 224, 240, 124, 62,  31,  15,  7,   3,   1,   128, 192, 224, 240, 120, 56,  60, 28, 30, 14, 14, 7,   7,   135, 231, 127, 31,  255, 255, 31,  127, 231, 135, 7,  7,  14,
                                                          14, 30, 28,  60,  56,  120, 240, 224, 192, 128, 1,   3,   7,   15,  31,  62,  124, 240, 224, 192, 0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   240, 252, 255, 31,  7,   1,  0,   0,   192, 240, 252, 254, 255, 247, 243, 177, 176, 48,  48,  48,  48,  48,  48,  48,  120, 254, 135, 1,   0,   0,   255, 255, 0,   0,   1,   135, 254, 120, 48,  48,  48, 48, 48,  48,  48,  176, 177, 243, 247, 255, 254, 252, 240, 192, 0,   0,   1,   7,   31,  255, 252, 240, 0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                                          0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   254, 255, 255, 1,   1,   7,  30, 120, 225, 129, 131, 131, 134, 134, 140, 140, 152, 152, 177, 183, 254, 248, 224, 255, 255, 224, 248, 254, 183, 177, 152, 152, 140, 140, 134, 134, 131, 131, 129, 225, 120, 30, 7,   1,   1,   255, 255, 254, 0,   0,   0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   255, 255, 0,   0,   192, 192, 48,  48,  0,   0,   240, 240, 0,   0,   0,   0,   0,  0,  240, 240, 0,   0,   240, 240, 192, 192, 48,  48,  48,  48,  192, 192, 0,   0,   48,  48,  243, 243, 0,  0,  0,  0,  0,  0,   48,  48,  48,  48,  48,  48,  192, 192, 0,   0,   0,   0,  0,  0,
                                                          0,  0,  255, 255, 255, 0,   0,   0,   0,   0,   127, 255, 255, 128, 128, 224, 120, 30,  135, 129, 193, 193, 97, 97, 49, 49, 25, 25, 141, 237, 127, 31, 7, 255, 255, 7, 31, 127, 237, 141, 25, 25, 49, 49, 97, 97,  193, 193, 129, 135, 30,  120, 224, 128, 128, 255, 255, 127, 0,  0,  0,   0,   0,   255, 255, 255, 0,   0,   0,   0,   63,  63,  3,   3,   12,  12,  48,  48,  0,   0,   0,   0,   51,  51,  51,  51,  51,  51,  15,  15,  0,   0,   63,  63,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   48,  48,  63,  63,  48,  48,  0,   0,   12,  12,  51,  51,  51,  51,  51,  51,  63,  63,  0,   0,   0,   0,   0,   0,   0,   0,  0,  15,  63,  255, 248, 224, 128, 0,   0,   3,   15,  63,  127, 255, 239, 207, 141, 13,  12,  12,  12,  12, 12, 12, 12, 30, 127, 225, 128, 0,   0,   255, 255, 0,   0,   128, 225, 127, 30, 12, 12,
                                                          12, 12, 12,  12,  12,  13,  141, 207, 239, 255, 127, 63,  15,  3,   0,   0,   128, 224, 248, 255, 63,  15,  0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   3,   7,   15,  62, 124, 248, 240, 224, 192, 128, 1,   3,   7,   15,  30,  28,  60,  56,  120, 112, 112, 224, 224, 225, 231, 254, 248, 255, 255, 248, 254, 231, 225, 224, 224, 112, 112, 120, 56, 60, 28,  30,  15,  7,   3,   1,   128, 192, 224, 240, 248, 124, 62,  15,  7,   3,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,
                                                          0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,  0,   0,   0,   0,  0, 0,   0,   0, 0,  0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   3,   7,   15, 14, 30,  28,  60,  56,  120, 112, 112, 112, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 224, 112, 112, 112, 120, 56,  60,  28,  30,  14,  15,  7,  3,   1,   1,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,  0,  0,  0,  0,  0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0};
                oled_write_raw_P(kyria_logo, sizeof(kyria_logo));
            }
            break;
        case _NAV:
            if (is_master) {
                oled_write_P(PSTR(",-----------------.\n"
                                  "|  |  |  |  |  |  |\n"
                                  "|--+--+--+--+--+--|\n"
                                  "|  |  |  |  |  |  |\n"
                                  "|--+--+--+--+--+--+-----.\n"
                                  "|  |  |  |  |  |  |  |  |\n"
                                  "`--------+--+--+--+--+--|\n"
                                  "         |  |  |  |  |  |\n"
                                  "         `--------------"),
                             false);
            }else {
                oled_write_P(PSTR("      ,-----------------.\n"
                                  "      |  |  | ↑|  |  |  |\n"
                                  "      |--+--+--+--+--+--|\n"
                                  "      |  | ←| ↓| →|  |  |\n"
                                  ",--+--+--+--+--+--+--+--|\n"
                                  "|  |  |  |  |  |  |  |  |\n"
                                  "|--+--+--+--+--+--------\n"
                                  "|  |  |  |  |  |\n"
                                  "`--------------"),
                             false);
            }
            break;
        case _SYM:
            if (is_master) {
                oled_write_P(PSTR(",-----------------.\n"
                                  "| `| 1| 2| 3| 4| 5|\n"
                                  "|--+--+--+--+--+--|\n"
                                  "| ~| !| @| #| $| %|\n"
                                  "|--+--+--+--+--+--+-----.\n"
                                  "| ||\\| :| ;| -| [| {|  |\n"
                                  "`--------+--+--+--+--+--|\n"
                                  "         |  |  |  |_F|  |\n"
                                  "         `--------------"),
                             false);
			}else{
                oled_write_P(PSTR("      ,-----------------.\n"
                                  "      | 6| 7| 8| 9| 0| =|\n"
                                  "      |--+--+--+--+--+--|\n"
                                  "      | ^| &| *| (| )| +|\n"
                                  ",-----+--+--+--+--+--+--|\n"
                                  "|  | }| ]| _| ,| .| /| ?|\n"
                                  "|--+--+--+--+--+--------'\n"
                                  "|  |CK|  |  |  |\n"
                                  "`--------------'"),
                             false);
            }
            break;
        case _FUNCTION:
            if (is_master) {
                oled_write_P(PSTR(",-----------------.\n"
                                  "|  |F9|F10|F11|F12|  |\n"
                                  "|--+--+--+--+--+--|\n"
                                  "|  |F5|F6|F7|F8|  |\n"
                                  "|--+--+--+--+--+--+----.\n"
                                  "|  |F1|F2|F3|F4|  |  |  |\n"
                                  "`--------+--+--+--+--+--|\n"
                                  "            |  |  |  |  |  |\n"
                                  "            `-----------'"),
                             false);
			}else{
                oled_write_P(PSTR("       ,-----------------.\n"
                                  "       |  |  |  |  |  |  |\n"
                                  "       |--+--+--+--+--+--|\n"
                                  "       |  |Sf|Ct|Al|GU|  |\n"
                                  " ,-----+--+--+--+--+--+--|\n"
                                  " |  |  |  |  |  |  |  |  |\n"
                                  " |--+--+--+--+--+--------'\n"
                                  " |  |CK|  |  |  |\n"
                                  " `--------------'"),
                             false);
            }
            break;
        default:
            oled_write_P(PSTR("Undefined\n"), false);
    }
    return false;
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(C(KC_RGHT));
        } else {
            tap_code16(C(KC_LEFT));
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    }
    return false;
}

layer_state_t layer_state_set_user(layer_state_t state){
		oled_clear();
    switch(get_highest_layer(state)){
        case _COLEMAK_DH:
            rgb_matrix_sethsv(0, 255, 100);
            break;
        case  _NAV:
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