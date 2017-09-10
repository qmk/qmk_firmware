#include QMK_KEYBOARD_H
#include "debug.h"
#include "action_layer.h"
#include "version.h"


// to build this keymap
// make ergodox_ez-dvorak_42_key-teensy

static bool mouse_lock = false;

enum custom_keycodes {
  PLACEHOLDER = SAFE_RANGE, // can always be here
  EPRM,
  VRSN,
  RGB_SLD,
  
};


#define BASE      0 // base dvorak layer
#define KEYNAV    1 // arrow navigation (right hand)
#define KEYSEL    2 // arrow navigation + shift (allow text selection)
#define SHELL_NAV 3 // bash shortcuts
#define MOUSE     4 // mouse layer (can be locked with lock key)
#define COMBINED  5 // combined numbers and symbols layer

// macros
#define MOUSE_TOGGLE 1
#define MOUSE_LOCK 2
#define SCREEN_TAB_LEFT 4
#define SCREEN_TAB_RIGHT 5
#define SCREEN_NEW_TAB 6
#define SWITCH_NDS 7
#define SCREEN_COPY_MODE 8
#define SCREEN_PASTE 9
#define SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND 15


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [BASE] = KEYMAP(
	  // left hand
	  KC_ESC,         KC_F1,         KC_F2,      KC_F3,        KC_F4,   KC_F5,   KC_F6,
	  KC_TAB,         KC_QUOTE,      KC_COMMA,   KC_DOT,       KC_P,    KC_Y,    MEH(KC_2),
	  MO(SHELL_NAV),  KC_A,          KC_O,       KC_E,         KC_U,    KC_I,
	  MEH(KC_0),      KC_SCOLON,     KC_Q,       KC_J,         KC_K,    KC_X,    MEH(KC_3),
	  MEH(KC_1),      OSM(MOD_LSFT), OSM(MOD_LCTL), M(MOUSE_TOGGLE), MO(KEYSEL),
	  
	  // left thumb cluster
	            MEH(KC_4),      MEH(KC_5),
	                            MEH(KC_6),
	  MO(COMBINED),MO(KEYNAV),  OSM(MOD_LALT),
	  
	  // right hand
	  KC_F7,     KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, MEH(KC_9),
	  MEH(KC_7), KC_F,  KC_G,  KC_C,   KC_R,   KC_L,   MEH(KC_F1),
			     KC_D,  KC_H,  KC_T,   KC_N,   KC_S,   MEH(KC_F2),
	  MEH(KC_8), KC_B,  KC_M,  KC_W,   KC_V,   KC_Z,   MEH(KC_F3),
	  KC_BSPC,   RCTL(KC_BSPC), KC_CAPSLOCK, OSM(MOD_LSFT),MEH(KC_F4),
    
	  // right thumb cluster
	  MEH(KC_F5),MEH(KC_F6),MEH(KC_F7),MEH(KC_F8),KC_ENTER,KC_SPACE
  
  ),
  
  [KEYNAV] = KEYMAP(
	// left hand
	KC_TRNS,KC_TRNS,     KC_TRNS,     KC_TRNS,      KC_TRNS,    KC_TRNS,     KC_TRNS,
	KC_TRNS,KC_ESC,      MEH(KC_F9),  RCTL(KC_Z),   RCTL(KC_S), MEH(KC_F10), KC_TRNS,
	KC_TRNS,MEH(KC_F11), MEH(KC_F12), RSFT(KC_TAB), KC_TAB,     MEH(KC_A),
	KC_TRNS,MEH(KC_B),   MEH(KC_C),   MEH(KC_D),    MEH(KC_E),  MEH(KC_F),   KC_TRNS,
	KC_TRNS,KC_TRNS,     KC_TRNS,     KC_TRNS,      KC_TRNS,
	// left thumb cluster
	KC_TRNS,KC_TRNS,KC_TRNS,TO(MOUSE),KC_TRNS,KC_TRNS,
	
	// right hand
	KC_TRNS,KC_TRNS,       KC_TRNS,    KC_TRNS,         KC_TRNS,    KC_TRNS,         MEH(KC_G),
	KC_TRNS,KC_NO,         KC_HOME,    KC_UP,           KC_END,     KC_PGUP,         MEH(KC_H),
	        LCTL(KC_LEFT), KC_LEFT,    KC_DOWN,         KC_RIGHT,   LCTL(KC_RIGHT),  MEH(KC_I),
	KC_TRNS,KC_NO,         RCTL(KC_C), RCTL(KC_X),      RCTL(KC_V), KC_PGDOWN,       MEH(KC_J),
	                       KC_BSPC,   RCTL(KC_BSPC),    KC_DELETE,  LCTL(KC_DELETE), MEH(KC_K),
	
	// right thumb cluster
	KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS
  ),  
  
	// key selection layer
	[KEYSEL] = KEYMAP(
		   // left hand
		   KC_TRNS,KC_TRNS,   KC_TRNS,  KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,
		   KC_TRNS,MEH(KC_G), MEH(KC_H),MEH(KC_I), MEH(KC_J), MEH(KC_K), KC_TRNS,
		   KC_TRNS,MEH(KC_L), MEH(KC_M),MEH(KC_N), MEH(KC_O), MEH(KC_P),
		   KC_TRNS,MEH(KC_Q), MEH(KC_R),MEH(KC_S), MEH(KC_T), MEH(KC_U), KC_TRNS,
				   // bottom row
				   KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
										   // thumb cluster
										   KC_TRNS,KC_TRNS,
												   KC_TRNS,
								   KC_TRNS,KC_TRNS,KC_TRNS,
		   // right hand
		   KC_TRNS,       KC_TRNS,             KC_TRNS,       KC_TRNS,       KC_TRNS,        KC_TRNS,              MEH(KC_Q),
		   RSFT(KC_PGUP), KC_TRNS,             RSFT(KC_HOME), RSFT(KC_UP),   RSFT(KC_END),   RSFT(KC_PGUP),        MEH(KC_R),
						  RSFT(RCTL(KC_LEFT)), RSFT(KC_LEFT), RSFT(KC_DOWN), RSFT(KC_RIGHT), RSFT(RCTL(KC_RIGHT)), MEH(KC_S),
		   RSFT(KC_PGDN), KC_TRNS,             RCTL(KC_C),    RCTL(KC_X),    RCTL(KC_V),     RSFT(KC_PGDN),        MEH(KC_T),
					// bottom row
					KC_BSPC,   RCTL(KC_BSPC),    KC_DELETE,  LCTL(KC_DELETE),                                      MEH(KC_U),
		   // thumb cluster
		   KC_TRNS, KC_TRNS,
		   KC_TRNS,
		   KC_TRNS, KC_TRNS, KC_TRNS
	),  
  
  // shell navigation layer
  [SHELL_NAV] = KEYMAP(
       // left hand
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
       KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
               // bottom row
               KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
                                       // thumb cluster
                                       KC_TRNS,KC_TRNS,
                                               LALT(KC_D),
                               KC_TRNS,RCTL(KC_W),KC_TRNS,
       // right hand
       KC_TRNS,    KC_TRNS,        KC_TRNS,             KC_TRNS,         KC_TRNS,         KC_TRNS,        M(SWITCH_NDS),
       RCTL(KC_L), RCTL(KC_W),     KC_HOME,             KC_UP,           KC_END,          LALT(KC_D),     RCTL(KC_R),
                   LALT(KC_B),     KC_LEFT,             KC_DOWN,         KC_RIGHT,        LALT(KC_F),     LALT(KC_DOT),
       RCTL(KC_C), RCTL(KC_U),     M(SCREEN_COPY_MODE), M(SCREEN_PASTE), MEH(KC_V),      RCTL(KC_K),     M(SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND),
                // bottom row
                 M(SCREEN_TAB_LEFT), M(SCREEN_TAB_RIGHT), M(SCREEN_NEW_TAB),  KC_TRNS,    KC_TRNS,
       // thumb cluster
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
  ),
  

  
  [COMBINED] = KEYMAP(
  
	// left hand
	KC_NO,  KC_TRNS, KC_TRNS,    KC_TRNS,     KC_TRNS,     KC_TRNS,KC_TRNS,
	KC_TRNS,KC_ESC,  KC_LABK,    KC_RABK,     KC_DQUO,     KC_GRAVE,KC_TRNS,
	KC_TRNS,KC_LPRN, KC_RPRN,    KC_LBRACKET, KC_RBRACKET, KC_UNDS,
	KC_TRNS,KC_LCBR, KC_RCBR,    KC_BSLS,     KC_PIPE,     KC_TILD,KC_TRNS,
	// bottom row
	KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
	// thumb cluster
	KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,
	
	// right hand
	KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     MEH(KC_L),
	KC_TRNS, KC_PLUS,     KC_7,    KC_8,    KC_9,    KC_ASTR,     MEH(KC_M),
	         KC_MINS,     KC_4,    KC_5,    KC_6,    KC_SLSH,     MEH(KC_N),
	KC_TRNS, KC_EQUAL,    KC_1,    KC_2,    KC_3,    KC_QUES,     MEH(KC_O),
	// bottom row 
	                      KC_0,  KC_DOT,  KC_TRNS, KC_TRNS,     MEH(KC_P),
	// thumb cluster
	KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS,KC_TRNS),
  
  
	[MOUSE] = KEYMAP(
		   KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,      KC_TRNS, KC_TRNS,
		   KC_TRNS, KC_TRNS,      KC_PGUP,       KC_MS_WH_UP,   KC_UP,        KC_TRNS, KC_TRNS,
		   KC_TRNS, KC_MS_ACCEL0, KC_PGDN,       KC_MS_WH_DOWN, KC_DOWN,      KC_TRNS,
		   KC_TRNS, KC_TRNS,      KC_TRNS,       KC_TRNS,       KC_TRNS,      KC_TRNS, KC_TRNS,
		   KC_TRNS, KC_TRNS,      M(MOUSE_LOCK), KC_TRNS,       KC_MS_ACCEL0,
		   
											   KC_TRNS, KC_TRNS,
														KC_TRNS,
									  KC_TRNS, KC_BTN3, KC_TRNS,
		// right hand
		   KC_TRNS,  KC_TRNS,   KC_TRNS,      KC_TRNS,      KC_TRNS,      KC_TRNS,       KC_TRNS,
		   KC_TRNS,  KC_UP,     KC_HOME,      KC_MS_U,      KC_END,       KC_MS_WH_UP,   KC_TRNS,
					 KC_DOWN,   KC_MS_L,      KC_MS_D,      KC_MS_R,      KC_MS_WH_DOWN, KC_TRNS,
		   KC_TRNS,  MEH(KC_X), MEH(KC_Y),    MEH(KC_Z),    KC_F5,        RCTL(KC_W),    KC_TRNS,
									// browser tab control
							        RSFT(RCTL(KC_TAB)), RCTL(KC_TAB), RCTL(KC_T), LALT(KC_LEFT), KC_TRNS,
		   KC_TRNS, KC_TRNS,
		   KC_TRNS,
		   KC_TRNS, KC_BTN1, KC_BTN2
	),  
	

};

const uint16_t PROGMEM fn_actions[] = {
  [1] = ACTION_LAYER_TAP_TOGGLE(1)
};

// leaving this in place for compatibilty with old keymaps cloned and re-compiled.
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
      switch(id) {
		case MOUSE_TOGGLE:
            if (record->event.pressed) {
				layer_on(MOUSE);
            } else {
				if(!mouse_lock)
					layer_off(MOUSE);
			}
			break;
		case MOUSE_LOCK:
			if (record->event.pressed)
			{
				if(mouse_lock)
				{
					mouse_lock = false;
					layer_off(MOUSE);
				}
				else
					mouse_lock = true;
			}
			break;
        case SCREEN_TAB_LEFT:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(P), END);
            }        
            break;
        case SCREEN_TAB_RIGHT:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(N), END);
            }                    
            break;
        case SCREEN_NEW_TAB:
             if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(C), END);
            }                                
        break;
        case SCREEN_COPY_MODE:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(ESC), END);
            }
        break;
        case SCREEN_PASTE:
            if (record->event.pressed) {
                return MACRO( D(LCTL), T(A), U(LCTL), T(RBRC), END); 
            }
        break;        
        case SWITCH_NDS:
            if (record->event.pressed) {
                return MACRO( D(LSFT), 
							  T(F11), 
							  U(LSFT), 
							  W(255), 
							  D(LALT), 
							  T(TAB), 
							  U(LALT), 
							  END); 
            }                                
        break;        
        case SHELL_RECALL_LAST_ARG_REMOVE_FIRST_COMMAND:
            if (record->event.pressed) {
                return MACRO( T(UP), T(HOME), D(LALT), T(D), U(LALT), END);
            }
        break;                                
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    // dynamically generate these.
    case EPRM:
      if (record->event.pressed) {
        eeconfig_init();
      }
      return false;
      break;
    case VRSN:
      if (record->event.pressed) {
        SEND_STRING (QMK_KEYBOARD "/" QMK_KEYMAP " @ " QMK_VERSION);
      }
      return false;
      break;
    case RGB_SLD:
      if (record->event.pressed) {
        rgblight_mode(1);
      }
      return false;
      break;
    
  }
  return true;
}

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        ergodox_right_led_1_on();
    } else {
        ergodox_right_led_1_off();
    }
}

void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
		case COMBINED:
		    ergodox_right_led_2_on();		
			break;
	    case KEYNAV:
		case KEYSEL:
		    ergodox_right_led_3_on();
			break;
        case MOUSE:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

};
