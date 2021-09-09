/* Copyright 2021 Rocco Jiang
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
#include "do43_oled.h"

/*
 * OLED drawing helper functions.
 * Adapted from https://github.com/joric/qmk/blob/master/drivers/qwiic/micro_oled.c
 */
void oled_draw_line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, bool on) {
    uint8_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        swap(x0, y0);
        swap(x1, y1);
    }

    if (x0 > x1) {
        swap(x0, x1);
        swap(y0, y1);
    }

    uint8_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int8_t err = dx / 2;
    int8_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    for (; x0 < x1; x0++) {
        if (steep) {
            oled_write_pixel(y0, x0, on);
        } else {
            oled_write_pixel(x0, y0, on);
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }
}

void oled_draw_line_hori(uint8_t x, uint8_t y, uint8_t width, bool on) {
    oled_draw_line(x, y, x + width, y, on);
}

void oled_draw_line_vert(uint8_t x, uint8_t y, uint8_t height, bool on) {
    oled_draw_line(x, y, x, y + height, on);
}

void oled_draw_rect_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    uint8_t tempHeight;

    oled_draw_line_hori(x + 1, y, width - 2, on);
    oled_draw_line_hori(x + 1, y + height - 1, width - 2, on);

    tempHeight = height - 2;

    // Skip drawing vertical lines to avoid overlapping of pixel that will
    // affect XOR plot if no pixel in between horizontal lines
    if (tempHeight < 1) return;

    oled_draw_line_vert(x, y + 1, tempHeight, on);
    oled_draw_line_vert(x + width - 1, y + 1, tempHeight, on);
}

void oled_draw_rect_filled(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    for (int i = x; i < x + width; i++) {
        oled_draw_line_vert(i, y, height, on);
    }
}

/*
 * Bongo Cat WPM visualiser.
 * 
 * Credits:
 * @j-inc for initial bongocat code
 * @obosob for initial animation approach
 * @pixelbenny for images
 * @aseiger for initial adaptation to 128x32 display
 * @vectorstorm for initial run length encoding to compress animation size
 * @filterpaper for improvements to RLE
 */

// Bongocat frames are encoded in pairs of 'byte, count'
// RLE decode will read each pair and render bytes based on count
static void decode_frame(unsigned char const *frame) {
    uint16_t cursor = 0;
    uint8_t size = pgm_read_byte_near(frame);

    oled_set_cursor(0, 0);
    for (uint8_t i = 1; i < size - 1; i += 2) {
        // Loop through pairs of byte and count
        char byte = pgm_read_byte_near(frame + i);
        uint8_t count = pgm_read_byte_near(frame + i + 1);

        for (uint8_t j = 0; j < count; ++j) {
            // Render byte repetition
            oled_write_raw_byte(byte, cursor);
            cursor++;
        }
    }
}

static void render_cat_idle(void) {
    static unsigned char const *idle_anim[IDLE_FRAMES] = { idle0, idle0, idle1, idle2, idle3 };

    static uint8_t current_frame = 0;
    current_frame = (current_frame < IDLE_FRAMES - 1) ? current_frame + 1 : 0;

    decode_frame(idle_anim[current_frame]);
}

static void render_cat_prep(void) {
    decode_frame(prep);
}

static void render_cat_tap(void) {
    static unsigned char const *tap_anim[TAP_FRAMES] = { tap0, tap1 };

    static unsigned char current_frame = 0;
    current_frame = (current_frame + 1) & 1;

    decode_frame(tap_anim[current_frame]);
}

static void render_bongocat(void) {

    void animate_cat(void) {
        if (get_current_wpm() <= IDLE_SPEED) {
            render_cat_idle();
        }
        if (get_current_wpm() > IDLE_SPEED && get_current_wpm() < TAP_SPEED) {
            render_cat_prep();
        }
        if (get_current_wpm() >= TAP_SPEED){
            render_cat_tap();
        }
    }

    if (get_current_wpm() != 0) {
        oled_on(); // not essential but turns on animation OLED with any alpha keypress
        if (timer_elapsed32(anim_timer) > FRAME_DURATION) {
            anim_timer = timer_read32();
            animate_cat();
        }
        anim_sleep = timer_read32();
    } else {
        if (timer_elapsed32(anim_sleep) > OLED_TIMEOUT) {
            oled_off();
        } else {
            if (timer_elapsed32(anim_timer) > FRAME_DURATION) {
                anim_timer = timer_read32();
                animate_cat();
            }
        }
    }
}

// Write WPM information without using sprintf() from <stdio.h>
// as the library increases firmware size
static void render_wpm_count(void) {
    char wpm_str[4];
    uint8_t wpm = get_current_wpm();

    wpm_str[3] = '\0';
    wpm_str[2] = '0' + wpm % 10;
    wpm_str[1] = '0' + (wpm /= 10) % 10;
    wpm_str[0] = '0' + wpm / 10;

    oled_write_P(PSTR("WPM:"), false);
    oled_write(wpm_str, false);
}

void render_wpm_mode(void) {
    render_bongocat();
    oled_set_cursor(0, 0);
    render_wpm_count();
}

/*
 * Keyboard information mode, inspired by the Satisfaction75.
 * A portion of code adapted from https://github.com/qmk/qmk_firmware/blob/master/keyboards/cannonkeys/satisfaction75/
 */
static void render_symbol(int x, int y, int num_rows, int row_length, const char data[][row_length + 1]) {
    for (int row = 0; row < num_rows; row++) {
        oled_set_cursor(x, y + row);
        oled_write_P(data[row], false);
    }
}

static void render_layer_num(void) {
    oled_set_cursor(LAYERS_CURSOR_X, LAYERS_CURSOR_Y);
    oled_write_P(layer_str, false);

    uint8_t layer = get_highest_layer(layer_state);
    oled_set_cursor(LAYERS_CURSOR_X + LAYER_STR_LENGTH, LAYERS_CURSOR_Y);
    oled_write_P(layer_row_1[layer], false);
    oled_set_cursor(LAYERS_CURSOR_X + LAYER_STR_LENGTH, LAYERS_CURSOR_Y + 1);
    oled_write_P(layer_row_2, false);
}

static void render_modifiers(void) {
    uint8_t modifiers = get_mods();

    if (modifiers & MOD_MASK_SHIFT)
        render_symbol(SHIFT_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, shift_pressed);
    else
        render_symbol(SHIFT_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, shift);

    if (modifiers & MOD_MASK_CTRL)
        render_symbol(CTRL_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, ctrl_pressed);
    else
        render_symbol(CTRL_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, ctrl);
    
    if (modifiers & MOD_MASK_ALT)
        render_symbol(OPTN_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, optn_pressed);
    else
        render_symbol(OPTN_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, optn);
    
    if (modifiers & MOD_MASK_GUI)
        render_symbol(CMD_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, cmd_pressed);
    else
        render_symbol(CMD_CURSOR_X, MODS_CURSOR_Y, MODS_ICON_NUM_ROWS, MODS_ICON_NUM_COLS, cmd);
}

// Adapted from https://github.com/qmk/qmk_firmware/blob/master/keyboards/cannonkeys/satisfaction75/satisfaction_oled.c
static void render_matrix_visualisation(void) {
    // Draw currently pressed keys
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        for (uint8_t y = 0; y < MATRIX_COLS; y++) {
            oled_draw_rect_filled(MATRIX_CURSOR_X + MATRIX_SIDE_PADDING + y * MATRIX_KEY_WIDTH, MATRIX_CURSOR_Y + MATRIX_SIDE_PADDING + MATRIX_OLED_HEIGHT + 1 + x * MATRIX_KEY_WIDTH, MATRIX_KEY_WIDTH, MATRIX_KEY_WIDTH, (matrix_get_row(x) & (1 << y)) > 0);
        }
    }
    // Draw keyboard outline
    oled_draw_rect_soft(MATRIX_CURSOR_X, MATRIX_CURSOR_Y, (MATRIX_KEY_WIDTH * MATRIX_COLS) + 2 * MATRIX_SIDE_PADDING, (MATRIX_KEY_WIDTH * MATRIX_ROWS) + 2 * MATRIX_SIDE_PADDING + MATRIX_OLED_HEIGHT + 1, true);
    // Draw OLED panel
    oled_draw_rect_filled(MATRIX_CURSOR_X + (MATRIX_KEY_WIDTH * MATRIX_COLS) + MATRIX_SIDE_PADDING - MATRIX_OLED_WIDTH, MATRIX_CURSOR_Y + MATRIX_SIDE_PADDING, MATRIX_OLED_WIDTH, MATRIX_OLED_HEIGHT, true);
}

void render_info_mode(void) {
    render_layer_num();
    render_modifiers();
    render_matrix_visualisation();
}

/* Init and rendering calls */

// Rotate OLED display to the correct orientation
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_180; };

void oled_task_user(void) {
    switch (oled_mode) {
        default:
        case OLED_INFO:
            render_info_mode();
            break;
        case OLED_WPM:
            render_wpm_mode();
            break;
    }
}
