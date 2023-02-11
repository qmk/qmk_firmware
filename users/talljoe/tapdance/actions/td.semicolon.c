/* Copyright 2020 Joseph Wasson
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

static struct {
  int semicolon;
  bool mods;
} tap_state = {0};

void tap_dance_semicolon_each(qk_tap_dance_state_t *state, void *user_data) {
    tap_state.mods |= get_mods();
}

// Send semi-colon + enter on two taps
void tap_dance_semicolon_finished(qk_tap_dance_state_t *state, void *user_data) {
  tap_state.semicolon = hold_cur_dance(state);
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: register_code(KC_SCLN); break;
    case SINGLE_HOLD: layer_on(_NUM); break;
  }
}

void tap_dance_semicolon_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (tap_state.semicolon) {
    case SINGLE_TAP: case DOUBLE_HOLD: unregister_code(KC_SCLN); break;
    case DOUBLE_TAP: {
      if (tap_state.mods) {
        SEND_STRING(";;"); // send normal when mods are pressed
      }
      else {
        SEND_STRING(";\n");
      }
      break;
    }
    case TRIPLE_TAP: {
      SEND_STRING(";\n\n");
    }
    case SPECIAL: layer_invert(_NUM); break;
    case SINGLE_HOLD: layer_off(_NUM); break;
  }
  tap_state.semicolon = 0;
}
