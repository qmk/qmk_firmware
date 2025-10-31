/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
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

#define IS31FL3741_REG_INTERRUPT_MASK 0xF0
#define IS31FL3741_REG_INTERRUPT_STATUS 0xF1
#define IS31FL3741_REG_ID 0xFC

#define IS31FL3741_REG_COMMAND 0xFD

#define IS31FL3741_COMMAND_PWM_0 0x00
#define IS31FL3741_COMMAND_PWM_1 0x01
#define IS31FL3741_COMMAND_SCALING_0 0x02
#define IS31FL3741_COMMAND_SCALING_1 0x03
#define IS31FL3741_COMMAND_FUNCTION 0x04

#define IS31FL3741_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3741_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3741_FUNCTION_REG_PULLDOWNUP 0x02
#define IS31FL3741_FUNCTION_REG_PWM_FREQUENCY 0x36
#define IS31FL3741_FUNCTION_REG_RESET 0x3F

#define IS31FL3741_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3741_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3741_I2C_ADDRESS_GND 0x30
#define IS31FL3741_I2C_ADDRESS_SCL 0x31
#define IS31FL3741_I2C_ADDRESS_SDA 0x32
#define IS31FL3741_I2C_ADDRESS_VCC 0x33

#if defined(RGB_MATRIX_IS31FL3741)
#    define IS31FL3741_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3741_I2C_ADDRESS_4)
#    define IS31FL3741_DRIVER_COUNT 4
#elif defined(IS31FL3741_I2C_ADDRESS_3)
#    define IS31FL3741_DRIVER_COUNT 3
#elif defined(IS31FL3741_I2C_ADDRESS_2)
#    define IS31FL3741_DRIVER_COUNT 2
#elif defined(IS31FL3741_I2C_ADDRESS_1)
#    define IS31FL3741_DRIVER_COUNT 1
#endif

typedef struct is31fl3741_led_t {
    uint8_t  driver : 2;
    uint16_t r : 9;
    uint16_t g : 9;
    uint16_t b : 9;
} PACKED is31fl3741_led_t;

extern const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT];

void is31fl3741_init_drivers(void);
void is31fl3741_init(uint8_t index);
void is31fl3741_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3741_select_page(uint8_t index, uint8_t page);

void is31fl3741_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void is31fl3741_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3741_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3741_update_pwm_buffers(uint8_t index);
void is31fl3741_update_led_control_registers(uint8_t index);
void is31fl3741_set_scaling_registers(const is31fl3741_led_t *pled, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3741_set_pwm_buffer(const is31fl3741_led_t *pled, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3741_flush(void);

#define IS31FL3741_PDR_0_OHM 0b000   // No pull-down resistor
#define IS31FL3741_PDR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3741_PDR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3741_PDR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3741_PDR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3741_PDR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3741_PDR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3741_PDR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3741_PUR_0_OHM 0b000   // No pull-up resistor
#define IS31FL3741_PUR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3741_PUR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3741_PUR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3741_PUR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3741_PUR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3741_PUR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3741_PUR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3741_PWM_FREQUENCY_29K_HZ 0b0000
#define IS31FL3741_PWM_FREQUENCY_3K6_HZ 0b0011
#define IS31FL3741_PWM_FREQUENCY_1K8_HZ 0b0111
#define IS31FL3741_PWM_FREQUENCY_900_HZ 0b1011

#define SW1_CS1 0x00
#define SW1_CS2 0x01
#define SW1_CS3 0x02
#define SW1_CS4 0x03
#define SW1_CS5 0x04
#define SW1_CS6 0x05
#define SW1_CS7 0x06
#define SW1_CS8 0x07
#define SW1_CS9 0x08
#define SW1_CS10 0x09
#define SW1_CS11 0x0A
#define SW1_CS12 0x0B
#define SW1_CS13 0x0C
#define SW1_CS14 0x0D
#define SW1_CS15 0x0E
#define SW1_CS16 0x0F
#define SW1_CS17 0x10
#define SW1_CS18 0x11
#define SW1_CS19 0x12
#define SW1_CS20 0x13
#define SW1_CS21 0x14
#define SW1_CS22 0x15
#define SW1_CS23 0x16
#define SW1_CS24 0x17
#define SW1_CS25 0x18
#define SW1_CS26 0x19
#define SW1_CS27 0x1A
#define SW1_CS28 0x1B
#define SW1_CS29 0x1C
#define SW1_CS30 0x1D

#define SW2_CS1 0x1E
#define SW2_CS2 0x1F
#define SW2_CS3 0x20
#define SW2_CS4 0x21
#define SW2_CS5 0x22
#define SW2_CS6 0x23
#define SW2_CS7 0x24
#define SW2_CS8 0x25
#define SW2_CS9 0x26
#define SW2_CS10 0x27
#define SW2_CS11 0x28
#define SW2_CS12 0x29
#define SW2_CS13 0x2A
#define SW2_CS14 0x2B
#define SW2_CS15 0x2C
#define SW2_CS16 0x2D
#define SW2_CS17 0x2E
#define SW2_CS18 0x2F
#define SW2_CS19 0x30
#define SW2_CS20 0x31
#define SW2_CS21 0x32
#define SW2_CS22 0x33
#define SW2_CS23 0x34
#define SW2_CS24 0x35
#define SW2_CS25 0x36
#define SW2_CS26 0x37
#define SW2_CS27 0x38
#define SW2_CS28 0x39
#define SW2_CS29 0x3A
#define SW2_CS30 0x3B

#define SW3_CS1 0x3C
#define SW3_CS2 0x3D
#define SW3_CS3 0x3E
#define SW3_CS4 0x3F
#define SW3_CS5 0x40
#define SW3_CS6 0x41
#define SW3_CS7 0x42
#define SW3_CS8 0x43
#define SW3_CS9 0x44
#define SW3_CS10 0x45
#define SW3_CS11 0x46
#define SW3_CS12 0x47
#define SW3_CS13 0x48
#define SW3_CS14 0x49
#define SW3_CS15 0x4A
#define SW3_CS16 0x4B
#define SW3_CS17 0x4C
#define SW3_CS18 0x4D
#define SW3_CS19 0x4E
#define SW3_CS20 0x4F
#define SW3_CS21 0x50
#define SW3_CS22 0x51
#define SW3_CS23 0x52
#define SW3_CS24 0x53
#define SW3_CS25 0x54
#define SW3_CS26 0x55
#define SW3_CS27 0x56
#define SW3_CS28 0x57
#define SW3_CS29 0x58
#define SW3_CS30 0x59

#define SW4_CS1 0x5A
#define SW4_CS2 0x5B
#define SW4_CS3 0x5C
#define SW4_CS4 0x5D
#define SW4_CS5 0x5E
#define SW4_CS6 0x5F
#define SW4_CS7 0x60
#define SW4_CS8 0x61
#define SW4_CS9 0x62
#define SW4_CS10 0x63
#define SW4_CS11 0x64
#define SW4_CS12 0x65
#define SW4_CS13 0x66
#define SW4_CS14 0x67
#define SW4_CS15 0x68
#define SW4_CS16 0x69
#define SW4_CS17 0x6A
#define SW4_CS18 0x6B
#define SW4_CS19 0x6C
#define SW4_CS20 0x6D
#define SW4_CS21 0x6E
#define SW4_CS22 0x6F
#define SW4_CS23 0x70
#define SW4_CS24 0x71
#define SW4_CS25 0x72
#define SW4_CS26 0x73
#define SW4_CS27 0x74
#define SW4_CS28 0x75
#define SW4_CS29 0x76
#define SW4_CS30 0x77

#define SW5_CS1 0x78
#define SW5_CS2 0x79
#define SW5_CS3 0x7A
#define SW5_CS4 0x7B
#define SW5_CS5 0x7C
#define SW5_CS6 0x7D
#define SW5_CS7 0x7E
#define SW5_CS8 0x7F
#define SW5_CS9 0x80
#define SW5_CS10 0x81
#define SW5_CS11 0x82
#define SW5_CS12 0x83
#define SW5_CS13 0x84
#define SW5_CS14 0x85
#define SW5_CS15 0x86
#define SW5_CS16 0x87
#define SW5_CS17 0x88
#define SW5_CS18 0x89
#define SW5_CS19 0x8A
#define SW5_CS20 0x8B
#define SW5_CS21 0x8C
#define SW5_CS22 0x8D
#define SW5_CS23 0x8E
#define SW5_CS24 0x8F
#define SW5_CS25 0x90
#define SW5_CS26 0x91
#define SW5_CS27 0x92
#define SW5_CS28 0x93
#define SW5_CS29 0x94
#define SW5_CS30 0x95

#define SW6_CS1 0x96
#define SW6_CS2 0x97
#define SW6_CS3 0x98
#define SW6_CS4 0x99
#define SW6_CS5 0x9A
#define SW6_CS6 0x9B
#define SW6_CS7 0x9C
#define SW6_CS8 0x9D
#define SW6_CS9 0x9E
#define SW6_CS10 0x9F
#define SW6_CS11 0xA0
#define SW6_CS12 0xA1
#define SW6_CS13 0xA2
#define SW6_CS14 0xA3
#define SW6_CS15 0xA4
#define SW6_CS16 0xA5
#define SW6_CS17 0xA6
#define SW6_CS18 0xA7
#define SW6_CS19 0xA8
#define SW6_CS20 0xA9
#define SW6_CS21 0xAA
#define SW6_CS22 0xAB
#define SW6_CS23 0xAC
#define SW6_CS24 0xAD
#define SW6_CS25 0xAE
#define SW6_CS26 0xAF
#define SW6_CS27 0xB0
#define SW6_CS28 0xB1
#define SW6_CS29 0xB2
#define SW6_CS30 0xB3

#define SW7_CS1 0x100
#define SW7_CS2 0x101
#define SW7_CS3 0x102
#define SW7_CS4 0x103
#define SW7_CS5 0x104
#define SW7_CS6 0x105
#define SW7_CS7 0x106
#define SW7_CS8 0x107
#define SW7_CS9 0x108
#define SW7_CS10 0x109
#define SW7_CS11 0x10A
#define SW7_CS12 0x10B
#define SW7_CS13 0x10C
#define SW7_CS14 0x10D
#define SW7_CS15 0x10E
#define SW7_CS16 0x10F
#define SW7_CS17 0x110
#define SW7_CS18 0x111
#define SW7_CS19 0x112
#define SW7_CS20 0x113
#define SW7_CS21 0x114
#define SW7_CS22 0x115
#define SW7_CS23 0x116
#define SW7_CS24 0x117
#define SW7_CS25 0x118
#define SW7_CS26 0x119
#define SW7_CS27 0x11A
#define SW7_CS28 0x11B
#define SW7_CS29 0x11C
#define SW7_CS30 0x11D

#define SW8_CS1 0x11E
#define SW8_CS2 0x11F
#define SW8_CS3 0x120
#define SW8_CS4 0x121
#define SW8_CS5 0x122
#define SW8_CS6 0x123
#define SW8_CS7 0x124
#define SW8_CS8 0x125
#define SW8_CS9 0x126
#define SW8_CS10 0x127
#define SW8_CS11 0x128
#define SW8_CS12 0x129
#define SW8_CS13 0x12A
#define SW8_CS14 0x12B
#define SW8_CS15 0x12C
#define SW8_CS16 0x12D
#define SW8_CS17 0x12E
#define SW8_CS18 0x12F
#define SW8_CS19 0x130
#define SW8_CS20 0x131
#define SW8_CS21 0x132
#define SW8_CS22 0x133
#define SW8_CS23 0x134
#define SW8_CS24 0x135
#define SW8_CS25 0x136
#define SW8_CS26 0x137
#define SW8_CS27 0x138
#define SW8_CS28 0x139
#define SW8_CS29 0x13A
#define SW8_CS30 0x13B

#define SW9_CS1 0x13C
#define SW9_CS2 0x13D
#define SW9_CS3 0x13E
#define SW9_CS4 0x13F
#define SW9_CS5 0x140
#define SW9_CS6 0x141
#define SW9_CS7 0x142
#define SW9_CS8 0x143
#define SW9_CS9 0x144
#define SW9_CS10 0x145
#define SW9_CS11 0x146
#define SW9_CS12 0x147
#define SW9_CS13 0x148
#define SW9_CS14 0x149
#define SW9_CS15 0x14A
#define SW9_CS16 0x14B
#define SW9_CS17 0x14C
#define SW9_CS18 0x14D
#define SW9_CS19 0x14E
#define SW9_CS20 0x14F
#define SW9_CS21 0x150
#define SW9_CS22 0x151
#define SW9_CS23 0x152
#define SW9_CS24 0x153
#define SW9_CS25 0x154
#define SW9_CS26 0x155
#define SW9_CS27 0x156
#define SW9_CS28 0x157
#define SW9_CS29 0x158
#define SW9_CS30 0x159

#define SW1_CS31 0x15A
#define SW1_CS32 0x15B
#define SW1_CS33 0x15C
#define SW1_CS34 0x15D
#define SW1_CS35 0x15E
#define SW1_CS36 0x15F
#define SW1_CS37 0x160
#define SW1_CS38 0x161
#define SW1_CS39 0x162

#define SW2_CS31 0x163
#define SW2_CS32 0x164
#define SW2_CS33 0x165
#define SW2_CS34 0x166
#define SW2_CS35 0x167
#define SW2_CS36 0x168
#define SW2_CS37 0x169
#define SW2_CS38 0x16A
#define SW2_CS39 0x16B

#define SW3_CS31 0x16C
#define SW3_CS32 0x16D
#define SW3_CS33 0x16E
#define SW3_CS34 0x16F
#define SW3_CS35 0x170
#define SW3_CS36 0x171
#define SW3_CS37 0x172
#define SW3_CS38 0x173
#define SW3_CS39 0x174

#define SW4_CS31 0x175
#define SW4_CS32 0x176
#define SW4_CS33 0x177
#define SW4_CS34 0x178
#define SW4_CS35 0x179
#define SW4_CS36 0x17A
#define SW4_CS37 0x17B
#define SW4_CS38 0x17C
#define SW4_CS39 0x17D

#define SW5_CS31 0x17E
#define SW5_CS32 0x17F
#define SW5_CS33 0x180
#define SW5_CS34 0x181
#define SW5_CS35 0x182
#define SW5_CS36 0x183
#define SW5_CS37 0x184
#define SW5_CS38 0x185
#define SW5_CS39 0x186

#define SW6_CS31 0x187
#define SW6_CS32 0x188
#define SW6_CS33 0x189
#define SW6_CS34 0x18A
#define SW6_CS35 0x18B
#define SW6_CS36 0x18C
#define SW6_CS37 0x18D
#define SW6_CS38 0x18E
#define SW6_CS39 0x18F

#define SW7_CS31 0x190
#define SW7_CS32 0x191
#define SW7_CS33 0x192
#define SW7_CS34 0x193
#define SW7_CS35 0x194
#define SW7_CS36 0x195
#define SW7_CS37 0x196
#define SW7_CS38 0x197
#define SW7_CS39 0x198

#define SW8_CS31 0x199
#define SW8_CS32 0x19A
#define SW8_CS33 0x19B
#define SW8_CS34 0x19C
#define SW8_CS35 0x19D
#define SW8_CS36 0x19E
#define SW8_CS37 0x19F
#define SW8_CS38 0x1A0
#define SW8_CS39 0x1A1

#define SW9_CS31 0x1A2
#define SW9_CS32 0x1A3
#define SW9_CS33 0x1A4
#define SW9_CS34 0x1A5
#define SW9_CS35 0x1A6
#define SW9_CS36 0x1A7
#define SW9_CS37 0x1A8
#define SW9_CS38 0x1A9
#define SW9_CS39 0x1AA
