#include "MakrOSU.h"

enum planck_layers {
  _OSU,
  _TUGAS,
  _RANDOM,
  _LOWER

};


enum planck_keycodes {
  OSU = SAFE_RANGE,
  TUGAS,
  RANDOM
  
};

#define LOWER MO(_LOWER)
#define IND_1          D4
#define IND_2          C6
#define IND_3          D7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_OSU] = KEYMAP(
		KC_ESC, KC_F1, KC_F2,
        LOWER, KC_Z, KC_X),

	[_TUGAS] = KEYMAP(
		LALT(KC_TAB), LGUI(KC_TAB), LCTL(KC_S),
        LOWER, LCTL(KC_C), LCTL(KC_V)),

	[_RANDOM] = KEYMAP(
		KC_ESC, KC_F1, KC_F2,
        LOWER, KC_Z, KC_X),

	[_LOWER] = KEYMAP(
		OSU, TUGAS, RANDOM,
        _______, _______, _______),

};


layer_state_t layer_state_set_user(layer_state_t state) {
  return update_tri_layer_state(state, _LOWER, X_PAUSE, X_PAUSE);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case OSU:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_OSU);
	writePinHigh(IND_1);
	writePinLow(IND_2);
 	writePinLow(IND_3); 

      }
      return false;
      break;
    case TUGAS:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_TUGAS);
	writePinLow(IND_1);
        writePinHigh(IND_2);
 	writePinLow(IND_3);
      }
      return false;
      break;
    case RANDOM:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_RANDOM);
	writePinLow(IND_1);
        writePinLow(IND_2);
	writePinHigh(IND_3);
      }
      return false;
      break;
    
  }
  return true;
}

void matrix_init_user(void) {
    //init the Pro Micro on-board LEDs
    setPinOutput(IND_1);
    setPinOutput(IND_2);
    setPinOutput(IND_3);
    //set to off
    writePinHigh(IND_1);
    writePinHigh(IND_2);
    writePinHigh(IND_3);
}

void matrix_scan_user(void) {
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (layer_state_is(_OSU)) {
	if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
   }

    else if (layer_state_is(_TUGAS)) {
	if (clockwise) {
      tap_code(KC_RGHT);
    } else {
      tap_code(KC_LEFT);
    }
   }

    else if (layer_state_is(_RANDOM)) {
	if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
   }
}
