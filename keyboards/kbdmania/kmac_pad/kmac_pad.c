/*
Copyright 2021 talsu <talsu84@gmail.com>

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

#include "quantum.h"

void keyboard_pre_init_kb(void) {

    /* Set Backlight pin as output
     * FN Pin PB3
     * PAD Pin PB1
     */
    gpio_set_pin_output(B3);
    gpio_set_pin_output(B1);
    keyboard_pre_init_user();
}
