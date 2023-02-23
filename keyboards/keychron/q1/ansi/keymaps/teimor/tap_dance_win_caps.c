/* Copyright 2022 @ Teimor Epstein
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

/* Windows CapsLock language change */
#include "tap_dance_win_caps.h"

static td_tap_t win_caps_language_tap_state = {.is_press_action = true, .state = TD_NONE};

void win_caps_language_finished(qk_tap_dance_state_t *state, void *user_data) {
    win_caps_language_tap_state.state = current_dance(state);
    switch (win_caps_language_tap_state.state) {
        case TD_SINGLE_TAP:
            register_code(KC_LGUI);
            register_code(KC_SPACE);
            break;
        case TD_SINGLE_HOLD:
            register_code(KC_CAPS_LOCK);
            break;
        default:
            break;
    }
}

void win_caps_language_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (win_caps_language_tap_state.state) {
        case TD_SINGLE_TAP:
            unregister_code(KC_SPACE);
            unregister_code(KC_LGUI);
            break;
        case TD_SINGLE_HOLD:
            unregister_code(KC_CAPS_LOCK);
            break;
        default:
            break;
    }
    win_caps_language_tap_state.state = TD_NONE;
}
