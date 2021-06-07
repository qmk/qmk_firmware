/* Copyright 2021 Vincent Santillo (vincentsantillo@gmail.com)
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
#pragma once

// Tap object to track status of Quick redo
static tap quick_redo_state = {
    .state = 0,
    .count = 0
};

void quick_redo_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    quick_redo_state.state = tap_dance_controller(state);

    // Send keys
    switch (quick_redo_state.state) {
        case DOUBLE_HOLD:
            register_code(KC_RALT);    // Right Alt
            register_code(KC_RSHIFT);  // + Right Shift
            register_code(KC_Z);       // + Z = redo on macOS
            break;
        default:
            register_code(KC_RALT); // Right Alt
            break;
    }
}

void quick_redo_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    // Unregister keys
    switch (quick_redo_state.state) {
        case DOUBLE_HOLD:
            unregister_code(KC_Z);
            unregister_code(KC_RSHIFT);
            unregister_code(KC_RALT);
            break;
        default:
            unregister_code(KC_RALT);
            break;
    }

    quick_redo_state.state = 0;
}
