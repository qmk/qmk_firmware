/* Copyright 2020 Stephen J. Bush
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

#ifdef TAP_DANCE_ENABLE

#    include QMK_KEYBOARD_H
#    include "muppetjones.h"
#    include "dancelayers.h"

// Initialize tap structure associated with example tap dance key
static td_tap_t lyr_tap_state = {.is_press_action = true, .state = TD_NONE};

/* @brief Determine the current tap dance state
 * @param A tap dance state struct.
 * @return A struct.
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    switch (state->count) {
        case 1:
            if (!state->pressed)
                return TD_1X_TAP;
            else
                return TD_1X_HOLD;
        case 2:
            return TD_2X_TAP;
            break;
        case 3:
            return TD_3X_TAP;
            break;
        case 4:
            return TD_4X_TAP;
            break;
        default:
            return TD_UNKNOWN;
    }
}

// Functions that control what our tap dance key does
__attribute__((weak)) void td_layer_finished(qk_tap_dance_state_t *state, void *user_data) {
    lyr_tap_state.state = cur_dance(state);
    switch (lyr_tap_state.state) {
        case TD_1X_TAP:
            if (layer_state_is(_MOUSE))
                layer_off(_MOUSE);
            else
                layer_on(_MOUSE);
            break;
        case TD_1X_HOLD:
            layer_on(_ADJUST);
            break;
        case TD_2X_TAP:
            // Toggle lower layer
            if (layer_state_is(_LOWER))
                layer_off(_LOWER);
            else
                layer_on(_LOWER);
            break;
        case TD_3X_TAP:
            // Toggle lower layer
            if (layer_state_is(_RAISE))
                layer_off(_RAISE);
            else
                layer_on(_RAISE);
            break;
        case TD_4X_TAP:
            // Toggle lower layer
            if (layer_state_is(_ADJUST))
                layer_off(_ADJUST);
            else
                layer_on(_ADJUST);
            break;
        default:
            break;
    }
}

__attribute__((weak)) void td_layer_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (lyr_tap_state.state == TD_1X_HOLD) {
        layer_off(_ADJUST);
    }
    lyr_tap_state.state = TD_NONE;
}

#endif
