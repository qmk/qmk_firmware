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

enum TAP_DANCE {
  TD_PLAY = 0,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  LAYOUT(TD(TD_PLAY)),
};

void tap_dance (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 0 ... 1:
      register_code(KC_MEDIA_PLAY_PAUSE);
      unregister_code(KC_MEDIA_PLAY_PAUSE);
      break;
    case 2:
      register_code(KC_MEDIA_NEXT_TRACK);
      unregister_code(KC_MEDIA_NEXT_TRACK);
      break;
    case 3:
      rgblight_step();
      break;
    case 4: default:
      rgblight_step_reverse();
      break;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_PLAY] = ACTION_TAP_DANCE_FN(tap_dance),
};
