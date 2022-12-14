/*
Copyright 2018 Cole Markham

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H


extern rgblight_config_t rgblight_config;

enum custom_keycodes {
  BL = SAFE_RANGE
};

enum custom_layers {
  BASE = 0,
  LED
};

//Tap Dance Declarations
enum {
  TD_TOGGLE = 0
};

void dance_toggle (tap_dance_state_t *state, void *user_data) {
  if (state->count >= 2) {
    println("Double tapped, switching layers");
    if (layer_state_is(LED)) {
      layer_off(LED);
    } else {
      layer_on(LED);
    }
  } else {
    print("Single tapped: ");
    if (layer_state_is(LED)) {
#ifdef RGBLIGHT_ENABLE
      if (!rgblight_config.enable) {
        rgblight_enable();
      }
      rgblight_step();
#endif
    } else {
      println("Base layer, sending string");
      SEND_STRING("This thing is BIG!!\n");
    }
  }
}

//Tap Dance Definitions
tap_dance_action_t tap_dance_actions[] = {
  [TD_TOGGLE]  = ACTION_TAP_DANCE_FN(dance_toggle)
// Other declarations would go here, separated by commas, if you have them
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[BASE] = LAYOUT(
    TD(TD_TOGGLE)),
[LED] = LAYOUT(
    TD(TD_TOGGLE)
    )


};
