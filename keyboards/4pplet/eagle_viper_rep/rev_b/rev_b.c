/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#include "rev_b.h"

void keyboard_pre_init_kb(void) {
    setPinOutput(LAYER_1);
    setPinOutput(LAYER_2);
    setPinOutput(LAYER_3);
    setPinOutput(LAYER_4);
    setPinOutput(LAYER_5);
    keyboard_pre_init_user();
}

layer_state_t layer_state_set_kb(layer_state_t state) {
    state = layer_state_set_user(state);
    setLayerLed(state);
    return state;
}
/* Set indicator leds to indicate which layer is active */
void setLayerLed(layer_state_t state){
    writePinLow(LAYER_1);
    writePinLow(LAYER_2);
    writePinLow(LAYER_3);
    writePinLow(LAYER_4);
    writePinLow(LAYER_5);
    switch (get_highest_layer(state)) {
        case 0:
            writePinHigh(LAYER_1);
            break;
        case 1:
            writePinHigh(LAYER_2);
            break;
        case 2:
            writePinHigh(LAYER_3);
            break;
        case 3:
            writePinHigh(LAYER_4);
            break;
        case 4:
            writePinHigh(LAYER_5);
            break;
    }
}

