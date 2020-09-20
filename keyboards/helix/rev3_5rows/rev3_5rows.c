/* Copyright 2020 yushakobo
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

#include "helix.h"

void dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
    case 0:
        if(active) { // Left no.1  Helix rev3 common
            keymap_config.swap_lalt_lgui = true;
        } else {
            keymap_config.swap_lalt_lgui = false;
        }
        break;
    default: // Left no.2 or Right no.1 or Right no.2 for user/keymap
        dip_switch_update_user(index, active);
        break;
    }
}
