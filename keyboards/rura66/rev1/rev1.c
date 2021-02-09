/* Copyright 2021 T.Shinohara
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

#include "rura66.h"

bool is_mac_mode(void) {
    return keymap_config.swap_lalt_lgui == false;
}

void set_mac_mode(bool macmode) {
    if (macmode) {
        /* The result is the same as pressing the AG_NORM(=MAGIC_UNSWAP_ALT_GUI) key. */
        /* https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L123-L124 */
        keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = false;
    } else {
        /* The result is the same as pressing the AG_SWAP(=MAGIC_SWAP_ALT_GUI) key. */
        /* https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L80-L81 */
        keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = true;
    }
}

