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
#include OLED_FONT_H

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

char* enc_mode_str[] = {"Splash", \
    "Volume", \
    "Media Control", \
    "Custom", \
    "Backlight Brightness", \
    "Underglow Brightness", \
    "Underglow Mode", \
    "Underglow Color", \
    "Scroll Wheel"
};

uint8_t enc_mode_str_startpos[] = {0, 49, 28, 49, 7, 7, 25, 22, 31};

uint8_t num_enc_modes = 9;
uint16_t enc_cw[] =  { KC_VOLU, KC_VOLU, KC_MEDIA_NEXT_TRACK, 0, 0, 0, 0, 0, KC_WH_D };
uint16_t enc_ccw[] = { KC_VOLD, KC_VOLD, KC_MEDIA_PREV_TRACK, 0, 0, 0, 0, 0, KC_WH_U };

uint8_t prev_layer = 255;
uint8_t prev_capslock = 255;
uint8_t prev_numlock = 255;
uint8_t prev_encodermode = 255;
bool is_splash = false;

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
    is_splash = false;
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
        if (is_splash == false) {
            is_splash = true;
            draw_splash();
        }
    } else {
        if (is_splash == true) {
            is_splash = false;
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

