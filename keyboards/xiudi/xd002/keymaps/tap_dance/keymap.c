#include QMK_KEYBOARD_H

enum layers {
  _BASE = 0,
};

enum {
  TD_BC = 0
};

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_BC]  = ACTION_TAP_DANCE_DOUBLE(KC_B, KC_C)
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_A,  TD(TD_BC)
  )
};
