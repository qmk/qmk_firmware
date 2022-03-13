/* Copyright 2018 MakotoKurauchi
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

// Each keymap.c should use is_keyboard_master() instead of 'is_master'.
// But keep 'is_master' for a while for backwards compatibility
//  for the old keymap.c.
uint8_t is_master = false;

#ifdef SSD1306OLED
#include "ssd1306.h"

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	return process_record_gfx(keycode,record) && process_record_user(keycode, record);
}
#endif

bool is_mac_mode(void) {
    // This is the opposite of the QMK standard, but we'll leave it for backwards compatibility.
    return keymap_config.swap_lalt_lgui == false;
}

void set_mac_mode_kb(bool macmode) {
    /* The result is the same as pressing the AG_NORM(=MAGIC_UNSWAP_ALT_GUI)/AG_SWAP(=MAGIC_SWAP_ALT_GUI) keys.
     * see
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L123-L124
     *   https://github.com/qmk/qmk_firmware/blob/fb4a6ad30ea7a648acd59793ed4a30c3a8d8dc32/quantum/process_keycode/process_magic.c#L80-L81
     */
    keymap_config.swap_lalt_lgui = keymap_config.swap_ralt_rgui = !macmode;
    eeconfig_update_keymap(keymap_config.raw);
}

void matrix_init_kb(void) {
    // Each keymap.c should use is_keyboard_master() instead of is_master.
    // But keep is_master for a while for backwards compatibility
    //  for the old keymap.c.
    is_master = is_keyboard_master();

    matrix_init_user();
};

void keyboard_post_init_kb(void) {
#if defined(DEBUG_MATRIX_SCAN_RATE)
    debug_enable = true;
#endif
    keyboard_post_init_user();
}

#if defined(SPLIT_KEYBOARD) && defined(SSD1306OLED)
void matrix_slave_scan_user(void) {
    matrix_scan_user();
}
#endif
