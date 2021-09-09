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

void render_info_mode(void) {
    render_layer_num();
    render_modifiers();
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
