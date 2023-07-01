/* Copyright 2023 deddia permana (@depermana12)
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

bool oled_task_kb(void) {
    oled_write_P(PSTR("LAYER: "), false);
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_P(PSTR("0"), false);
            break;
        case 1:
            oled_write_P(PSTR("1"), false);
            break;
        case 2:
            oled_write_P(PSTR("2"), false);
            break;
        case 3:
            oled_write_P(PSTR("3"), false);
            break;
    }

    led_t led_state = host_keyboard_led_state();
    oled_set_cursor(0, 1);
    oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
    oled_set_cursor(0, 2);
    oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
    oled_set_cursor(0, 3);
    oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false);

    return false;
}
