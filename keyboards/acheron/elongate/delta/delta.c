/* Copyright 2021 Gondolindrim
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

#include "quantum.h"

// Inits all indicator LEDs as push-pull outputs
void led_init_ports(void) {
    palSetLineMode(LED1_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED2_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED3_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED4_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED5_PIN, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(LED6_PIN, PAL_MODE_OUTPUT_PUSHPULL);
}

// This function updates LEDs 1, 2 and 3 according to num, caps and scroll lock states
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(LED1_PIN, !led_state.num_lock);
        writePin(LED2_PIN, !led_state.caps_lock);
        writePin(LED3_PIN, !led_state.scroll_lock);
    }
    return res;
}

// Turns off all bottom LEDs
void turn_off_bottom_leds(void){
	writePin(LED4_PIN, 1);
	writePin(LED5_PIN, 1);
	writePin(LED6_PIN, 1);
}

/*
Here the bottom LEDs get updated. The idea being that LED4 is lit when the default layer is active, LED5 when layer 1 is active and LED6 when layer 2.
Before updating, however, all bottom LEDs are turned off.
*/
layer_state_t layer_state_set_kb(layer_state_t state) {
    turn_off_bottom_leds();
    switch (get_highest_layer(state)) {
// The base layer, or layer zero, will be handled by the default case.
    case 1:
	writePin(LED4_PIN, 1);
	writePin(LED5_PIN, 0);
	writePin(LED6_PIN, 1);
        break;
    case 2:
	writePin(LED4_PIN, 1);
	writePin(LED5_PIN, 1);
	writePin(LED6_PIN, 0);
        break;
    default:
	writePin(LED4_PIN, 0);
	writePin(LED5_PIN, 1);
	writePin(LED6_PIN, 1);
        break;
    }
  return state;
}

// Since the keyboard starts at layer 0, the init function starts LED4 as lit up.
void keyboard_post_init_kb(void){
	writePin(LED4_PIN, 0);
}
