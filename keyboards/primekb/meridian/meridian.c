/*
Copyright 2020 Holten Campbell
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

#include "meridian.h"

//Initialize B12 for in-switch caps lock
void keyboard_pre_init_kb(void){
    setPinOutput(B12);
    keyboard_pre_init_user();
}

//Refernce the following QMK documentation for implementing Lighting Layers and layer change indication:
// https://docs.qmk.fm/#/feature_rgblight?id=lighting-layers

// Light the top LED when caps lock is active.
const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}       // Light 1 LEDs, starting with LED 0
);
// Light the middle LED when layer 1 is active. 
const rgblight_segment_t PROGMEM my_layer1[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED}       // Light 1 LEDs, starting with LED 1
);
// Light the bottom LED when layer 2 active. 
const rgblight_segment_t PROGMEM my_layer2[] = RGBLIGHT_LAYER_SEGMENTS(
    {2, 1, HSV_GREEN}       // Light 1 LEDs, starting with LED 2
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_layer1,
    my_layer2
);

__attribute__((weak))
void keyboard_post_init_user(void) {
    rgblight_layers = my_rgb_layers; //Enable the LED layers
    rgblight_disable();    //set RGB lights to off by default. 
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        writePin(B12, !led_state.caps_lock);
    
    rgblight_set_layer_state(0, led_state.caps_lock);
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(1, layer_state_cmp(state, 1));
    rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    return state;
}