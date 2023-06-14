/* Copyright 2018 Jason Williams (Wilba)
 * Copyright 2021 Doni Crosby
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

#pragma once

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "progmem.h"

// Simple interface option.
// If these aren't defined, just define them to make it compile

#ifndef DRIVER_COUNT
#    define DRIVER_COUNT 2
#endif

#ifndef RGB_MATRIX_LED_COUNT
#    define RGB_MATRIX_LED_COUNT 96
#endif

typedef struct is31_led {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} __attribute__((packed)) is31_led;

extern const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT];

void IS31FL3736_init(uint8_t addr);
void IS31FL3736_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void IS31FL3736_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void IS31FL3736_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void IS31FL3736_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void IS31FL3736_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

void IS31FL3736_mono_set_brightness(int index, uint8_t value);
void IS31FL3736_mono_set_brightness_all(uint8_t value);
void IS31FL3736_mono_set_led_control_register(uint8_t index, bool enabled);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void IS31FL3736_update_pwm_buffers(uint8_t addr, uint8_t index);
void IS31FL3736_update_led_control_registers(uint8_t addr, uint8_t index);

#define PUR_0R 0x00   // No PUR resistor
#define PUR_05KR 0x01 // 0.5k Ohm resistor
#define PUR_1KR 0x02  // 1.0k Ohm resistor
#define PUR_2KR 0x03  // 2.0k Ohm resistor
#define PUR_4KR 0x04  // 4.0k Ohm resistor
#define PUR_8KR 0x05  // 8.0k Ohm resistor
#define PUR_16KR 0x06 // 16k Ohm resistor
#define PUR_32KR 0x07 // 32k Ohm resistor

#define A_1 0x00
#define A_2 0x02
#define A_3 0x04
#define A_4 0x06
#define A_5 0x08
#define A_6 0x0A
#define A_7 0x0C
#define A_8 0x0E

#define B_1 0x10
#define B_2 0x12
#define B_3 0x14
#define B_4 0x16
#define B_5 0x18
#define B_6 0x1A
#define B_7 0x1C
#define B_8 0x1E

#define C_1 0x20
#define C_2 0x22
#define C_3 0x24
#define C_4 0x26
#define C_5 0x28
#define C_6 0x2A
#define C_7 0x2C
#define C_8 0x2E

#define D_1 0x30
#define D_2 0x32
#define D_3 0x34
#define D_4 0x36
#define D_5 0x38
#define D_6 0x3A
#define D_7 0x3C
#define D_8 0x3E

#define E_1 0x40
#define E_2 0x42
#define E_3 0x44
#define E_4 0x46
#define E_5 0x48
#define E_6 0x4A
#define E_7 0x4C
#define E_8 0x4E

#define F_1 0x50
#define F_2 0x52
#define F_3 0x54
#define F_4 0x56
#define F_5 0x58
#define F_6 0x5A
#define F_7 0x5C
#define F_8 0x5E

#define G_1 0x60
#define G_2 0x62
#define G_3 0x64
#define G_4 0x66
#define G_5 0x68
#define G_6 0x6A
#define G_7 0x6C
#define G_8 0x6E

#define H_1 0x70
#define H_2 0x72
#define H_3 0x74
#define H_4 0x76
#define H_5 0x78
#define H_6 0x7A
#define H_7 0x7C
#define H_8 0x7E

#define I_1 0x80
#define I_2 0x82
#define I_3 0x84
#define I_4 0x86
#define I_5 0x88
#define I_6 0x8A
#define I_7 0x8C
#define I_8 0x8E

#define J_1 0x90
#define J_2 0x92
#define J_3 0x94
#define J_4 0x96
#define J_5 0x98
#define J_6 0x9A
#define J_7 0x9C
#define J_8 0x9E

#define K_1 0xA0
#define K_2 0xA2
#define K_3 0xA4
#define K_4 0xA6
#define K_5 0xA8
#define K_6 0xAA
#define K_7 0xAC
#define K_8 0xAE

#define L_1 0xB0
#define L_2 0xB2
#define L_3 0xB4
#define L_4 0xB6
#define L_5 0xB8
#define L_6 0xBA
#define L_7 0xBC
#define L_8 0xBE
