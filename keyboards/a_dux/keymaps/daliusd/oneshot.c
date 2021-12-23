/* Copyright 2021 @daliusd
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
#include "print.h"
#include "oneshot.h"

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                case os_up_queued:
                    *state = os_up_queued_used;
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool update_oneshot_layer(
    oneshot_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            *state = os_down_unused;
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the layer while trigger was held, queue it.
                *state = os_up_queued;
                return false;
            case os_down_used:
                // If we did use the layer while trigger was held, turn off it.
                *state = os_up_unqueued;
                layer_off(layer);
                return false;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                *state = os_up_unqueued;
                layer_off(layer);
                return false;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    return true;
                case os_up_queued:
                    if (is_oneshot_mod_key(keycode)) {
                        *state = os_up_unqueued;
                        layer_off(layer);
                        return false;
                    } else {
                        *state = os_up_queued_used;
                    }
                    return true;
               case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return false;
                default:
                    break;
                }
            }
        } else {
            // Ignore key ups from other layers
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_up_queued:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return true;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    return true;
                default:
                    break;
                }
            }
        }
    }
    return true;
}
