/* Copyright 2022 @daliusd
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
#include "flow.h"

extern const uint16_t flow_config[FLOW_COUNT][2];
extern const uint16_t flow_layers_config[FLOW_LAYERS_COUNT][2];

// Represents the states a flow key can be in
typedef enum {
    flow_up_unqueued,
    flow_up_queued,
    flow_up_queued_used,
    flow_down_unused,
    flow_down_used,
} flow_state_t;

#ifdef FLOW_ONESHOT_TERM
const int g_flow_oneshot_term = FLOW_ONESHOT_TERM;
#else
const int g_flow_oneshot_term = 500;
#endif

#ifdef FLOW_ONESHOT_WAIT_TERM
const int g_flow_oneshot_wait_term = FLOW_ONESHOT_WAIT_TERM;
#else
const int g_flow_oneshot_wait_term = 500;
#endif

flow_state_t flow_state[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = flow_up_unqueued };
bool flow_pressed[FLOW_COUNT][2] = { [0 ... FLOW_COUNT - 1] = {false, false} };
uint16_t flow_timers[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = 0 };
bool flow_timeout_timers_active[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = false };
uint16_t flow_timeout_timers_value[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = 0 };
uint16_t flow_timeout_wait_timers_value[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = 0 };

flow_state_t flow_layers_state[FLOW_LAYERS_COUNT] = {
    [0 ... FLOW_LAYERS_COUNT - 1] = flow_up_unqueued
};
bool flow_layer_timeout_timers_active[FLOW_LAYERS_COUNT] = { [0 ... FLOW_LAYERS_COUNT - 1] = false };
uint16_t flow_layer_timeout_timers_value[FLOW_LAYERS_COUNT] = { [0 ... FLOW_LAYERS_COUNT - 1] = 0 };
uint16_t flow_layer_timeout_wait_timers_value[FLOW_LAYERS_COUNT] = { [0 ... FLOW_LAYERS_COUNT - 1] = 0 };

bool is_flow_ignored_key(uint16_t keycode) {
    for (int i = 0; i < FLOW_COUNT; i++) {
        if (flow_config[i][0] == keycode) {
            return true;
        }
    }

    for (int i = 0; i < FLOW_LAYERS_COUNT; i++) {
        if (flow_layers_config[i][0] == keycode) {
            return true;
        }
    }

    if (keycode == KC_LSFT || keycode == KC_RSFT
            || keycode == KC_LCTL || keycode == KC_RCTL
            || keycode == KC_LALT || keycode == KC_RALT
            || keycode == KC_LGUI || keycode == KC_RGUI) {
        return true;
    }

    return false;
}

bool update_flow_mods(
    uint16_t keycode,
    bool pressed
) {
    bool pass = true;
    bool flow_key_list_triggered[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = false };
    bool flow_key_list_pressed[FLOW_COUNT] = { [0 ... FLOW_COUNT - 1] = false };

    bool flow_triggered = false;

    for (uint8_t i = 0; i < FLOW_COUNT; i++) {
        // Layer key
        if (keycode == flow_config[i][0]) {
            if (pressed) {
                flow_pressed[i][0] = true;
            } else {
                flow_pressed[i][0] = false;
            }
        // KC mod key
        } else if (keycode == flow_config[i][1]) {
            if (pressed) {
                if (flow_pressed[i][0]) {
                    flow_pressed[i][1] = true;
                    flow_key_list_triggered[i] = true;
                    flow_triggered = true;
                    flow_key_list_pressed[i] = true;
                    pass = false;
                 }
            } else if (flow_pressed[i][1]) {
                flow_pressed[i][1] = false;
                if (flow_pressed[i][0]) {
                    flow_key_list_triggered[i] = true;
                    flow_triggered = true;
                    pass = false;
                } else if ((flow_state[i] == flow_down_unused)
                        || (flow_state[i] == flow_down_used)) {
                    flow_key_list_triggered[i] = true;
                    flow_triggered = true;
                    pass = false;
                }
            }
        }
    }

    for (uint8_t i = 0; i < FLOW_COUNT; i++) {
        if (flow_key_list_triggered[i]) {
            if (flow_key_list_pressed[i]) {
                if (flow_state[i] == flow_up_unqueued) {
                    register_code(flow_config[i][1]);
                }
                flow_timeout_wait_timers_value[i] = timer_read();
                flow_state[i] = flow_down_unused;
            } else {
                // Trigger keyup
                switch (flow_state[i]) {
                case flow_down_unused:
                    if (!flow_pressed[i][1]) {
                        if (timer_elapsed(flow_timeout_wait_timers_value[i]) > g_flow_oneshot_wait_term) {
                            flow_state[i] = flow_up_unqueued;
                            unregister_code(flow_config[i][1]);
                        } else {
                            // If we didn't use the mod while trigger was held, queue it.
                            flow_state[i] = flow_up_queued;
                            flow_timeout_timers_active[i] = true;
                            flow_timeout_timers_value[i] = timer_read();
                        }
                    }
                    break;
                case flow_down_used:
                    // If we did use the mod while trigger was held, unregister it.
                    if (!flow_pressed[i][1]) {
                        flow_state[i] = flow_up_unqueued;
                        unregister_code(flow_config[i][1]);
                    }
                    break;
                default:
                    break;
                }
            }
        } else if (!flow_triggered) {
            if (pressed) {
                if (!is_flow_ignored_key(keycode)) {
                    switch (flow_state[i]) {
                    case flow_up_queued:
                        flow_state[i] = flow_up_queued_used;
                        flow_timeout_timers_active[i] = false;
                        break;
                    case flow_up_queued_used:
                        flow_state[i] = flow_up_unqueued;
                        unregister_code(flow_config[i][1]);
                        break;
                    default:
                        break;
                    }
                }
            } else {
                if (!is_flow_ignored_key(keycode)) {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (flow_state[i]) {
                    case flow_down_unused:
                        flow_state[i] = flow_down_used;
                        break;
                    case flow_up_queued:
                        flow_state[i] = flow_up_unqueued;
                        unregister_code(flow_config[i][1]);
                        break;
                    case flow_up_queued_used:
                        flow_state[i] = flow_up_unqueued;
                        unregister_code(flow_config[i][1]);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    return pass;
}

void change_pressed_status(uint16_t keycode, bool pressed) {
    for (int i = 0; i < FLOW_COUNT; i++) {
        if (flow_config[i][0] == keycode) {
            flow_pressed[i][0] = pressed;
        }
    }
}

bool update_flow_layers(
    uint16_t keycode,
    bool pressed,
    keypos_t key_position
) {
    uint8_t key_layer = read_source_layers_cache(key_position);
    bool pass = true;

    for (int i = 0; i < FLOW_LAYERS_COUNT; i++) {
        uint16_t trigger = flow_layers_config[i][0];
        uint16_t layer = flow_layers_config[i][1];

        if (keycode == trigger) {
            if (pressed) {
                // Trigger keydown
                if (flow_layers_state[i] == flow_up_unqueued) {
                    layer_on(layer);
                    change_pressed_status(trigger, true);
                }
                flow_layer_timeout_wait_timers_value[i] = timer_read();
                flow_layers_state[i] = flow_down_unused;
                pass = false;
            } else {
                // Trigger keyup
                switch (flow_layers_state[i]) {
                case flow_down_unused:
                    if (timer_elapsed(flow_layer_timeout_wait_timers_value[i]) > g_flow_oneshot_wait_term) {
                        flow_layers_state[i] = flow_up_unqueued;
                        layer_off(layer);
                        change_pressed_status(trigger, false);
                        pass = false;
                    } else {
                        // If we didn't use the layer while trigger was held, queue it.
                        flow_layers_state[i] = flow_up_queued;
                        flow_layer_timeout_timers_active[i] = true;
                        flow_layer_timeout_timers_value[i] = timer_read();
                        pass = false;
                        change_pressed_status(trigger, true);
                    }
                    break;
                case flow_down_used:
                    // If we did use the layer while trigger was held, turn off it.
                    flow_layers_state[i] = flow_up_unqueued;
                    layer_off(layer);
                    change_pressed_status(trigger, false);
                    pass = false;
                    break;
                default:
                    break;
                }
            }
        } else {
            if (pressed) {
                if (key_layer == layer) {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (flow_layers_state[i]) {
                    case flow_down_unused:
                        flow_layers_state[i] = flow_down_used;
                        break;
                    case flow_up_queued:
                        flow_layers_state[i] = flow_up_queued_used;
                        flow_layer_timeout_timers_active[i] = false;
                        break;
                   case flow_up_queued_used:
                        flow_layers_state[i] = flow_up_unqueued;
                        layer_off(layer);
                        change_pressed_status(trigger, false);
                        pass = false;
                        break;
                    default:
                        break;
                    }
                }
            } else {
                // Ignore key ups from other layers
                if (key_layer == layer) {
                    // On non-ignored keyup, consider the oneshot used.
                    switch (flow_layers_state[i]) {
                    case flow_up_queued:
                        flow_layers_state[i] = flow_up_unqueued;
                        layer_off(layer);
                        change_pressed_status(trigger, false);
                        break;
                    case flow_up_queued_used:
                        flow_layers_state[i] = flow_up_unqueued;
                        layer_off(layer);
                        change_pressed_status(trigger, false);
                        break;
                    default:
                        break;
                    }
                }
            }
        }
    }

    return pass;
}

bool update_flow(
    uint16_t keycode,
    bool pressed,
    keypos_t key_position
) {
    bool pass = update_flow_mods(keycode, pressed);
    pass = update_flow_layers(keycode, pressed, key_position) & pass;
    return pass;
}

void flow_matrix_scan(void) {
    for (int i = 0; i < FLOW_COUNT; i++) {
        if (flow_timeout_timers_active[i]
                && timer_elapsed(flow_timeout_timers_value[i]) > g_flow_oneshot_term) {
            flow_timeout_timers_active[i] = false;
            flow_state[i] = flow_up_unqueued;
            unregister_code(flow_config[i][1]);
        }
    }

    for (int i = 0; i < FLOW_LAYERS_COUNT; i++) {
        if (flow_layer_timeout_timers_active[i]
                && timer_elapsed(flow_layer_timeout_timers_value[i]) > g_flow_oneshot_term) {
            flow_layer_timeout_timers_active[i] = false;
            flow_layers_state[i] = flow_up_unqueued;
            layer_off(flow_layers_config[i][1]);
            change_pressed_status(flow_layers_config[i][0], false);
        }
    }
}
