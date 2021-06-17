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
#include "quantum.h"
#include "spi_master.h"

// Configure our MAX7219's
#define MAX_BYTES MAX7219_CONTROLLERS * 2
#define LED_COUNT MAX7219_CONTROLLERS * 64

// Opcodes for the MAX7219
#define OP_NOOP   0
#define OP_DIGIT0 1
#define OP_DIGIT1 2
#define OP_DIGIT2 3
#define OP_DIGIT3 4
#define OP_DIGIT4 5
#define OP_DIGIT5 6
#define OP_DIGIT6 7
#define OP_DIGIT7 8
#define OP_DECODEMODE  9
#define OP_INTENSITY   10
#define OP_SCANLIMIT   11
#define OP_SHUTDOWN    12
#define OP_DISPLAYTEST 15

// Datastructures
uint8_t max7219_spidata[MAX_BYTES];
uint8_t max7219_led_a[8][MAX7219_CONTROLLERS];

// Functions
void shift_out(uint8_t val);
void max7219_write(int device_num, volatile uint8_t opcode, volatile uint8_t data);
void max7219_write_all(void);
void max7219_write_frame(void);
void max7219_clear_display(int device_num);
void max7219_display_test(int device_num, bool enabled);
void max7219_init(void);
void max7219_set_decode_mode(int device_num, int mode);
void max7219_set_intensity(int device_num, int intensity);
void max7219_set_led(int row, int column, bool state);
void max7219_set_all_leds(uint8_t led_matrix[LED_COUNT]);
void max7219_set_row(int device_num, int row, unsigned char value);
void max7219_set_col(int device_num, int col, unsigned char value);
void max7219_set_scan_limit(int device_num, int limit);
void max7219_shutdown(int device_num, bool is_in_shutdown);

