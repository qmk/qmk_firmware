/* Copyright 2020 Purdea Andrei
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

#include "overnumpad_1xb.h"

void keyboard_post_init_kb(void)
{
    // Led pins:
    // C12 is the left-most led, normally Num Lock, but on Spacesaver M it's Caps Lock. Configured in config.h
    setPinOutput(C11); // middle led, always off on Spacesaver M
    writePin(C11, 0);
    setPinOutput(C10); // right-most led, normally Scroll Lock, but on Spacesaver M indicates function layer

    //debug_enable=true;
    //debug_matrix=true;
}


layer_state_t layer_state_set_kb(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case 0:
            writePin(C10, 0);
            break;
        default:
            writePin(C10, 1);
            break;
    }
     return layer_state_set_user(state);
}
