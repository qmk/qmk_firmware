/* Copyright 2021 JasonRen(biu)
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

#include "kb_press_graph.h"


const uint8_t kb_graph_start_line = 8;
//                                   0   1   2   3   4
const uint8_t kb_press_row_map[5] = {65, 68, 71, 74, 77};
//                                    0  1  2  3  4  5   6   7   8   9   10  11  12  13  14
const uint8_t kb_press_col_map[15] = {3, 6, 6, 9, 9, 12, 12, 15, 18, 18, 21, 21, 24, 27, 27};

void render_r65_kb(uint8_t col, uint8_t row, uint16_t keycode, bool on, uint16_t key_press_count) {
    if (key_press_count == 0) {
        oled_set_cursor(0, kb_graph_start_line);
        oled_write_raw(my_font_lib_etc_r65kb, 32);
        oled_set_cursor(0, kb_graph_start_line+1);
        oled_write_raw(my_font_lib_etc_r65kb+32, 32);
        oled_set_cursor(0,0);
        return;
    }
    if (col == 255 && row == 255) return;
    // skip the encoder map key
    if (col == 3 && row == 4) return;
    if (col == 4 && row == 4) return;
    // space keypress
    if (col == 5 && row == 4) {
        for (uint8_t i = kb_press_col_map[5-2];i<=kb_press_col_map[5+2]+1; ++i) {
            oled_write_pixel(i, kb_press_row_map[4], on);
            oled_write_pixel(i, kb_press_row_map[4]+1, on);
        }
        return;
    }
    uint8_t y_oled = kb_press_row_map[row];
    uint8_t x_oled = kb_press_col_map[col];
    oled_write_pixel(x_oled, y_oled, on);
    oled_write_pixel(x_oled, y_oled+1, on);
    oled_write_pixel(x_oled+1, y_oled, on);
    oled_write_pixel(x_oled+1, y_oled+1, on);
}
