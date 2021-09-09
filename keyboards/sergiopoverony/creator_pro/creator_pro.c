/* Copyright 2020-2021 SergioPoverony
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
 
#include "creator_pro.h"

void matrix_init_kb(void) {
    matrix_init_user();
/* led pins */
    setPinOutput(RED_LED);
    setPinOutput(BLUE_LED);
    setPinOutput(GREEN_LED);
}
void turn_off_leds(void) {
    writePinLow(RED_LED);
    writePinLow(BLUE_LED);
    writePinLow(GREEN_LED);
}
void turn_on_led(pin_t pin) {
    writePinHigh(pin);
}
