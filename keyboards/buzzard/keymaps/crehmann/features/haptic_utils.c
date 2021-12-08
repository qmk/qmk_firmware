/* Copyright 2021 Christoph Rehmann (crehmann)
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

#include "haptic_utils.h"

#ifdef HAPTIC_ENABLE
#include "drivers/haptic/DRV2605L.h"
#endif


#ifdef HAPTIC_ENABLE
bool get_haptic_enabled_key(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BTN1 ... KC_BTN5:
            return true;
            break;
    }

    return false;
}
#endif

void process_layer_pulse(layer_state_t state) {
#ifdef HAPTIC_ENABLE
    switch(biton32(state)) {
    case 1:
        DRV_pulse(soft_bump);
        break;
    case 2:
        DRV_pulse(sh_dblsharp_tick);
        break;
    case 3:
        DRV_pulse(lg_dblclick_str);
        break;
    case 4:
        DRV_pulse(soft_bump);
        break;
    case 5:
        DRV_pulse(pulsing_sharp);
        break;
    }
#endif
}

