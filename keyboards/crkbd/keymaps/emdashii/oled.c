/* Copyright 2022 @toinux
  * Copyright 2022 @emdashii
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
#include "keycodes.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

// #define _QWERTY 0
// #define _NAVIGATION 1
// #define _GAMING 2
// #define _NUMBER 3
// #define _SYMBOL 4
// #define _FUNCTION 5
// #define _ADJUST 6

// This renders, but the switching function is very broken.
void oled_render_layer_state(void) {
    oled_write_P(PSTR("\nLayer: "), false);
    switch (get_highest_layer(layer_state|default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _NAVIGATION:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _GAMING:
            oled_write_ln_P(PSTR("Gaming"), false);
            break;
        case _NUMBER:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case _SYMBOL:
            oled_write_ln_P(PSTR("Symbols"), false);
            break;
        case _FUNCTION:
            oled_write_ln_P(PSTR("Fn Keys"), false);
            break;
        case _ADJUST:
            oled_write_ln_P(PSTR("Settings"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Default"), false);
            break;
    }
}


//
char keylog_str[24] = {};

const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', '_', '-', '=', '[', ']', '\\',
    '#', ';', '\'', '`', ',', '.', '/', ' ', ' ', ' '};

uint8_t last_row = 0;
uint8_t last_col = 0;

// this code does not run yet. error on name. potentially simpler
// void set_keylog(uint16_t keycode, keyrecord_t *record) {
//     char name = ' ';
//     if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
//         (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { keycode = keycode & 0xFF; }
//     if (keycode < 60) {
//         name = code_to_name[keycode];
//     }
//     // update keylog
//     oled_write(get_u8_str(record->event.key.row, ' '), false);
//     oled_write_P(PSTR("x"), false);
//     oled_write(get_u8_str(record->event.key.col, ' '), false);
//     oled_write_P(PSTR(", k"), false);
//     oled_write(get_u16_str(keycode, ' '), false);
//     oled_write_P(PSTR(" : "), false);
//     oled_write(name, false);
//     last_row = record->event.key.row;
//     last_col = record->event.key.col;
// }

// void oled_render_keylog(void) {
//     // oled_write_char(last_row + '0', false);
//     // oled_write_char('x', false);
//     // oled_write_char(last_col + '0', false);
//     oled_write(keylog_str, false);
// }


// code from r2g.c, Copyright 2019 @foostan, 2020 Drashna Jaelre <@drashna>, 2021 Elliot Powell @e11i0t23

char key_name_r2g = ' ';
uint16_t last_keycode_r2g;
uint8_t last_row_r2g;
uint8_t last_col_r2g;

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    key_name_r2g = ' ';
    last_keycode_r2g = keycode;
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) { last_keycode_r2g = keycode & 0xFF; }
    if (keycode < 60) {
      key_name_r2g = code_to_name[keycode];
    }
    last_row_r2g = record->event.key.row;
    last_col_r2g = record->event.key.col;
}

const char *depad_str(const char *depad_str, char depad_char) {
    while (*depad_str == depad_char) ++depad_str;
    return depad_str;
}

void oled_render_keylog(void) {
    //oled_write(keylog_str_r2g, false);
    const char *last_row_r2g_str = get_u8_str(last_row_r2g, ' ');
    oled_write(depad_str(last_row_r2g_str, ' '), false);
    oled_write_P(PSTR("x"), false);
    const char *last_col_r2g_str = get_u8_str(last_col_r2g, ' ');
    oled_write(depad_str(last_col_r2g_str, ' '), false);
    oled_write_P(PSTR(", k"), false);
    const char *last_keycode_r2g_str = get_u16_str(last_keycode_r2g, ' ');
    oled_write(depad_str(last_keycode_r2g_str, ' '), false);
    oled_write_P(PSTR(":"), false);
    oled_write_char(key_name_r2g, false);
}

static void oled_render_logo(void) {
    static const char PROGMEM raw_logo[] = {
        2,  2,  2,  0,  4,  4,  4, 12,  8, 16, 32, 96,192,128,  0,  0,  0,128,128,192,128,128,192, 64, 64, 96, 32, 32, 32, 32, 32, 32, 96, 64,192,128,  0,  0,  0,  2,  0,  0,  0,  0,  0,128,128,128,  0,  0,  0,128,128,  0,128,128,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,240,240, 96,192,128,192,224,192,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,248,  4,  2,  2,  3,  1,  1,  2,  2,  2,  2,  2,  3,  1,  3,  0,  0, 12,255,193,192,192,128,128,128,  0,  0,  0,  0,  0,  0,  0, 64, 64, 64, 32, 31, 15,  0,  0,  0,  0,  0,  0,144,255,255,197,  7,  7,  3,131,131,131,131,129,129,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,255,255, 48, 28,  7,  1,  2,  4,  9, 55,252,224,128,  0,  0,  0,  0,  2,  2,  6,  6, 12,244,  4,  5,255,  4,  4,  8,  8,  8,  8,  8,  8,  8,  8, 24,248,216,252, 12,  6,  6,  6,  6,  6,  6,  2,  6,  2,  2,  2,  0,  0,  0,  0,  0,
        0,129,131,  6,  4, 12, 24,  8, 16, 16, 16,  0,128,128,128,  0,  0,  0,  0,  0, 15,248,  0,  0,  0,  1,  1,  6,  4, 24, 48, 96,192,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,128,255,  7,  7,  3,255,  3,  1,  1,  1,129,129,129,129,128,128,128,192,192, 64, 64, 64, 64,192,192,224,240,254,159,  4,  0,  2,  2,  2,  2,  2,  3,  3,  3, 15,255,254,240,192,  0,  0,128,128,128,227,255,224,240,255,224, 96, 96, 40, 32, 32, 32, 38,110,254,254,111,199,255,143,130,  2,  2,  1,  1,129,129,209,121,120, 18,  0,  0,  0,  0,  0,
        0,  0,  0,  1,  1,  1,  1,  1,  1,  3,  1,  3,  3,  3,  7, 15,  7,  7, 15, 14, 60,127,124, 48,  0,  0,  0,  0,  0,  0,  0,  0,  1, 15, 30,124, 60, 56, 24, 28, 30, 15,  7, 15, 31, 59, 58, 31,  7,  1,  1,  1,  3,  3,  3,  7,  7,  7,  3,  1,  0,  0,  0,  0,  0,  0,  0,  3,  3,  3,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,  7,  7,  3,  3,  3,  7,  5,  9,  0,  0,  0,  1,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0, 15,  7,  2,  2,  2,  3,  3,  3,  1,  1,  1,  0,  0,  0,  0, 16, 16, 16,  0, 96,152,148,
        68
    };
    oled_write_raw_P(raw_logo, sizeof(raw_logo));
}

// Use this to display the crkbd logo
// void oled_render_logo(void) {
//     static const char PROGMEM crkbd_logo[] = {
//         0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
//         0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
//         0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
//         0};
//     oled_write_P(crkbd_logo, false);
// }

bool oled_task_user(void) {
    if (is_keyboard_master ()) {
        oled_render_layer_state();
        oled_render_keylog();
    } else {
        // render_YOUR_logo();
        oled_render_logo();
        // oled_scroll_right();
        // oled_scroll_set_speed(4);
    }
    return false;
}
