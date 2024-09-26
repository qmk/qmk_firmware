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
#include "./oled_routines.h"

void render_logo(void) {
    static const char PROGMEM logo[] = OLED_LOGO_CORNIA;
    oled_write_raw_P(logo, sizeof(logo));
}

void render_layer_status(void) {
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
}

void render_boot(bool bootloader) {
    oled_clear();
    oled_set_cursor(0, 2);
    if (bootloader) {
        oled_write_P(PSTR("FLASH"), false);
    } else {
        oled_write_P(PSTR("RESET"), false);
    }
    oled_render_dirty(true);
}
