/* Copyright 2024 TAB
 * Copyright 2024 OWLab
 * Copyright 2024 Qwertykeys
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

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef DRIVER_ADDR_1
#    define IS31FL3761_I2C_ADDRESS_1 DRIVER_ADDR_1
#endif
#ifdef DRIVER_ADDR_2
#    define IS31FL3761_I2C_ADDRESS_2 DRIVER_ADDR_2
#endif
#ifdef DRIVER_ADDR_3
#    define IS31FL3761_I2C_ADDRESS_3 DRIVER_ADDR_3
#endif
#ifdef DRIVER_ADDR_4
#    define IS31FL3761_I2C_ADDRESS_4 DRIVER_ADDR_4
#endif
#ifdef ISSI_TIMEOUT
#    define IS31FL3761_I2C_TIMEOUT ISSI_TIMEOUT
#endif

#define is31_led is31fl3761_led_t
#define g_is31_leds g_is31fl3761_leds

// ========

#define IS31FL3761_COMMAND_PAGE_0 0x00
#define IS31FL3761_COMMAND_PAGE_1 0x01
#define IS31FL3761_COMMAND_PAGE_2 0x02

#define IS31FL3761_FUNCTION_REG_CONFIGURATION 0xA0
#define IS31FL3761_FUNCTION_REG_GLOBAL_CURRENT 0xA1
#define IS31FL3761_FUNCTION_REG_PULLDOWNUP 0xA3
#define IS31FL3761_FUNCTION_REG_PWM_FREQUENCY 0xA4
#define IS31FL3761_FUNCTION_REG_RESET 0xDF

#define IS31FL3761_REG_PWM_UPDATE 0xFD
#define IS31FL3761_REG_COMMAND 0xFE
#define IS31FL3761_REG_COMMAND_WRITE_LOCK 0xFF
#define IS31FL3761_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3761_I2C_ADDRESS_GND_GND 0x30
#define IS31FL3761_I2C_ADDRESS_GND_SCL 0x31
#define IS31FL3761_I2C_ADDRESS_GND_SDA 0x32
#define IS31FL3761_I2C_ADDRESS_GND_VCC 0x33

#define IS31FL3761_I2C_ADDRESS_SCL_GND 0x34
#define IS31FL3761_I2C_ADDRESS_SCL_SCL 0x35
#define IS31FL3761_I2C_ADDRESS_SCL_SDA 0x36
#define IS31FL3761_I2C_ADDRESS_SCL_VCC 0x37

#define IS31FL3761_I2C_ADDRESS_SDA_GND 0x38
#define IS31FL3761_I2C_ADDRESS_SDA_SCL 0x39
#define IS31FL3761_I2C_ADDRESS_SDA_SDA 0x3A
#define IS31FL3761_I2C_ADDRESS_SDA_VCC 0x3B

#define IS31FL3761_I2C_ADDRESS_VCC_GND 0x3C
#define IS31FL3761_I2C_ADDRESS_VCC_SCL 0x3D
#define IS31FL3761_I2C_ADDRESS_VCC_SDA 0x3E
#define IS31FL3761_I2C_ADDRESS_VCC_VCC 0x3F

#if defined(RGB_MATRIX_IS31FL3761)
#    define IS31FL3761_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3761_I2C_ADDRESS_4)
#    define IS31FL3761_DRIVER_COUNT 4
#elif defined(IS31FL3761_I2C_ADDRESS_3)
#    define IS31FL3761_DRIVER_COUNT 3
#elif defined(IS31FL3761_I2C_ADDRESS_2)
#    define IS31FL3761_DRIVER_COUNT 2
#elif defined(IS31FL3761_I2C_ADDRESS_1)
#    define IS31FL3761_DRIVER_COUNT 1
#endif

typedef struct is31fl3761_led_t {
    uint8_t  driver : 2;
    uint16_t r : 10;
    uint16_t g : 10;
    uint16_t b : 10;
} PACKED is31fl3761_led_t;

extern const is31fl3761_led_t PROGMEM g_is31fl3761_leds[IS31FL3761_LED_COUNT];

void is31fl3761_init_drivers(void);
void is31fl3761_init(uint8_t index);
void is31fl3761_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3761_select_page(uint8_t index, uint8_t page);

void is31fl3761_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void is31fl3761_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3761_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3761_update_pwm_buffers(uint8_t index);
void is31fl3761_update_led_control_registers(uint8_t index);
void is31fl3761_set_scaling_registers(const is31fl3761_led_t *pled, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3761_set_pwm_buffer(const is31fl3761_led_t *pled, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3761_flush(void);

// SWPDR SWx Pull down Resister Selection Bit
#define IS31FL3761_PDR_NO 0b000  // No pull up
#define IS31FL3761_PDR_2V6 0b001 // 2.6V
#define IS31FL3761_PDR_2V2 0b010 // 2.2V
#define IS31FL3761_PDR_1V9 0b011 // 1.9V
#define IS31FL3761_PDR_1V6 0b100 // 1.6V
#define IS31FL3761_PDR_1V2 0b101 // 1.2V
#define IS31FL3761_PDR_0V9 0b110 // 0.9V
#define IS31FL3761_PDR_GND 0b111 // GND

// CSPUR  CSy Pull up Resister Selection Bit
#define IS31FL3761_PUR_NO 0b000          // No pull up
#define IS31FL3761_PUR_VCC_SUB_2V3 0b001 // PVCC-2.3V
#define IS31FL3761_PUR_VCC_SUB_2V0 0b010 // PVCC-2.0V
#define IS31FL3761_PUR_VCC_SUB_1V7 0b011 // PVCC-1.7V
#define IS31FL3761_PUR_VCC_SUB_1V4 0b100 // PVCC-1.4V
#define IS31FL3761_PUR_VCC_SUB_1V1 0b101 // PVCC-1.1V
#define IS31FL3761_PUR_VCC_SUB_0V8 0b110 // PVCC-0.8V
#define IS31FL3761_PUR_VCC 0b111         // PVCC

// 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_26K_HZ 0b000   // 26kHz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_13k_HZ 0b001   // 13kHz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_6k5k_HZ 0b010  // 6.5kHz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_3k25_HZ 0b011  // 3.25kHz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_1k625_HZ 0b100 // 1.625kHz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_810_HZ 0b101   // 810Hz for 6+2-bit Mode
#define IS31FL3761_PWM_FREQUENCY_400_HZ 0b110   // 400Hz for 6+2-bit Mode

/** page 0 */
#define CS1_SW1 0x01
#define CS1_SW2 0x02
#define CS1_SW3 0x04
#define CS1_SW4 0x05
#define CS1_SW5 0x07
#define CS1_SW6 0x08
#define CS1_SW7 0x0A
#define CS1_SW8 0x0B
#define CS1_SW9 0x0D
#define CS1_SW10 0x0E
#define CS1_SW11 0x10
#define CS1_SW12 0x11

#define CS2_SW1 0x13
#define CS2_SW2 0x14
#define CS2_SW3 0x16
#define CS2_SW4 0x17
#define CS2_SW5 0x19
#define CS2_SW6 0x1A
#define CS2_SW7 0x1C
#define CS2_SW8 0x1D
#define CS2_SW9 0x1F
#define CS2_SW10 0x20
#define CS2_SW11 0x22
#define CS2_SW12 0x23

#define CS3_SW1 0x25
#define CS3_SW2 0x26
#define CS3_SW3 0x28
#define CS3_SW4 0x29
#define CS3_SW5 0x2B
#define CS3_SW6 0x2C
#define CS3_SW7 0x2E
#define CS3_SW8 0x2F
#define CS3_SW9 0x31
#define CS3_SW10 0x32
#define CS3_SW11 0x34
#define CS3_SW12 0x35

#define CS4_SW1 0x37
#define CS4_SW2 0x38
#define CS4_SW3 0x3A
#define CS4_SW4 0x3B
#define CS4_SW5 0x3D
#define CS4_SW6 0x3E
#define CS4_SW7 0x40
#define CS4_SW8 0x41
#define CS4_SW9 0x43
#define CS4_SW10 0x44
#define CS4_SW11 0x46
#define CS4_SW12 0x47

#define CS5_SW1 0x49
#define CS5_SW2 0x4A
#define CS5_SW3 0x4C
#define CS5_SW4 0x4D
#define CS5_SW5 0x4F
#define CS5_SW6 0x50
#define CS5_SW7 0x52
#define CS5_SW8 0x53
#define CS5_SW9 0x55
#define CS5_SW10 0x56
#define CS5_SW11 0x58
#define CS5_SW12 0x59

#define CS6_SW1 0x5B
#define CS6_SW2 0x5C
#define CS6_SW3 0x5E
#define CS6_SW4 0x5F
#define CS6_SW5 0x61
#define CS6_SW6 0x62
#define CS6_SW7 0x64
#define CS6_SW8 0x65
#define CS6_SW9 0x67
#define CS6_SW10 0x68
#define CS6_SW11 0x6A
#define CS6_SW12 0x6B

#define CS7_SW1 0x6D
#define CS7_SW2 0x6E
#define CS7_SW3 0x70
#define CS7_SW4 0x71
#define CS7_SW5 0x73
#define CS7_SW6 0x74
#define CS7_SW7 0x76
#define CS7_SW8 0x77
#define CS7_SW9 0x79
#define CS7_SW10 0x7A
#define CS7_SW11 0x7C
#define CS7_SW12 0x7D

#define CS8_SW1 0x7F
#define CS8_SW2 0x80
#define CS8_SW3 0x82
#define CS8_SW4 0x83
#define CS8_SW5 0x85
#define CS8_SW6 0x86
#define CS8_SW7 0x88
#define CS8_SW8 0x89
#define CS8_SW9 0x8B
#define CS8_SW10 0x8C
#define CS8_SW11 0x8E
#define CS8_SW12 0x8F

#define CS9_SW1 0x91
#define CS9_SW2 0x92
#define CS9_SW3 0x94
#define CS9_SW4 0x95
#define CS9_SW5 0x97
#define CS9_SW6 0x98
#define CS9_SW7 0x9A
#define CS9_SW8 0x9B
#define CS9_SW9 0x9D
#define CS9_SW10 0x9E
#define CS9_SW11 0xA0
#define CS9_SW12 0xA1

#define CS10_SW1 0xA3
#define CS10_SW2 0xA4
#define CS10_SW3 0xA6
#define CS10_SW4 0xA7
#define CS10_SW5 0xA9
#define CS10_SW6 0xAA
#define CS10_SW7 0xAC
#define CS10_SW8 0xAD
#define CS10_SW9 0xAF
#define CS10_SW10 0xB0
#define CS10_SW11 0xB2
#define CS10_SW12 0xB3

#define CS11_SW1 0xB5
#define CS11_SW2 0xB6
#define CS11_SW3 0xB8
#define CS11_SW4 0xB9
#define CS11_SW5 0xBB
#define CS11_SW6 0xBC
#define CS11_SW7 0xBE
#define CS11_SW8 0xBF
#define CS11_SW9 0xC1
#define CS11_SW10 0xC2
#define CS11_SW11 0xC4
#define CS11_SW12 0xC5

#define CS12_SW1 0xC7
#define CS12_SW2 0xC8
#define CS12_SW3 0xCA
#define CS12_SW4 0xCB
#define CS12_SW5 0xCD
#define CS12_SW6 0xCE
#define CS12_SW7 0xD0
#define CS12_SW8 0xD1
#define CS12_SW9 0xD3
#define CS12_SW10 0xD4
#define CS12_SW11 0xD6
#define CS12_SW12 0xD7

#define CS13_SW1 0xD9
#define CS13_SW2 0xDA
#define CS13_SW3 0xDC
#define CS13_SW4 0xDD
#define CS13_SW5 0xDF
#define CS13_SW6 0xE0
#define CS13_SW7 0xE2
#define CS13_SW8 0xE3
#define CS13_SW9 0xE5
#define CS13_SW10 0xE6
#define CS13_SW11 0xE8
#define CS13_SW12 0xE9

#define CS14_SW1 0xEB
#define CS14_SW2 0xEC
#define CS14_SW3 0xEE
#define CS14_SW4 0xEF
#define CS14_SW5 0xF1
#define CS14_SW6 0xF2
#define CS14_SW7 0xF4
#define CS14_SW8 0xF5
#define CS14_SW9 0xF7
#define CS14_SW10 0xF8
#define CS14_SW11 0xFA
#define CS14_SW12 0xFB

/** page 1 */
#define CS15_SW1 0x101
#define CS15_SW2 0x102
#define CS15_SW3 0x104
#define CS15_SW4 0x105
#define CS15_SW5 0x107
#define CS15_SW6 0x108
#define CS15_SW7 0x10A
#define CS15_SW8 0x10B
#define CS15_SW9 0x10D
#define CS15_SW10 0x10E
#define CS15_SW11 0x110
#define CS15_SW12 0x111

#define CS16_SW1 0x113
#define CS16_SW2 0x114
#define CS16_SW3 0x116
#define CS16_SW4 0x117
#define CS16_SW5 0x119
#define CS16_SW6 0x11A
#define CS16_SW7 0x11C
#define CS16_SW8 0x11D
#define CS16_SW9 0x11F
#define CS16_SW10 0x120
#define CS16_SW11 0x122
#define CS16_SW12 0x123

#define CS17_SW1 0x125
#define CS17_SW2 0x126
#define CS17_SW3 0x128
#define CS17_SW4 0x129
#define CS17_SW5 0x12B
#define CS17_SW6 0x12C
#define CS17_SW7 0x12E
#define CS17_SW8 0x12F
#define CS17_SW9 0x131
#define CS17_SW10 0x132
#define CS17_SW11 0x134
#define CS17_SW12 0x135

#define CS18_SW1 0x137
#define CS18_SW2 0x138
#define CS18_SW3 0x13A
#define CS18_SW4 0x13B
#define CS18_SW5 0x13D
#define CS18_SW6 0x13E
#define CS18_SW7 0x140
#define CS18_SW8 0x141
#define CS18_SW9 0x143
#define CS18_SW10 0x144
#define CS18_SW11 0x146
#define CS18_SW12 0x147

#define CS19_SW1 0x149
#define CS19_SW2 0x14A
#define CS19_SW3 0x14C
#define CS19_SW4 0x14D
#define CS19_SW5 0x14F
#define CS19_SW6 0x150
#define CS19_SW7 0x152
#define CS19_SW8 0x153
#define CS19_SW9 0x155
#define CS19_SW10 0x156
#define CS19_SW11 0x158
#define CS19_SW12 0x159

#define CS20_SW1 0x15B
#define CS20_SW2 0x15C
#define CS20_SW3 0x15E
#define CS20_SW4 0x15F
#define CS20_SW5 0x161
#define CS20_SW6 0x162
#define CS20_SW7 0x164
#define CS20_SW8 0x165
#define CS20_SW9 0x167
#define CS20_SW10 0x168
#define CS20_SW11 0x16A
#define CS20_SW12 0x16B

#define CS21_SW1 0x16D
#define CS21_SW2 0x16E
#define CS21_SW3 0x170
#define CS21_SW4 0x171
#define CS21_SW5 0x173
#define CS21_SW6 0x174
#define CS21_SW7 0x176
#define CS21_SW8 0x177
#define CS21_SW9 0x179
#define CS21_SW10 0x17A
#define CS21_SW11 0x17C
#define CS21_SW12 0x17D

#define CS22_SW1 0x17F
#define CS22_SW2 0x180
#define CS22_SW3 0x182
#define CS22_SW4 0x183
#define CS22_SW5 0x185
#define CS22_SW6 0x186
#define CS22_SW7 0x188
#define CS22_SW8 0x189
#define CS22_SW9 0x18B
#define CS22_SW10 0x18C
#define CS22_SW11 0x18E
#define CS22_SW12 0x18F

#define CS23_SW1 0x191
#define CS23_SW2 0x192
#define CS23_SW3 0x194
#define CS23_SW4 0x195
#define CS23_SW5 0x197
#define CS23_SW6 0x198
#define CS23_SW7 0x19A
#define CS23_SW8 0x19B
#define CS23_SW9 0x19D
#define CS23_SW10 0x19E
#define CS23_SW11 0x1A0
#define CS23_SW12 0x1A1

#define CS24_SW1 0x1A3
#define CS24_SW2 0x1A4
#define CS24_SW3 0x1A6
#define CS24_SW4 0x1A7
#define CS24_SW5 0x1A9
#define CS24_SW6 0x1AA
#define CS24_SW7 0x1AC
#define CS24_SW8 0x1AD
#define CS24_SW9 0x1AF
#define CS24_SW10 0x1B0
#define CS24_SW11 0x1B2
#define CS24_SW12 0x1B3

#define CS25_SW1 0x1B5
#define CS25_SW2 0x1B6
#define CS25_SW3 0x1B8
#define CS25_SW4 0x1B9
#define CS25_SW5 0x1BB
#define CS25_SW6 0x1BC
#define CS25_SW7 0x1BE
#define CS25_SW8 0x1BF
#define CS25_SW9 0x1C1
#define CS25_SW10 0x1C2
#define CS25_SW11 0x1C4
#define CS25_SW12 0x1C5

#define CS26_SW1 0x1C7
#define CS26_SW2 0x1C8
#define CS26_SW3 0x1CA
#define CS26_SW4 0x1CB
#define CS26_SW5 0x1CD
#define CS26_SW6 0x1CE
#define CS26_SW7 0x1D0
#define CS26_SW8 0x1D1
#define CS26_SW9 0x1D3
#define CS26_SW10 0x1D4
#define CS26_SW11 0x1D6
#define CS26_SW12 0x1D7

#define CS27_SW1 0x1D9
#define CS27_SW2 0x1DA
#define CS27_SW3 0x1DC
#define CS27_SW4 0x1DD
#define CS27_SW5 0x1DF
#define CS27_SW6 0x1E0
#define CS27_SW7 0x1E2
#define CS27_SW8 0x1E3
#define CS27_SW9 0x1E5
#define CS27_SW10 0x1E6
#define CS27_SW11 0x1E8
#define CS27_SW12 0x1E9

#define CS28_SW1 0x1EB
#define CS28_SW2 0x1EC
#define CS28_SW3 0x1EE
#define CS28_SW4 0x1EF
#define CS28_SW5 0x1F1
#define CS28_SW6 0x1F2
#define CS28_SW7 0x1F4
#define CS28_SW8 0x1F5
#define CS28_SW9 0x1F7
#define CS28_SW10 0x1F8
#define CS28_SW11 0x1FA
#define CS28_SW12 0x1FB

/** page 2 */
#define CS29_SW1 0x201
#define CS29_SW2 0x202
#define CS29_SW3 0x204
#define CS29_SW4 0x205
#define CS29_SW5 0x207
#define CS29_SW6 0x208
#define CS29_SW7 0x20A
#define CS29_SW8 0x20B
#define CS29_SW9 0x20D
#define CS29_SW10 0x20E
#define CS29_SW11 0x210
#define CS29_SW12 0x211

#define CS30_SW1 0x213
#define CS30_SW2 0x214
#define CS30_SW3 0x216
#define CS30_SW4 0x217
#define CS30_SW5 0x219
#define CS30_SW6 0x21A
#define CS30_SW7 0x21C
#define CS30_SW8 0x21D
#define CS30_SW9 0x21F
#define CS30_SW10 0x220
#define CS30_SW11 0x222
#define CS30_SW12 0x223

#define CS31_SW1 0x225
#define CS31_SW2 0x226
#define CS31_SW3 0x228
#define CS31_SW4 0x229
#define CS31_SW5 0x22B
#define CS31_SW6 0x22C
#define CS31_SW7 0x22E
#define CS31_SW8 0x22F
#define CS31_SW9 0x231
#define CS31_SW10 0x232
#define CS31_SW11 0x234
#define CS31_SW12 0x235

#define CS32_SW1 0x237
#define CS32_SW2 0x238
#define CS32_SW3 0x23A
#define CS32_SW4 0x23B
#define CS32_SW5 0x23D
#define CS32_SW6 0x23E
#define CS32_SW7 0x240
#define CS32_SW8 0x241
#define CS32_SW9 0x243
#define CS32_SW10 0x244
#define CS32_SW11 0x246
#define CS32_SW12 0x247

#define CS33_SW1 0x249
#define CS33_SW2 0x24A
#define CS33_SW3 0x24C
#define CS33_SW4 0x24D
#define CS33_SW5 0x24F
#define CS33_SW6 0x250
#define CS33_SW7 0x252
#define CS33_SW8 0x253
#define CS33_SW9 0x255
#define CS33_SW10 0x256
#define CS33_SW11 0x258
#define CS33_SW12 0x259
