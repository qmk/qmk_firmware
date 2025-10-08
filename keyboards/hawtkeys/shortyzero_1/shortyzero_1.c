// Copyright 2025 Hawtkeys
// SPDX-License-Identifier: GPL-2.0-or-later

#include "shortyzero_1.h"
#include "hal.h" 

#define PIN_7SD_A 15
#define PIN_7SD_B 16
#define PIN_7SD_C 19
#define PIN_7SD_D 18
#define PIN_7SD_E 17
#define PIN_7SD_F 14
#define PIN_7SD_G 13

static const bool seven_segment_digits[10][7] = {
    {1, 1, 1, 1, 1, 1, 0}, // 0
    {0, 1, 1, 0, 0, 0, 0}, // 1
    {1, 1, 0, 1, 1, 0, 1}, // 2
    {1, 1, 1, 1, 0, 0, 1}, // 3
    {0, 1, 1, 0, 0, 1, 1}, // 4
    {1, 0, 1, 1, 0, 1, 1}, // 5
    {1, 0, 1, 1, 1, 1, 1}, // 6
    {1, 1, 1, 0, 0, 0, 0}, // 7
    {1, 1, 1, 1, 1, 1, 1}, // 8
    {1, 1, 1, 1, 0, 1, 1}  // 9
};

static const uint8_t seven_segment_pins[7] = {
    PIN_7SD_A, PIN_7SD_B, PIN_7SD_C, PIN_7SD_D, 
    PIN_7SD_E, PIN_7SD_F, PIN_7SD_G
};

void init_seven_segment(void) {
    for (int i = 0; i < 7; i++) {
        palSetPadMode(IOPORT1, seven_segment_pins[i], PAL_MODE_OUTPUT_PUSHPULL);
        palClearPad(IOPORT1, seven_segment_pins[i]);
    }
}

void display_seven_segment_digit(uint8_t digit) {
    if (digit > 9) return; 
    
    for (int i = 0; i < 7; i++) {
        if (seven_segment_digits[digit][i]) {
            palSetPad(IOPORT1, seven_segment_pins[i]);   // Turn on segment (HIGH for common cathode)
        } else {
            palClearPad(IOPORT1, seven_segment_pins[i]); // Turn off segment (LOW for common cathode)
        }
    }
}

void clear_seven_segment(void) {
    for (int i = 0; i < 7; i++) {
        palClearPad(IOPORT1, seven_segment_pins[i]);
    }
}
