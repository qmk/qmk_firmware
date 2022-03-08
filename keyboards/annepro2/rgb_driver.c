/* Copyright 2022 Jose Pablo Ramirez <jp.ramangulo@gmail.com>
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

#include "rgb_matrix.h"
#include "ap2_led.h"

uint8_t led_pos[DRIVER_LED_TOTAL];

void init(void) {
    unsigned int i = 0;
    for (unsigned int y = 0; y < LED_MATRIX_ROWS; y++) {
        for (unsigned int x = 0; x < LED_MATRIX_COLS; x++) {
            if (g_led_config.matrix_co[y][x] != NO_LED) {
                led_pos[g_led_config.matrix_co[y][x]] = i;
            }
            i++;
        }
    }
}

void flush(void) {}

void set_color(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (r != ledMask[led_pos[index]].p.red   ||
        g != ledMask[led_pos[index]].p.green ||
        b != ledMask[led_pos[index]].p.blue)
        {
            ledMask[led_pos[index]] = (annepro2Led_t){
                .p.blue  = b,
                .p.red   = r,
                .p.green = g,
                .p.alpha = 0xff,
            };
            int row = led_pos[index] / LED_MATRIX_COLS;
            rgb_row_changed[row] = 1;
        }
}

void set_color_all(uint8_t r, uint8_t g, uint8_t b) {
    for (int i=0; i<DRIVER_LED_TOTAL; i++)
        set_color(i, r, g, b);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init          = init,
    .flush         = flush,
    .set_color     = set_color,
    .set_color_all = set_color_all,
};
