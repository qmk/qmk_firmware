#include QMK_KEYBOARD_H

#define _MAIN 0

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { 
    if (clockwise) {
      tap_code(KC_F13);
    } else {
      tap_code(KC_F14);
    }
  } 
}

enum {
  TD_RGB = 0
};

void dance_rgb_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_F19);
	unregister_code (KC_F19);
  } else if (state->count == 2) {
    rgblight_toggle();
  } else if (state->count == 3) {
    rgblight_step();
  }
}

enum custom_keycodes {
    CTRLF22 = SAFE_RANGE,
	ALTV,
	ALTS,
	ALTT,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case CTRLF22:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_TAP(X_F22)SS_LCTRL(""));
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case ALTV:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LALT("v"));
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case ALTS:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LALT("s"));
        } else {
            // when keycode QMKBEST is released
        }
        break;
	case ALTT:
        if (record->event.pressed) {
            // when keycode QMKBEST is pressed
            SEND_STRING(SS_LALT("t"));
        } else {
            // when keycode QMKBEST is released
        }
        break;	
    }
    return true;
};

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RGB] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_rgb_finished, NULL)
};

//
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT(
     KC_F15, KC_F16, KC_F17, KC_F18, TD(TD_RGB)
  )
};
