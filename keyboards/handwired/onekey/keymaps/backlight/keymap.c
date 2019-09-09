#include QMK_KEYBOARD_H

//Tap Dance Declarations
enum {
  TD_BL = 0
};

void dance_cln_finished (qk_tap_dance_state_t *state, void *user_data) {
  // noop
}

void dance_cln_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1:
      // single tap - step through backlight
      backlight_step();
      break;
#ifdef BACKLIGHT_BREATHING
    case 2:
      // double tap - toggle breathing
      breathing_toggle();
      break;
    case 3:
      //tripple tap - do some pulse stuff
      breathing_pulse();
      break;
#endif
    default:
      // more - nothing
      break;
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BL]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_cln_finished, dance_cln_reset)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT( TD(TD_BL) )
};
