

#include QMK_KEYBOARD_H


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {

  QWERTY = SAFE_RANGE,
//  DYNAMIC_MACRO_RANGE,
};

//#include "dynamic_macro.h"

#define _______ KC_TRNS
//#define KC_REC DYN_REC_START1
//#define KC_DONE DYN_REC_STOP
//#define KC_PLAY DYN_MACRO_PLAY1
#define _BL 0
#define _FL 1
#define _CL 2
#define TAPPING_TOGGLE 2
#define FN_CAPS LT(_FL, KC_CAPSLOCK)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
 
 /* Keymap _BL: Base Layer (Default Layer)
 ____________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |               |                 
|  ESC   |   1    |   2    |   3    |   4    |   5    |   6    |   7    |   8    |   9    |   0    |  _ -   | =  +   |  BACKSPACE    |
|________|________|________|________|________|________|________|________|________|________|________|________|________|_______________|
|            |        |        |        |        |        |        |        |        |        |        |  [     |   ]    |           |
|    TAB     |   Q    |   W    |   E    |   R    |   T    |   Y    |   U    |   I    |   O    |   P    |  {     |   }    |  |   \    |  
|____________|________|________|________|________|________|________|________|________|________|________|________|________|___________|
|              |        |        |        | ------ |        |        | ------ |        |        |   ;    |   '    |                  | 
|   FN 1       |   A    |   S    |   D    |   F    |   G    |   H    |   J    |   K    |   L    |   :    |   "    |       ENTER      | 
|______________|________|________|________|________|________|________|________|________|________|________|________|__________________|
|                  |        |        |        |        |        |        |        |   ,    |    .   |   /    |                       |
|     SHIFT        |   Z    |   X    |   C    |   V    |   B    |   N    |   M    |   <    |    >   |   ?    |       SHIFT           |
|__________________|________|________|________|________|________|________|________|________|________|________|_______________________|
|          |          |          |                                                       |          |          |          |          | 
| CTRL     |   LGUI   | L ALT    |                      FN 1                             | R ALT    |   WIN    |   FN 1   |  RCTRL   |
|__________|__________|__________|_______________________________________________________|__________|__________|__________|__________|
*/


    [_BL] = LAYOUT(
    KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,
    FN_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,          
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, 				KC_RSFT,         
    KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, TT(_FL), KC_RCTL
	),	

  /* Keymap _FL: Function Layer
 ____________________________________________________________________________________________________________________________________
|        |        |        |        |        |        |        |        |        |        |        |        |        |               |
| RESET  |  F1    |   F2   |  F3    |   F4   |   F5   |  F6    |   F7   |  F8    |   F9   |   F10  |  F11   |   F12  |    DELETE     |
|________|________|________|________|________|________|________|________|________|________|________|________|________|_______________|
|            |   	  |        |     	|      	 |	      |  	   |   	    |        |	   	  |        |        |        |           |
|            |  PLAY  |  VOLUP | MUTE   |		 |   	  |	 CALC  | HOME   |	UP   |	END   | PGUP   |        |        |    PSC    |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|___________|
|              |        |        |        | ------ |        |        | ------ |        |        |        |        |                  |
|              | PREV   | VOLDN  |  NEXT  |        |        | MYCOMP | LEFT   |  DOWN  | RIGHT  |  PGDN  |        |    INSERT        |
|______________|________|________|________|________|________|________|________|________|________|________|________|__________________|
|                  |        |        |        |        |        |        |        |        |        |        |                       |
|                  |        |        |        |        |        | MENU   | MACRO  | M_REC  | M_END  |        |                       |
|__________________|________|________|________|________|________|________|________|________|________|________|_______________________|
|          |          |          |                                                        |          |          |          |         |      
|          |          |          |                                                        |          |          |          |         |      
|__________|__________|__________|________________________________________________________|__________|__________|__________|_________|

*/
	
	[_FL] = LAYOUT(
	
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, 
    MO(_CL), KC_MPLY, KC_VOLU, KC_MUTE, _______, _______, KC_CALC, KC_HOME, KC_UP  , KC_END , KC_PGUP, _______, _______, KC_PSCR,         
    _______, KC_MPRV, KC_VOLD, KC_MNXT, _______, _______, KC_MYCM, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN, _______,       KC_INS,                  
    _______, _______, _______, _______, _______, _______, KC_APP,  _______, _______, _______, _______, 				_______,           
    _______, _______, _______,                            _______,                            _______, _______, _______, _______
	),

  /* Keymap _CL: CALC Layer
 ____________________________________________________________________________________________________________________________________ 
|        |        |        |        |        |        |        |        |        |        |        |        |        |               |
|        |        |        |        |        |        |        |        |        |        |        |        |        |               |
|________|________|________|________|________|________|________|________|________|________|________|________|________|_______________|
|            |   	  |        |     	|      	 |	      |  	   |   	    |        |	   	  |        |        |        |           |
|            |        |        |        |		 |   	  |	  /    |   7    |   8    |    9   |   -    |  DEL   |        |           |
|____________|________|________|________|________|________|________|________|________|________|________|________|________|___________|
|              |        |        |        | ------ |        |        | ------ |        |        |        |        |                  |
|              |        |        |        |        |        |   *    |   4    |   5    |   6    |   +    |  ESC   |      Enter       |
|______________|________|________|________|________|________|________|________|________|________|________|________|__________________|
|                  |        |        |        |        |        |        |        |        |        |        |                       |
|                  |        |        |        |        |        |   0    |   1    |   2    |   3    |   .    |                       |
|__________________|________|________|________|________|________|________|________|________|________|________|_______________________|
|          |          |          |                                                       |          |          |          |          |
|          |          |          |                                                       |          |          |          |          |
|__________|__________|__________|_______________________________________________________|__________|__________|__________|__________|
*/

	[_CL] = LAYOUT(
	
    RESET,   RGB_TOG, RGB_MOD, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, _______, _______, _______, _______,
    _______, _______, _______, _______, _______, _______, KC_PSLS, KC_7, 	KC_8, 	 KC_9,    KC_PMNS, KC_DEL,  _______, _______,
    _______, _______, _______, _______, _______, _______, KC_PAST, KC_4, 	KC_5, 	 KC_6,    KC_PPLS, KC_ESC,        KC_ENT,         
    _______, _______, _______, _______, _______, _______, _______, KC_1,    KC_2,    KC_3,    _______, 				_______,         
    _______, _______, _______,                            KC_0,                               KC_DOT,  _______, _______, _______
	),	
	
};

//RGB LAYERS BEGIN

// RGB Modes
// 1 = Static
// 2-5 = Breathing
// 6-8 = Rainbow
// 9-14 = Swirl
// 15-20 = Snake
// 21-24 = Nightrider
// 25 = Christmas
// 26-30 = Static Gradient

uint8_t prev = _BL;
uint32_t desired = 4;
uint16_t hue = 39;
uint16_t sat = 255;
uint16_t val = 255;

void get_hsv(void) {
	hue = rgblight_get_hue();
	sat = rgblight_get_sat();
	val = rgblight_get_val();
}

void reset_hsv(void) {
	rgblight_sethsv(hue, sat, val);
}

void matrix_init_user() {
	rgblight_mode(desired);
	rgblight_enable();
	reset_hsv();
}

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);
  if (prev!=_CL) {
      switch (layer) {
        case _BL:
          rgblight_sethsv(39, 255, 255);
          rgblight_mode(1);
          if (host_keyboard_leds()  & (1<<USB_LED_CAPS_LOCK) ) {
            rgblight_sethsv_at(0, 255, 255, 0);
            rgblight_sethsv_at(0, 255, 255, 1);
          }
          break;

        case _FL:
          rgblight_mode(1);
          rgblight_sethsv(240, 255, 255);
          break;

        case _CL:
          rgblight_mode(1);
          rgblight_sethsv(43, 218, 218);
          break;


      }
  } else {
      desired = rgblight_get_mode();
      get_hsv();
  }
  prev = layer;
  return state;
}
//RGB LAYERS END


//CAPS LOCK UNDERGLOW BEGIN

void led_set_user(uint8_t usb_led) {
  if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
     rgblight_sethsv_at(0, 255, 255, 0);
     rgblight_sethsv_at(0, 255, 255, 1);
  } else { 
    if (biton32(layer_state) == _BL) {
       rgblight_sethsv_at(39, 255, 255, 0);
       rgblight_sethsv_at(39, 255, 255, 1);
    }
  }
}

//CAPS LOCK UNDERGLOW END
