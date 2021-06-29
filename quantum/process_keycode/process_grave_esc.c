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
#include "process_grave_esc.h"
#include "qmk_settings.h"

/* true if the last press of GRAVE_ESC was shifted (i.e. GUI or SHIFT were pressed), false otherwise.
 * Used to ensure that the correct keycode is released if the key is released.
 */
static bool grave_esc_was_shifted = false;

bool process_grave_esc(uint16_t keycode, keyrecord_t *record) {
    if (keycode == GRAVE_ESC) {
        const uint8_t mods    = get_mods();
        uint8_t       shifted = mods & MOD_MASK_SG;

if (QS_grave_esc_alt_override) {
        // if ALT is pressed, ESC is always sent
        // this is handy for the cmd+opt+esc shortcut on macOS, among other things.
        if (mods & MOD_MASK_ALT) {
            shifted = 0;
        }
}

if (QS_grave_esc_ctrl_override) {
        // if CTRL is pressed, ESC is always sent
        // this is handy for the ctrl+shift+esc shortcut on windows, among other things.
        if (mods & MOD_MASK_CTRL) {
            shifted = 0;
        }
}

if (QS_grave_esc_gui_override) {
        // if GUI is pressed, ESC is always sent
        if (mods & MOD_MASK_GUI) {
            shifted = 0;
        }
}

if (QS_grave_esc_shift_override) {
        // if SHIFT is pressed, ESC is always sent
        if (mods & MOD_MASK_SHIFT) {
            shifted = 0;
        }
}

        if (record->event.pressed) {
            grave_esc_was_shifted = shifted;
            add_key(shifted ? KC_GRAVE : KC_ESCAPE);
        } else {
            del_key(grave_esc_was_shifted ? KC_GRAVE : KC_ESCAPE);
        }

        send_keyboard_report();
        return false;
    }

    // Not a grave keycode so continue processing
    return true;
}
