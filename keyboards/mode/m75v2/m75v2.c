/* Copyright 2025 Gondolindrim
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

void keyboard_post_init_kb(void) {
    led_update_kb(host_keyboard_led_state());
    rgblight_set_effect_range(0, 36);
    keyboard_post_init_user();
}

bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if (res) {
        hsv_t current_color = rgblight_get_hsv();
        led_state.caps_lock ? rgblight_sethsv_at(current_color.h, current_color.s, current_color.v, 37) : rgblight_sethsv_at(HSV_OFF, 37); 
        led_state.caps_lock ? rgblight_sethsv_at(current_color.h, current_color.s, current_color.v, 38) : rgblight_sethsv_at(HSV_OFF, 38); 
    }   
    return res;
}
