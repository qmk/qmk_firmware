/*
Copyright 2021 Swiftrax <swiftrax@gmail.com>

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
#include "bumblebee.h"

// Initialize all RGB indicators to 'off'
void keyboard_post_init_kb(void) {
    rgblight_setrgb_at(0, 0, 0, 0); // [..., 0] = top LED
    rgblight_setrgb_at(0, 0, 0, 1); // [..., 1] = middle LED
    rgblight_setrgb_at(0, 0, 0, 2); // [..., 2] = bottom LED
    keyboard_post_init_user();
}

// RGB Layer Indicators
layer_state_t layer_state_set_kb(layer_state_t state) {
    if (get_highest_layer(state) == 0) {
        rgblight_setrgb_at(255, 0, 0, 0); //red
    } else {
        rgblight_setrgb_at(0, 0, 0, 0);
    }
    if (get_highest_layer(state) == 1){
        rgblight_setrgb_at(0, 0, 255, 1); //green
    } else{
        rgblight_setrgb_at(0, 0, 0, 1);
    }
    if (get_highest_layer(state) == 2){
        rgblight_setrgb_at(0, 255, 0, 2); //blue
    } else{
        rgblight_setrgb_at(0, 0, 0, 2);
    }
    return layer_state_set_user(state);
}
