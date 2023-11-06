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
} lock_state = {0};

// Send semi-colon + enter on two taps
void tap_dance_lock_finished(tap_dance_state_t *state, void *user_data) {
  lock_state.state = cur_dance(state);
  switch (lock_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: macro_lock(); break;
  }
}

void tap_dance_lock_reset(tap_dance_state_t *state, void *user_data) {
  switch (lock_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
  }
  lock_state.state = 0;
}
