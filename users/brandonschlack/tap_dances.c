/* Copyright 2020 Brandon Schlack
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
#include "tap_dances.h"
#include "process_keycode/process_tap_dance.h"

int cur_dance (tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        else return SINGLE_HOLD;
    } else if (state->count == 2) {
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    if (state->count == 3) {
        if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
        else return TRIPLE_HOLD;
    }
    else return 8;
}

__attribute__ ((weak))
void process_tap_dance_keycode (bool reset, uint8_t toggle_layer) { };

void td_trigger_layer_finished (tap_dance_state_t *state, void *user_data) {
    tap_dance_trigger_layer_t *data = (tap_dance_trigger_layer_t *)user_data;
    data->state = cur_dance(state);

    if (data->state == data->trigger) {
        layer_on(data->layer);
    } else {
        process_tap_dance_keycode(false, data->layer);
    }

}
void td_trigger_layer_reset (tap_dance_state_t *state, void *user_data) {
    tap_dance_trigger_layer_t *data = (tap_dance_trigger_layer_t *)user_data;
    if (data->state == data->trigger) {
        switch (data->trigger) {
            case SINGLE_HOLD:
            case DOUBLE_HOLD:
            case TRIPLE_HOLD:
                layer_off(data->layer);
                break;
        }
    } else {
        process_tap_dance_keycode(true, data->layer);
    }
    data->state = 0;
}

/* Tap Dance: Layer Mod. Toggles Layer when tapped, Mod when held. */
void td_layer_mod_each(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *data = (tap_dance_dual_role_t *)user_data;

    // Single tap → toggle layer, Single hold → mod
    if (state->pressed) {
        register_code(data->kc);
    } else if (state->count == 1) {
        state->finished = true;
    }
}

void td_layer_mod_finished(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *data = (tap_dance_dual_role_t *)user_data;

    if (state->count == 1 && !state->pressed) {
        layer_invert(data->layer);
    }
}

void td_layer_mod_reset(tap_dance_state_t *state, void *user_data) {
    tap_dance_dual_role_t *data = (tap_dance_dual_role_t *)user_data;

    if (state->count == 1) {
        unregister_code(data->kc);
    }
}
