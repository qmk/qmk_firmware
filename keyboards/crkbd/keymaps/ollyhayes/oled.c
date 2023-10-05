/* Copyright 2022 Olly Hayes (@ollyhayes)
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
#include "ollyhayes.h"

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

#define L_BASE 0
#define L_NUM 8
#define L_FUNCTIONS 16
#define L_ARR 32
#define L_PUNC 64
#define L_DUBPUNC 128
#define L_MEDIA 256

#define DL_COLEMAK 1
#define DL_QWERTY 2
#define DL_GAMES 4

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (layer_state) {
        case L_BASE:
            switch (default_layer_state) {
                case DL_QWERTY:
                    oled_write_ln_P(PSTR("Qwerty"), false);
                    break;
                case DL_GAMES:
                    oled_write_ln_P(PSTR("Games"), false);
                    break;
                case DL_COLEMAK:
                default:
                    oled_write_ln_P(PSTR("Colemak"), false);
                    break;
            }
            break;
        case L_NUM:
            oled_write_ln_P(PSTR("Numbers"), false);
            break;
        case L_FUNCTIONS:
        case L_FUNCTIONS|L_NUM:
            oled_write_ln_P(PSTR("Functions"), false);
            break;
        case L_ARR:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case L_PUNC:
            oled_write_ln_P(PSTR("Punctuation"), false);
            break;
        case L_MEDIA:
        case L_MEDIA|L_NUM:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case L_DUBPUNC:
        case L_DUBPUNC|L_PUNC:
            oled_write_ln_P(PSTR("Specials"), false);
            break;
    }
}

void oled_render_timer(void) {
    static uint16_t microticks = 0;
    static uint16_t ticks = 0;

    if (microticks++ % 1000 == 0) {
        ticks++;
    }

    oled_write_P(PSTR("Ticks:   "), false);
    oled_write_ln(get_u16_str(ticks, ' '), false);
}

void oled_render_presses(void) {
    oled_write_P(PSTR("Presses: "), false);
    oled_write_ln(get_u16_str(key_presses, ' '), false);
}

void oled_render_rgb_mode(void) {
    oled_write_P(PSTR("Animation: "), false);
    oled_write_ln(get_u8_str(rgb_matrix_get_mode(), ' '), false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
    }
    oled_render_timer();
    if (is_keyboard_master()) {
        oled_render_presses();
    }
    oled_render_rgb_mode();
    return false;
}
