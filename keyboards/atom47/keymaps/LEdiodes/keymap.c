#include QMK_KEYBOARD_H

// These are all aliases for the  function layers.
#define _L0 0
#define _L1 1
#define _L2 2
#define _L3 3

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_L0] = KEYMAP_ANSI(
  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,  	\
  KC_LSFT,		KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_RSFT,				MO(_L1),	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	TG(_L3),	KC_SPC, 				KC_SPC,					MO(_L2),	KC_RALT,	KC_APP,					KC_RCTRL),	\
 
[_L2] = KEYMAP_ANSI(
  _______,		KC_VOLD,	KC_VOLU,	KC_MUTE,	RESET,		_______,	KC_CALC,	KC_PGUP,	KC_UP,		KC_PGDN,	KC_PSCR,	KC_SLCK,	KC_PAUS,	\
  KC_CAPS,		KC_MPRV,	KC_MPLY,	KC_MNXT,	_______,	_______,	KC_HOME,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_INS,					_______,	\
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	BL_TOGG,	BL_DEC,		BL_INC,		_______,				_______,	\
  _______,		_______,	_______,	_______,	_______, 				_______,				_______,	_______,	_______,				_______),	\
 
[_L1] = KEYMAP_ANSI(
  KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		\
  KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,				KC_EQL,		\
  _______,		_______,	_______,	_______,	_______,	KC_QUOT,	KC_SLSH,	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_RSFT,				_______,	\
  _______,		_______,	_______,	_______,	_______, 				_______,				_______,	_______,	_______,				_______),	\
 
[_L3] = KEYMAP_ANSI(
  _______,		_______,	_______,	   KC_7,	   KC_8,	   KC_9,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	\
  _______,		_______,	_______,	   KC_4,	   KC_5,	   KC_6,	_______,	_______,	_______,	_______,	_______,				_______,	\
  _______,		_______,	_______,	   KC_1,	   KC_2,	   KC_3,	_______,	_______,	_______,	_______,	_______,				_______,	\
  _______,		_______,	_______,	   _______,    KC_0,	  KC_DOT, 	        	            _______,	_______,	_______,				RESET),     \
};
