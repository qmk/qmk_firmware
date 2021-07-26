#include QMK_KEYBOARD_H

/* enum custom_keycodes {
  SHIFTEN = SAFE_RANGE,
  LOWER,
  RAISE,
  SPACFNL,
  SPACFNR,
  MAIN,
  ADJUST
}; */

#define _MAIN 0
#define _SPLEFT 1
#define _SPRIGHT 2
#define _LOWER 3
#define _RAISE 4
#define _ADJUST 5

#define _DPAD 6
#define _DPADNUM 7


#define SHIFTEN RSFT_T(KC_ENT)
#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define SPACFNL LT(_SPLEFT, KC_SPC)
#define SPACFNR LT(_SPRIGHT, KC_SPC)

#define DP_ON TO(_DPAD)
#define DP_OFF TO(_MAIN)
#define DPADNUM MO(_DPADNUM)


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	
	// Primary layer	
	[_MAIN] = LAYOUT(
	  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,
	  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_QUOT,
	  KC_LSFT,					KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	SHIFTEN,
	  KC_LCTL,		KC_LGUI,	KC_LALT,	LOWER,					SPACFNL, 				SPACFNR,				RAISE,		KC_RALT,	KC_APP,		KC_RCTRL
	),

	// Main Fn navigation layer
	[_SPLEFT] = LAYOUT(
	  _______,		KC_VOLU, 	KC_PGUP, 	KC_UP,   	KC_PGDN, 	KC_INS,  	_______, 	_______, 	KC_UP,   	_______, 	KC_PSCR,	_______,	_______,	
	  _______,		KC_VOLD, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	KC_HOME, 	_______, 	KC_LEFT, 	KC_DOWN, 	KC_RGHT, 	_______, 				KC_DEL , 	
	  _______,					_______,    KC_MPRV, 	KC_MPLY, 	KC_MNXT, 	KC_END,  	_______, 	_______, 	KC_VOLD, 	KC_VOLU, 	KC_MUTE,	_______,	
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______
	),	

	// Primary numeric layer using right Spacebar
	[_SPRIGHT] = LAYOUT(
	  KC_GRV,		_______,	_______,	KC_LBRC, 	KC_RBRC,	_______,	_______,	KC_7,		KC_8,		KC_9,		KC_0,		_______,	_______,	
	  _______,		_______,	_______,	KC_LCBR, 	KC_RCBR,	_______,	_______,	KC_4,		KC_5,		KC_6,	 	KC_MINUS, 				KC_BSLS, 	
	  _______,					_______,	_______,	_______,	_______,	_______,	_______,	KC_1,		KC_2,		KC_3,		KC_EQUAL,	_______,	
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______
	),	

	// Secondary symbol layer, also Lower
	[_LOWER] = LAYOUT(
	  KC_TILD, 		_______,	_______,	_______,	_______,	_______,	_______, 	KC_AMPR, 	KC_ASTR, 	KC_LPRN, 	KC_RPRN,	KC_SLCK,	KC_PAUS,	
	  KC_CAPS,		KC_F1,   	KC_F2,   	KC_F3,   	KC_F4,   	KC_F5,   	KC_F6,		KC_DLR,  	KC_PERC, 	KC_CIRC, 	KC_UNDS, 				KC_PIPE,	
	  _______,					KC_F7,   	KC_F8,   	KC_F9,   	KC_F10,  	KC_F11,  	KC_F12,		KC_EXLM, 	KC_AT,   	KC_HASH, 	KC_PLUS,	_______,	
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	KC_VOLD, 	KC_VOLU, 	KC_MPLY
	),	
	  
	// Numpad layer // Also a homage to Planck with the media player/pause button
	[_RAISE] = LAYOUT(
	  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	
	  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,				_______,
	  _______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	KC_VOLD, 	KC_VOLU, 	KC_MPLY
	),	

	// Safety layer for special functions
	[_ADJUST] = LAYOUT(
	  _______,		RESET,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,
	  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,				_______,
	  _______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	DP_ON,
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______
	),
	
	[_DPAD] = LAYOUT(
	  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,
	  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_QUOT,
	  KC_LSFT,					KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_UP,		KC_ENT,
	  KC_LCTL,		KC_LGUI,	KC_LALT,	XXXXXXX,				DPADNUM, 				KC_SPC,					DP_OFF,		KC_LEFT,	KC_DOWN,	KC_RGHT
	),
	
	[_DPADNUM] = LAYOUT(
	  _______,		KC_1,		KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		_______,	_______,
	  _______,		_______,	_______,	_______,	_______,	KC_F1,   	KC_F2,   	KC_F3,   	KC_F4,   	KC_F5,   	KC_F6,					_______,
	  _______,					_______,	_______,	_______,	_______,	KC_F7,   	KC_F8,   	KC_F9,   	KC_F10,  	KC_F11,  	KC_F12,		_______,
	  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______
	),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
/*     case MAIN:
      if (record->event.pressed) {
        persistant_default_layer_set(1UL<<_MAIN);
      }
      return false;
      break; */
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
/*     case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break; */
  }
  return true;
}

void led_set_user(uint8_t usb_led) {
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        // Turn capslock on
 	   	writePinLow(E6);


    } else {
        // Turn capslock off
    	writePinHigh(E6);
    }
}
