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

#include "quantum.h"

//Initialize B12 for in-switch caps lock
void keyboard_pre_init_kb(void){
    gpio_set_pin_output(B12);
    keyboard_pre_init_user();
}

//Initialize all RGB indicators to 'off'
__attribute__((weak))
void keyboard_post_init_user(void) {
    rgblight_setrgb_at(0, 0, 0, 0); // [..., 0] = top LED
    rgblight_setrgb_at(0, 0, 0, 1); // [..., 1] = middle LED
    rgblight_setrgb_at(0, 0, 0, 2); // [..., 2] = bottom LED
}

//Indicator light function
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
 //       gpio_write_pin(B12, !led_state.caps_lock);  //Un-comment this line to enable in-switch capslock indicator
    if (led_state.caps_lock) {
        rgblight_setrgb_at(0, 255, 0, 0); //green
    } else {
        rgblight_setrgb_at(0, 0, 0, 0);
    }
    if (led_state.num_lock) {
        rgblight_setrgb_at(0, 0, 255, 1); //blue
    } else {
        rgblight_setrgb_at(0, 0, 0, 1);
    }
   if (led_state.scroll_lock) {          
        rgblight_setrgb_at(255, 0, 0, 2); //red
    } else {
        rgblight_setrgb_at(0, 0, 0, 2);
    }
}
    return res;
}

//Below is an exmaple of layer indication using one of the RGB indicatiors. As configured, uses the bottom indicator (2) to light up red when layer 1 is in use. 
/*
layer_state_t layer_state_set_kb(layer_state_t state) {
    if (get_highest_layer(state) == 1) {
        rgblight_setrgb_at(255, 0, 0, 2);
    } else {
        rgblight_setrgb_at(0, 0, 0, 2);
    }
    return state;
}
*/
