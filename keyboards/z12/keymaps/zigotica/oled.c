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
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_P(PSTR("Volume         Scroll"), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("             z12 v1.1"), false);
            break;
        case _FIGMA:
            oled_write_P(PSTR("Tabs             Zoom"), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("ZoomFit  Grids   Full"), false);
            oled_write_P(PSTR("Zoom100  Next   Color"), false);
            break;
        case _BROWSER:
            oled_write_P(PSTR("Tabs           Scroll"), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("Search   Fav  DevTool"), false);
            oled_write_P(PSTR("Zoom100  Mute    Read"), false);
            break;
        case _VIM:
            oled_write_P(PSTR("Buffer         Scroll"), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("Find-F  Format    New"), false);
            oled_write_P(PSTR("Rename  Go-Def Action"), false);
            break;
        default:
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("                     "), false);
            oled_write_P(PSTR("                     "), false);
    }
}

bool oled_task_user(void) {
    render_status();
    return false;
}
