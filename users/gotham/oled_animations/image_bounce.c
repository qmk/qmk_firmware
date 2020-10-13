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

#ifdef OLED_ANIM_IMAGE_BOUNCE
#    include "image_bounce.h"

#    define IMAGE_WIDTH 32
#    define IMAGE_HEIGHT 16

// clang-format off
static const uint8_t image_data[] = {
0x00, 0xf0, 0xff, 0xff, 0xff, 0xc3, 0xc3, 0xe3, 0x67, 0x7f, 0x3f, 0x1f, 0x0f, 0x3f, 0xff, 0xf8,
0xf0, 0x78, 0x3c, 0x1f, 0xc7, 0xff, 0xff, 0xff, 0xcf, 0xc3, 0xc3, 0xe3, 0x7f, 0x7f, 0x3e, 0x1c,
0x00, 0x08, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x36, 0x37, 0x37,
0x36, 0x36, 0x36, 0x3e, 0x3e, 0x3e, 0x3e, 0x3e, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x1c, 0x08, 0x00
};
// clang-format on

static bool     move_up;
static bool     move_left;
static int16_t  logo_x;
static int16_t  logo_y;
static uint16_t image_update_timer = 0;

void oled_init_image_bounce(void) {
    random16_set_seed(timer_read());
    logo_x    = random8_max(OLED_DISPLAY_WIDTH - IMAGE_WIDTH);
    logo_y    = random8_max(OLED_DISPLAY_HEIGHT - IMAGE_HEIGHT);
    move_up   = (random8() % 2 == 0);
    move_left = (random8() % 2 == 0);
}

void update_image_bounce(void) {
    if (move_left) {
        logo_x -= IMAGE_BOUNCE_SPEED;
    } else {
        logo_x += IMAGE_BOUNCE_SPEED;
    }
    if (move_up) {
        logo_y -= IMAGE_BOUNCE_SPEED;
    } else {
        logo_y += IMAGE_BOUNCE_SPEED;
    }
    uint8_t collision_mask = rect_out_of_bounds(logo_x, logo_y, IMAGE_WIDTH, IMAGE_HEIGHT, IMAGE_BOUNCE_OFFSCREEN_PADDING);
    if ((collision_mask & COLLISION_MASK_UP || collision_mask & COLLISION_MASK_DOWN)) {
        move_up = !move_up;
    }
    if ((collision_mask & COLLISION_MASK_LEFT || collision_mask & COLLISION_MASK_RIGHT)) {
        move_left = !move_left;
    }
}

void render_image_bounce(void) {
    if (timer_elapsed(image_update_timer) >= UPDATE_DELAY) {
        oled_write_bitmap(image_data, logo_x, logo_y, IMAGE_WIDTH, IMAGE_HEIGHT, true);
        update_image_bounce();
        oled_write_bitmap(image_data, logo_x, logo_y, IMAGE_WIDTH, IMAGE_HEIGHT, false);
        image_update_timer = timer_read();
    }
}
#endif
