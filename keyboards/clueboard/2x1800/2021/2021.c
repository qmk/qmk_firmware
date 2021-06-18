/* Copyright 2017 Zach White <skullydazed@gmail.com>
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

/* Portions of this file are based on LEDControl by Eberhard Fahle. You can
 * find the original code here: <https://github.com/wayoda/LedControl>
 *
 * The license for that code follows.
 *
 *    LedControl.h - A library for controling Leds with a MAX7219/MAX7221
 *    Copyright (c) 2007 Eberhard Fahle
 *
 *    Permission is hereby granted, free of charge, to any person
 *    obtaining a copy of this software and associated documentation
 *    files (the "Software"), to deal in the Software without
 *    restriction, including without limitation the rights to use,
 *    copy, modify, merge, publish, distribute, sublicense, and/or sell
 *    copies of the Software, and to permit persons to whom the
 *    Software is furnished to do so, subject to the following
 *    conditions:
 *
 *    This permission notice shall be included in all copies or
 *    substantial portions of the Software.
 *
 *    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
 *    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
 *    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
 *    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 *    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 *    OTHER DEALINGS IN THE SOFTWARE.
 */
#include "2021.h"
#include "max7219.h"
#include "font.h"

#if !defined(MAX7219_LED_TEST) && !defined(MAX7219_LED_ITERATE) && !defined(MAX7219_LED_DANCE) && !defined(MAX7219_LED_FONTTEST) && !defined(MAX7219_LED_CLUEBOARD) && !defined(MAX7219_LED_KONAMI) && !defined(MAX7219_LED_QMK_POWERED) && !defined(MAX7219_DRAWING_TOY_MODE) && !defined(MAX7219_LED_CUSTOM)
#    define MAX7219_LED_CLUEBOARD
#endif

#ifndef DRAWING_TOY_MODE
static uint16_t led_frame_timer = 0;

void matrix_scan_kb(void) {
    if (timer_elapsed(led_frame_timer) > 100) {
        max7219_message_sign_task(true);
        led_frame_timer = timer_read();
    }
}
#endif

void matrix_init_kb(void) {
    max7219_init();

#if defined(MAX7219_LED_TEST)
    while(1) {
        for (int i=0; i<MAX7219_CONTROLLERS; i++) {
            max7219_display_test(i, true);
            wait_ms(500);
            max7219_display_test(i, false);
        }
    }
#elif defined(MAX7219_LED_ITERATE)
    while (1) {
        for (int row=0; row<8; row++) {
            for(int col=0;col<8*MAX7219_CONTROLLERS;col++) {
                max7219_set_led(row, col, true);
                wait_ms(500);
                max7219_set_led(row, col, false);
            }
        }
    }
#elif defined(MAX7219_LED_DANCE)
    while (1) {
        for (int col=0; col<8; col++) {
            for (int device_num=0; device_num<MAX7219_CONTROLLERS; device_num++) {
                if (col % 2 == 0) {
                    max7219_led_a[col][device_num] = 0b01010101;
                } else {
                    max7219_led_a[col][device_num] = 0b10101010;
                }
            }
        }
        max7219_write_frame();
        wait_ms(500);
        for (int col=0; col<8; col++) {
            for (int device_num=0; device_num<MAX7219_CONTROLLERS; device_num++) {
                if (col % 2 == 0) {
                    max7219_led_a[col][device_num] = 0b10101010;
                } else {
                    max7219_led_a[col][device_num] = 0b01010101;
                }
            }
        }
        max7219_write_frame();
        wait_ms(500);
    }
#elif defined(MAX7219_LED_FONTTEST)
    uint8_t message[104][6] = {L_TILDE, L_BANG, L_AT, L_POUND, L_PERCENT, L_CARET, L_AMPERSAND, L_LPAREN, L_RPAREN, L_UNDERSCORE, L_PLUS, L_BACKTICK, L_1, L_2, L_3, L_4, L_5, L_6, L_7, L_8, L_9, L_0, L_DASH, L_EQUAL, L_A, L_B, L_C, L_D, L_E, L_F, L_G, L_H, L_I, L_J, L_K, L_L, L_M, L_N, L_O, L_P, L_Q, L_R, L_S, L_T, L_U, L_V, L_W, L_X, L_Y, L_Z, L_a, L_b, L_c, L_d, L_e, L_f, L_g, L_h, L_i, L_j, L_k, L_l, L_m, L_n, L_o, L_p, L_q, L_r, L_s, L_t, L_u, L_v, L_w, L_x, L_y, L_z, L_LCURLY, L_RCURLY, L_PIPE, L_COLON, L_QUOTE, L_LESSTHAN, L_GREATERTHAN, L_QUESTIONMARK, L_INTERROBANG, L_LBRACKET, L_RBRACKET, L_BACKSLASH, L_SEMICOLON, L_APOSTROPHE, L_COMMA, L_PERIOD, L_SLASH, L_CENT, L_DEGREES, L_DEGREES_C, L_DEGREES_F, L_DIVISION, L_LEFT_ARROW, L_RIGHT_ARROW, L_UP_ARROW, L_DOWN_ARROW, L_PI, L_PSI};
    max7219_message_sign(message, 104);
#elif defined(MAX7219_LED_CLUEBOARD)
    uint8_t message[10][6] = {L_INTERROBANG, L_C, L_l, L_u, L_e, L_b, L_o, L_a, L_r, L_d};
    max7219_message_sign(message, 10);
#elif defined(MAX7219_LED_KONAMI)
    uint8_t message[36][6] = {L_UP_ARROW, L_SPACE, L_UP_ARROW, L_SPACE, L_DOWN_ARROW, L_SPACE, L_DOWN_ARROW, L_SPACE, L_LEFT_ARROW, L_SPACE, L_RIGHT_ARROW, L_SPACE, L_LEFT_ARROW, L_SPACE, L_RIGHT_ARROW, L_SPACE, L_B, L_SPACE, L_A, L_SPACE, L_LESSTHAN, L_S, L_E, L_L, L_E, L_C, L_T, L_GREATERTHAN, L_SPACE, L_LESSTHAN, L_S, L_T, L_A, L_R, L_T, L_GREATERTHAN};
    max7219_message_sign(message, 36);
#elif defined(MAX7219_LED_QMK_POWERED)
    uint8_t message[15][6] = {L_PSI, L_P, L_o, L_w, L_e, L_r, L_e, L_d, L_SPACE, L_b, L_y, L_SPACE, L_Q, L_M, L_K};
    max7219_message_sign(message, 15);
#elif defined(DRAWING_TOY_MODE)
    max7219_set_led(0, 0, true);
#endif
}

__attribute__ ((weak))
bool encoder_update_keymap(int8_t index, bool clockwise) {
    return false;
}

#define NUM_COLUMNS 8*MAX7219_CONTROLLERS
uint8_t led_position[2] = {0,0};  // The location of the cursor in the matrix

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) {
#if defined(DRAWING_TOY_MODE)
        // Encoder 1, left
        if (index == 0 && clockwise) {
            if (led_position[0] < NUM_COLUMNS-1) {  // turned right
                led_position[0]++;
            } else {
                led_position[0]=0;
            }
        } else if (index == 0) {
            if (led_position[0] > 0) {  // turned left
                led_position[0]--;
            } else {
                led_position[0]=NUM_COLUMNS-1;
            }
        }

        // Encoder 2, right
        else if (index == 1 && clockwise) {
            if (led_position[1] < 7) {  // turned right
                led_position[1]++;
            } else {
                led_position[1]=0;
            }
        } else if (index == 1) {
            if (led_position[1] > 0) {  // turned left
                led_position[1]--;
            } else {
                led_position[1]=7;
            }
        }

        max7219_set_led(led_position[1], led_position[0], true);
#else
        // Encoder 1, left
        if (index == 0 && clockwise) {
            tap_code(KC_MS_R);  // turned right
        } else if (index == 0) {
            tap_code(KC_MS_L);  // turned left
        }

        // Encoder 2, right
        else if (index == 1 && clockwise) {
            tap_code(KC_MS_U);  // turned right
        } else if (index == 1) {
            tap_code(KC_MS_D);  // turned left
        }
#endif
    }
    return true;  // FIXME: check which I should return
}
