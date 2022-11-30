/* Copyright 2022 Jason Devadoss (@jasonj2232)
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

#ifdef OLED_ENABLE
static void render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240,240,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,120, 20, 18, 18, 20,120,  0,  0,126, 10, 26, 58,106, 78,  0,  0,126, 66, 82, 82, 82,114,  0,  0,126, 66, 66, 66, 66,126,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255,255,  0,  0,252,252,140,140,140,140,140,140,140,140,140,140,140,140,  0,  0,252,252,128,128,128,128,128,128,128,128,128,128,128,252,252,  0,  0,255,255,255,  0,  0,  0,  0,  0,  0,255,255,153,153,255,255,  0,  0,255,255,195,195,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 62, 64, 48, 48, 64, 62,  0,  0,126, 66, 66, 66, 66,126,  0,  0,126, 10, 26, 58,106, 78,  0,  0,126, 24, 60,102, 66, 66,  0,  0, 36, 74, 74, 82, 82, 36,  0,  0,  0,255,255,255,  0,  0, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 49, 63, 63,  0,  0, 63, 63,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1, 63, 63,  0,  0,255,255,255,  0,  0,  0,  0,  0,  0,252,  8, 16,  8,252, 48, 72,132,  0,  0,120,132,132,120,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15, 15, 15,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}



bool oled_task_kb(void) {
        render_logo();
    return false;
}
#endif
