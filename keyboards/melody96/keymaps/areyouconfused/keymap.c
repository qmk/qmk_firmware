#include QMK_KEYBOARD_H

#include "my_keycodes.h"

enum layers {
	_QWERTY,
	_RAISE,
	_LOWER,
	_ADJUST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_QWERTY] = LAYOUT_hotswap(
	 //---ESC---|----F1---|---F2----|----F3---|----F4---|----F5---|----F6---|----F7---|----F8---|----F9---|---F10---|----F11---|---F12---|---HOME--|---END---|---PGUP--|---PGDN--|---PRT---|----DEl---
	     KC_ESC,	KC_F1,	KC_F2,	KC_F3,	KC_F4,	KC_F5, 	KC_F6, 	KC_F7, 	KC_F8, 	KC_F9, 	KC_F10, 	KC_F11, 	KC_F12, 	KC_HOME, 	KC_END, 	KC_PGUP, 	KC_PGDN, 	KC_PSCR, 	KC_DEL, 
	 //--grave--|----1----|----2----|----3----|----4----|----5----|----6----|----7----|----7----|----9----|----0----|----sub---|----=----|--------back-------|----NL---|---div---|---mult--|----sub---
         	KC_GRV, 	KC_1, 	KC_2, 	KC_3, 	KC_4, 	KC_5, 	KC_6, 	KC_7, 	KC_8, 	KC_9, 	KC_0, 	KC_MINS, 	KC_EQL,		KC_BSPC,    	KC_NLCK, 	KC_PSLS, 	KC_PAST, 	KC_PMNS, 
	 //----tab---|----q---|----w----|----e----|----r----|----t----|----y----|----u----|----i----|----o----|----p----|-----[-----|------]-----|-------\-------|----7----|----8----|----9----|
	    	KC_TAB, 	KC_Q, 	KC_W, 	KC_E, 	KC_R, 	KC_T, 	KC_Y, 	KC_U, 	KC_I, 	KC_O, 	KC_P, 	KC_LBRC, 	KC_RBRC,		KC_BSLS,		KC_P7, 	KC_P8, 	KC_P9, 
	 //----caps---|---A----|---s----|----d----|----f----|----g----|----h----|----j----|----k----|----l----|----;----|-----'-----|---------enter--------------|----4----|----5----|----6----|----+-----
	    	KC_CAPS, 	  KC_A, 	KC_S, 	KC_D, 	KC_F, 	KC_G, 	KC_H, 	KC_J, 	KC_K, 	KC_L, 	KC_SCLN, 	KC_QUOT, 			KC_ENT, 			KC_P4, 	KC_P5, 	KC_P6, 	KC_PPLS, 
	 //----shift---|-----z-----|----x----|----c-----|---v----|----b----|----n-----|----m----|----,-----|-----.----|-----/------|-----shift------|------up----|----1----|----2----|----3----|
	    	KC_LSFT, 		KC_Z, 	KC_X, 	KC_C, 	KC_V, 	KC_B, 	KC_N, 	KC_M, 	KC_COMM, 	 KC_DOT, 	  KC_SLSH, 	 KC_RSFT, 		 KC_UP, 	KC_P1, 	KC_P2, 	KC_P3, 
	 //---ctrl---|---gui----|----alt-----|----------------------space------------------|-------alt----|------fn----|------ctrl------------|------left---|--down--|---right--|----0----|----.----|---enter---
	    	KC_LCTL, 	KC_LGUI, 	KC_LALT, 							KC_SPC, 				KC_RALT, 	MO(_RAISE), 	LT(_LOWER, KC_RCTL), 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_P0, 	KC_PDOT, 	KC_PENT),
	 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

     [_RAISE] = LAYOUT_hotswap(	
	 //---ESC---|----F1---|---F2----|----F3---|----F4---|----F5---|----F6---|----F7---|----F8---|----F9---|---F10---|----F11---|---F12---|---HOME--|---END---|---PGUP--|---PGDN--|---PRT---|----DEl---
		KC_TRNS, KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //--grave--|----1----|----2----|----3----|----4----|----5----|----6----|----7----|----7----|----9----|----0----|----sub---|----=----|--------back-------|----NL---|---div---|---mult--|----sub---
	 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_DEL, 		KC_NLCK, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 
	 //----tab---|----q---|----w----|----e----|----r----|----t----|----y----|----u----|----i----|----o----|----p----|-----[-----|------]-----|-------\-------|----7----|----8----|----9----|
		KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_APP, 		KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //----caps---|---A----|---s----|----d----|----f----|----g----|----h----|----j----|----k----|----l----|----;----|-----'-----|---------enter--------------|----4----|----5----|----6----|----+-----
		KC_TRNS,   KC_TRNS,	 BL_DEC,  BL_INC, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_MPRV, 	KC_MPLY, 	KC_MNXT,       	KC_TRNS,			KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //----shift---|-----z-----|----x----|----c-----|---v----|----b----|----n-----|----m----|----,-----|-----.----|-----/------|-----shift------|------up----|----1----|----2----|----3----|
		KC_TRNS,	  RGB_HUI,    RGB_SAI,	RGB_VAI, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_MUTE, 	KC_VOLD, 	KC_VOLU, 	      KC_TRNS, 	     KC_TRNS, 	KC_TRNS,	KC_TRNS, 	KC_TRNS,
	 //---ctrl---|---gui----|----alt-----|----------------------space------------------|-------alt----|------fn----|------ctrl------------|---left---|---down---|---right--|----0----|----.----|---enter---
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 					KC_TRNS, 						KC_TRNS, 		KC_TRNS, 	OSL(_ADJUST), 		 KC_TRNS,    KC_TRNS,   KC_TRNS, 	KC_TRNS, 	KC_TRNS, KC_TRNS),
	 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

	[_LOWER] = LAYOUT_hotswap(	// software macro layout keys are keys + hyper
	 //---ESC---|----F1---|---F2----|----F3---|----F4---|----F5---|----F6---|----F7---|----F8---|----F9---|---F10---|----F11---|---F12---|---HOME--|---END---|---PGUP--|---PGDN--|---PRT---|----DEl---
		KC_TRNS, HYPR(KC_F1), HYPR(KC_F2), HYPR(KC_F3), HYPR(KC_F4), HYPR(KC_F5), HYPR(KC_F6), HYPR(KC_F7), HYPR(KC_F8), HYPR(KC_F9), HYPR(KC_F10), HYPR(KC_F11), HYPR(KC_F12), HYPR(KC_HOME), HYPR(KC_END), HYPR(KC_PGUP), HYPR(KC_PGDN), HYPR(KC_PSCR), HYPR(KC_DEL),
	 //--grave--|----1----|----2----|----3----|----4----|----5----|----6----|----7----|----7----|----9----|----0----|----sub---|----=----|--------back-------|----NL---|---div---|---mult--|----sub---
		HYPR(KC_GRV), HYPR(KC_1), HYPR(KC_2), HYPR(KC_3), HYPR(KC_4), HYPR(KC_5), HYPR(KC_6), HYPR(KC_7), HYPR(KC_8), HYPR(KC_9), HYPR(KC_0), HYPR(KC_MINS), HYPR(KC_EQL),                 HYPR(KC_BSPC),    HYPR(KC_NLCK), HYPR(KC_PSLS), HYPR(KC_PAST), HYPR(KC_PMNS),
	 //----tab---|----q---|----w----|----e----|----r----|----t----|----y----|----u----|----i----|----o----|----p----|-----[-----|------]-----|-------\-------|----7----|----8----|----9----|
		HYPR(KC_TAB),   HYPR(KC_Q), HYPR(KC_W), HYPR(KC_E), HYPR(KC_R), HYPR(KC_T), HYPR(KC_Y), HYPR(KC_U), HYPR(KC_I), HYPR(KC_O), HYPR(KC_P), HYPR(KC_LBRC), HYPR(KC_RBRC),         HYPR(KC_BSLS),		HYPR(KC_P7), HYPR(KC_P8), HYPR(KC_P9),
	 //----caps---|---A----|---s----|----d----|----f----|----g----|----h----|----j----|----k----|----l----|----;----|-----'-----|---------enter--------------|----4----|----5----|----6----|----+-----
		HYPR(KC_CAPS), 	HYPR(KC_A), HYPR(KC_S), HYPR(KC_D), HYPR(KC_F), HYPR(KC_G), HYPR(KC_H), HYPR(KC_J), HYPR(KC_K), HYPR(KC_L), HYPR(KC_SCLN), HYPR(KC_QUOT), 			HYPR(KC_ENT), 		HYPR(KC_P4), HYPR(KC_P5), HYPR(KC_P6), HYPR(KC_PPLS),
	 //----shift---|-----z-----|----x----|----c-----|---v----|----b----|----n-----|----m----|----,-----|-----.----|-----/------|-----shift------|------up----|----1----|----2----|----3----|
		HYPR(KC_F13),    HYPR(KC_Z), HYPR(KC_X), HYPR(KC_C), HYPR(KC_V), HYPR(KC_B), HYPR(KC_N), HYPR(KC_M), HYPR(KC_COMM), HYPR(KC_DOT), HYPR(KC_SLSH), 		HYPR(KC_F18), 			HYPR(KC_UP), HYPR(KC_P1), HYPR(KC_P2), HYPR(KC_P3),
	 //---ctrl---|---gui----|----alt-----|----------------------space------------------|-------alt----|------fn----|------ctrl------------|------left---|--down--|---right--|----0----|----.----|---enter---
		HYPR(KC_F14), HYPR(KC_F15), HYPR(KC_F16), 					HYPR(KC_SPC), 				HYPR(KC_F17), KC_TRNS, KC_TRNS, 				 HYPR(KC_LEFT), HYPR(KC_DOWN), HYPR(KC_RGHT), HYPR(KC_P0), HYPR(KC_PDOT), HYPR(KC_PENT)),
	 //----------------------------------|------------------------------------------------------|----------|--------|-------------------|----------|---------|---------|---------|---------|----------

	[_ADJUST] = LAYOUT_hotswap(
	 //---ESC---|----F1---|---F2----|----F3---|----F4---|----F5---|----F6---|----F7---|----F8---|----F9---|---F10---|----F11---|---F12---|---HOME--|---END---|---PGUP--|---PGDN--|---PRT---|----DEl---
		RESET, 	RGB_TOG,	pHSV,     BL_TOGG,	BL_BRTG, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //--grave--|----1----|----2----|----3----|----4----|----5----|----6----|----7----|----7----|----9----|----0----|----sub---|----=----|--------back-------|----NL---|---div---|---mult--|----sub---
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_TRNS, 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	
	 //----tab---|----q---|----w----|----e----|----r----|----t----|----y----|----u----|----i----|----o----|----p----|-----[-----|------]-----|-------\-------|----7----|----8----|----9----|
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 		KC_TRNS, 		KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //----caps---|---A----|---s----|----d----|----f----|----g----|----h----|----j----|----k----|----l----|----;----|-----'-----|---------enter--------------|----4----|----5----|----6----|----+-----
		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	   KC_TRNS, 		 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //----shift---|-----z-----|----x----|----c-----|---v----|----b-----|----n-----|----m----|----,-----|-----.----|-----/------|-----shift------|------up----|----1----|----2----|----3----|
		KC_TRNS, 	    KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, 	KC_TRNS, 	KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,      KC_TRNS,  		KC_TRNS,	KC_TRNS, 	KC_TRNS, 	KC_TRNS,
	 //---ctrl---|---gui----|----alt-----|----------------------space------------------|-------alt----|------fn----|------ctrl------------|------left---|--down--|---right--|----0----|----.----|---enter---
		KC_TRNS, 	KC_TRNS, 	KC_TRNS,							KC_TRNS, 				KC_TRNS, 	KC_TRNS, 	     TG(_ADJUST), 	   KC_TRNS,  KC_TRNS, 	KC_TRNS, 	KC_TRNS,	KC_TRNS, KC_TRNS)
	 //-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
};
