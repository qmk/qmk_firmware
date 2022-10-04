/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#include "rev_b.h"



void keyboard_pre_init_kb(void) {
    setPinOutput(CAPS_PIN);
    setPinOutput(SCROLL_PIN);
    setPinOutput(NUM_PIN);
    setPinOutput(LAYER_1);
    setPinOutput(LAYER_2);
    setPinOutput(LAYER_3);
    setPinOutput(LAYER_4);
    setPinOutput(LAYER_5);
    keyboard_pre_init_user();
}

/* Set indicator leds to indicate lock states */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res && LOCK_LIGHTS) {
        writePin(NUM_PIN, led_state.num_lock);
        writePin(CAPS_PIN, led_state.caps_lock);
        writePin(SCROLL_PIN, led_state.scroll_lock);
    }
    return true;
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
            writePin(LAYER_1, 1);
            writePin(LAYER_2, 0);
            writePin(LAYER_3, 0);
            writePin(LAYER_4, 0);
            writePin(LAYER_5, 0);
            break;
        case 1 :
            writePin(LAYER_1, 0);
            writePin(LAYER_2, 1);
            writePin(LAYER_3, 0);
            writePin(LAYER_4, 0);
            writePin(LAYER_5, 0);
            break;
        case 2 :
            writePin(LAYER_1, 0);
            writePin(LAYER_2, 0);
            writePin(LAYER_3, 1);
            writePin(LAYER_4, 0);
            writePin(LAYER_5, 0);
            break;
        case 3 :
            writePin(LAYER_1, 0);
            writePin(LAYER_2, 0);
            writePin(LAYER_3, 0);
            writePin(LAYER_4, 1);
            writePin(LAYER_5, 0);
            break;
        case 4 :
            writePin(LAYER_1, 0);
            writePin(LAYER_2, 0);
            writePin(LAYER_3, 0);
            writePin(LAYER_4, 0);
            writePin(LAYER_5, 1);
            break;
        default :
            writePin(LAYER_1, 0);
            writePin(LAYER_2, 0);
            writePin(LAYER_3, 0);
            writePin(LAYER_4, 0);
            writePin(LAYER_5, 0);
    }
}
