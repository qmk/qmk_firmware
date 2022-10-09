/* Copyright 2020 Stephen J. Bush @muppetjones
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

#include QMK_KEYBOARD_H
#include "muppetjones.h"
#include "tapmods.h"
#include "features/casemodes.h"

/* Placeholder function
 * If defined in a keymap.c, this will be ignored.
 */
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) { return true; }

/* Handle keypresses
 */
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_case_modes(keycode, record)) {
        return false;
    }
    // Regular user keycode case statement
    switch (keycode) {
        case CLMK_DH:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_CLMK_DH);
            }
            return false;
            break;
        case QWERTY:
            if (record->event.pressed) {
                // print("mode just switched to qwerty and this is a huge string\n");
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
            break;
        case CAPSWRD:
            if (record->event.pressed) {
                toggle_caps_word();
            }
            return false;
        default:
            break;
    }
    return process_record_keymap(keycode, record);
}
