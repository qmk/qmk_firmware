/* Copyright 2021 TweetyDaBird
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

enum layers {
    _QWERTY,
    _COLEMAK,
    _NUM,
    _FUNC,
	_SYSTEM,
};

enum custom_keycodes {
    KC_QWERTY = SAFE_RANGE,
    KC_COLEMAK,
    KC_NUM,
    KC_FUNC,
    KC_SYSTEM,
};

// Tap Dance declarations
enum {
    MEDIA_SCROLL,
	PG_UP,
	PG_DN,
	DEL_INS,
	ESC_PIPE,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    [MEDIA_SCROLL] = ACTION_TAP_DANCE_DOUBLE(KC_MPLY, KC_MUTE),
	[PG_DN] = ACTION_TAP_DANCE_DOUBLE(KC_DOWN, KC_PGDN),
	[PG_UP] = ACTION_TAP_DANCE_DOUBLE(KC_UP, KC_PGUP),
	[DEL_INS] = ACTION_TAP_DANCE_DOUBLE(KC_DEL, KC_INS),
	[ESC_PIPE] = ACTION_TAP_DANCE_DOUBLE(KC_ESC, KC_NUBS),
	
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/*  Base Layer
 * ,-----------------------------------------------.                       			      ,-----------------------------------------------.
 * |  ESC  |   1   |   2   |   3   |   4   |   5   |                    		         |   6   |   7   |   8   |   9   |   0   |   +   |
 * |       |       |       |       |       |       |                      		    	 |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|                	 			   	 |-------+-------+-------+-------+-------+-------|
 * |  TAB  |   Q   |   W   |   E   |   R   |   T   |  ______      			     ______  |   Y   |   U   |   I   |   O   |   P   |   Å   |
 * |       |       |       |       |       |       | /      \     		        /      \ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------||        |     		   	   | MEDIA  ||-------+-------+-------+-------+-------+-------|
 * |   '   |   A   |   S   |   D   |   F   |   G   ||        |				   | SCROLL ||   H   |   J   |   K   |   L   |   Ö   |   Ä   |
 * |       |       |       |       |       |       | \______/     		        \______/ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|--------.    		     	,--------|-------+-------+-------+-------+-------+-------|
 * | LEFT  |   Z   |   X   |   C   |   V   |   B   |  DOWN  | 					|   UP   |   N   |   M   |   ,   |   .   |   -   | RIGHT |       
 * |(CTRL) |       |       |       |       |       | (PGDN) |     		 	    | (PGUP) |       |       |       |       |       | (CTRL)| 
 * '-----------------------------------------------|--------|    	  		 	|--------|-----------------------------------------------' 
 *          			|  DEL  | Lower |  ALT  | / SPACE  /	     	    	 \ ENTER  \ | ALT_GR | Raise | BCKSP |
 *                      | (INS) |       | (WIN) |/ (SHIFT)/         	    	  \(SHIFT) \| (MENU) |       |       |
 *                      `--------------------------------'          		   	   '---------------------------------'
 */
[_QWERTY] = LAYOUT( \
	TD(ESC_PIPE), 			KC_1, KC_2, KC_3, KC_4, KC_5, 										KC_6, KC_7, KC_8, KC_9, KC_0, 		KC_MINS, \
    KC_TAB, 				KC_Q, KC_W, KC_E, KC_R,	KC_T,    									KC_Y, KC_U,	KC_I, KC_O,	KC_P, 		KC_LBRC, \
	KC_NUHS,   				KC_A, KC_S, KC_D, KC_F, KC_G, KC_NO,			TD(MEDIA_SCROLL), 	KC_H, KC_J,	KC_K, KC_L,	KC_SCLN,	KC_QUOT, \
	MT(MOD_LCTL, KC_LEFT), 	KC_Z, KC_X, KC_C, KC_V,	KC_B, TD(PG_DN),			TD(PG_UP),		KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, MT(MOD_RCTL, KC_RIGHT), \
	KC_DEL, TT(_NUM), MT(MOD_LALT, KC_RGUI), MT(MOD_LSFT, KC_SPC),		MT(MOD_RSFT,KC_ENT), MT(MOD_RALT, KC_APP), TT(_FUNC), KC_BSPC \
),

/* Numeric Layer
 * ,-----------------------------------------------.              	    	  			 ,-----------------------------------------------.
 * |  ESC  |   F1  |   F2  |   F3  |   F4  |   F5  |            	    	             |   &   |   7   |   8   |   9   |   0   |   +   |
 * |       |       |       |       |       |       |                    	    	   	 |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|                			 	   	 |-------+-------+-------+-------+-------+-------|
 * |  TAB  |       |   UP  |       |       |       |  ______        		     ______  |   #   |   4   |   5   |   6   |   P   |   Å   |
 * |       |       |       |       |       |       | /      \       		    /      \ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------||        |      		   | MEDIA  ||-------+-------+-------+-------+-------+-------|
 * |       |  LEFT |  DOWN | RIGHT |       |       ||        |				   | SCROLL ||   /   |   1   |   2   |   3   |   Ö   |   Ä   |
 * |       |       |       |       |       |       | \______/           		\______/ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|--------.       		  	,--------|-------+-------+-------+-------+-------+-------|
 * | LEFT  |       |   *   |   +   |   /   |   B   |  DOWN  | 					|   UP   |   N   |   0   |   ö   |       |   -   | RIGHT |       
 * |(CTRL) |       |       |       |       |       | (PGDN) |   	    	    | (PGUP) |       |       |       |       |       | (CTRL)| 
 * '-----------------------------------------------|--------|   	    		|--------|-----------------------------------------------' 
 *          			|  DEL  | Lower |  ALT  | / SPACE  /	 	    		 \ ENTER  \ | ALT_GR | Raise | BCKSP |
 *                      | (INS) |       | (WIN) |/ (SHIFT)/     	       		  \(SHIFT) \| (MENU) |       |       |
 *                      `--------------------------------'         	    		   '---------------------------------'
 */
[_NUM] = LAYOUT( \
  _______, KC_F1,   KC_F2,   KC_F3,    KC_F4,   KC_F5,                       	 KC_CIRC, KC_7,    KC_8,    KC_9,    KC_PAST, XXXXXXX, \
  _______, XXXXXXX, KC_UP,   XXXXXXX,  XXXXXXX, XXXXXXX,        				 KC_HASH, KC_4,    KC_5,    KC_6,    KC_PPLS, XXXXXXX, \
  XXXXXXX, KC_LEFT, KC_DOWN, KC_RIGHT, XXXXXXX, XXXXXXX, _______,       _______, KC_AMPR, KC_1,    KC_2, 	KC_3,    KC_EQL,  XXXXXXX, \
  _______, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, _______,       _______, KC_DLR,  KC_0,    KC_SCLN, KC_COLN, KC_PMNS, _______, \
							 _______, _______,  _______, _______,       _______, _______, _______, _______\
),
/* RAISE
 * ,-----------------------------------------------.           	            	    	 ,-----------------------------------------------.
 * |  ESC  |   F1  |   F2  |   F3  |   F4  |   F5  |            	            	     |   F6  |   F7  |   F8  |   F9  |  F10  |   +   |
 * |       |       |       |       |       |       |                	          	 	 |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|           		     		 	   	 |-------+-------+-------+-------+-------+-------|
 * |  TAB  |   Q   |   W   |   E   |   R   |   T   |  ______        	    	 ______  |   Y   |   U   |   I   |   O   |   P   |   Å   |
 * |       |       |       |       |       |       | /      \     		      	/      \ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------||        |    		  	   | MEDIA  ||-------+-------+-------+-------+-------+-------|
 * |   '   |   A   |   S   |   D   |   F   |   G   ||        |			       | SCROLL ||   H   |   J   |   K   |   L   |   Ö   |   Ä   |
 * |       |       |       |       |       |       | \______/     		        \______/ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|--------.      		   		,--------|-------+-------+-------+-------+-------+-------|
 * | LEFT  |   Z   |   X   |   C   |   V   |   B   |  DOWN  | 					|   UP   |   N   |   M   |   ,   |   .   |   -   | RIGHT |       
 * |(CTRL) |       |       |       |       |       | (PGDN) |           		| (PGUP) |       |       |       |       |       | (CTRL)| 
 * '-----------------------------------------------|--------|       			|--------|-----------------------------------------------' 
 *          			|  DEL  | Lower |  ALT  | / SPACE  /	     	 		\ ENTER  \ | ALT_GR | Raise | BCKSP |
 *                      | (INS) |       | (WIN) |/ (SHIFT)/            	  		 \(SHIFT) \| (MENU) |       |       |
 *                      `--------------------------------'         		    	  '---------------------------------'
 */
[_FUNC] = LAYOUT( \
  _______,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  _______, \
  _______, _______, _______, _______, _______, _______,                         _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______, _______,       _______, _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______,       _______, _______, _______, _______ \
),
/* RAISE
 * ,-----------------------------------------------.       			                     ,-----------------------------------------------.
 * |       |       |       |       |       |       |         	 	                     |       |       |       |       |       |       |
 * |       |       |       |       |       |       |                           	  	 	 |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|                	 	   	  	     |-------+-------+-------+-------+-------+-------|
 * | RESET |       | QWERTY|COLEMAK|       | AUTO  |  ______             		 ______  |       |       |       |       |       |       |
 * |       |       |       |       |       | SHIFT | /      \           	    /      \ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------||        |         		   |        ||-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       ||        |		   		   |        ||       |       |       |       |       |       |
 * |       |       |       |       |       |       | \______/         	  		\______/ |       |       |       |       |       |       |
 * |-------+-------+-------+-------+-------+-------|--------.     		       	,--------|-------+-------+-------+-------+-------+-------|
 * |       |       |       |       |       |       |        | 					|        |       |       |       |       |       |       |       
 * |       |       |       |       |       |       |        |        			|        |       |       |       |       |       |       | 
 * '-----------------------------------------------|--------|    			   	|--------|-----------------------------------------------' 
 *          			|  DEL  | Lower |  ALT  | / SPACE  /	  			   	 \ ENTER  \ | ALT_GR | Raise | BCKSP |
 *                      | (INS) |       | (WIN) |/ (SHIFT)/         		   	  \(SHIFT) \| (MENU) |       |       |
 *                      `--------------------------------'    		         	   '---------------------------------'
 */
  [_SYSTEM] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX,                     	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  RESET  , XXXXXXX, KC_QWERTY, KC_COLEMAK, XXXXXXX, KC_ASTG,                     	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX, 	XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX,   XXXXXXX,    XXXXXXX, XXXXXXX, XXXXXXX,     XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
								  _______, _______, _______, _______,     _______,  _______, _______, _______ \
  )
};

#ifdef OLED_DRIVER_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,0x90,0x91,0x92,0x93,0x94,
        0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,0xb0,0xb1,0xb2,0xb3,0xb4,
        0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,0xd0,0xd1,0xd2,0xd3,0xd4,0
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n"), false);
	oled_write_P(PSTR(""), false);
    oled_write_P(PSTR("Lotus -58-"), false);
	oled_write_P(PSTR("\n"), false);   

    switch (get_highest_layer(default_layer_state)) {
        case _QWERTY:
            oled_write_P(PSTR("Qwrty"), false);
            break;
        case _COLEMAK:
            oled_write_P(PSTR("Colmk"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    // Print current layer
    oled_write_P(PSTR("Layer"), false);
    switch (get_highest_layer(layer_state)) {
        case _COLEMAK:
        case _QWERTY:
            oled_write_P(PSTR("-Base\n"), false);
            break;
        case _FUNC:
            oled_write_P(PSTR("-Func\n"), false);
            break;
        case _NUM:
            oled_write_P(PSTR("-Num \n"), false);
            break;
        case _SYSTEM:
            oled_write_P(PSTR("-Sys \n"), false);
            break;
        default:
            oled_write_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n"), false);
    led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("CPSLK"), led_usb_state.caps_lock);
	
	oled_write_P(PSTR("\n"), false);
    //led_t led_usb_state = host_keyboard_led_state();
    oled_write_ln_P(PSTR("Auto-Shift"), get_autoshift_state());

}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

void oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
			
        case KC_COLEMAK:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_COLEMAK);
            }
            return false;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
   return update_tri_layer_state(state, _NUM, _FUNC, _SYSTEM);
}


void keyboard_post_init_user(void) {
	autoshift_disable();
}

#ifdef ENCODER_ENABLE

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_PGDN);
        } else {
            tap_code(KC_PGUP);
        }
    } else if (index == 1) {
        if (clockwise) {
            if (get_mods() & MOD_MASK_CTRL) {
				tap_code(KC_MPRV);
			} else {
				tap_code(KC_VOLD);
			}
			
        } else {
			
			if (get_mods() & MOD_MASK_CTRL) {
				tap_code(KC_MNXT);
			} else {
				tap_code(KC_VOLU);
			}
        }
    }
}

#endif