/*
 * Copyright 2023 Raster Software Vigo
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


const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, 85,255,192} // not-so-bright HSV_GREEN for CAPS LOCK
);
const rgblight_segment_t PROGMEM my_scroll_lock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_RED} // HSV_RED for SCROLL LOCK
);
const rgblight_segment_t PROGMEM my_fn_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 3, HSV_ORANGE} // HSV_ORANGE for Fn key pressed
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    my_capslock_layer,
    my_scroll_lock_layer,
    my_fn_layer
);

void keyboard_post_init_kb(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    if (led_update_user(led_state)) {
            rgblight_set_layer_state(0, led_state.caps_lock); // all LEDs green in caps lock
            rgblight_set_layer_state(1, led_state.scroll_lock); // all LEDs red in scroll lock
    }
    return true;
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    rgblight_set_layer_state(2, layer_state_cmp(state, 1)); // all LEDs orange if FN is pressed
    return layer_state_set_user(state);
}
