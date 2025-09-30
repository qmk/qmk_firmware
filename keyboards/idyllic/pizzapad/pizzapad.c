/*
Copyright 2025 Zykrah
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

#define ENCODER_PIN_C GP27

void keyboard_pre_init_kb(void) {
    // Set encoder pin C low
    gpio_set_pin_output_push_pull(ENCODER_PIN_C);
    gpio_write_pin_low(ENCODER_PIN_C);

    keyboard_pre_init_user();
}
