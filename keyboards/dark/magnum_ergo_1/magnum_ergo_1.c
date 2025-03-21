/* Copyright 2023 Gondolindrim <gondolindrim@acheronproject.com>
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

void keyoard_post_init_kb(void) {
    gpio_set_pin_output(LED_CAPS_LOCK_PIN);
    gpio_set_pin_output(LED_INDICATOR_1);
    gpio_set_pin_output(LED_INDICATOR_2);
    gpio_set_pin_output(LED_INDICATOR_3);
    gpio_set_pin_output(LED_INDICATOR_4);
    gpio_set_pin_output(LED_INDICATOR_5);
#ifndef LED_CAPS_LOCK_PIN
    gpio_write_pin(LED_CAPS_LOCK_PIN, 0);
#endif

#ifndef LED_INDICATOR_1
    gpio_write_pin(LED_INDICATOR_1, 0);
#endif

#ifndef LED_INDICATOR_2
    gpio_write_pin(LED_INDICATOR_2, 0);
#endif

#ifndef LED_INDICATOR_3
    gpio_write_pin(LED_INDICATOR_3, 0);
#endif

#ifndef LED_INDICATOR_4
    gpio_write_pin(LED_INDICATOR_4, 0);
#endif

#ifndef LED_INDICATOR_5
    gpio_write_pin(LED_INDICATOR_5, 0);
#endif
    keyboard_post_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
        switch (get_highest_layer(state)) {
        case 1:
#ifdef LED_INDICATOR_4
            gpio_write_pin(LED_INDICATOR_4, 1);
#endif

#ifdef LED_INDICATOR_5
            gpio_write_pin(LED_INDICATOR_5, 1);
#endif
            break;
        case 2:
#ifdef LED_INDICATOR_1
            gpio_write_pin(LED_INDICATOR_1, 1);
#endif
#ifdef LED_INDICATOR_2
            gpio_write_pin(LED_INDICATOR_2, 1);
#endif
#ifdef LED_INDICATOR_3
            gpio_write_pin(LED_INDICATOR_3, 1);
#endif
            break;
        default:
#ifdef LED_INDICATOR_1
            gpio_write_pin(LED_INDICATOR_1, 0);
#endif
#ifdef LED_INDICATOR_2
            gpio_write_pin(LED_INDICATOR_2, 0);
#endif
#ifdef LED_INDICATOR_3
            gpio_write_pin(LED_INDICATOR_3, 0);
#endif
#ifdef LED_INDICATOR_4
            gpio_write_pin(LED_INDICATOR_4, 0);
#endif
#ifdef LED_INDICATOR_5
            gpio_write_pin(LED_INDICATOR_5, 0);
#endif
            break;
    }
    return layer_state_set_user(state);
}
