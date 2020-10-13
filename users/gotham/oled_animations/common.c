/* Copyright 2020 Gautham Yerroju <gautham.yerroju@gmail.com>
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

#include "common.h"

uint8_t rect_out_of_bounds(int16_t x, int16_t y, uint8_t width, uint8_t height, int8_t padding) {
    /* Return a bit mask representing the direction collission happened.
     * Direction positions are like vim arrow keys: <left><down><up><right>
     */
    uint8_t collision_map = 0x00;
    if (x < -padding) {
        collision_map |= COLLISION_MASK_LEFT;
    }
    if ((x + width) >= (OLED_DISPLAY_WIDTH + padding)) {
        collision_map |= COLLISION_MASK_RIGHT;
    }
    if (y < -padding) {
        collision_map |= COLLISION_MASK_UP;
    }
    if ((y + height) >= (OLED_DISPLAY_HEIGHT + padding)) {
        collision_map |= COLLISION_MASK_DOWN;
    }
    return collision_map;
}

bool point_out_of_bounds(int16_t x, int16_t y, int8_t padding) { return ((x < -padding) || (y < -padding) || (x > (OLED_DISPLAY_WIDTH + padding)) || (y > (OLED_DISPLAY_HEIGHT + padding))); }

static const uint8_t column_masks[8] = {1, 2, 4, 8, 16, 32, 64, 128};
/*
 * NOTE: This function is proof-of-concept for now, tearing occurs near
 * the bottom of the screen and there's possibility for optimization.
 */
void oled_write_bitmap(const uint8_t* data, int16_t x, int16_t y, uint8_t width, uint8_t height, bool erase) {
    if ((x + width <= 0) || (x >= OLED_DISPLAY_WIDTH) || (y + height <= 0) || (y >= OLED_DISPLAY_HEIGHT)) {
        return;
    }
    int16_t draw_x   = x;
    int16_t draw_y   = y;
    uint8_t draw_w   = width;
    uint8_t draw_h   = height;
    uint8_t sprite_x = 0;
    uint8_t sprite_y = 0;
    // If partially out of screen, calculate bounds for the visible part;
    if (x < 0) {
        draw_x   = 0;
        draw_w   = x + width;
        sprite_x = -x;
    } else if ((x + width) > OLED_DISPLAY_WIDTH) {
        draw_w = OLED_DISPLAY_WIDTH - x;
    }
    if (y < 0) {
        draw_y   = 0;
        draw_h   = y + height;
        sprite_y = -y;
    } else if ((y + height) > OLED_DISPLAY_HEIGHT) {
        draw_h = OLED_DISPLAY_HEIGHT - y;
    }
    uint8_t sprite_y_row_offset = sprite_y / 8;
    uint8_t sprite_y_bit_offset = sprite_y % 8;

    uint8_t total_rows          = (height / 8);
    uint8_t n_trailing_row_bits = height % 8;
    if (n_trailing_row_bits > 0) {
        total_rows++;
    }
    total_rows -= sprite_y_row_offset;
    // TODO: Check for the case (y % 8 == 0) and just set bytes directly
    for (uint8_t sprite_row_i = 0; sprite_row_i < total_rows; sprite_row_i++) {
        uint8_t n_bits    = 8;
        uint8_t bit_start = 0;
        bool    first_row = (sprite_row_i == 0);
        bool    last_row  = (sprite_row_i == total_rows - 1);
        if (first_row && sprite_y_bit_offset) {
            n_bits    = 8 - sprite_y_bit_offset;
            bit_start = sprite_y_bit_offset;
        } else if (last_row) {
            if ((n_trailing_row_bits > 0) && (n_trailing_row_bits < n_bits)) {
                n_bits = n_trailing_row_bits;
            }
            if (draw_h < n_bits) {
                n_bits = draw_h;
            }
        }
        for (uint8_t sprite_col_i = 0; sprite_col_i < draw_w; sprite_col_i++) {
            uint8_t byte     = data[((sprite_row_i + sprite_y_row_offset) * width) + sprite_x + sprite_col_i];
            uint8_t canvas_x = draw_x + sprite_col_i;
            for (uint8_t bit_i = 0; bit_i < n_bits; bit_i++) {
                if (byte & column_masks[bit_start + bit_i]) {
                    uint8_t canvas_y = draw_y + bit_i;
                    if (!point_out_of_bounds(canvas_x, canvas_y, 0)) oled_write_pixel(canvas_x, canvas_y, !erase);
                }
            }
        }
        draw_y += n_bits;
    }
}
