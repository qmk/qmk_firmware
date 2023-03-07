/* Copyright 2023 Christoph Jabs (BifbofII)
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

#include "callbacks.h"

#include "bifbofii.h"

__attribute__((weak)) void keyboard_post_init_keymap(void) {}
void                       keyboard_post_init_user(void) {
#ifdef RGBLIGHT_ENABLE
    keyboard_post_init_rgb_light();
#endif
    keyboard_post_init_keymap();
}

__attribute__((weak)) layer_state_t layer_state_set_keymap(layer_state_t state) {
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
#ifdef RGBLIGHT_ENABLE
    state = layer_state_set_rgb_light(state);
#endif
    return layer_state_set_keymap(state);
}

__attribute__((weak)) bool led_update_keymap(led_t led_state) {
    return true;
}
bool led_update_user(led_t led_state) {
    bool ret = true;
#ifdef RGBLIGHT_ENABLE
    ret &= led_update_rgb_light(led_state);
#endif
    return ret;
}

__attribute__((weak)) bool oled_task_keymap(void) {
    return false;
}
bool oled_task_user(void) {
    return oled_task_keymap();
}

__attribute__((weak)) void housekeeping_task_keymap(void) {}
void                       housekeeping_task_user(void) {
    housekeeping_task_keymap();
}
