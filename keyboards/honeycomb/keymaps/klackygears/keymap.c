
#include QMK_KEYBOARD_H

#include "klackygears.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
 enum honeycomb_layers {
	_NAVI,
	_NUMPAD,
    _FUNCTN,
    _EXCLONE,
    _EXCLTWO
};

// Macro definitions for readability


extern int8_t encoderValue;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NAVI] = LAYOUT(
		MO(_FUNCTN),   TO(_NUMPAD),  MO(_EXCLTWO), KC_MUTE,
		G(S(KC_O)),    A(KC_C),      G(KC_F5),     G(KC_F4),
        KC_LEFT,       KC_UP,        KC_DOWN,      KC_RIGHT,
		KC_COPY,       KC_PASTE,     MO(_EXCLTWO), MO(_EXCLONE)
	),

	[_NUMPAD] = LAYOUT(
		KC_7, KC_8,          KC_9,   C(KC_UP),
		KC_4, KC_5,          KC_6,   TD(TD_MINPLS),
		KC_1, KC_2,          KC_3,   TD(TD_DIVMLT),
        KC_0, TD(TD_DOTEQL), KC_ENT, TO(_NAVI)
	),

	[_EXCLONE] = LAYOUT(
		LCTL(KC_A),    TD(TD_CCPY), TD(TD_PSTI),   C(KC_HOME),
		C(KC_LEFT),    C(KC_UP),    C(KC_DOWN),    C(KC_RIGHT),
		C(S(KC_LEFT)), C(S(KC_UP)), C(S(KC_DOWN)), C(S(KC_RIGHT)),
        TD(TD_PTSP),   TD(TD_DDEL), TD(TD_ACCW),   _______
	),

	[_EXCLTWO] = LAYOUT(
		_______,    _______, _______,  C(KC_END),
		A(KC_PGUP), KC_PGUP, KC_PGDN,  A(KC_PGDN),
		_______, _______, _______,  _______,
		_______, _______, _______,  _______
	),

    [_FUNCTN] = LAYOUT(
		_______,   _______, _______, LGUI(KC_UP),
		_______,   _______, _______, KC_FIND,
		MAKEKF,    _______, _______, _______,
		KC_SLEP,   _______, _______, _______
    )
};

report_mouse_t currentReport = {};


void matrix_scan_user(void) {
	/* Leaving some LED stuff in here in comment form so you can see how to use it.
    if (shiftLED || capsLED){
		red_led_on;
    } else {
		red_led_off;
    }
    if (numLED){
		grn_led_on;
    } else {
		grn_led_off;
    }
    if (mouseLED){
		blu_led_on;
    } else {
		blu_led_off;
	}
	*/

    switch(biton32(layer_state)) {
      case _NAVI:
        while (encoderValue < 0){
		tap_code(KC_VOLU);
		encoderValue++;
	    }
	    while (encoderValue > 0){
		tap_code(KC_VOLD);
		encoderValue--;
        }
      break;
      case _NUMPAD:
        while (encoderValue < 0){
        register_code(KC_LCTL);
        tap_code(KC_LEFT);
        unregister_code(KC_LCTL);
		encoderValue++;
	    }
	    while (encoderValue > 0){
		register_code(KC_LCTL);
        tap_code(KC_RIGHT);
        unregister_code(KC_LCTL);
		encoderValue--;
        }
      break;
      case _FUNCTN:
        while (encoderValue < 0){
        tap_code(KC_PGUP);
		encoderValue++;
	    }
	    while (encoderValue > 0){
        tap_code(KC_PGDN);
		encoderValue--;
        }
       break;
       case _EXCLONE:
        while (encoderValue < 0){
        register_code(KC_LCTL);
        tap_code(KC_PGUP);
        unregister_code(KC_LCTL);
		encoderValue++;
	    }
	    while (encoderValue > 0){
        register_code(KC_LCTL);
        tap_code(KC_PGDOWN);
        unregister_code(KC_LCTL);
		encoderValue--;
        }
       break;
       case _EXCLTWO:
        while (encoderValue < 0){
        register_code(KC_LCTL);
        tap_code(KC_F6);
        unregister_code(KC_LCTL);
		encoderValue++;
	    }
	    while (encoderValue > 0){
		register_code(KC_LCTL);
        register_code(KC_LSFT);
        tap_code(KC_F6);
        unregister_code(KC_LSFT);
        unregister_code(KC_LCTL);
		encoderValue--;
        }
       break;
    }

};
