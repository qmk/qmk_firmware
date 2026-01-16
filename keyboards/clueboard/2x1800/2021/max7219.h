/*
 * Copyright (c) 2021 Zach White <skullydazed@gmail.com>
 * Copyright (c) 2007 Eberhard Fahle
 *
 *    max7219.h - A library for controling Leds with a MAX7219/MAX7221
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
#pragma once

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

// Set defaults if they're not set
#ifndef MAX7219_LOAD
#    define MAX7219_LOAD B0
#endif

#ifndef MAX7219_CONTROLLERS
#    define MAX7219_CONTROLLERS 4
#endif

#ifndef MAX7219_LED_INTENSITY
#    define MAX7219_LED_INTENSITY 1
#endif

#ifndef MAX7219_SCROLL_TIME
#    define MAX7219_SCROLL_TIME 100
#endif

#ifndef MAX7219_BUFFER_MULTIPLIER
#    define MAX7219_BUFFER_MULTIPLIER 24
#endif

#if !defined(MAX7219_LED_TEST) && !defined(MAX7219_LED_ITERATE) && !defined(MAX7219_LED_DANCE) && !defined(MAX7219_LED_FONTTEST) && !defined(MAX7219_LED_CLUEBOARD) && !defined(MAX7219_LED_KONAMI) && !defined(MAX7219_LED_QMK_POWERED) && !defined(MAX7219_DRAWING_TOY_MODE) && !defined(MAX7219_LED_CUSTOM)
#    define MAX7219_QMK_POWERED
#endif

// Configure our MAX7219's
#define MAX_BYTES MAX7219_CONTROLLERS * 2
#define LED_COUNT MAX7219_CONTROLLERS * 64
#define MAX7219_BUFFER_SIZE MAX7219_CONTROLLERS*MAX7219_BUFFER_MULTIPLIER

// Opcodes for the MAX7219
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

// Datastructures
extern uint8_t max7219_led_a[8][MAX7219_BUFFER_SIZE];
extern bool max7219_led_scrolling;

// Functions
void max7219_write(int device_num, volatile uint8_t opcode, volatile uint8_t data);
void max7219_write_all(void);
void max7219_write_frame(void);
void max7219_clear_display(void);
void max7219_display_test(int device_num, bool enabled);
void max7219_init(void);
void max7219_message_sign(uint8_t message[][6], size_t message_len);
void max7219_message_sign_task(bool loop_message);
void max7219_set_decode_mode(int device_num, int mode);
void max7219_set_intensity(int device_num, int intensity);
void max7219_set_led(int row, int column, bool state);
void max7219_set_all_leds(uint8_t led_matrix[LED_COUNT]);
void max7219_set_scan_limit(int device_num, int limit);
void max7219_shutdown(int device_num, bool is_in_shutdown);
