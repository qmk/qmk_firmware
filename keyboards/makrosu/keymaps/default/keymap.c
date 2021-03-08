#include QMK_KEYBOARD_H

enum planck_layers {
  _1,
  _2,
  _3,
  _4

};


enum planck_keycodes {
  L1,
  L2,
  L3
  
};

#define LOWER MO(_4)
#define IND_1          D4
#define IND_2          C6
#define IND_3          D7

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

	[_1] = LAYOUT(
		KC_ESC, KC_F1, KC_F2,
        LOWER, KC_Z, KC_X),

	[_2] = LAYOUT(
		LALT(KC_TAB), LGUI(KC_TAB), LCTL(KC_S),
        LOWER, LCTL(KC_C), LCTL(KC_V)),

	[_3] = LAYOUT(
		KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS),

	[_4] = LAYOUT(
		L1, L2, L3,
        _______, _______, _______),

};


layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, _LOWER, X_PAUSE, X_PAUSE);
    switch (get_highest_layer(state)) {
        case _1:
            writePinHigh(IND_1);
	        writePinLow(IND_2);
 	        writePinLow(IND_3); 
            return state;
            break;
        case _2:
            writePinLow(IND_1);
            writePinHigh(IND_2);
 	        writePinLow(IND_3);
            return state;
            break;
        case _3:
            writePinLow(IND_1);
            writePinLow(IND_2);
	        writePinHigh(IND_3);
            return state;
            break;
            
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case L1:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_1);
	

      }
      return false;
      break;
    case L2:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_2);
	
      }
      return false;
      break;
    case L3:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_3);
	
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
    if (layer_state_is(_1)) {
	if (clockwise) {
      tap_code(KC_UP);
    } else {
      tap_code(KC_DOWN);
    }
   }

    else if (layer_state_is(_2)) {
	if (clockwise) {
      tap_code(KC_RGHT);
    } else {
      tap_code(KC_LEFT);
    }
   }

    else if (layer_state_is(_3)) {
	if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
   }
}
