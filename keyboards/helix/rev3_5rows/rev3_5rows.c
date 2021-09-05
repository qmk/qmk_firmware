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

bool is_mac_mode(void) {
    return keymap_config.swap_lalt_lgui == false;
}

void set_mac_mode(bool macmode) {
    /* The result is the same as pressing the AG_NORM(=MAGIC_UNSWAP_ALT_GUI)/AG_SWAP(=MAGIC_SWAP_ALT_GUI) keys.
     * see
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L123-L124
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L80-L81
     */
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !macmode;
    eeconfig_update_keymap(keymap_config.raw);
}

#ifdef DIP_SWITCH_ENABLE
bool dip_switch_update_kb(uint8_t index, bool active) {
    switch (index) {
    case 0:
        if(active) { // Left no.1  Helix rev3 common
            set_mac_mode(false);
        } else {
            set_mac_mode(true);
        }
        break;
    default: // Left no.2 or Right no.1 or Right no.2 for user/keymap
        dip_switch_update_user(index, active);
        break;
    }
    return true;
}
#endif
