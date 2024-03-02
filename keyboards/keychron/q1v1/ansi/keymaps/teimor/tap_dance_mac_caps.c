/* Copyright 2021 @ Teimor Epstein
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

/* macOS CapsLock language change */
#include "tap_dance_mac_caps.h"

static td_tap_t mac_caps_language_tap_state = {.is_press_action = true, .state = TD_NONE};

void mac_caps_language_finished(tap_dance_state_t *state, void *user_data) {
    mac_caps_language_tap_state.state = current_dance(state);
    switch (mac_caps_language_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LCTL);
            register_code(KC_SPACE);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_CAPS_LOCK);
            break;
        default:
            break;
    }
}

void mac_caps_language_reset(tap_dance_state_t *state, void *user_data) {
    switch (mac_caps_language_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_SPACE);
            unregister_code(KC_LCTL);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_CAPS_LOCK);
            break;
        default:
            break;
    }
    mac_caps_language_tap_state.state = TD_NONE;
}
