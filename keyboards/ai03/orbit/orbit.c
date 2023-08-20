/* Copyright 2018 Ryota Goto
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
#include "orbit.h"
#include "split_util.h"

void led_init_ports(void) {
    // Initialize indicator LEDs to output
    if (isLeftHand) {
        setPinOutput(C6);
        setPinOutput(B6);
        setPinOutput(B5);
    } else {
        setPinOutput(F6);
        setPinOutput(F7);
        setPinOutput(C7);
    }

    set_layer_indicators(0);
}

// Call led_toggle to set LEDs easily
// LED IDs:
//
// (LEFT) 0 1 2   |   3 4 5 (RIGHT)
void led_toggle(uint8_t id, bool on) {
    if (isLeftHand) {
        switch (id) {
            case 0:
                // Left hand C6
                writePin(C6, on);
                break;
            case 1:
                // Left hand B6
                writePin(B6, on);
                break;
            case 2:
                // Left hand B5
                writePin(B5, on);
                break;
            default:
                break;
        }
    } else {
        switch (id) {
            case 3:
                // Right hand F6
                writePin(F6, on);
                break;
            case 4:
                // Right hand F7
                writePin(F7, on);
                break;
            case 5:
                // Right hand C7
                writePin(C7, on);
                break;
            default:
                break;
        }
    }
}

// Set all LEDs at once using an array of 6 booleans
// LED IDs:
//
// (LEFT) 0 1 2   |   3 4 5 (RIGHT)
//
// Ex. set_all_leds({ false, false, false, true, true, true }) would turn off left hand, turn on right hand

void set_all_leds(bool leds[6]) {
    for (int i = 0; i < 6; i++) {
        led_toggle(i, leds[i]);
    }
}

void set_layer_indicators(uint8_t layer) {
    switch (layer) {
        case 0:
            led_toggle(0, true);
            led_toggle(1, false);
            led_toggle(2, false);
            break;
        case 1:
            led_toggle(0, true);
            led_toggle(1, true);
            led_toggle(2, false);
            break;
        case 2:
            led_toggle(0, true);
            led_toggle(1, true);
            led_toggle(2, true);
            break;
        case 3:
            led_toggle(0, false);
            led_toggle(1, true);
            led_toggle(2, true);
            break;
        case 4:
            led_toggle(0, false);
            led_toggle(1, false);
            led_toggle(2, true);
            break;
        default:
            led_toggle(0, true);
            led_toggle(1, false);
            led_toggle(2, true);
            break;
    }
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        led_toggle(3, led_state.num_lock);
        led_toggle(4, led_state.caps_lock);
        led_toggle(5, led_state.scroll_lock);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    set_layer_indicators(get_highest_layer(state));

    return layer_state_set_user(state);
}
