/* 
 * Good on you for modifying your layout, this is the most nonQMK layout you will come across
 * There are three modes, Steno (the default), QWERTY (Toggleable) and a Momentary symbol layer
 *
 * Don't modify the steno layer directly, instead add chords using the keycodes and macros
 * from sten.h to the layout you want to modify.
 *
 * Observe the comment above processQWERTY!
 */

#include QMK_KEYBOARD_H
#include "keymap_steno.h"
#include "sten.h"
#define IGNORE_MOD_TAP_INTERRUPT

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Steno layer
 * FN1: 		Qwerty Toggle (processQwerty)
 * PWR:		 	Symbol Momentary (Combo with press, processSymbol)
 * FN1+PWR:		Command Mode
 *
 * ,-------------------------.    ,-----------------------.
 * | FN1 | S | T | P | H |ST1|    |ST3| F | P | L | T | D |
 * |-----+---+---+---+---|---|    |---|---+---+---+---+---|
 * | PWR | S | K | W | R |ST2|    |ST4| R | G | B | S | Z |
 * `-------------------------'    `-----------------------'
 *               ,-----------,    .-----------.
 *               | # | A | O |    | E | U | # |
 *               `-----------'    `-----------'
 */
// Temporary Gergo Shim
[0] = LAYOUT_GERGO(  
KC_NO,KC_NO,   KC_NO,KC_NO,KC_NO,KC_NO,                         KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,KC_NO, 
KC_NO,STN_FN,  STN_S1, STN_TL, STN_PL, STN_HL, STN_ST1,       STN_ST3, STN_FR, STN_PR, STN_LR, STN_TR, STN_DR, KC_NO, 
KC_NO,STN_PWR, STN_S2, STN_KL, STN_WL, STN_RL, STN_ST2,       STN_ST4, STN_RR, STN_BR, STN_GR, STN_SR, STN_ZR, KC_NO,
                                      
			                             KC_NO, STN_N1,       STN_N1, KC_NO,
                                                 KC_NO,       KC_NO,
                                		  STN_A, STN_O,       STN_E, STN_U)
};

//P will return from processing on the first match it finds. Therefore
//YOU MUST ORDER THIS!
//
//First any mods should be checked, you can use the PJ macro to suppress the return
//Also, your chords should be arranged from Longest to shortest
void processQwerty(void) {
	// Mods 
	PJ( RT | RD | RS | RZ, 			register_code(KC_LGUI););
	PJ( RT | RD, 					register_code(KC_LCTL););
	PJ( RS | RZ, 					register_code(KC_LSFT););
	PJ( LA | LO, 					register_code(KC_LALT););
	PJ( LA | NUM, 					register_code(KC_LGUI););

	// Letters
	P( RU | NUM, 					register_code(KC_TAB););
	P( RE | RU, 					register_code(KC_DOT););
	P( LSU | LSD,			 		register_code(KC_A););
	P( LFT | LK, 					register_code(KC_S););
	P( LP  | LW, 					register_code(KC_D););
	P( LH  | LR, 					register_code(KC_F););
	P( ST1 | ST2, 					register_code(KC_G););
	P( ST3 | ST4, 					register_code(KC_H););
	P( RF  | RR, 					register_code(KC_J););
	P( RD  | RZ, 					register_code(KC_ENT););
	P( RT  | RS, 					register_code(KC_SCLN););
	P( RG  | RL, 					register_code(KC_L););
	P( RP  | RB, 					register_code(KC_K););
	P( LSU,							register_code(KC_Q););
	P( LSD,		 					register_code(KC_Z););
	P( LFT,		 					register_code(KC_W););
	P( LK, 							register_code(KC_X););
	P( LP, 							register_code(KC_E););
	P( LW, 							register_code(KC_C););
	P( LH, 							register_code(KC_R););
	P( LR, 							register_code(KC_V););
	P( ST1, 						register_code(KC_T););
	P( ST2, 						register_code(KC_B););
	P( ST3, 						register_code(KC_Y););
	P( ST4, 						register_code(KC_N););
	P( RF, 							register_code(KC_U););
	P( RR, 							register_code(KC_M););
	P( RP, 							register_code(KC_I););
	P( RB, 							register_code(KC_COMM););
	P( RL,		 					register_code(KC_O););
	P( RG,	 						register_code(KC_DOT););
	P( RT, 							register_code(KC_P););
	P( RS, 							register_code(KC_SLSH););
	P( RD, 							register_code(KC_L););
	P( RZ, 							register_code(KC_LSFT););

	P( LA, 							register_code(KC_SPC););
	P( RU, 							register_code(KC_SPC););
	P( LO, 							register_code(KC_ESC););
	P( RE, 							register_code(KC_ENT););
	P( NUM, 						register_code(KC_BSPC););

	return;
}

// Read the above notice
void processSymbol(void) {
	P( RE | RU, 				register_code(KC_ENT););
	P( LA | LO, 				register_code(KC_ENT););
	P( LP | LW, 				register_code(KC_LSFT); register_code(KC_9);); // (
	P( LH | LR,		 			register_code(KC_LSFT); register_code(KC_0);); // )
	P( ST1 | ST2, 				register_code(KC_GRV););
	P( RD | RZ, 				register_code(KC_ESC););
	P( LSU | LSD, 				register_code(KC_LSFT); register_code(KC_3);); // #
	P( LFT | LK, 				register_code(KC_LSFT); register_code(KC_4);); // $

	P( NUM | LSU, 				register_code(KC_1););
	P( NUM | LFT, 				register_code(KC_2););
	P( NUM | LP, 				register_code(KC_3););
	P( NUM | LH, 				register_code(KC_4););
	P( NUM | ST1, 				register_code(KC_5););
	P( NUM | ST3, 				register_code(KC_6););
	P( NUM | RF, 				register_code(KC_7););
	P( NUM | RP, 				register_code(KC_8););
	P( NUM | RL, 				register_code(KC_9););
	P( NUM | RT, 				register_code(KC_0););
	P( NUM | LA, 				register_code(KC_5););
	P( NUM | RT, 				register_code(KC_0););

	P( LSU, 					register_code(KC_LSFT); register_code(KC_1);); // !
	P( LSD, 					register_code(KC_LSFT); register_code(KC_5);); // %
	P( LFT,						register_code(KC_LSFT); register_code(KC_2);); // @
	P( LK, 						register_code(KC_LSFT); register_code(KC_6);); // ^
	P( LP, 						register_code(KC_LSFT); register_code(KC_LBRC);); // {
	P( LW, 						register_code(KC_LBRC););
	P( LH, 						register_code(KC_LSFT); register_code(KC_RBRC);); // }
	P( LR, 						register_code(KC_RBRC););
	P( ST1,						register_code(KC_LSFT); register_code(KC_BSLS);); // |
	P( ST2, 					register_code(KC_LSFT); register_code(KC_GRV);); // ~
	P( ST3, 					register_code(KC_QUOT););
	P( ST4, 					register_code(KC_MINS););
	P( RF, 						register_code(KC_KP_PLUS););
	P( RR, 						register_code(KC_LSFT); register_code(KC_7);); // &
	P( RP, 						register_code(KC_MINS););
	P( RB, 						register_code(KC_EQL););
	P( RL, 						register_code(KC_SLSH););
	P( RG, 						register_code(KC_COMM););
	P( RT, 						register_code(KC_PAST););
	P( RS, 						register_code(KC_DOT););
	P( RD, 						register_code(KC_TAB););
	P( RZ, 						register_code(KC_LSFT););
	P( LA, 						register_code(KC_SCLN););
	P( LO, 						register_code(KC_SLSH););
	P( RE, 						register_code(KC_SCLN););
	P( RU, 						register_code(KC_SLSH););

	return;
	//case STN(RG) | STN(RL): 			register_code(KC_L); break;
	//case STN(ST3) | STN(ST4): 			register_code(KC_H); break;
	//case STN(RF) | STN(RR): 			register_code(); break;
	//case STN(RP) | STN(RB): 			register_code(KC_K); break;
	//case STN(RT) | STN(RS): 			register_code(KC_SCLN); break;
	
}

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {
  steno_set_mode(STENO_MODE_GEMINI); // or STENO_MODE_BOLT
};

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {
};
