#include QMK_KEYBOARD_H

enum keyboard_layers {
  _BL = 0, // Base Layer
  _NL,    // Navigation Layer
  _GL,    // Game Layer
  _FL     // Function Layer
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BL] = LAYOUT_60_b_ansi(
		KC_GESC,   			KC_1,   	KC_2,     		KC_3,   	KC_4,   	KC_5, 		KC_6,   	KC_7,   	KC_8,    	KC_9,   			KC_0,   	KC_MINS,   	KC_EQL,   KC_BSPC,   KC_DEL, 
		KC_TAB,    			KC_Q,   	KC_W,     		KC_E,   	KC_R,   	KC_T,   	KC_Y,   	KC_U,   	KC_I,    	KC_O,   			KC_P,   	KC_LBRC,   	KC_RBRC,  RCTL_T(KC_BSLS), 
		LT(_NL,KC_CAPS),   	KC_A,     	KC_S,   		KC_D,   	KC_F,   	KC_G,   	KC_H,   	KC_J,    	KC_K,   	KC_L,   			KC_SCLN,   	KC_QUOT,  	KC_ENT, 
		KC_LSFT,   KC_Z,   	KC_X,     	KC_C,   		KC_V,   	KC_B,   	KC_N,   	KC_M,   	KC_COMM, 	KC_DOT, 	RSFT_T(KC_SLSH),   	KC_UP,    	MO(_FL), 
		LCTL_T(KC_ENT),    	KC_LGUI,  	LALT_T(KC_SPC), KC_BSPC, 	TT(_NL), 	KC_SPC, 	KC_RALT, 	TG(_GL), 	KC_LEFT, 	KC_DOWN, 			KC_RGHT),
	
	
	[_NL] = LAYOUT_60_b_ansi(
		LALT(KC_F4), 	KC_F1, 		KC_F2, 		KC_F3, 		KC_F4, 		KC_F5, 		KC_F6, 		KC_F7, 		KC_F8, 		KC_F9, 		KC_F10, 	KC_F11, KC_F12, KC_NO, KC_PSCR, 
		KC_TRNS, 		KC_NO, 		KC_HOME, 	KC_UP, 		KC_END, 	KC_PGUP, 	KC_PGUP, 	KC_HOME, 	KC_UP, 		KC_END, 	KC_NO, 		KC_NO, 	KC_NO, 	KC_INS, 
		C(S(KC_ESC)), 	KC_LCTL, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_PGDN, 	KC_PGDN, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_NO, 		KC_NO, 	KC_TRNS, 
		KC_TRNS, 		LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_RCTL, 	KC_NO, 	KC_NO, 
		KC_TRNS, 		KC_NO, 		KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_NLCK, 	KC_NO, 		KC_NO, 		KC_NO),
	
	
	[_GL] = LAYOUT_60_b_ansi(
		KC_ESC, 	KC_1, 	KC_2, 		KC_3, 	KC_4, 		KC_5, 	KC_6, 	KC_7, 		KC_8, 		KC_9, 		KC_0, 		KC_MINS, KC_EQL, 	KC_GRV, KC_BSPC, 
		KC_TRNS, 	KC_Q, 	KC_W, 		KC_E, 	KC_R, 		KC_T, 	KC_Y, 	KC_U, 		KC_I, 		KC_O, 		KC_P, 		KC_LBRC, KC_RBRC, 	KC_BSLS, 
		KC_F2, 		KC_A, 	KC_S, 		KC_D, 	KC_F, 		KC_G, 	KC_H, 	KC_J, 		KC_K, 		KC_L, 		KC_SCLN, 	KC_QUOT, KC_ENT, 
		KC_TRNS, 	KC_Z, 	KC_X, 		KC_C, 	KC_V, 		KC_B, 	KC_N, 	KC_M, 		KC_COMM, 	KC_DOT, 	KC_SLSH, 	KC_TRNS, KC_TRNS, 
		KC_TRNS, 	KC_NO, 	KC_LALT, 	KC_SPC, KC_LALT, 	KC_SPC, KC_NO, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS, 	KC_TRNS),
	
	
	[_FL] = LAYOUT_60_b_ansi(
		RESET, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 				KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_CALC, 	KC_MYCM, KC_VOLU, 
		KC_SLEP, 	RGB_M_P, 	RGB_M_B, 	RGB_M_R, 	RGB_M_SW, 			RGB_M_SN, 	RGB_M_K, 	RGB_M_X, 	RGB_M_G, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_VOLD, 
		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 		KC_NO, 				KC_NO, 		KC_NO, 		RGB_SAI,	RGB_HUI, 	KC_NO, 		KC_NO, 		KC_NO, 		KC_MUTE, 
		BL_INC, 	BL_TOGG, 	BL_BRTG, 	KC_NO, 		KC_NO, 				KC_NO, 		KC_NO, 		RGB_SAD, 	RGB_HUD, 	RGB_MOD, 	RGB_TOG, 	RGB_VAI, 	KC_TRNS, 
		BL_DEC, 	BL_STEP, 	KC_NO, 		KC_NO, 		MAGIC_TOGGLE_NKRO, 	KC_NO, 		KC_NO, 		RGB_RMOD, 	RGB_SPD, 	RGB_VAD, 	RGB_SPI)
};