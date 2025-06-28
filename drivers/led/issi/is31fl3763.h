/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
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
#include "progmem.h"
#include "util.h"

typedef struct is31_led {
    uint8_t  driver;
    uint16_t r;
    uint16_t g;
    uint16_t b;
} __attribute__((packed)) is31_led;

extern const is31_led PROGMEM g_is31_leds[RGB_MATRIX_LED_COUNT];

void is31fl3763_init_drivers(void);
void is31fl3763_init(uint8_t index);
void is31fl3763_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3763_select_page(uint8_t index, uint8_t page);

void is31fl3763_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void is31fl3763_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3763_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3763_update_pwm_buffers(uint8_t index);
void is31fl3763_update_led_control_registers(uint8_t index);

void is31fl3763_flush(void);

#define PUR_0R 0x00   // No PUR resistor
#define PUR_05KR 0x02 // 0.5k Ohm resistor in t_NOL
#define PUR_3KR 0x03  // 3.0k Ohm resistor on all the time
#define PUR_4KR 0x04  // 4.0k Ohm resistor on all the time
#define PUR_8KR 0x05  // 8.0k Ohm resistor on all the time
#define PUR_16KR 0x06 // 16k Ohm resistor on all the time
#define PUR_32KR 0x07 // 32k Ohm resistor in t_NOL

// SW1
#define A_1 0x01
#define B_1 0x13
#define C_1 0x25
#define D_1 0x37
#define E_1 0x49
#define F_1 0x5B
#define G_1 0x6D
#define H_1 0x7F
#define I_1 0x91
#define J_1 0xA3
#define K_1 0xB5
#define L_1 0xC7
#define M_1 0xD9
#define N_1 0xEB
#define O_1 0x101
#define P_1 0x113
#define Q_1 0x125
#define R_1 0x137

// SW2
#define A_2 0x02
#define C_2 0x26
#define F_2 0x5C
#define I_2 0x92
#define L_2 0xC8
#define B_2 0x14
#define E_2 0x4A
#define H_2 0x80
#define K_2 0xB6
#define N_2 0xEC
#define D_2 0x38
#define G_2 0x6E
#define J_2 0xA4
#define M_2 0xDA
#define O_2 0x102
#define P_2 0x114
#define Q_2 0x126
#define R_2 0x138

// SW3
#define C_3 0x28
#define F_3 0x5E
#define I_3 0x94
#define L_3 0xCA
#define B_3 0x16
#define E_3 0x4C
#define H_3 0x82
#define K_3 0xB8
#define N_3 0xEE
#define A_3 0x04
#define D_3 0x3A
#define G_3 0x70
#define J_3 0xA6
#define M_3 0xDC
#define O_3 0x104
#define P_3 0x116
#define Q_3 0x128
#define R_3 0x13A

// SW4
#define C_4 0x29
#define F_4 0x5F
#define I_4 0x95
#define L_4 0xCB
#define B_4 0x17
#define E_4 0x4D
#define H_4 0x83
#define K_4 0xB9
#define N_4 0xEF
#define A_4 0x05
#define D_4 0x3B
#define G_4 0x71
#define J_4 0xA7
#define M_4 0xDD
#define O_4 0x105
#define P_4 0x117
#define Q_4 0x129
#define R_4 0x13B

// SW5
#define C_5 0x2B
#define F_5 0x61
#define I_5 0x97
#define L_5 0xCD
#define B_5 0x19
#define E_5 0x4F
#define H_5 0x85
#define K_5 0xBB
#define N_5 0xF1
#define A_5 0x07
#define D_5 0x3D
#define G_5 0x73
#define J_5 0xA9
#define M_5 0xDF
#define O_5 0x107
#define P_5 0x119
#define Q_5 0x12B
#define R_5 0x13D

// SW6
#define C_6 0x2C
#define F_6 0x62
#define I_6 0x98
#define L_6 0xCE
#define B_6 0x1A
#define E_6 0x50
#define H_6 0x86
#define K_6 0xBC
#define N_6 0xF2
#define A_6 0x08
#define D_6 0x3E
#define G_6 0x74
#define J_6 0xAA
#define M_6 0xE0
#define O_6 0x108
#define P_6 0x11A
#define Q_6 0x12C
#define R_6 0x13E

// SW7
#define C_7 0x2E
#define F_7 0x64
#define I_7 0x9A
#define L_7 0xD0
#define B_7 0x1C
#define E_7 0x52
#define H_7 0x88
#define K_7 0xBE
#define N_7 0xF4
#define A_7 0x0A
#define D_7 0x40
#define G_7 0x76
#define J_7 0xAC
#define M_7 0xE2
#define O_7 0x10A
#define P_7 0x11C
#define Q_7 0x12E
#define R_7 0x140

// SW8
#define C_8 0x2F
#define F_8 0x65
#define I_8 0x9B
#define L_8 0xD1
#define B_8 0x1D
#define E_8 0x53
#define H_8 0x89
#define K_8 0xBF
#define N_8 0xF5
#define A_8 0x0B
#define D_8 0x41
#define G_8 0x77
#define J_8 0xAD
#define M_8 0xE3
#define O_8 0x10B
#define P_8 0x11D
#define Q_8 0x12F
#define R_8 0x141

// SW9
#define C_9 0x31
#define F_9 0x67
#define I_9 0x9D
#define L_9 0xD3
#define B_9 0x1F
#define E_9 0x55
#define H_9 0x8B
#define K_9 0xC1
#define N_9 0xF7
#define A_9 0x0D
#define D_9 0x43
#define G_9 0x79
#define J_9 0xAF
#define M_9 0xE5
#define O_9 0x10D
#define P_9 0x11F
#define Q_9 0x131
#define R_9 0x143

// SW10
#define C_10 0x32
#define F_10 0x68
#define I_10 0x9E
#define L_10 0xD4
#define B_10 0x20
#define E_10 0x56
#define H_10 0x8C
#define K_10 0xC2
#define N_10 0xF8
#define A_10 0x0E
#define D_10 0x44
#define G_10 0x7A
#define J_10 0xB0
#define M_10 0xE6
#define O_10 0x10E
#define P_10 0x120
#define Q_10 0x132
#define R_10 0x144

// SW11
#define C_11 0x34
#define F_11 0x6A
#define I_11 0xA0
#define L_11 0xD6
#define B_11 0x22
#define E_11 0x58
#define H_11 0x8E
#define K_11 0xC4
#define N_11 0xFA
#define A_11 0x10
#define D_11 0x46
#define G_11 0x7C
#define J_11 0xB2
#define M_11 0xE8
#define O_11 0x110
#define P_11 0x122
#define Q_11 0x134
#define R_11 0x146

// SW12
#define C_12 0x35
#define F_12 0x6B
#define I_12 0xA1
#define L_12 0xD7
#define B_12 0x23
#define E_12 0x59
#define H_12 0x8F
#define K_12 0xC5
#define N_12 0xFB
#define A_12 0x11
#define D_12 0x47
#define G_12 0x7D
#define J_12 0xB3
#define M_12 0xE9
#define O_12 0x111
#define P_12 0x123
#define Q_12 0x135
#define R_12 0x147
