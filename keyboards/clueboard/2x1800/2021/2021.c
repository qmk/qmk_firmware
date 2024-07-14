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

#include "quantum.h"
#include "max7219.h"
#include "font.h"

#ifndef DRAWING_TOY_MODE
static uint16_t led_frame_timer = 0;

void matrix_scan_kb(void) {
    if (timer_elapsed(led_frame_timer) > 100) {
        max7219_message_sign_task(true);
        led_frame_timer = timer_read();
    }

    matrix_scan_user();
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
    uint8_t message[MSG_FONTTEST_LEN][6] = MSG_FONTTEST;
    max7219_message_sign(message, MSG_FONTTEST_LEN);
#elif defined(MAX7219_LED_CLUEBOARD)
    uint8_t message[MSG_CLUEBOARD_LEN][6] = MSG_CLUEBOARD;
    max7219_message_sign(message, MSG_CLUEBOARD_LEN);
#elif defined(MAX7219_LED_KONAMI)
    uint8_t message[MSG_KONAMI_LEN][6] = MSG_KONAMI;
    max7219_message_sign(message, MSG_KONAMI_LEN);
#elif defined(MAX7219_LED_QMK_POWERED)
    uint8_t message[MSG_QMK_POWERED_LEN][6] = MSG_QMK_POWERED;
    max7219_message_sign(message, MSG_QMK_POWERED_LEN);
#elif defined(DRAWING_TOY_MODE)
    max7219_set_led(0, 0, true);
#endif

    matrix_init_user();
}

#define NUM_COLUMNS 8*MAX7219_CONTROLLERS
uint8_t led_position[2] = {0,0};  // The location of the cursor in the matrix

bool encoder_update_kb(uint8_t index, bool clockwise) {
    if (encoder_update_user(index, clockwise)) {
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
    return true;
}
