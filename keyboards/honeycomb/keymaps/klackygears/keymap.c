#include QMK_KEYBOARD_H

#include "klackygears.h"

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum honeycomb_layers {
	_NAVI,
  _MNAV,
	_VERT,
  _HORZ,
  _MD,
  _NUMBER
};



// Macro definitions for readability
enum honeycomb_keycodes {
	HW = SAFE_RANGE,
	COPY,
	PASTA
};

extern int8_t encoderValue;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[_NAVI] = LAYOUT( /* Base layout, put whatever defaults. */
		TO(_MDIA), MO(_HORZ), MO(_VERT), KC_MUTE,
		_______,   _______,  LGUI(KC_F4),  KC_TAB,
    KC_8,    KC_9,    KC_A,    LSFT(KC_TAB),
		KC_C,    KC_D,    KC_E,    KC_LALT
	),

  [_MNAV] = LAYOUT( /* Base layout, put whatever defaults. */
		MO(_MDIA), MO(_HORZ), MO(_VERT), KC_MUTE,
		LCTL(KC_LEFT), LCTL(KC_UP), LCTL(KC_DOWN), LCTL(KC_RGHT),
    KC_8,    KC_9,    KC_A,    KC_ENT,
		KC_C,    KC_D,    KC_E,    KC_F
	),

	[_VERT] = LAYOUT( /* Alternate layer */
		_______, _______, _______, KC_HOME,
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______
	),


	[_HORZ] = LAYOUT( /* Alternate layer */
		_______, _______, _______, KC_END,
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______
	),


	[_MD] = LAYOUT( /* Alternate layer */
		TO(_NAVI), _______, LGUI(KC_F4), KC_MUTE,
		_______, _______, _______, _______,
		_______, _______, _______, _______,
		_______, _______, _______, _______
	),


	[_NUMBER] = LAYOUT( /* Alternate layer */
		KC_7,    KC_8,          KC_9,    KC_MUTE,
		KC_4,    KC_5,          KC_6,    TD(TD_DIVMLT),
		KC_1,    KC_2,          KC_3,    TD(TD_MINPLS),
		KC_0,    TD(TD_DOTEQL), _______, TO(_NAVI)
	)
};

report_mouse_t currentReport = {};
/*
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	//uint8_t layer = biton32(layer_state);  // get the current layer

	// Basic example functions
	switch (keycode) {
		case HW:
			if (record->event.pressed) {
					SEND_STRING("Hello, world!");
				} else {
					SEND_STRING("Goodbye, cruel world!");
				}
			break;
			case COPY:
				if (record->event.pressed) {
					tap_code16(LCTL(KC_C)); // Replace with tap_code16(LCMD(KC_C)) to enable for Mac
				}
			break;
			case PASTA:
				if (record->event.pressed) {
					tap_code16(LCTL(KC_V)); // Replace with tap_code16(LCMD(KC_V)) to enable for Mac
				}
			break;
		return false;
	}
	return true;
};
*/
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
	while (encoderValue < 0){
		tap_code(KC_VOLD);
		encoderValue++;
	}
	while (encoderValue > 0){
		tap_code(KC_VOLU);
		encoderValue--;
	}*/
};


#ifdef ENCODER_ENABLE
void encoder_update_user(uint8_t index, bool clockwise) {
if (index == 0) {
    switch(biton32(layer_state)) {
      case _VERT:
        clockwise ? tap_code(KC_WH_U) : tap_code(KC_WH_D);
        break;
      case _HORZ:
        clockwise ? tap_code(KC_WH_L) : tap_code(KC_WH_R);
        break;
      case _MDIA:
        clockwise ? tap_code(KC_AUDIO_VOL_UP) : tap_code(KC_AUDIO_VOL_DOWN);
        break;
      default:
        clockwise ? tap_code(KC_TAB) : tap_code(LSFT(KC_TAB));
        break;
      }
  }
}
#endif // ENCODER_ENABLE


