/* Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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

#include "fallacy.h"
#include "indicators.h"

void matrix_init_kb(void) {
    init_fallacy_leds();
    matrix_init_user();
}

void matrix_scan_kb(void) {
    update_fallacy_leds();
    matrix_scan_user();
}
 
/* update LED driver with usb led_state
 */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        set_fallacy_led(2, led_state.caps_lock);    /* caps */
        set_fallacy_led(1, led_state.num_lock);     /* num lock */
        set_fallacy_led(0, led_state.scroll_lock);  /* scroll lock */
    }
    return res;
}
