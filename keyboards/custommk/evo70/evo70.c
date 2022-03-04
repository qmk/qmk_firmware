/* Copyright 2021 customMK
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

#include "evo70.h"
#include <stdbool.h>
#include "matrix.h"
#include OLED_FONT_H

//#define BONGOCAT 

/* Placement information for display elements */
#define ENC_DISPLAY_X 0
#define ENC_DISPLAY_Y 0

#define LAYER_DISPLAY_X 5
#define LAYER_DISPLAY_Y 19

#define CAPSLOCK_DISPLAY_X 80
#define CAPSLOCK_DISPLAY_Y 19

#define NUMLOCK_DISPLAY_X 105
#define NUMLOCK_DISPLAY_Y 19

/* Encoder Parameters */
uint8_t enc_mode = 0;

#define ENCODER_MATRIX_ROW 5
#define ENCODER_MATRIX_COL 6

#define ENC_SPLASH 0
#define ENC_VOLUME 1
#define ENC_MEDIA 2
#define ENC_CUSTOM 3
#define ENC_BL_BRIGHT 4
#define ENC_RGB_BRIGHT 5
#define ENC_RGB_MODE 6
#define ENC_RGB_COLOR 7
#define ENC_SCROLL 8
#ifdef BONGOCAT
#define ENC_BONGO 9
#endif //bongocat

extern matrix_row_t matrix[MATRIX_ROWS];

char* enc_mode_str[] = {
#ifdef BONGOCAT
    "Splash", \
    "Volume", \
    "Media Control", \
    "Custom", \
    "Backlight Brightness", \
    "Underglow Brightness", \
    "Underglow Mode", \
    "Underglow Color", \
    "Scroll Wheel", \
    "BongoCat"
#else
    "Splash", \
    "Volume", \
    "Media Control", \
    "Custom", \
    "Backlight Brightness", \
    "Underglow Brightness", \
    "Underglow Mode", \
    "Underglow Color", \
    "Scroll Wheel"
#endif //bongocat
};

uint8_t enc_mode_str_startpos[] = {0, 49, 28, 49, 7, 7, 25, 22, 31, 0};

#ifdef BONGOCAT
uint8_t num_enc_modes = 10;
uint16_t enc_cw[] =  { KC_VOLU, KC_VOLU, KC_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_VOLD, KC_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0, KC_WH_U };
#else
uint8_t num_enc_modes = 9;
uint16_t enc_cw[] =  { KC_VOLU, KC_VOLU, KC_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_VOLD, KC_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0, KC_WH_U };
#endif //bongocat



uint8_t prev_layer = 255;
uint8_t prev_capslock = 255;
uint8_t prev_numlock = 255;
uint8_t prev_encodermode = 255;
uint8_t current_enc_mode = 1;

/* OLED Draw Functions */
/* TODO: Reimplement using Quantum Painter when available  */

static void draw_line_h(uint8_t x, uint8_t y, uint8_t len, bool on) {
     for (uint8_t i = 0; i < len; i++) {
         oled_write_pixel(i + x, y, on);
     }
 }

 static void draw_line_v(uint8_t x, uint8_t y, uint8_t len, bool on) {
     for (uint8_t i = 0; i < len; i++) {
         oled_write_pixel(x, i + y, on);
     }
 }

void draw_rect_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    uint8_t tempHeight;

    draw_line_h(x + 1, y, width - 2, on);
    draw_line_h(x + 1, y + height - 1, width - 2, on);

    tempHeight = height - 2;

    if (tempHeight < 1) return;

    draw_line_v(x, y + 1, tempHeight, on);
    draw_line_v(x + width - 1, y + 1, tempHeight, on);
}

void write_char_at_pixel_xy(uint8_t x, uint8_t y, const char data, bool invert) {
    uint8_t i, j, temp;
    uint8_t cast_data = (uint8_t)data;
    
    const uint8_t *glyph = &font[(cast_data - OLED_FONT_START) * OLED_FONT_WIDTH];
    temp = pgm_read_byte(glyph);
    for (i = 0; i < OLED_FONT_WIDTH ; i++) {
        for (j = 0; j < OLED_FONT_HEIGHT; j++) {
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
        temp = pgm_read_byte(++glyph);
    }
}

void write_chars_at_pixel_xy(uint8_t x, uint8_t y, const char *data, bool invert) {
    uint8_t c = data[0];
    uint8_t offset = 0;
    while (c != 0) {
        write_char_at_pixel_xy(x + offset, y, c, invert);
        data++;
        c = data[0];
        offset += 6;
    }
}


void draw_rect_filled_soft(uint8_t x, uint8_t y, uint8_t width, uint8_t height, bool on) {
    for (int i = x; i < x + width; i++) {
        if (i == x || i == (x + width - 1))
            draw_line_v(i, y + 1, height - 2, on);
        else
            draw_line_v(i, y, height, on);
    }
}

void draw_text_rectangle(uint8_t x, uint8_t y, uint8_t width, char* str, bool filled) {
    if (filled) {
        draw_rect_filled_soft(x, y, width, 11, true);
        write_chars_at_pixel_xy(x+3, y+2, str, true);
    } else {
        draw_rect_filled_soft(x, y, width, 11, false);
        draw_rect_soft(x, y, width, 11, true);
        write_chars_at_pixel_xy(x+3, y+2, str, false);
    }
}

void draw_keyboard_layer(void){
    draw_rect_filled_soft(LAYER_DISPLAY_X, LAYER_DISPLAY_Y, 48, 11, false);
    draw_rect_filled_soft(LAYER_DISPLAY_X + get_highest_layer(layer_state)*12, LAYER_DISPLAY_Y, 11, 11, true);

    write_chars_at_pixel_xy(LAYER_DISPLAY_X+3, LAYER_DISPLAY_Y+2, "0", get_highest_layer(layer_state) == 0);
    write_chars_at_pixel_xy(LAYER_DISPLAY_X+3+12, LAYER_DISPLAY_Y+2, "1", get_highest_layer(layer_state) == 1);
    write_chars_at_pixel_xy(LAYER_DISPLAY_X+3+24, LAYER_DISPLAY_Y+2, "2", get_highest_layer(layer_state) == 2);
    write_chars_at_pixel_xy(LAYER_DISPLAY_X+3+36, LAYER_DISPLAY_Y+2, "3", get_highest_layer(layer_state) == 3);

    draw_line_h(0, 14, 128, true);

}



uint8_t splash[] = { \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x1c, 0x06, 0x02, 0x02, \
    0x03, 0x03, 0x83, 0x83, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x83, 0x83, 0x03, \
    0x03, 0x03, 0x83, 0x83, 0x83, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x83, 0x83, 0x83, 0x83, 0x03, \
    0x02, 0x02, 0x06, 0x0c, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0xf8, 0xfe, 0x87, 0xe1, 0xbf, 0x9f, 0x00, 0x00, \
    0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0xff, 0xff, 0xff, 0x3f, 0xfc, 0xe0, 0xc0, 0xf8, 0x7f, 0x0f, 0xff, 0xff, 0x00, 0x00, \
    0x00, 0x00, 0xff, 0xff, 0xff, 0x80, 0xc0, 0xf0, 0xf8, 0x3c, 0x1f, 0x0f, 0x03, 0x01, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 0xfe, 0xc7, 0x83, \
    0x83, 0x8f, 0xc6, 0xc0, 0xfe, 0xff, 0xc7, 0xc0, 0xf0, 0xff, 0xff, 0x81, 0xc0, 0xe0, 0x70, 0x9e, \
    0x8f, 0xbf, 0xf8, 0xf0, 0x80, 0xc1, 0xe3, 0x7f, 0xff, 0xff, 0x83, 0x83, 0x83, 0xc1, 0xfc, 0xfe, \
    0xff, 0x83, 0x83, 0xdf, 0xff, 0x7e, 0x18, 0x18, 0xfe, 0xff, 0xfb, 0x1c, 0x06, 0xff, 0xff, 0xff, \
    0x3c, 0x0e, 0xe7, 0xff, 0xff, 0x80, 0xc0, 0xe0, 0x60, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x01, 0x0f, 0x0f, 0x03, 0x00, 0x00, 0xff, 0xff, 0x00, 0x00, \
    0x00, 0x00, 0xff, 0xff, 0xff, 0x07, 0x03, 0x03, 0x0f, 0x3f, 0x7c, 0xf8, 0xe0, 0x80, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, \
    0x01, 0x01, 0x01, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x01, \
    0x03, 0x03, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x01, \
    0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, \
    0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x38, 0x20, 0x40, 0x40, \
    0x40, 0x40, 0x43, 0x43, 0x43, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x43, 0x43, 0x40, 0x40, \
    0x40, 0x40, 0x43, 0x43, 0x43, 0x40, 0x40, 0x40, 0x40, 0x40, 0x40, 0x41, 0x43, 0x43, 0x43, 0x40, \
    0x40, 0x40, 0x60, 0x30, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

#ifdef BONGOCAT


#define ANIM_FRAME_DURATION 75
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750
#define SLEEP_TIMEOUT 15000


static const uint8_t bongofont[] PROGMEM = { \
    0xFC, 0x60, 0x01, 0x01, 0x01, \
    0xE0, 0x18, 0x06, 0x01, 0x00, \
    0xC2, 0xCA, 0x24, 0x88, 0xF0, \
    0xC0, 0x30, 0x0C, 0x03, 0x00, \
    0x8C, 0x9C, 0x1C, 0x1E, 0x0E, \
    0x84, 0x44, 0x44, 0x42, 0x82, \
    0x80, 0x86, 0x86, 0x40, 0x40, \
    0x80, 0x83, 0x83, 0x40, 0x40, \
    0x80, 0x80, 0x40, 0x40, 0x40, \
    0x80, 0x80, 0x40, 0x40, 0x20, \
    0x80, 0x40, 0x40, 0x20, 0x20, \
    0x80, 0x00, 0x00, 0x60, 0x60, \
    0x40, 0x40, 0x40, 0x20, 0x10, \
    0x40, 0x40, 0x21, 0x22, 0x22, \
    0x40, 0x40, 0x20, 0x21, 0x21, \
    0x40, 0x00, 0x00, 0x30, 0x30, \
    0x3C, 0x78, 0xF8, 0xF0, 0x70, \
    0x30, 0x40, 0x80, 0x80, 0x00, \
    0x24, 0x98, 0xC0, 0x88, 0x88, \
    0x24, 0x18, 0x00, 0x00, 0x00, \
    0x20, 0x40, 0x40, 0x41, 0x42, \
    0x20, 0x20, 0x40, 0x80, 0x80, \
    0x20, 0x20, 0x20, 0x20, 0x20, \
    0x20, 0x11, 0x11, 0x10, 0x10, \
    0x20, 0x10, 0x10, 0x10, 0x10, \
    0x18, 0x19, 0x00, 0x05, 0xFE, \
    0x18, 0x04, 0x02, 0x01, 0x02, \
    0x10, 0x20, 0x40, 0x80, 0x80, \
    0x10, 0x08, 0x04, 0x02, 0x04, \
    0x08, 0x10, 0x20, 0x40, 0x80, \
    0x08, 0x10, 0x10, 0x20, 0x20, \
    0x08, 0x08, 0x08, 0x08, 0x04, \
    0x08, 0x08, 0x08, 0x04, 0x04, \
    0x08, 0x04, 0x02, 0x01, 0x02, \
    0x06, 0x00, 0x00, 0x00, 0x00, \
    0x04, 0x08, 0x10, 0x20, 0x40, \
    0x04, 0x08, 0x10, 0x20, 0x20, \
    0x04, 0x08, 0x10, 0x10, 0x20, \
    0x04, 0x08, 0x08, 0x10, 0x10, \
    0x04, 0x04, 0x04, 0x08, 0x08, \
    0x04, 0x04, 0x04, 0x04, 0x08, \
    0x04, 0x04, 0x04, 0x02, 0x02, \
    0x03, 0x03, 0x61, 0xF0, 0xF8, \
    0x02, 0x64, 0x18, 0x04, 0x12, \
    0x02, 0x04, 0x04, 0x08, 0x08, \
    0x02, 0x04, 0x04, 0x02, 0x02, \
    0x02, 0x02, 0x04, 0x04, 0x08, \
    0x02, 0x02, 0x02, 0x01, 0x01, \
    0x02, 0x02, 0x01, 0x01, 0x01, \
    0x02, 0x01, 0x01, 0x00, 0x00, \
    0x01, 0x01, 0x02, 0x02, 0x04, \
    0x01, 0x01, 0x01, 0x02, 0x02, \
    0x01, 0x01, 0x01, 0x00, 0x00, \
    0x01, 0x01, 0x00, 0x00, 0x00, \
    0x01, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x0C, 0x03, 0x00, 0x02, \
    0x00, 0x06, 0x0F, 0x0F, 0x07, \
    0x00, 0x06, 0x0D, 0x31, 0xC1, \
    0x00, 0x01, 0x86, 0x98, 0x60, \
    0x00, 0x01, 0x01, 0x02, 0x04, \
    0x00, 0x01, 0x01, 0x02, 0x02, \
    0x00, 0x00, 0x80, 0x00, 0x00, \
    0x00, 0x00, 0x40, 0x80, 0x80, \
    0x00, 0x00, 0x1C, 0x32, 0xC4, \
    0x00, 0x00, 0x01, 0x02, 0x04, \
    0x00, 0x00, 0x01, 0x01, 0x01, \
    0x00, 0x00, 0x00, 0x80, 0x80, \
    0x00, 0x00, 0x00, 0x7E, 0x82, \
    0x00, 0x00, 0x00, 0x3F, 0xC1, \
    0x00, 0x00, 0x00, 0x00, 0x80, \
    0x00, 0x00, 0x00, 0x00, 0x01, \
    0x00, 0x00, 0x00, 0x00, 0x00, \
    0x40, 0x40, 0x80, 0x80, 0x00, \
    0x80, 0x80, 0x00, 0x00, 0x00, \
    0x80, 0x00, 0x00, 0x00, 0x00}; 


uint8_t bongo_line_x[] = {63, 48, 50, 57};
uint8_t bongo_line_y[] = {0, 8, 16, 24};
uint8_t bongo_line_len[] = {5, 10, 10, 9};


uint8_t bongo_line_data[8][34] = {
    { //idle1
    9, 23, 27, 37, 73, \
    69, 51, 42, 55, 70, 63, 16, 71, 45, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle2
    67, 13, 34, 36, 74, \
    69, 51, 42, 53, 72, 62, 12, 65, 39, 22, \
    4, 72, 72, 7, 14, 24, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle3
    67, 10, 29, 30, 75, \
    68, 47, 33, 50, 72, 62, 12, 60, 39, 22, \
    4, 72, 72, 7, 14, 24, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle4
    67, 10, 29, 30, 75, \
    64, 40, 33, 50, 70, 63, 16, 61, 40, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //idle5
    9, 23, 27, 37, 73, \
    58, 52, 46, 55, 70, 63, 16, 71, 45, 28, \
    2, 72, 72, 8, 15, 25, 32, 41, 18, 59, \
    38, 21, 20, 72, 72, 72, 72, 66, 72}, \
    { //prep
    67, 11, 29, 31, 73, \
    69, 51, 6, 53, 70, 63, 16, 71, 44, 3, \
    2, 56, 26, 8, 15, 25, 32, 42, 49, 55, \
    48, 54, 72, 72, 72, 72, 72, 72, 72}, \
    { //tap1
    67, 11, 29, 31, 73, \
    69, 51, 42, 53, 70, 63, 16, 71, 44, 3, \
    2, 72, 72, 8, 15, 25, 32, 42, 49, 55, \
    38, 21, 19, 5, 35, 72, 72, 72, 72}, \
    { //tap2
    67, 11, 29, 31, 73, \
    69, 51, 6, 53, 70, 63, 16, 71, 45, 28, \
    2, 56, 26, 8, 15, 25, 32, 41, 18, 59, \
    48, 54, 72, 72, 72, 57, 43, 1, 17}
};

enum anin_states { sleep, idle, prep, tap };
uint8_t anim_state = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 6;

void write_bongochar_at_pixel_xy(uint8_t x, uint8_t y, const char data, bool invert) {
    uint8_t i, j, temp;
    uint8_t cast_data = (uint8_t)data-1;
    const uint8_t *glyph = &bongofont[cast_data * 5]; // 5 = font width
    temp = pgm_read_byte(glyph);
    for (i = 0; i < 5 ; i++) { // 5 = font width
        for (j = 0; j < 8; j++) {  // 8 = font height
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
        temp = pgm_read_byte(++glyph);
    }
}

bool is_key_down(void) {
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > 0) {
            return true;
        }
    }
    return false;
}

void eval_anim_state(void) {
    bool key_down;
    key_down = is_key_down();

    switch (anim_state) {
        case sleep:
            if(key_down) { anim_state = tap; }
            break; 
        case idle:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= SLEEP_TIMEOUT) //prep to idle
                {
                    anim_state = sleep;
                    current_idle_frame = 0;
                }
            break;
        case prep:
            if(key_down) { anim_state = tap; }
            else if (timer_elapsed32(idle_timeout_timer) >= IDLE_TIMEOUT) //prep to idle
                {
                    anim_state = idle;
                    current_idle_frame = 0;
                }
            break;
        case tap:
            if (!key_down)
            {
                anim_state = prep;
                idle_timeout_timer = timer_read32();
            }
            break;
        default:
            break;
    }
}

void draw_bongo_table(void) {
    //draws the table edge for bongocat, this edge doesn't change during the animation
    uint8_t i;
    for (i = 27; i < 128; i++) {
        oled_write_pixel(i, 32 - ((i - 27) >> 2), true); //every four horizontal pixels, move up one pixel to make a diagonal line
    }
}


void draw_bongocat_frame(int framenumber) {
    static uint8_t last_bongo_frame = 0;
    //only redraw if the animation frame has changed
    if (framenumber != last_bongo_frame) {
        last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                write_bongochar_at_pixel_xy(bongo_line_x[i] + j*5, bongo_line_y[i], bongo_line_data[framenumber][current_bongochar], false);
                current_bongochar++;
            }
        }
    }
}

void draw_bongocat(void) {
    static bool already_tapped = false;
    eval_anim_state();
    switch (anim_state) {
        case sleep:
            draw_bongocat_frame(4);
            break;
        case idle:
            draw_bongocat_frame(4 - current_idle_frame);
            if (timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
                current_idle_frame = (current_idle_frame + 1) % 5;
                anim_timer = timer_read32();
            }
            break;
        case prep:
            draw_bongocat_frame(5);
            already_tapped = false;
            break;
        case tap:
            draw_bongocat_frame(current_tap_frame);
            if (already_tapped == false) {
                if (current_tap_frame == 6) {
                    current_tap_frame = 7;
                }
                else {
                    current_tap_frame = 6;
                }
            }
            already_tapped = true;
            break;
        default:
            draw_bongocat_frame(4);
            already_tapped = false;
            break;

    }
}

#endif //BONGOCAT

void draw_splash(void) {
    uint8_t i, j, k, temp;
    uint16_t count;
    count = 0;
    temp = splash[count];
    for (i = 0; i < 4 ; i++) {
        for (j = 0; j < 128; j++) {
            for (k = 0; k < 8; k++) {
                if (temp & 0x01) {
                     oled_write_pixel(j, (i * 8) + k, true);
                } else {
                    oled_write_pixel(j, (i * 8) + k, false);
                }
                temp >>= 1;
                
            }
            temp = splash[++count];
        }
    }
}

void blank_oled(void) {
    int i, j;
    for (i = 0; i < 32 ; i++) {
        for (j = 0; j < 128; j++) {
            oled_write_pixel(j, i, false);
        }
    }
}

void draw_media_arrow(uint8_t x, uint8_t y, bool fwd) {
    draw_line_v(x, y, 7, true);
    draw_line_v(x+4, y, 7, true);
    draw_line_v(x+2, y+2, 3, true);
    if (fwd) {
        draw_line_v(x+1, y+1, 5, true);
        draw_line_v(x+3, y+3, 1, true);
    } else {
        draw_line_v(x+3, y+1, 5, true);
        draw_line_v(x+1, y+3, 1, true);
    }
}

void draw_enc_mode(void){
    draw_rect_filled_soft(ENC_DISPLAY_X, ENC_DISPLAY_Y, 128, 11, false);
    write_chars_at_pixel_xy(enc_mode_str_startpos[enc_mode], ENC_DISPLAY_Y + 2, enc_mode_str[enc_mode], false);
    if (enc_mode == ENC_MEDIA) {
        draw_media_arrow(enc_mode_str_startpos[enc_mode] - 16, ENC_DISPLAY_Y + 2, false);
        draw_media_arrow(enc_mode_str_startpos[enc_mode] + 88, ENC_DISPLAY_Y + 2, true);
    }
}

void draw_keyboard_locks(void) {
    led_t led_state = host_keyboard_led_state();
    draw_text_rectangle(CAPSLOCK_DISPLAY_X, CAPSLOCK_DISPLAY_Y, 5 + (3 * 6), "CAP", led_state.caps_lock);
    draw_text_rectangle(NUMLOCK_DISPLAY_X, NUMLOCK_DISPLAY_Y, 5 + (3 * 6), "NUM", led_state.num_lock);
}

/* Encoder handling functions */

void matrix_init_kb(void) {
    prev_layer = 255;
    prev_capslock = 255;
    prev_numlock = 255;
    prev_encodermode = 255;
    current_enc_mode = 1;
    oled_on();
    matrix_init_user();
}

__attribute__((weak)) void set_custom_encoder_mode_user(bool custom_encoder_mode) {}

void handle_encoder_switch_process_record(keyrecord_t *record) {
    static bool OLED_awakened = false;
    static uint32_t encoder_press_timer = 0;
    if (record->event.pressed) {
        if (!is_oled_on()) {
            oled_on();
            OLED_awakened = true;
        } else {
            encoder_press_timer = timer_read32();
        }
    } else {
        if (OLED_awakened == true) {
            OLED_awakened = false;
        } else {
            if (timer_elapsed32(encoder_press_timer) < 300) {

                if (get_mods() & MOD_MASK_SHIFT) {
                    enc_mode = (enc_mode + (num_enc_modes- 1)) % num_enc_modes;
                } else {
                    enc_mode = (enc_mode + 1) % num_enc_modes;
                }
                set_custom_encoder_mode_user(enc_mode == ENC_CUSTOM);
            } else {
                oled_off();
            }
        }
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.key.row == ENCODER_MATRIX_ROW && record->event.key.col == ENCODER_MATRIX_COL){
        handle_encoder_switch_process_record(record);
    }
    return process_record_user(keycode, record);
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    if (enc_mode == ENC_RGB_MODE) {
        if (clockwise) {
            rgblight_step();
        } else {
            rgblight_step_reverse();
        }
    } else if (enc_mode == ENC_RGB_BRIGHT) {
        if (clockwise) {
            rgblight_increase_val();
        } else {
            rgblight_decrease_val();
        }
    } else if (enc_mode == ENC_BL_BRIGHT) {
        if (clockwise) {
            backlight_increase();
        } else {
            backlight_decrease();
        }
    } else if (enc_mode == ENC_RGB_COLOR) {
        if (clockwise) {
            rgblight_increase_hue();
        } else {
            rgblight_decrease_hue();
        }
    } else {
        if (clockwise) {
            tap_code(enc_cw[enc_mode]);
        } else {
            tap_code(enc_ccw[enc_mode]);
        }
    }
    return true;
}


void matrix_scan_kb(void) {
    matrix_scan_user();

    led_t current_led_state = host_keyboard_led_state();
    uint8_t current_layer = get_highest_layer(layer_state);
    
    if (enc_mode == ENC_SPLASH) {
        if (current_enc_mode != 0) {
            current_enc_mode = 0;
            draw_splash();
        }
    }
#ifdef BONGOCAT
    else if (enc_mode == ENC_BONGO) {
        if (current_enc_mode != 2) {
            current_enc_mode = 2;
            blank_oled();
            draw_bongo_table();
        }
        draw_bongocat();
    }
#endif //BONGOCAT
    else  {
        
        if (current_enc_mode != 1) {
            current_enc_mode = 1;
            blank_oled();
            draw_keyboard_layer();
            draw_keyboard_locks();
            draw_enc_mode();
        }
        if (prev_layer != current_layer) {
            prev_layer = current_layer;
            draw_keyboard_layer();
        }
        if (prev_capslock != current_led_state.caps_lock || prev_numlock != current_led_state.num_lock) {
            prev_capslock = current_led_state.caps_lock;
            prev_numlock = current_led_state.num_lock;
            draw_keyboard_locks();
        }
        if (prev_encodermode != enc_mode) {
            prev_encodermode = enc_mode;
            draw_enc_mode();
        }
    }
}

