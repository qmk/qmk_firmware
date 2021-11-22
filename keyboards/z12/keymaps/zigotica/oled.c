/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "zigotica.h"

static void render_status(void) {
    oled_write_P(PSTR("z12 v1.0\n"), false);
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state)) {
        case _VIM:
            oled_write_P(PSTR("VIM\n\nBUFFER       SCROLL"), false);
            break;
        case _FIGMA:
            oled_write_P(PSTR("FIGMA\n\nVOLUME         ZOOM"), false);
            break;
        case _BROWSER:
            oled_write_P(PSTR("BROWSER\n\nTABS         SCROLL"), false);
            break;
        case _TERMINAL:
            oled_write_P(PSTR("TERMINAL\n\nVOLUME       SCROLL"), false);
            break;
        default:
            oled_write_P(PSTR("Undef\n"), false);
    }
}

void oled_task_user(void) {
    render_status();
}

