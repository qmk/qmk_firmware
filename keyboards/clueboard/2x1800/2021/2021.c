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

void matrix_init_kb(void) {
    max7219_init();

#ifdef MAX7219_LED_TEST
    while(1) {
        for (int i=0; i<MAX7219_CONTROLLERS; i++) {
            max7219_display_test(i, true);
            wait_ms(500);
            max7219_display_test(i, false);
        }
    }
#endif

#ifdef MAX7219_LED_ITERATE
    while (1) {
        for (int row=0; row<8; row++) {
            for(int col=0;col<8*MAX7219_CONTROLLERS;col++) {
                max7219_set_led(row, col, true);
                wait_ms(500);
                max7219_set_led(row, col, false);
            }
        }
    }
#endif

#ifdef MAX7219_LED_DANCE
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
#endif

#ifdef MAX7219_LED_SCROLL
    // Interrobang art
    max7219_led_a[1][0] = 0b01100000;
    max7219_led_a[2][0] = 0b10000000;
    max7219_led_a[3][0] = 0b11101101;
    max7219_led_a[4][0] = 0b10010000;
    max7219_led_a[5][0] = 0b01100000;

    max7219_led_a[7][0] = L_C[0];
    max7219_led_a[0][1] = L_C[1];
    max7219_led_a[1][1] = L_C[2];
    max7219_led_a[2][1] = L_C[3];
    max7219_led_a[3][1] = L_C[4];

    max7219_led_a[5][1] = L_L[0];
    max7219_led_a[6][1] = L_L[1];
    max7219_led_a[7][1] = L_L[2];
    max7219_led_a[0][2] = L_L[3];
    max7219_led_a[1][2] = L_L[4];

    max7219_led_a[3][2] = L_U[0];
    max7219_led_a[4][2] = L_U[1];
    max7219_led_a[5][2] = L_U[2];
    max7219_led_a[6][2] = L_U[3];
    max7219_led_a[7][2] = L_U[4];

    max7219_led_a[1][3] = L_E[0];
    max7219_led_a[2][3] = L_E[1];
    max7219_led_a[3][3] = L_E[2];
    max7219_led_a[4][3] = L_E[3];
    max7219_led_a[5][3] = L_E[4];

    max7219_led_a[7][3] = L_B[0];
    max7219_led_a[0][4] = L_B[1];
    max7219_led_a[1][4] = L_B[2];
    max7219_led_a[2][4] = L_B[3];
    max7219_led_a[3][4] = L_B[4];

    max7219_led_a[5][4] = L_O[0];
    max7219_led_a[6][4] = L_O[1];
    max7219_led_a[7][4] = L_O[2];
    max7219_led_a[0][5] = L_O[3];
    max7219_led_a[1][5] = L_O[4];

    max7219_led_a[3][5] = L_A[0];
    max7219_led_a[4][5] = L_A[1];
    max7219_led_a[5][5] = L_A[2];
    max7219_led_a[6][5] = L_A[3];
    max7219_led_a[7][5] = L_A[4];

    max7219_led_a[1][6] = L_R[0];
    max7219_led_a[2][6] = L_R[1];
    max7219_led_a[3][6] = L_R[2];
    max7219_led_a[4][6] = L_R[3];
    max7219_led_a[5][6] = L_R[4];

    max7219_led_a[7][6] = L_D[0];
    max7219_led_a[0][7] = L_D[1];
    max7219_led_a[1][7] = L_D[2];
    max7219_led_a[2][7] = L_D[3];
    max7219_led_a[3][7] = L_D[4];

    max7219_write_frame();

    while (1) {
        uint8_t left_col = max7219_led_a[0][0];

        for (int device_num=0; device_num<MAX7219_BUFFER_SIZE; device_num++) {
            for (int col=0; col<8; col++) {
                if (col < 7) {
                    max7219_led_a[col][device_num] = max7219_led_a[col+1][device_num];
                    xprintf("1 col:%d dev:%d val:%d\n", col, device_num, max7219_led_a[col][device_num]);
                } else if (device_num == MAX7219_BUFFER_SIZE-1) {
                    max7219_led_a[col][device_num] = left_col;
                    xprintf("2 col:%d dev:%d val:%d\n", col, device_num, max7219_led_a[col][device_num]);
                } else {
                    max7219_led_a[col][device_num] = max7219_led_a[0][device_num+1];
                    xprintf("3 col:%d dev:%d val:%d\n", col, device_num, max7219_led_a[col][device_num]);
                }
            }
        }
        wait_ms(100);
        max7219_write_frame();
    }
#endif

    max7219_set_led(0, 0, true);
}

__attribute__ ((weak))
bool encoder_update_keymap(int8_t index, bool clockwise) {
    return false;
}

#define NUM_COLUMNS 8*MAX7219_CONTROLLERS
uint8_t led_position[2] = {0,0};  // The location of the cursor in the matrix

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (!encoder_update_keymap(index, clockwise)) {
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
    }
    return true;  // FIXME: check which I should return
}
