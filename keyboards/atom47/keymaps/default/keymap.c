#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _MA 0 //Main layer
#define _FN 1 //Fn
#define _FN1 2 //Fn1
#define _PN 3 //Pn

#define _______ KC_TRNS

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MA] = LAYOUT(
  KC_ESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,  	\
  KC_LSFT,					KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_RSFT,	MO(_FN1),	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	MO(_PN),				KC_SPC, 				KC_SPC,					MO(_FN),	KC_RALT,	KC_APP,		KC_RCTRL),	\
 
[_FN] = LAYOUT(
  _______,		KC_VOLD,	KC_VOLU,	KC_MUTE,	RESET,		_______,	KC_CALC,	KC_PGUP,	KC_UP,		KC_PGDN,	KC_PSCR,	KC_SLCK,	KC_PAUS,	\
  KC_CAPS,		KC_MPRV,	KC_MPLY,	KC_MNXT,	_______,	_______,	KC_HOME,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	KC_INS,					_______,	\
  _______,					_______,	_______,	_______,	_______,	_______,	_______,	BL_TOGG,	BL_DEC,		BL_INC,		_______,	_______,	\
  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______),	\
 
[_FN1] = LAYOUT(
  KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		\
  KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,				KC_EQL,		\
  _______,					_______,	_______,	_______,	_______,	KC_QUOT,	KC_SLSH,	KC_LBRC,	KC_RBRC,	KC_BSLS,	KC_RSFT,	_______,	\
  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______),	\
 
[_PN] = LAYOUT(
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	\
  RGB_TOG,		RGB_HUI,	RGB_SAI,	RGB_VAI,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	\
  RGB_MOD,					RGB_HUD,	RGB_SAD,	RGB_VAD,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	_______,	\
  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	RESET),
};

void led_set_user(uint8_t usb_led) {
    if (usb_led & (1<<USB_LED_CAPS_LOCK)) {
        // Turn capslock on
 	   	PORTE &= ~(1 << 6);


    } else {
        // Turn capslock off
    	PORTE |= (1 << 6);
    }
}

