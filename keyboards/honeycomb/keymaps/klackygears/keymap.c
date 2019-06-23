
#include QMK_KEYBOARD_H

#include "klackygears.h"
// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
 enum honeycomb_layers {
	_MEDIA,
	_NUMPAD,
    _FUNCTION,
    _MAUSONE,
    _MAUSTWO
};

// Macro definitions for readability


extern int8_t encoderValue;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_MEDIA] = LAYOUT(
		MO(_FUNCTION), MO(_MAUSONE), MO(_MAUSTWO), KC_MUTE,
		KC_MPLY,       KC_MRWD,      KC_MFFD,      _______,
        KC_LEFT,       KC_UP,        KC_DOWN,      KC_RIGHT,
		KC_COPY,       KC_PASTE,     KC_SPACE,     TO(_NUMPAD)
	),

	[_NUMPAD] = LAYOUT(
		KC_7, KC_8,          KC_9,   LCTL(KC_UP),
		KC_4, KC_5,          KC_6,   TD(TD_MINPLS),
		KC_1, KC_2,          KC_3,   TD(TD_DIVMLT),
        KC_0, TD(TD_DOTEQL), KC_ENT, TO(_MEDIA)
	),

	[_MAUSONE] = LAYOUT(
		_______,    _______, _______,  KC_MS_BTN1,
		KC_MS_BTN1, _______, _______,  KC_MS_BTN1,
		KC_MS_BTN2, _______, _______,  KC_MS_BTN2,
		KC_MS_BTN3, _______, _______,  KC_MS_BTN3
	),

	[_MAUSTWO] = LAYOUT(
		_______,    _______, _______,  KC_MS_BTN1,
		KC_MS_BTN1, _______, _______,  KC_MS_BTN1,
		KC_MS_BTN2, _______, _______,  KC_MS_BTN2,
		KC_MS_BTN3, _______, _______,  KC_MS_BTN3
	),

[_FUNCTION] = LAYOUT(
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
      case _MEDIA:
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
      case _FUNCTION:
        while (encoderValue < 0){
        tap_code(KC_PGUP);
		encoderValue++;
	    }
	    while (encoderValue > 0){
        tap_code(KC_PGDN);
		encoderValue--;
        }
       break;
       case _MAUSONE:
        while (encoderValue < 0){
        tap_code(KC_MS_U);
		encoderValue++;
	    }
	    while (encoderValue > 0){
		tap_code(KC_MS_D);
		encoderValue--;
        }
       break;
       case _MAUSTWO:
        while (encoderValue < 0){
        tap_code(KC_MS_L);
		encoderValue++;
	    }
	    while (encoderValue > 0){
		tap_code(KC_MS_R);
		encoderValue--;
        }
       break;
    }

};
