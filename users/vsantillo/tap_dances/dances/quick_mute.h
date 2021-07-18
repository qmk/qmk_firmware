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

// Tap object to track status of Quick Mute
static tap quick_mute_state = {
    .state = 0,
    .count = 0
};

void quick_mute(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    quick_mute_state.state = tap_dance_controller(state);
    quick_mute_state.count = state->count;

    // Send keys
    switch (quick_mute_state.state) {
        case SINGLE_HOLD:
        case DOUBLE_HOLD:
        case TRIPLE_HOLD:
        case QUAD_HOLD:
            register_code(KC_MUTE);
            unregister_code(KC_MUTE);
            break;
        default:
            for (int vold_counter = 0; vold_counter < quick_mute_state.count; vold_counter++) {
                register_code(KC_VOLD);
                unregister_code(KC_VOLD);
            }
            break;
    }

    // Reset state
    quick_mute_state.state = 0;
}
