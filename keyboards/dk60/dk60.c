/*
Copyright 2017 Damien Broqua <contact@darkou.fr>

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

#include "dk60.h"

extern inline void dk60_caps_led_on(void);
extern inline void dk60_esc_led_on(void);

extern inline void dk60_caps_led_off(void);
extern inline void dk60_esc_led_off(void);

extern inline void dk60_led_all_on(void);
extern inline void dk60_led_all_off(void);

void dk60_blink_all_leds(void) {
    dk60_led_all_off();
    dk60_led_all_on();
    wait_ms(500);
    dk60_led_all_off();
}

void matrix_init_kb(void) {
    dk60_blink_all_leds();

    matrix_init_user();
}

void led_init_ports(void) {
    setPinOutput(E6);
    setPinOutput(F0);
}

void led_update_ports(led_t led_state) {
    if (led_state.caps_lock) {
        dk60_caps_led_on();
    } else {
        dk60_caps_led_off();
    }
}
