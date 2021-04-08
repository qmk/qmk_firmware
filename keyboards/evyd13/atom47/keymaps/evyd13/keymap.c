#include QMK_KEYBOARD_H

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

#define _MA 0 //Main layer
#define _LO 1 //FN1
#define _RA 2 //FN

enum custom_keycodes {
    CTRLZ = SAFE_RANGE,
    CTRLX,
    CTRLC,
    CTRLV
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_MA] = LAYOUT(
  KC_GESC,		KC_Q,		KC_W,		KC_E,		KC_R,		KC_T,		KC_Y,		KC_U,		KC_I,		KC_O,		KC_P,		KC_DEL,		KC_BSPC,	\
  KC_TAB,		KC_A,		KC_S,		KC_D,		KC_F,		KC_G,		KC_H,		KC_J,		KC_K,		KC_L,		KC_SCLN,				KC_ENT,  	\
  KC_LSFT,					KC_Z,		KC_X,		KC_C,		KC_V,		KC_B,		KC_N,		KC_M,		KC_COMM,	KC_DOT,		KC_SLSH,	KC_RSFT,	\
  KC_LCTL,		KC_LGUI,	KC_LALT,	MO(_LO),				KC_SPC, 				KC_SPC,					MO(_RA),	KC_RALT,	KC_APP,		KC_RCTRL),	\

[_LO] = LAYOUT(
  KC_GRV,		KC_F1,		KC_F2,		KC_F3,		KC_F4,		KC_F5,		KC_F6,		KC_F7,		KC_F8,		KC_F9,		KC_F10,		KC_F11,		KC_F12,		\
  KC_1,			KC_2,		KC_3,		KC_4,		KC_5,		KC_6,		KC_7,		KC_8,		KC_9,		KC_0,		KC_MINS,				KC_EQL,		\
  _______,					CTRLZ,		CTRLX,		CTRLC,		CTRLV,		_______,	_______,	KC_QUOT,	KC_LBRC,	KC_RBRC,	KC_BSLS,	_______,	\
  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	RESET),	\

[_RA] = LAYOUT(
  _______,		_______,	_______,	_______,	_______,	_______,	_______,	KC_PGUP,	KC_UP,		KC_PGDN,	_______,	_______,	_______,	\
  KC_CAPS,		_______,	_______,	_______,	_______,	_______,	_______,	KC_LEFT,	KC_DOWN,	KC_RIGHT,	_______,				_______,	\
  _______,					_______,	_______,	_______,	_______,	_______,	_______,	_______,	KC_VOLD,	KC_VOLU,	KC_MPLY,	KC_PSCR,	\
  _______,		_______,	_______,	_______,				_______, 				_______,				_______,	_______,	_______,	_______),	\

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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        switch(keycode) {
            case CTRLZ:
                SEND_STRING(SS_LCTRL("z"));
                return false;
            case CTRLX:
                SEND_STRING(SS_LCTRL("x"));
                return false;
            case CTRLC:
                SEND_STRING(SS_LCTRL("c"));
                return false;
            case CTRLV:
                SEND_STRING(SS_LCTRL("v"));
                return false;
        }
    }
    return true;
};
