#include QMK_KEYBOARD_H
#include "pointing_device.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum honeycomb_layers {
	_BS,
	_EN
};

// Macro definitions for readability
enum honeycomb_keycodes {
	HW = SAFE_RANGE,
	COPY,
	PASTA
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

extern int8_t encoderValue;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_BS] = LAYOUT( /* Base layout, put whatever defaults. */
		HW,      COPY,    PASTA,   KC_MUTE,
		KC_4,    KC_5,    KC_6,    KC_7,
    KC_8,    KC_9,    KC_A,    KC_B,
		KC_C,    KC_D,    KC_E,    KC_F
	),

	[_EN] = LAYOUT( /* Alternate layer */
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______
	)
};


const uint16_t PROGMEM fn_actions[] = {

};

report_mouse_t currentReport = {};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//uint8_t layer;
	//layer = biton32(layer_state);  // get the current layer  //Or don't, I didn't use it.
	bool returnVal = true; //this is to determine if more key processing is needed.

	// Frankly, I don't need this for the macropad, but I want to leave an example in...
	switch (keycode) {
		case HW:
			if (record->event.pressed) {
				SEND_STRING("Hello, world!");
			} else {
				SEND_STRING("Goodbye, cruel world!");
			}
			returnVal = false;
		break;
		case COPY:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("c"));
				SEND_STRING(SS_LGUI("c"));
			}
			returnVal = false;
		break;
		case PASTA:
			if (record->event.pressed) {
				SEND_STRING(SS_LCTRL("v"));
				SEND_STRING(SS_LGUI("v"));
			}
			returnVal = false;
		break;
	}
	return returnVal;
};

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
	}*/
	while (encoderValue < 0){
	    SEND_STRING(SS_TAP(X_AUDIO_VOL_DOWN));
	    encoderValue++;
	}
	while (encoderValue > 0){
	    SEND_STRING(SS_TAP(X_AUDIO_VOL_UP));
	    encoderValue--;
	}
};
