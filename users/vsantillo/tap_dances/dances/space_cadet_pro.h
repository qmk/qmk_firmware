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

// Tap object to track status of Space Cadet Pro
static tap space_cadet_pro_state = {
    .state = 0,
    .count = 0
};

void left_space_cadet_pro_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    space_cadet_pro_state.state = tap_dance_controller(state);

    // Send keys
    switch (space_cadet_pro_state.state) {
        case SINGLE_TAP:
            register_code(KC_LSFT); // Left Shift
            register_code(KC_9);    // + 9 = (
            break;
        case DOUBLE_TAP:
            register_code(KC_LBRC); // [
            break;
        case TRIPLE_TAP:
            register_code(KC_LSFT); // Left Shift
            register_code(KC_LBRC); // + [ = {
            break;
        default:
            register_code(KC_LSFT); // Shift
            break;
    }
}

void left_space_cadet_pro_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    // Unregister keys
    switch (space_cadet_pro_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_9);
            unregister_code(KC_LSFT);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_LBRC);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_LBRC);
            unregister_code(KC_LSFT);
            break;
        default:
            unregister_code(KC_LSFT);
            break;
    }

    // Reset state
    space_cadet_pro_state.state = 0;
}

void right_space_cadet_pro_on_finish(qk_tap_dance_state_t *state, void *user_data) {
    // Get current state
    space_cadet_pro_state.state = tap_dance_controller(state);

    // Send keys
    switch (space_cadet_pro_state.state) {
        case SINGLE_TAP:
            register_code(KC_RSFT); // Right Shift
            register_code(KC_0);    // + 0 = )
            break;
        case DOUBLE_TAP:
            register_code(KC_RBRC); // ]
            break;
        case TRIPLE_TAP:
            register_code(KC_RSFT); // Right Shift
            register_code(KC_RBRC); // + ] = }
            break;
        default:
            register_code(KC_RSFT); // Shift
            break;
    }
}

void right_space_cadet_pro_on_reset(qk_tap_dance_state_t *state, void *user_data) {
    // Unregister keys
    switch (space_cadet_pro_state.state) {
        case SINGLE_TAP:
            unregister_code(KC_0);
            unregister_code(KC_RSFT);
            break;
        case DOUBLE_TAP:
            unregister_code(KC_RBRC);
            break;
        case TRIPLE_TAP:
            unregister_code(KC_RBRC);
            unregister_code(KC_RSFT);
            break;
        default:
            unregister_code(KC_RSFT);
            break;
    }

    // Reset state
    space_cadet_pro_state.state = 0;
}
