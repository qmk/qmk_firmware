#include QMK_KEYBOARD_H

#define _MAIN 0

void encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder*/
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
  } else if (index == 1) { /* Second encoder*/  
    if (clockwise) {
      tap_code(KC_F13);
    } else {
      tap_code(KC_F14);
    }
  } else if (index == 2) { /* Third encoder*/  
    if (clockwise) {
      tap_code(KC_F15);
    } else {
      tap_code(KC_F16);
    }
  } else if (index == 3) { /* Fourth encoder*/  
    if (clockwise) {
      tap_code(KC_F17);
    } else {
      tap_code(KC_F18);
    }
  } else if (index == 4) { /* Fifth encoder*/  
    if (clockwise) {
      tap_code(KC_F19);
    } else {
      tap_code(KC_F20);
    }
  }
}

enum {
  TD_RGB = 0
};

void dance_rgb_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    register_code (KC_F24);
	unregister_code (KC_F24);
  } else if (state->count == 2) {
    rgblight_toggle();
  } else if (state->count == 3) {
    rgblight_step();
  }
}

//All tap dance functions would go here. Only showing this one.
qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_RGB] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_rgb_finished, NULL)
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = { //buttion closest to usb is first
  [_MAIN] = LAYOUT(
     KC_MUTE, KC_F21, KC_F22, KC_F23, TD(TD_RGB) 
  )
};
