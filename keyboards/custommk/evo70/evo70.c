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

//If Bongo cat not undefined, Scroll wheel will be enabled,
//but for scroll wheel to work, you must also set MOUSEKEY_ENABLE = yes
//in rules.mk 
#define BONGOCAT

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
static bool OLED_awakened = false;
static bool OLED_redraw = false;
static bool startup_complete = false;
static bool startup_delay = false;
static bool starting_up = false;

#define ENCODER_MATRIX_ROW 5
#define ENCODER_MATRIX_COL 6

#define ENC_SPLASH 0
#define ENC_VOLUME 1
#define ENC_MEDIA 2
#define ENC_CUSTOM 3
#define ENC_BL_BRIGHT 4
#define ENC_BL_BREATH 5
#define ENC_RGB_BRIGHT 6
#define ENC_RGB_MODE 7
#define ENC_RGB_COLOR 8
#define ENC_SCROLL 9
#ifdef BONGOCAT
#define ENC_BONGO 9
#endif //bongocat


extern matrix_row_t matrix[MATRIX_ROWS];

char* enc_mode_str[] = {
#ifdef BONGOCAT
    /* Splash */ "", \
    "Volume", \
    "Media Control", \
    "Custom", \
    "Backlight Brightness", \
    "Backlight Breathing", \
    "Underglow Brightness", \
    "Underglow Mode", \
    "Underglow Color", \
    "" // Bongo Cat
};

uint16_t enc_cw[] =  { KC_VOLU, KC_VOLU, KC_MEDIA_NEXT_TRACK, KC_VOLU, 0, 0, 0, 0, 0, KC_VOLU };
uint16_t enc_ccw[] = { KC_VOLD, KC_VOLD, KC_MEDIA_PREV_TRACK, KC_VOLD, 0, 0, 0, 0, 0, KC_VOLD };
#else
    /* Splash */ "", \
    "Volume", \
    "Media Control", \
    "Custom", \
    "Backlight Brightness", \
    "Backlight Breathing", \
    "Underglow Brightness", \
    "Underglow Mode", \
    "Underglow Color", \
    "Scroll Wheel"
};

uint16_t enc_cw[] =  { KC_VOLU, KC_VOLU, KC_MEDIA_NEXT_TRACK, KC_VOLU, 0, 0, 0, 0, 0, KC_WH_U };
uint16_t enc_ccw[] = { KC_VOLD, KC_VOLD, KC_MEDIA_PREV_TRACK, KC_VOLD, 0, 0, 0, 0, 0, KC_WH_D };
#endif //bongocat

uint8_t num_enc_modes = 10;

uint8_t enc_mode_str_startpos[] = {0, 49, 28, 49, 7, 10, 7, 25, 22, 31};

uint8_t prev_layer = 255;
uint8_t prev_capslock = 255;
uint8_t prev_numlock = 255;

typedef union {
    uint32_t raw;
    struct {
        uint8_t enc_mode;
        uint8_t breathingperiod;
        bool oled_is_on : 1;
    };
} user_config_t;

user_config_t user_config;



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
    
    const uint8_t *glyph = &font[((uint8_t)cast_data - OLED_FONT_START) * OLED_FONT_WIDTH];
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
        draw_rect_soft(x, y, width, 11, true);
        write_chars_at_pixel_xy(x+3, y+2, str, false);
    }
}

void draw_keyboard_layer(void){
    uint8_t highest_layer;
    highest_layer = get_highest_layer(layer_state);
    draw_rect_filled_soft(LAYER_DISPLAY_X + highest_layer*12, LAYER_DISPLAY_Y, 11, 11, true);

    write_char_at_pixel_xy(LAYER_DISPLAY_X+3,  LAYER_DISPLAY_Y+2, '0', highest_layer == 0);
    write_char_at_pixel_xy(LAYER_DISPLAY_X+3+12, LAYER_DISPLAY_Y+2, '1', highest_layer == 1);
    write_char_at_pixel_xy(LAYER_DISPLAY_X+3+24, LAYER_DISPLAY_Y+2, '2', highest_layer == 2);
    write_char_at_pixel_xy(LAYER_DISPLAY_X+3+36, LAYER_DISPLAY_Y+2, '3', highest_layer == 3);

    draw_line_h(0, 14, 128, true);
}


static const uint8_t splash[] PROGMEM = { \
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

uint16_t startup_timer = 0;
bool redrawn_splash = false;


#ifdef BONGOCAT


#define ANIM_FRAME_DURATION 75
#define IDLE_FRAMES 5
#define IDLE_TIMEOUT 750
#define SLEEP_TIMEOUT 15000


static const uint8_t bongofont[] PROGMEM = { \
    0xC1, 0xC1, 0xC2, 0x04, 0x08, 0x10, \
    0xC0, 0x38, 0x04, 0x03, 0x00, 0x00, \
    0xA0, 0x22, 0x24, 0x14, 0x12, 0x12, \
    0xA0, 0x21, 0x22, 0x12, 0x11, 0x11, \
    0x83, 0x7C, 0x41, 0x41, 0x40, 0x40, \
    0x82, 0x82, 0x84, 0x08, 0x10, 0x20, \
    0x80, 0x80, 0x00, 0x00, 0x00, 0x00, \
    0x80, 0x70, 0x19, 0x06, 0x00, 0x00, \
    0x80, 0x70, 0x0C, 0x03, 0x00, 0x00, \
    0x80, 0x00, 0x30, 0x30, 0x00, 0xC0, \
    0x80, 0x00, 0x30, 0x30, 0x00, 0x00, \
    0x49, 0x88, 0x08, 0x08, 0x08, 0x00, \
    0x44, 0x84, 0x04, 0x04, 0x00, 0x00, \
    0x40, 0x80, 0x00, 0x00, 0x00, 0x00, \
    0x40, 0x40, 0x20, 0x20, 0x20, 0x20, \
    0x3C, 0xC2, 0x01, 0x01, 0x02, 0x02, \
    0x35, 0x01, 0x8A, 0x7C, 0x00, 0x00, \
    0x20, 0x40, 0x80, 0x00, 0x00, 0x00, \
    0x20, 0x21, 0x22, 0x12, 0x11, 0x11, \
    0x20, 0x20, 0x10, 0x10, 0x10, 0x10, \
    0x1E, 0xE1, 0x00, 0x00, 0x01, 0x01, \
    0x1C, 0xE2, 0x01, 0x01, 0x02, 0x02, \
    0x18, 0x64, 0x82, 0x02, 0x02, 0x02, \
    0x18, 0x60, 0x80, 0x00, 0x00, 0x00, \
    0x18, 0x18, 0x1B, 0x03, 0x00, 0x40, \
    0x18, 0x06, 0x05, 0x98, 0x99, 0x84, \
    0x12, 0x0B, 0x08, 0x08, 0x08, 0x08, \
    0x11, 0x09, 0x08, 0x08, 0x08, 0x08, \
    0x10, 0x10, 0xD0, 0x11, 0x0F, 0x21, \
    0x10, 0x10, 0x10, 0x11, 0x0F, 0x01, \
    0x10, 0x08, 0x08, 0x04, 0x04, 0x04, \
    0x10, 0x08, 0x04, 0x02, 0x02, 0x04, \
    0x0C, 0x30, 0x40, 0x80, 0x00, 0x00, \
    0x0C, 0x0C, 0x0D, 0x01, 0x00, 0x40, \
    0x08, 0xE8, 0x08, 0x07, 0x10, 0x24, \
    0x08, 0x30, 0x40, 0x80, 0x00, 0x00, \
    0x08, 0x08, 0x08, 0x07, 0x00, 0x00, \
    0x08, 0x08, 0x04, 0x02, 0x02, 0x02, \
    0x08, 0x04, 0x02, 0x01, 0x01, 0x02, \
    0x05, 0x05, 0x09, 0x09, 0x10, 0x10, \
    0x04, 0x38, 0x40, 0x80, 0x00, 0x00, \
    0x04, 0x04, 0x08, 0x08, 0x10, 0x10, \
    0x04, 0x04, 0x04, 0x04, 0x04, 0x04, \
    0x04, 0x04, 0x02, 0x01, 0x00, 0x00, \
    0x02, 0x02, 0x81, 0x80, 0x80, 0x00, \
    0x02, 0x02, 0x04, 0x04, 0x08, 0x08, \
    0x02, 0x02, 0x02, 0x01, 0x01, 0x01, \
    0x02, 0x02, 0x01, 0x00, 0x00, 0x00, \
    0x01, 0xE1, 0x1A, 0x06, 0x09, 0x31, \
    0x01, 0x01, 0x02, 0x04, 0x08, 0x10, \
    0x01, 0x00, 0x00, 0x00, 0x00, 0x00, \
    0x00, 0x80, 0x80, 0x00, 0x00, 0x00, \
    0x00, 0x80, 0x40, 0x40, 0x20, 0x20, \
    0x00, 0x00, 0x80, 0x80, 0x40, 0x40, \
    0x00, 0x00, 0x60, 0x60, 0x00, 0x81, \
    0x00, 0x00, 0x01, 0x01, 0x00, 0x40, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x18, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x0C, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x03, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x01, \
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00}; 


static const uint8_t bongo_line_x[] = {51, 49, 48, 57};
static const uint8_t bongo_line_y[] = {0, 8, 16, 24};
static const uint8_t bongo_line_len[] = {5, 7, 8, 6};

const uint8_t bongo_line_data[8][26] PROGMEM = {
    { //idle1
    60, 52, 19, 30, 35, \
    22, 47, 51, 60, 9, 0, 17, \
    1, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle2
    60, 52, 19, 30, 35, \
    22, 47, 51, 60, 9, 0, 17, \
    1, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle3
    60, 53, 14, 31, 23, \
    15, 43, 60, 60, 54, 5, 13, \
    7, 56, 24, 2, 26, 39, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle4
    6, 52, 19, 38, 32, \
    20, 47, 51, 60, 9, 0, 17, \
    8, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //idle5
    60, 52, 19, 37, 40, \
    21, 47, 51, 60, 9, 0, 17, \
    8, 57, 33, 3, 27, 41, 29, 50, \
    45, 36, 60, 60, 60, 60}, \
    { //prep
    6, 52, 19, 38, 32, \
    20, 44, 51, 60, 10, 48, 16, \
    8, 25, 4, 18, 27, 42, 46, 50, \
    60, 60, 60, 60, 60, 60}, \
    { //tap1
    6, 52, 19, 38, 32, \
    20, 44, 51, 60, 10, 49, 17, \
    8, 25, 4, 18, 27, 41, 28, 11, \
    60, 60, 60, 60, 58, 59}, \
    { //tap2
    6, 52, 19, 38, 32, \
    20, 47, 51, 60, 10, 48, 16, \
    8, 60, 55, 3, 27, 42, 46, 50, \
    45, 34, 12, 60, 60, 60}
};

enum anin_states { sleep, idle, prep, tap };
uint8_t anim_state = idle;
uint32_t idle_timeout_timer = 0;
uint32_t anim_timer = 0;
uint8_t current_idle_frame = 0;
uint8_t current_tap_frame = 6;
uint8_t last_bongo_frame = 12;

void write_bongochar_at_pixel_xy(uint8_t x, uint8_t y, uint8_t data, bool invert) {
    uint8_t i, j, temp;
    for (i = 0; i < 6 ; i++) { // 6 = font width
        temp = pgm_read_byte(&bongofont[data * 6]+i);
        for (j = 0; j < 8; j++) {  // 8 = font height
            if (temp & 0x01) {
                oled_write_pixel(x + i, y + j, !invert);
            } else {
                oled_write_pixel(x + i, y + j, invert);
            }
            temp >>= 1;
        }
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
    uint8_t y = 31;
    uint8_t j = 0;
    for (i = 17; i < 57; i++) {
        oled_write_pixel(i, y, true); //every five horizontal pixels, move up one pixel to make a diagonal line
        if (j == 4) {
            --y;
            j=0;
        } else {
            j++;
        }
    }

    y=15;
    j=0;
    for (i = 91; i < 128; i++) {

        oled_write_pixel(i, y, true); //every four horizontal pixels, move up one pixel to make a diagonal line
        if (j == 3) {
            --y;
            j=0;
        } else {
            j++;
        }
    }


}


void draw_bongocat_frame(int framenumber) {
    //only redraw if the animation frame has changed
    if (framenumber != last_bongo_frame) {
        last_bongo_frame = framenumber;
        uint8_t i, j, current_bongochar = 0;
        for (i = 0; i < 4; i++) {
            for (j = 0; j < bongo_line_len[i]; j++) {
                write_bongochar_at_pixel_xy(bongo_line_x[i] + j*6, bongo_line_y[i], pgm_read_byte(&bongo_line_data[framenumber][current_bongochar]), false);
                current_bongochar++;
            }
        }
    }
    
}

bool is_new_tap(void) {
    static matrix_row_t old_matrix[] = { 0, 0, 0, 0, 0, 0 };
    bool new_tap = false;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] > old_matrix[i]) { // more 1's detected, there was a new tap
            new_tap = true;
        }
        old_matrix[i] = matrix[i];
    }
    return new_tap;
}

void draw_bongocat(void) {
    static bool already_tapped = false;
    if (is_new_tap()) {
        already_tapped = false;
    };
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
    temp = pgm_read_byte(&splash[count]);
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
            temp = pgm_read_byte(&splash[++count]);
        }
    }
}

void draw_media_arrow(uint8_t x, uint8_t y, bool fwd) {
    draw_line_v(x, y, 7, true);
    draw_line_v(x+4, y, 7, true);
    draw_line_v(x+2, y+2, 3, true);
    if (fwd) {
        draw_line_v(x+1, y+1, 5, true);
        oled_write_pixel(x+3, y+3, true);
    } else {
        draw_line_v(x+3, y+1, 5, true);
        oled_write_pixel(x+1, y+3, true);
    }
}

void draw_enc_mode(void){
    write_chars_at_pixel_xy(enc_mode_str_startpos[user_config.enc_mode], ENC_DISPLAY_Y + 2, enc_mode_str[user_config.enc_mode], false);
    if (user_config.enc_mode == ENC_MEDIA) {
        draw_media_arrow(enc_mode_str_startpos[user_config.enc_mode] - 16, ENC_DISPLAY_Y + 2, false);
        draw_media_arrow(enc_mode_str_startpos[user_config.enc_mode] + 88, ENC_DISPLAY_Y + 2, true);
    }
}

void draw_keyboard_locks(void) {
    led_t led_state = host_keyboard_led_state();
    draw_text_rectangle(CAPSLOCK_DISPLAY_X, CAPSLOCK_DISPLAY_Y, 5 + (3 * 6), "CAP", led_state.caps_lock);
    draw_text_rectangle(NUMLOCK_DISPLAY_X, NUMLOCK_DISPLAY_Y, 5 + (3 * 6), "NUM", led_state.num_lock);
}


/* Encoder handling functions */

__attribute__((weak)) void set_custom_encoder_mode_user(bool custom_encoder_mode) {}

void update_custom_encoder_mode_user(void) {
#ifdef BONGOCAT
    set_custom_encoder_mode_user((user_config.enc_mode == ENC_CUSTOM) || (user_config.enc_mode == ENC_SPLASH) || (user_config.enc_mode == ENC_BONGO));
#else
    set_custom_encoder_mode_user((user_config.enc_mode == ENC_CUSTOM) || (user_config.enc_mode == ENC_SPLASH));
#endif
}

void update_kb_eeprom(void) {
    eeconfig_update_kb(user_config.raw);
}

void update_breathing(void);
void matrix_init_kb(void) {

    user_config.raw = eeconfig_read_kb();
    if (user_config.enc_mode == 0xFF) { //EEPROM was cleared
        user_config.enc_mode = 0;
        user_config.oled_is_on = true;
        user_config.breathingperiod = 1;
        update_kb_eeprom();

    }
    startup_delay = true;
    update_custom_encoder_mode_user();
    matrix_init_user();
}

void handle_encoder_switch_process_record(keyrecord_t *record) {

    static uint32_t encoder_press_timer = 0;
    if (record->event.pressed) {
        if (!user_config.oled_is_on) {
            oled_on();
            user_config.oled_is_on = true;
            OLED_awakened = true;
            OLED_redraw = true;
            update_kb_eeprom();
        }
        encoder_press_timer = timer_read32();
    } else {
        if (OLED_awakened == true) {
            OLED_awakened = false;
        } else {
            if (timer_elapsed32(encoder_press_timer) < 300) {

                if (get_mods() & MOD_MASK_SHIFT) {
                    user_config.enc_mode = (user_config.enc_mode + (num_enc_modes- 1)) % num_enc_modes;
                } else {
                    user_config.enc_mode = (user_config.enc_mode + 1) % num_enc_modes;
                }
                OLED_redraw = true;
                update_custom_encoder_mode_user();
                update_kb_eeprom();
            } else {
                OLED_redraw = false;
                oled_clear();
                user_config.oled_is_on = false;
                update_kb_eeprom();
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

void update_breathing(void) {
    if (user_config.breathingperiod == 1) {
        breathing_disable();
    }
    else {
        breathing_period_set(user_config.breathingperiod);
        breathing_enable();
    }
    update_kb_eeprom();
}


void backlight_breath_change(bool increase) { //increase period or decrease period
    if ((increase) && (user_config.breathingperiod < 15)) {
        user_config.breathingperiod++;
        update_breathing();
    }
    if (!increase) {
        if (user_config.breathingperiod > 2) {
            user_config.breathingperiod--;
            update_breathing();
        } 
        else {
            user_config.breathingperiod = 1;
            update_breathing();

            
        }
    }
}

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_user(index, clockwise)) return false;
    switch (user_config.enc_mode) {
        case ENC_RGB_MODE :
            if (clockwise) {
                rgblight_step();
            } else {
                rgblight_step_reverse();
            }
            break;
        case ENC_RGB_BRIGHT :
            if (clockwise) {
                rgblight_increase_val();
            } else {
                rgblight_decrease_val();
            }
            break;
        case ENC_BL_BRIGHT :
            if (clockwise) {
                backlight_increase();
            } else {
                backlight_decrease();
            }
            break;
        case ENC_BL_BREATH :
            backlight_breath_change(clockwise);
            break;
        case ENC_RGB_COLOR :
            if (clockwise) {
                rgblight_increase_hue();
            } else {
                rgblight_decrease_hue();
            }
            break;
        default:
            if (clockwise) {
                tap_code(enc_cw[user_config.enc_mode]);
            } else {
                tap_code(enc_ccw[user_config.enc_mode]);
            }
    }
    return true;
}


void matrix_scan_kb(void) {
    matrix_scan_user();
    led_t current_led_state = host_keyboard_led_state();
    uint8_t current_layer = get_highest_layer(layer_state);
    if (startup_delay) {
        startup_timer = timer_read();
        startup_delay = false;
        startup_complete = false;
        starting_up = true;
        OLED_redraw = false;
    }
    else if (starting_up) {
        if (timer_elapsed(startup_timer) >= 200) {
            update_breathing();
            startup_complete = true;
            starting_up = false;
            if (user_config.oled_is_on) {
                oled_on();
                OLED_redraw = true;
            } else
            {
                oled_clear();
                user_config.oled_is_on = false;
            }
        }
    }
    if (startup_complete) {
        if (user_config.enc_mode == ENC_SPLASH) {
            if (user_config.oled_is_on && OLED_redraw) {
                draw_splash();
            }
        }
    #ifdef BONGOCAT
        else if (user_config.enc_mode == ENC_BONGO) {
            if (user_config.oled_is_on) {
                if (OLED_redraw) {
                    oled_clear();
                    last_bongo_frame = 12; //force a redraw
                    draw_bongo_table();
                    OLED_redraw = false;
                }
                draw_bongocat();

            }

        }
    #endif //BONGOCAT
        else  {        
            if (user_config.oled_is_on && (
                    OLED_redraw
                    || (prev_layer != current_layer)
                    || (prev_capslock != current_led_state.caps_lock)
                    || (prev_numlock != current_led_state.num_lock))) {

                prev_layer = current_layer;
                prev_capslock = current_led_state.caps_lock;
                prev_numlock = current_led_state.num_lock;

                oled_clear();
                draw_keyboard_layer();
                draw_keyboard_locks();
                draw_enc_mode();
            }
        }
        OLED_redraw = false;
    }
    
}

