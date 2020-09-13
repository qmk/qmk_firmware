#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  KC_MUTE,
  KC_LEFT, KC_RGHT,
  KC_UP,   KC_UP),

[1] = LAYOUT(
  KC_MUTE,
  KC_LEFT, KC_RGHT,
  KC_UP,   KC_UP),

[2] = LAYOUT(
  KC_MUTE,
  KC_LEFT, KC_RGHT,
  KC_UP,   KC_UP),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if (clockwise) {
        tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
}

void matrix_init_user(void) {
  // set top LED to output and off (active low)
  setPinOutput(D5);
  writePinHigh(D5);
  // set middle LED to output and off (active low)
  setPinOutput(D4);
  writePinHigh(D4);
  // set bottom LED to output and off (active low)
  setPinOutput(D3);
  writePinHigh(D3);
}

// write to above indicators in a binary fashion based on current layer
layer_state_t layer_state_set_user(layer_state_t state)
{
  switch (get_highest_layer(state)){
    case 0:
      writePin(D5, true);
      break;
    case 1:
      writePin(D4, true);
      break;
    case 2:
      writePin(D3, true);
      break;
  }
    return state;
}