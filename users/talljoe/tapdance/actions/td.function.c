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
  int state;
} function_state = {0};

// Send semi-colon + enter on two taps
void tap_dance_function_finished(qk_tap_dance_state_t *state, void *user_data) {
  function_state.state = hold_cur_dance(state);
  switch (function_state.state) {
    case SINGLE_HOLD: layer_on(_ADJUST); break;
  }
}

void tap_dance_function_reset(qk_tap_dance_state_t *state, void *user_data) {
  switch (function_state.state) {
    case SPECIAL: reset_keyboard(); break;
    case SINGLE_HOLD: layer_off(_ADJUST); break;
  }
  function_state.state = 0;
}
