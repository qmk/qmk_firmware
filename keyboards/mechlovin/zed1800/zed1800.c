/* Copyright 2022 Mechlovin' Studio
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

const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS({2, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_numlock_layer[] = RGBLIGHT_LAYER_SEGMENTS({0, 1, HSV_GREEN});
const rgblight_segment_t PROGMEM my_scroll_layer[] = RGBLIGHT_LAYER_SEGMENTS({1, 1, HSV_GREEN});

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM my_rgb_layers[] =
RGBLIGHT_LAYERS_LIST( 
            my_capslock_layer,
            my_numlock_layer,
            my_scroll_layer
        );

void keyboard_post_init_kb(void) {
    rgblight_layers = my_rgb_layers;

    keyboard_post_init_user();
}

// Activate rgb layer for caps when capslock is enabled
bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        rgblight_set_layer_state(0, led_state.caps_lock);
        rgblight_set_layer_state(1, led_state.num_lock);
        rgblight_set_layer_state(2, led_state.scroll_lock);
    }
    return true;
}