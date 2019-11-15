/*
Copyright 2017 Luiz Ribeiro <luizribeiro@gmail.com>

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

#include "jj50.h"

#include "backlight.h"
#include "backlight_custom.h"

void matrix_init_kb(void) { matrix_init_user(); }

__attribute__ ((weak))
void matrix_init_user(void) {}

void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__ ((weak))
void matrix_scan_user(void) {}

#ifdef BACKLIGHT_ENABLE
void backlight_init_ports(void) {
    b_led_init_ports();
}

void backlight_task(void) {
    b_led_task();
}

void backlight_set(uint8_t level) {
    b_led_set(level);
}
#endif
