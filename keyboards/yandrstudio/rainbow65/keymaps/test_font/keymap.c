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


#include QMK_KEYBOARD_H
#include <stdio.h>
#include <string.h>
#include "dynamic_keymap.h"
#include "oled_font_lib/logo.h"
#include "oled_font_lib/ext_font.h"

enum layer_names { _BASE, _FN, _SYS, _USER };
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
        KC_ESC, RESET, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_MUTE,
        KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS,
        KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT,
        KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT, KC_VOLD, KC_VOLU, KC_SPC, KC_RALT, MO(1), MO(2), MO(3), KC_DOWN, KC_RGHT),

    [_FN] = LAYOUT(
        KC_GRV,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_DEL, TO(_BASE),
        KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_CAPS,
        KC_TRNS, RGB_TOG, RGB_MOD, RGB_MODE_REVERSE, RGB_VAI, RGB_VAD, RGB_SPI, RGB_SPD, RGB_MODE_PLAIN, RGB_MODE_BREATHE, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_SYS] = LAYOUT(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS),

    [_USER] = LAYOUT(
        KC_TRNS, KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,   KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS,   KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS)
};



#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 3);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            tap_code16(keycode);
        }
    } else {
        uint16_t keycode = dynamic_keymap_get_keycode(biton32(layer_state), 4, 4);
        if (keycode >= MACRO00 && keycode <= MACRO15) {
            dynamic_keymap_macro_send(keycode - MACRO00);
        } else {
            tap_code16(keycode);
        }
    }
    return false;
}
#endif



// #define I_AM_LEFT



#ifdef OLED_DRIVER_ENABLE

#   define UNC (94+0x21)
volatile char current_alp[7];
volatile uint8_t cur_alp_index;

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    strcpy((char *)(current_alp), "[    ]");
    current_alp[1] = UNC;
    current_alp[2] = UNC;
    current_alp[3] = UNC;
    current_alp[4] = UNC;

    cur_alp_index = 1;
#   ifdef I_AM_LEFT
        return OLED_ROTATION_180;
#   else
        return OLED_ROTATION_0;
#   endif
}


void render_logo(void) {
    uint8_t i = 0, j = 0;
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 32; ++j) {
#   ifdef I_AM_LEFT
            oled_write_raw_byte(logo_idobao[i*32+j], i*128+j);
#   else
            oled_write_raw_byte(logo_idobao[i*32+j], i*128+j+96);
#   endif
        }
    }
}


void render_layer_helper_fun(uint8_t start_line, const char * data, uint8_t gap_w) {
    uint8_t j = 0, k = 0, l = strlen(data);
    for (j = 0; j < l; ++j) { // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(32) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(ext_big_font[data[j]-0x21][k], start_line*2*128 + 32 + gap_w + j*12+k);
            oled_write_raw_byte(ext_big_font[data[j]-0x21][k+12], start_line*2*128+128 + 32 + gap_w + j*12+k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(blank_block, start_line*2*128 + 32 + j);
        oled_write_raw_byte(blank_block, start_line*2*128 + 32 + gap_w + l*12 + j);

        oled_write_raw_byte(blank_block, start_line*2*128+128 + 32 + j);
        oled_write_raw_byte(blank_block, start_line*2*128+128 + 32 + gap_w + l*12 + j);

    }
}
void render_layer(uint8_t layer) {
    render_layer_helper_fun(0, PSTR("LAYER:"), 12);
    switch (layer)
    {
    case 0:
        render_layer_helper_fun(1, PSTR("1:HOME"), 12);
        break;
    case 1:
        render_layer_helper_fun(1, PSTR("2:CODE"), 12);
        break;
    case 2:
        render_layer_helper_fun(1, PSTR("3:OFFICE"), 0);
        break;
    case 3:
    default:
        render_layer_helper_fun(1, PSTR("OTHER"), 18);
        break;
    }
}

void render_cur_input_helper_fun(uint8_t start_line, const char * data, uint8_t gap_w) {
    uint8_t j = 0, k = 0, l = strlen(data);
    for (j = 0; j < l; ++j) { // font index
        for (k = 0; k < 12; ++k) { // font byte index
            //                                        base + logo_w(0) + gap_w(12) +l*font_w(12)+current_byte_index
            oled_write_raw_byte(ext_big_font[data[j]-0x21][k], start_line*2*128 + gap_w + j*12+k);
            oled_write_raw_byte(ext_big_font[data[j]-0x21][12+k], start_line*2*128+128 + gap_w + j*12+k);
        }
    }
    for (j = 0; j < gap_w; ++j) {
        oled_write_raw_byte(blank_block, start_line*2*128 + j);
        oled_write_raw_byte(blank_block, start_line*2*128 + gap_w + l*12 + j);

        oled_write_raw_byte(blank_block, start_line*2*128+128 + j);
        oled_write_raw_byte(blank_block, start_line*2*128+128 + gap_w + l*12 + j);
    }
}

void render_cur_input(void) {
    render_cur_input_helper_fun(0, PSTR("INPUTS:"), 6);
    render_cur_input_helper_fun(1, (const char *)(current_alp), 12);
    return;
}


void oled_task_user(void) {
    render_logo();
#   ifdef I_AM_LEFT
    render_layer(biton32(layer_state));
#   else
    render_cur_input();
#   endif
}



static const char PROGMEM code_to_name[0xFF] = {
//   0    1    2    3    4    5    6    7    8    9    A    B    c    D    E    F
    UNC,        UNC,        UNC,        UNC,        'a',        'b',        'c',        'd',        'e',        'f',        'g',        'h',        'i',        'j',        'k',        'l',         // 0x
    'm',        'n',        'o',        'p',        'q',        'r',        's',        't',        'u',        'v',        'w',        'x',        'y',        'z',        '1',        '2',         // 1x
    '3',        '4',        '5',        '6',        '7',        '8',        '9',        '0',        UNC,        UNC,        UNC,        UNC,        UNC,        '-',        '=',        '[',         // 2x
    ']',       '\\',        '#',        ';',       '\'',        '`',        ',',        '.',        '/',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 3x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 4x
    UNC,        UNC,        UNC,        UNC,        '/',        '*',        '-',        '+',        UNC,        '1',        '2',        '3',        '4',        '5',        '6',        '7',         // 5x
    '8',        '9',        '0',        '.',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 6x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 7x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 8x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // 9x
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Ax
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Bx
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Cx
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Dx
    UNC,        UNC,        'A',        'W',        UNC,        'S',        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,         // Ex
    UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC,        UNC        // Fx
};




void get_cur_alp_hook(uint16_t keycode) {
    if (keycode >= 0xF0) {
        keycode = 0xF0;
    }
    if (cur_alp_index < 4) {
        current_alp[cur_alp_index] = code_to_name[keycode];
        cur_alp_index++;
    } else {
        for (uint8_t i = 2; i <= 4; ++i) {
            current_alp[i-1] = current_alp[i];
        }
        current_alp[cur_alp_index] = code_to_name[keycode];
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    get_cur_alp_hook(keycode);
    return true;

}


void matrix_scan_user(void) {
    if(!is_oled_on()) {
        cur_alp_index = 1;
    }
}


#endif
