#include QMK_KEYBOARD_H

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[0] = LAYOUT(
  TO(1), //windows
  KC_MSTP, KC_MPLY,
  KC_MPRV, KC_MNXT),

[1] = LAYOUT( //macOS
  TO(2),
  KC_MSTP, KC_MPLY,
  KC_MRWD, KC_MFFD),

[2] = LAYOUT(
  TO(0),
  KC_HOME, KC_PGUP,
  KC_END,  KC_PGDN),
};

void encoder_update_user(uint8_t index, bool clockwise) {
  if(IS_LAYER_ON(2)){
    if (clockwise)
      tap_code(KC_LEFT);
    else 
      tap_code(KC_RGHT);
  }
  else{
    if(clockwise)
      tap_code(KC_VOLU);
    else
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
layer_state_t layer_state_set_user(layer_state_t state) {
    writePin(D5, get_highest_layer(state));
    writePin(D4, !layer_state_cmp(state, 1));
    writePin(D3, !layer_state_cmp(state, 2));
    return state;
}