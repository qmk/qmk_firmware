/* Copyright 2020
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
#include "process_grave.h"

bool process_grave(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case GRAVE_ESC: {
            /* true if the last press of GRAVE_ESC was shifted (i.e. GUI or SHIFT were pressed), false otherwise.
             * Used to ensure that the correct keycode is released if the key is released.
             */
            static bool grave_esc_was_shifted = false;

            uint8_t shifted = get_mods() & ((MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT) | MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI)));

#ifdef GRAVE_ESC_ALT_OVERRIDE
            // if ALT is pressed, ESC is always sent
            // this is handy for the cmd+opt+esc shortcut on macOS, among other things.
            if (get_mods() & (MOD_BIT(KC_LALT) | MOD_BIT(KC_RALT))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_CTRL_OVERRIDE
            // if CTRL is pressed, ESC is always sent
            // this is handy for the ctrl+shift+esc shortcut on windows, among other things.
            if (get_mods() & (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_GUI_OVERRIDE
            // if GUI is pressed, ESC is always sent
            if (get_mods() & (MOD_BIT(KC_LGUI) | MOD_BIT(KC_RGUI))) {
                shifted = 0;
            }
#endif

#ifdef GRAVE_ESC_SHIFT_OVERRIDE
            // if SHIFT is pressed, ESC is always sent
            if (get_mods() & (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT))) {
                shifted = 0;
            }
#endif

            if (record->event.pressed) {
                grave_esc_was_shifted = shifted;
                add_key(shifted ? KC_GRAVE : KC_ESCAPE);
            } else {
                del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
            }

            send_keyboard_report();
            return false;
        }
    }

    // Not a grave keycode so continue processing
    return true;
}
