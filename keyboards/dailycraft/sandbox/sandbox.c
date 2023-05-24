/* Copyright 2021 yfuku
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

#include "sandbox.h"

#ifdef OLED_ENABLE
bool oled_task_user(void) {
    if (!oled_task_user()) { return false; }
    switch (get_highest_layer(layer_state)) {
        case 0:
            oled_write_ln_P(PSTR("Layer: Default"), false);
            break;
        case 1:
            oled_write_ln_P(PSTR("Layer: 1"), false);
            break;
        case 2:
            oled_write_ln_P(PSTR("Layer: 2"), false);
            break;
        case 3:
            oled_write_ln_P(PSTR("Layer: 3"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Layer: Undefined"), false);
    }

        return true;
}

oled_rotation_t oled_init_kb(oled_rotation_t rotation) {
    return OLED_ROTATION_180;
}
#endif
