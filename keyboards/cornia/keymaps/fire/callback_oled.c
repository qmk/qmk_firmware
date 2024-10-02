/* Copyright 2024 Vaarai
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

#include "./keymap.h"
#include "./cornia.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}

bool oled_task_user(void) {
    /* Print cornia logo */
    cornia_render_logo();

    /* Print layer status */
    oled_set_cursor(0, 7);
    switch (get_highest_layer(layer_state)) {
        case _ALPHA:
            oled_write_ln("ALPHA", 0);
            break;
        case _NAV:
            oled_write_ln("NAV", 0);
            break;
        case _NUM:
            oled_write_ln("NUM", 0);
            break;
        case _ADJUST:
            oled_write_ln("ADJUS", 0);
            break;
        case _G0:
            oled_write_ln("GAME0", 0);
            break;
        case _G1:
            oled_write_ln("GAME1", 0);
            break;
    }
    return false;
}
