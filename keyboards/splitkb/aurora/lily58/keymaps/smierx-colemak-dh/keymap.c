#include QMK_KEYBOARD_H
#include "raw_hid.h"
#include <string.h>
#include "keymap_german.h"

uint8_t mod_state;
uint8_t HID_TOOL = 0;
uint8_t response[32];

// Turn off Liatris LED
void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}

typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;
// Tap Dance declarations([{}])

enum {
    TD_EXAMPLE,
	TD_PAREN,
	TD_1_BRACKET,
	TD_2_BRACKET,
	TD_QUOTES,
	TD_EQ_PLUS,
	TD_VERTBSL_QUESTION,
	TD_SLASH,
	TD_AE,
	TD_OE,
	TD_UE,
	TD_LA_RA,
	TD_COMMA_DOT,
	TD_SEMICOLON,
	TD_MINUS,
	TD_PERCENT,
	TD_AT_EXCL,
	TD_TAG_DOLLAR,
	TD_AND_MUL,
    TD_HOME_END
};

enum {
	BASE,
	SPECIAL,
	MOUSE,
	FKEYS,
	MEDIA,
	SPECIAL2,
	NUMBERS,
	QWERTY
};

enum custom_keycodes {
    TOGGLE_HID = SAFE_RANGE,
	TOGGLE_BASE,
};

td_state_t cur_dance(tap_dance_state_t *state);

// For the x tap dance. Put it here so it can be used in any keymap
void x_finished(tap_dance_state_t *state, void *user_data);
void x_reset(tap_dance_state_t *state, void *user_data);

void dance_open_bracket(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(LSFT(KC_8));
        unregister_code16(LSFT(KC_8));
    } else if (state->count == 2) {
        register_code16(RALT(KC_8));
        unregister_code16(RALT(KC_8));
    } else if (state->count == 3) {
        register_code16(RALT(KC_7));
        unregister_code16(RALT(KC_7));
    } else {
        reset_tap_dance (state);
    }
}
void dance_close_bracket(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code16(LSFT(KC_9));
        unregister_code16(LSFT(KC_9));
    } else if (state->count == 2) {
        register_code16(RALT(KC_9));
        unregister_code16(RALT(KC_9));
    } else if (state->count == 3) {
        register_code16(RALT(KC_0));
        unregister_code16(RALT(KC_0));
    } else {
        reset_tap_dance (state);
    }
}

typedef struct {
    uint16_t tap;
    uint16_t hold;
    uint16_t held;
} tap_dance_tap_hold_t;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TOGGLE_HID:
        // Ich will das drin lassen als erinnerung wie ich custom Keycodes und co mache
        if (record->event.pressed) {
            // when keycod QMKBEST is pressed
            if (HID_TOOL==0) {
				HID_TOOL = 1;
			} else {
				HID_TOOL = 0;
			}
        } else {
            // when keycode QMKBEST is release
        }

	case TOGGLE_BASE:
		if (record->event.pressed) {
            default_layer_or(QWERTY);
        }
    }
	return true;
};

// Tap Dance definitions333333333333
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_EXAMPLE] = ACTION_TAP_DANCE_DOUBLE(KC_P1, KC_P2),
	[TD_PAREN] = ACTION_TAP_DANCE_DOUBLE(KC_LPRN,KC_RPRN),
	[TD_EQ_PLUS] = ACTION_TAP_DANCE_DOUBLE(KC_EQL,KC_EQL),//##
	[TD_1_BRACKET] = ACTION_TAP_DANCE_FN (dance_open_bracket),
	[TD_2_BRACKET] = ACTION_TAP_DANCE_FN (dance_close_bracket),
	[TD_QUOTES] = ACTION_TAP_DANCE_DOUBLE(DE_QUOT,DE_DQUO),//##
	[TD_VERTBSL_QUESTION] = ACTION_TAP_DANCE_DOUBLE(KC_QUES,KC_BSLS),//##
	[TD_SLASH] = ACTION_TAP_DANCE_DOUBLE(DE_SLSH,DE_BSLS),
	[TD_AE] = ACTION_TAP_DANCE_DOUBLE(DE_ADIA,LSFT(DE_ADIA)),
	[TD_OE] = ACTION_TAP_DANCE_DOUBLE(DE_ODIA,LSFT(DE_ODIA)),
	[TD_UE] = ACTION_TAP_DANCE_DOUBLE(DE_UDIA,LSFT(DE_UDIA)),
	[TD_LA_RA] = ACTION_TAP_DANCE_DOUBLE(DE_LABK,DE_RABK),
	[TD_COMMA_DOT] = ACTION_TAP_DANCE_DOUBLE(KC_DOT,KC_COMMA),
	[TD_SEMICOLON] = ACTION_TAP_DANCE_DOUBLE(KC_SCLN,LSFT(KC_SCLN)),
	[TD_MINUS] = ACTION_TAP_DANCE_DOUBLE(KC_MINS,LSFT(KC_MINS)),
	[TD_PERCENT] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_6),	KC_PERC),
	[TD_AT_EXCL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_1),LSFT(KC_2)),
	[TD_TAG_DOLLAR] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_3),LSFT(KC_4)),
	[TD_AND_MUL] = ACTION_TAP_DANCE_DOUBLE(LSFT(KC_7),LSFT(KC_8)),
    [TD_HOME_END] = ACTION_TAP_DANCE_DOUBLE(KC_HOME,KC_END),
};

const key_override_t left_thumb_override  = ko_make_basic(MOD_MASK_SHIFT, LT(SPECIAL,KC_ENT), KC_ESC);
const key_override_t right_thumb_override  = ko_make_basic(MOD_MASK_SHIFT, LT(SPECIAL2,KC_BSPC), KC_DEL);
const key_override_t space_override  = ko_make_basic(MOD_MASK_SHIFT, KC_SPC, KC_TAB);
// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
    &left_thumb_override,
	&right_thumb_override,
	&space_override, 
    NULL // Null terminate the array of overrides!R%
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[BASE] = LAYOUT(
		KC_ESC,	            KC_NO,	            LSFT(KC_8), 		RALT(KC_8), 		RALT(KC_7), 	 	KC_NO, 								        KC_NO, 					LSFT(KC_9), 		RALT(KC_9),       	RALT(KC_0),  		KC_NO,   		    KC_NO,
		LGUI(LSFT(KC_S)),	KC_Q,	            KC_W, 				KC_F, 				KC_P,   			KC_B,    							        KC_J, 					KC_L, 				KC_U,   			DE_Y,  				TD(TD_QUOTES),	    KC_NO,
		KC_NO,	            MT(MOD_LSFT,KC_A),	MT(MOD_LALT,KC_R), 	MT(MOD_LGUI,KC_S), 	MT(MOD_LCTL,KC_T), 	KC_G,    							        KC_M, 					MT(MOD_RCTL,KC_N), 	MT(MOD_RGUI,KC_E),  MT(MOD_RALT,KC_I),  MT(MOD_RSFT,KC_O),  KC_NO,
		KC_NO,	            DE_Z,	            KC_X, 				KC_C, 				KC_D,   			KC_V,  			 	LCTL(KC_X),	LCTL(KC_A),	KC_K, 					KC_H, 				KC_COMM,			KC_DOT,				TD(TD_SLASH),	    KC_NO,
						                        LCTL(KC_C),			TD(TD_HOME_END),				KC_DEL,			    LT(SPECIAL,KC_ENT), 				        LT(SPECIAL2,KC_BSPC),	KC_SPC,				KC_TAB,				LCTL(KC_V)),

	[SPECIAL] = LAYOUT(
		KC_NO,	KC_NO,			KC_NO,	  	KC_NO, 			KC_NO, 			KC_NO, 						KC_NO, 	 	KC_NO, 				KC_NO,  			KC_NO,  		KC_NO, 			KC_NO,
		KC_NO,	DE_AT,			DE_UNDS, 	DE_MINS, 	    DE_PIPE, 		DE_CIRC, 					KC_NO, 	 	TD(TD_AE), 			TD(TD_OE),   		TD(TD_UE),   	KC_NO,  	    KC_NO,
		KC_NO,	DE_PLUS, 		DE_HASH, 	DE_AMPR,		DE_PERC, 	    DE_COLN, 					DE_SCLN, 	KC_LEFT, 			KC_DOWN, 			KC_UP,			KC_RGHT,  		KC_NO,
		KC_NO,	DE_ASTR,    	LSFT(KC_1),	LSFT(KC_MINS), 	DE_EQL, 		DE_TILD, 	KC_NO,	KC_NO,	KC_NO,		DE_LABK,        	DE_RABK,	        DE_SS,   		KC_NO,  		KC_NO,
								KC_NO,		KC_NO, 	    	KC_NO, 			KC_NO, 						KC_NO,		KC_NO,		 		KC_NO, 	 			KC_NO),
	[SPECIAL2] = LAYOUT(
		KC_NO, KC_NO,	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 				KC_NO, KC_NO, 	KC_NO,KC_NO,KC_NO, KC_NO,
		KC_NO, KC_NO,   KC_F1,  KC_F2,  KC_F3,  KC_F10, 			KC_NO, KC_1,	KC_2, KC_3,	KC_NO, KC_NO,
		KC_NO, KC_NO,   KC_F4,  KC_F5,  KC_F6,  KC_F11, 			KC_NO, KC_4,	KC_5, KC_6, KC_0, KC_NO,
		KC_NO, KC_NO,	KC_F7, 	KC_F8, 	KC_F9, 	KC_F12,KC_NO, KC_NO,KC_NO, KC_7,	KC_8, KC_9, KC_NO, KC_NO,
					  	KC_NO, 	KC_NO, 	KC_NO, 	KC_NO, 				KC_NO, KC_NO, 	KC_NO,KC_NO),


	[MOUSE] = LAYOUT(
		KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO, 			  KC_NO,   KC_NO, 	KC_NO,   KC_NO,   KC_NO,   KC_NO,
		KC_NO, KC_NO, KC_NO,   KC_MS_U, KC_NO,   KC_NO, 			  KC_NO,   KC_NO, 	KC_NO,   KC_NO,   KC_NO,   TG(BASE),
		KC_NO, KC_NO, KC_MS_L, KC_MS_D, KC_MS_R, KC_NO, 			  KC_NO,   KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN3, KC_BTN4,
		KC_NO, KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_NO,   KC_BTN5, KC_BTN6, KC_BTN7, KC_BTN8, KC_NO,
					  KC_NO,   KC_NO,   KC_LSFT, KC_NO, 			  KC_WH_U, KC_WH_D, KC_NO,   KC_NO),


	[FKEYS] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[MEDIA] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),

	[NUMBERS] = LAYOUT(
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_NO, KC_1,  KC_2,  KC_3,  KC_NO, KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, 				KC_NO, KC_4,  KC_5,  KC_6,  KC_0,  KC_NO,
		KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_7,  KC_8,  KC_9,  KC_NO, KC_NO,
					  KC_NO, KC_NO, KC_NO, TO(0), 				KC_NO, KC_NO, KC_NO, KC_NO),


	[QWERTY] = LAYOUT(
		KC_ESC,KC_1,  KC_2,  KC_3, 	 KC_4, 	  KC_5, 								KC_6, 					KC_7,  KC_8,  KC_9,  KC_0,  KC_NO,
		KC_NO, KC_Q,  KC_W,  KC_E,   KC_R,    KC_T, 								DE_Y,  					KC_U,  KC_I,  KC_O,  KC_P,  KC_NO,
		KC_NO, KC_A,  KC_S,  KC_D,   KC_F,	  KC_G, 								KC_H,  					KC_J,  KC_K,  KC_L,  KC_NO, KC_NO,
		KC_NO, DE_Z,  KC_X,  KC_C,   KC_V,    KC_B, 				KC_NO, KC_NO,  	KC_N,  					KC_M,  KC_NO, KC_NO,  KC_NO, KC_NO,
					  KC_NO, KC_DEL, KC_LSFT, LT(SPECIAL,KC_ENT), 					LT(SPECIAL2,KC_BSPC),	KC_SPC,				KC_TAB,				KC_NO),
	[8] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[9] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[10] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[11] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[12] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[13] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[14] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO),
	[15] = LAYOUT(KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, TO(0), KC_NO, KC_NO, KC_NO, KC_NO)
};
#ifdef RGB_MATRIX
// FARBEN FÜR LAYER
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
    case SPECIAL:
        rgb_matrix_set_color(25,80,80,80);
        break;
    case MOUSE:
        rgb_matrix_set_color_all(0,  100, 100);
        break;
	case NUMBERS:
        rgb_matrix_set_color_all(0,  100, 100);
        break;
	case MEDIA:
        rgb_matrix_set_color_all(0,  100, 100);
        break;
	case SPECIAL2:
		rgb_matrix_set_color_all(HSV_MAGENTA);
		break;
    default:
		rgb_matrix_set_color_all(HSV_GREEN);
        rgb_matrix_set_color(25,80,80,80);
        break;
    }
  return state;
}


bool rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
	for (uint8_t i = led_min; i < led_max; i++) {
		switch(get_highest_layer(layer_state)) {
			case SPECIAL:
				rgb_matrix_set_color(i, RGB_BLUE);
				break;
			case SPECIAL2:
                if (i - led_min == 0) {
                    rgb_matrix_set_color(i,RGB_RED);
                } else if (i - led_min==1) {
					rgb_matrix_set_color(i, RGB_YELLOW);
                } else if(i - led_min==2) {
                	rgb_matrix_set_color(i, RGB_GREEN);
                } else if(i - led_min==3) {
                	rgb_matrix_set_color(i, RGB_PURPLE);
                } else if(i - led_min==4) {
                	rgb_matrix_set_color(i, RGB_GOLD);
                } else{
                	rgb_matrix_set_color(i, RGB_TURQUOISE);
                }
				break;
			default:
				rgb_matrix_set_color(i, RGB_AZURE);
				break;
		}
	}
	return false;
}
#endif
#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_0;
    }
    return OLED_ROTATION_180;
}

bool oled_task_user(void) {
	if (is_keyboard_master()) {
		// Host Keyboard Layer Status
		oled_write_P(PSTR("Layer:\n"), false);

		switch (get_highest_layer(layer_state)) {
			case BASE:
				oled_write_P(PSTR("BASE\n"), false);
				break;
			case SPECIAL:
				oled_write_P(PSTR("SPECIAL\n"), false);
				break;
			case SPECIAL2:
				oled_write_P(PSTR("SPECIAL2\n"), false);
				break;
			case MOUSE:
				oled_write_P(PSTR("MOUSE\n"), false);
				break;
			case FKEYS:
				oled_write_P(PSTR("FKEYS\n"), false);
				break;
			case MEDIA:
				oled_write_P(PSTR("MEDIA\n"), false);
				break;
			default:
				// Or use the write_ln shortcut over adding '\n' to the end of your string
				oled_write_ln_P(PSTR("Undefined"), false);
		}
		// Host Keyboard LED Status
		led_t led_state = host_keyboard_led_state();
		oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
		oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
		oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

	} else {
		oled_write_P(PSTR("Was zeige ich hier an?\n"), false);
		//oled_write_P(PSTR(), false);

	}

    return false;
}
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	uint8_t col = record->event.key.col;
	uint8_t row = record->event.key.row;
	uint8_t value = keymaps[0][col][row];
	oled_write_P(PSTR(value), false);
	return true; // Process all other keycodes normally

}*/
#endif
