/*
Copyright 2022 Stefan Sundin "4pplet" <mail@4pplet.com>

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
#include "rev_a.h"

void board_init(void) {
    setPinInputHigh(NEXT_LED_L);
    setPinInputHigh(NEXT_LED_R);
}

/* Set indicator leds to indicate lock states */
bool led_update_kb(led_t led_state) {
    bool res = led_update_user(led_state);
    if(res) {
        if(led_state.caps_lock){
            setPinOutput(NEXT_LED_L);
            setPinOutput(NEXT_LED_R);
            writePin(NEXT_LED_L, 0);
            writePin(NEXT_LED_R, 0);
        }
        else
            setPinInputHigh(NEXT_LED_L);
            setPinInputHigh(NEXT_LED_R);
    }
    return res;
}
