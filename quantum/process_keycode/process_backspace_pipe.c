/* Copyright (c) 2022 Christiano Haesbaert <haesbaert@haesbaert.org>
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
#include "process_backspace_pipe.h"

/*
 * true if the last press was modded (i.e. GUI or SHIFT were pressed), false
 * otherwise.  Used to ensure that the correct keycode is released if the key is
 * released.
 */
static bool backspace_pipe_was_modded = false;

bool process_backspace_pipe(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_BACKSPACE_PIPE) {
        const uint8_t mods   = get_mods();
        uint8_t       modded = mods & MOD_MASK_SG;

        if (record->event.pressed) {
            backspace_pipe_was_modded = modded;
            add_key(modded ? KC_BSLS : KC_BSPC);
        } else {
            del_key(backspace_pipe_was_modded ? KC_BSLS : KC_BSPC);
        }

        send_keyboard_report();
        return false;
    }

    // Not a backspace keycode so continue processing
    return true;
}
