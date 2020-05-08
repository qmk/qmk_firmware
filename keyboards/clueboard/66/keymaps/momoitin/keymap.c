#include QMK_KEYBOARD_H

#define _BL 0 /* Keymap _BL "Base Layer" */
#define _FL 1 /* Keymap _FL "Function Layer" */
#define _CL 2 /* Keymap _CL "Control Layer + Mouse Layer" */

#define TT_CL TT(_CL)



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	/* Base Layer */
	[_BL] = LAYOUT_66_ansi( KC_ESC,    KC_1,    KC_2,    KC_3,   KC_4,    KC_5,    KC_6,    KC_7,    KC_8,     KC_9,     KC_0,   KC_MINS,  KC_EQL, KC_BSPC, 		  KC_PGUP,
						    KC_TAB,    KC_Q,    KC_W,    KC_E,   KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,     KC_O,     KC_P,   KC_LBRC, KC_RBRC, KC_BSLS, 		  KC_PGDN,
						   KC_CAPS,    KC_A,    KC_S,    KC_D,   KC_F,    KC_G,    KC_H,    KC_J,    KC_K,     KC_L,  KC_SCLN,   KC_QUOT,  KC_ENT,
						   KC_LSFT,    KC_Z,    KC_X,    KC_C,   KC_V,    KC_B,    KC_N,    KC_M, KC_COMM,   KC_DOT,  KC_SLSH,   KC_RSFT, 		             KC_UP,
						   KC_LCTL, KC_LGUI, KC_LALT,  			        KC_SPC,  				                      KC_RALT,   MO(_FL), KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT),
	
	/* Function Layer */
	[_FL] = LAYOUT_66_ansi( KC_GRV,   KC_F1,   KC_F2,   KC_F3,  KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,    KC_F9,   KC_F10,    KC_F11,  KC_F12,   KC_DEL,  	      KC_VOLU, 
						     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_MPRV,  KC_MPLY,   KC_MNXT,   KC_NO,  KC_MUTE, 		  KC_VOLD, 
						     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,    KC_NO,    KC_NO,     KC_NO,   KC_NO, 
						   KC_TRNS,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,  MU_MOD,  MU_TOG,   KC_NO,    KC_NO,    KC_NO,   KC_TRNS,         		     KC_PGUP, 
						   KC_TRNS,   KC_NO,   KC_NO,                    KC_NO, 					                    KC_NO,   KC_TRNS,   TT_CL,  KC_HOME, KC_PGDN, KC_END),
	
	/* Control Layer + Mouse Layer */
	[_CL] = LAYOUT_66_ansi(  KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, 	KC_NO, 	  KC_NO,    KC_NO,     KC_NO,   KC_NO, 	  KC_NO, 		    KC_NO, 
						     KC_NO,   KC_NO,   KC_NO,   KC_NO,  RESET,   KC_NO,   KC_NO,   KC_NO, 	KC_NO, 	  KC_NO,    KC_NO,     KC_NO,   KC_NO, 	  KC_NO, 		    KC_NO, 
						     KC_NO,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, 	KC_NO, 	  KC_NO,    KC_NO,     KC_NO,   KC_NO, 
						   CK_TOGG,   KC_NO,   KC_NO,   KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO, 	KC_NO,  KC_BTN1,  KC_BTN2,   KC_BTN3, 		             KC_MS_U, 
						    CK_RST,   CK_UP, CK_DOWN,                    KC_NO, 				                        KC_NO,   KC_TRNS, KC_TRNS,  KC_MS_L, KC_MS_D, KC_MS_R)
};

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_66_ansi(
	
	51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65,
	36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
	23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35,
	10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22,
	 0,  1,  2,  3,  4,  5,  6,  7,  8,  9
);

#ifdef AUDIO_ENABLE

float BL_SONG[][2] = SONG(TERMINAL_SOUND);
float FL_SONG[][2] = SONG(UNICODE_WINDOWS);
float CL_SONG[][2] = SONG(UNICODE_LINUX);

layer_state_t layer_state_set_user(layer_state_t state) {

		switch (get_highest_layer(state)) {
		case _BL:
			PLAY_SONG(BL_SONG);
			break;
			
		case _FL:
			PLAY_SONG(FL_SONG);
			break;
		
		case _CL:
			PLAY_SONG(CL_SONG);
			break;
		}
	return state;
};
#endif