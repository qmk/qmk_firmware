/*
Copyright 2021 Stefan Sundin "4pplet" <4pplet@protonmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rev_a.h"

void board_init(void) {
    gpio_set_pin_input_high(CAPS_PIN);
    gpio_set_pin_input_high(SCROLL_PIN);
    gpio_set_pin_input_high(NUM_PIN);
}

/* Set indicator leds to indicate lock states */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res && LOCK_LIGHTS) {
        if(led_state.caps_lock){
            gpio_set_pin_output(CAPS_PIN);
            gpio_write_pin(CAPS_PIN, 0);
        }
        else
            gpio_set_pin_input_high(CAPS_PIN);
        if(led_state.scroll_lock){
            gpio_set_pin_output(SCROLL_PIN);
            gpio_write_pin(SCROLL_PIN, 0);
        }
        else
            gpio_set_pin_input_high(SCROLL_PIN);
        if(led_state.num_lock){
            gpio_set_pin_output(NUM_PIN);
            gpio_write_pin(NUM_PIN, 0);
        }
        else
            gpio_set_pin_input_high(NUM_PIN);
    }
    return res;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    if(DISPLAY_LAYERS){
        setLayerLed(state);
    }
    return state;
}
/* Set indicator leds to indicate which layer is active */
void setLayerLed(layer_state_t state){
    switch(get_highest_layer(state)){
        case 0 :
            gpio_set_pin_output(LAYER_1);
            gpio_write_pin(LAYER_1, 0);
            gpio_set_pin_input_high(LAYER_2);
            gpio_set_pin_input_high(LAYER_3);
            gpio_set_pin_input_high(LAYER_4);
            gpio_set_pin_input_high(LAYER_5);
            break;
        case 1 :
            gpio_set_pin_output(LAYER_2);
            gpio_write_pin(LAYER_2, 0);
            gpio_set_pin_input_high(LAYER_1);
            gpio_set_pin_input_high(LAYER_3);
            gpio_set_pin_input_high(LAYER_4);
            gpio_set_pin_input_high(LAYER_5);
            break;
        case 2 :
            gpio_set_pin_output(LAYER_3);
            gpio_write_pin(LAYER_3, 0);
            gpio_set_pin_input_high(LAYER_1);
            gpio_set_pin_input_high(LAYER_2);
            gpio_set_pin_input_high(LAYER_4);
            gpio_set_pin_input_high(LAYER_5);
            break;
        case 3 :
            gpio_write_pin(LAYER_4, 0);
            gpio_set_pin_input_high(LAYER_5);
            gpio_set_pin_input_high(LAYER_1);
            gpio_set_pin_input_high(LAYER_2);
            gpio_set_pin_input_high(LAYER_3);
            gpio_set_pin_output(LAYER_4);
            break;
        case 4 :
            gpio_set_pin_output(LAYER_5);
            gpio_write_pin(LAYER_5, 0);
            gpio_set_pin_input_high(LAYER_1);
            gpio_set_pin_input_high(LAYER_2);
            gpio_set_pin_input_high(LAYER_3);
            gpio_set_pin_input_high(LAYER_4);
            break;
        default :
            gpio_set_pin_input_high(LAYER_1);
            gpio_set_pin_input_high(LAYER_2);
            gpio_set_pin_input_high(LAYER_3);
            gpio_set_pin_input_high(LAYER_4);
            gpio_set_pin_input_high(LAYER_5);
    }
}
