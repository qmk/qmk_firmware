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

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef ISSI_TIMEOUT
#    define IS31FL3741_I2C_TIMEOUT ISSI_TIMEOUT
#endif
#ifdef ISSI_PERSISTENCE
#    define IS31FL3741_I2C_PERSISTENCE ISSI_PERSISTENCE
#endif
#ifdef ISSI_CONFIGURATION
#    define IS31FL3741_CONFIGURATION ISSI_CONFIGURATION
#endif
#ifdef ISSI_SWPULLUP
#    define IS31FL3741_SW_PULLUP ISSI_SWPULLUP
#endif
#ifdef ISSI_CSPULLUP
#    define IS31FL3741_CS_PULLDOWN ISSI_CSPULLUP
#endif
#ifdef ISSI_GLOBALCURRENT
#    define IS31FL3741_GLOBALCURRENT ISSI_GLOBALCURRENT
#endif

#define PUR_0R IS31FL3741_PUR_0_OHM
#define PUR_05KR IS31FL3741_PUR_0K5_OHM
#define PUR_1KR IS31FL3741_PUR_1K_OHM
#define PUR_2KR IS31FL3741_PUR_2K_OHM
#define PUR_4KR IS31FL3741_PUR_4K_OHM
#define PUR_8KR IS31FL3741_PUR_8K_OHM
#define PUR_16KR IS31FL3741_PUR_16K_OHM
#define PUR_32KR IS31FL3741_PUR_32K_OHM
// ========

#define IS31FL3741_I2C_ADDRESS_GND 0x30
#define IS31FL3741_I2C_ADDRESS_SCL 0x31
#define IS31FL3741_I2C_ADDRESS_SDA 0x32
#define IS31FL3741_I2C_ADDRESS_VCC 0x33

#if defined(LED_MATRIX_IS31FL3741)
#    define IS31FL3741_LED_COUNT LED_MATRIX_LED_COUNT
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
    uint16_t v : 9;
} PACKED is31fl3741_led_t;

extern const is31fl3741_led_t PROGMEM g_is31fl3741_leds[IS31FL3741_LED_COUNT];

void is31fl3741_init_drivers(void);
void is31fl3741_init(uint8_t addr);
void is31fl3741_write_register(uint8_t addr, uint8_t reg, uint8_t data);
bool is31fl3741_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void is31fl3741_set_value(int index, uint8_t value);
void is31fl3741_set_value_all(uint8_t value);

void is31fl3741_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3741_update_pwm_buffers(uint8_t addr, uint8_t index);
void is31fl3741_update_led_control_registers(uint8_t addr, uint8_t index);
void is31fl3741_set_scaling_registers(const is31fl3741_led_t *pled, uint8_t value);

void is31fl3741_set_pwm_buffer(const is31fl3741_led *pled, uint8_t value);

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

#define CS1_SW1 0x00
#define CS2_SW1 0x01
#define CS3_SW1 0x02
#define CS4_SW1 0x03
#define CS5_SW1 0x04
#define CS6_SW1 0x05
#define CS7_SW1 0x06
#define CS8_SW1 0x07
#define CS9_SW1 0x08
#define CS10_SW1 0x09
#define CS11_SW1 0x0A
#define CS12_SW1 0x0B
#define CS13_SW1 0x0C
#define CS14_SW1 0x0D
#define CS15_SW1 0x0E
#define CS16_SW1 0x0F
#define CS17_SW1 0x10
#define CS18_SW1 0x11
#define CS19_SW1 0x12
#define CS20_SW1 0x13
#define CS21_SW1 0x14
#define CS22_SW1 0x15
#define CS23_SW1 0x16
#define CS24_SW1 0x17
#define CS25_SW1 0x18
#define CS26_SW1 0x19
#define CS27_SW1 0x1A
#define CS28_SW1 0x1B
#define CS29_SW1 0x1C
#define CS30_SW1 0x1D

#define CS1_SW2 0x1E
#define CS2_SW2 0x1F
#define CS3_SW2 0x20
#define CS4_SW2 0x21
#define CS5_SW2 0x22
#define CS6_SW2 0x23
#define CS7_SW2 0x24
#define CS8_SW2 0x25
#define CS9_SW2 0x26
#define CS10_SW2 0x27
#define CS11_SW2 0x28
#define CS12_SW2 0x29
#define CS13_SW2 0x2A
#define CS14_SW2 0x2B
#define CS15_SW2 0x2C
#define CS16_SW2 0x2D
#define CS17_SW2 0x2E
#define CS18_SW2 0x2F
#define CS19_SW2 0x30
#define CS20_SW2 0x31
#define CS21_SW2 0x32
#define CS22_SW2 0x33
#define CS23_SW2 0x34
#define CS24_SW2 0x35
#define CS25_SW2 0x36
#define CS26_SW2 0x37
#define CS27_SW2 0x38
#define CS28_SW2 0x39
#define CS29_SW2 0x3A
#define CS30_SW2 0x3B

#define CS1_SW3 0x3C
#define CS2_SW3 0x3D
#define CS3_SW3 0x3E
#define CS4_SW3 0x3F
#define CS5_SW3 0x40
#define CS6_SW3 0x41
#define CS7_SW3 0x42
#define CS8_SW3 0x43
#define CS9_SW3 0x44
#define CS10_SW3 0x45
#define CS11_SW3 0x46
#define CS12_SW3 0x47
#define CS13_SW3 0x48
#define CS14_SW3 0x49
#define CS15_SW3 0x4A
#define CS16_SW3 0x4B
#define CS17_SW3 0x4C
#define CS18_SW3 0x4D
#define CS19_SW3 0x4E
#define CS20_SW3 0x4F
#define CS21_SW3 0x50
#define CS22_SW3 0x51
#define CS23_SW3 0x52
#define CS24_SW3 0x53
#define CS25_SW3 0x54
#define CS26_SW3 0x55
#define CS27_SW3 0x56
#define CS28_SW3 0x57
#define CS29_SW3 0x58
#define CS30_SW3 0x59

#define CS1_SW4 0x5A
#define CS2_SW4 0x5B
#define CS3_SW4 0x5C
#define CS4_SW4 0x5D
#define CS5_SW4 0x5E
#define CS6_SW4 0x5F
#define CS7_SW4 0x60
#define CS8_SW4 0x61
#define CS9_SW4 0x62
#define CS10_SW4 0x63
#define CS11_SW4 0x64
#define CS12_SW4 0x65
#define CS13_SW4 0x66
#define CS14_SW4 0x67
#define CS15_SW4 0x68
#define CS16_SW4 0x69
#define CS17_SW4 0x6A
#define CS18_SW4 0x6B
#define CS19_SW4 0x6C
#define CS20_SW4 0x6D
#define CS21_SW4 0x6E
#define CS22_SW4 0x6F
#define CS23_SW4 0x70
#define CS24_SW4 0x71
#define CS25_SW4 0x72
#define CS26_SW4 0x73
#define CS27_SW4 0x74
#define CS28_SW4 0x75
#define CS29_SW4 0x76
#define CS30_SW4 0x77

#define CS1_SW5 0x78
#define CS2_SW5 0x79
#define CS3_SW5 0x7A
#define CS4_SW5 0x7B
#define CS5_SW5 0x7C
#define CS6_SW5 0x7D
#define CS7_SW5 0x7E
#define CS8_SW5 0x7F
#define CS9_SW5 0x80
#define CS10_SW5 0x81
#define CS11_SW5 0x82
#define CS12_SW5 0x83
#define CS13_SW5 0x84
#define CS14_SW5 0x85
#define CS15_SW5 0x86
#define CS16_SW5 0x87
#define CS17_SW5 0x88
#define CS18_SW5 0x89
#define CS19_SW5 0x8A
#define CS20_SW5 0x8B
#define CS21_SW5 0x8C
#define CS22_SW5 0x8D
#define CS23_SW5 0x8E
#define CS24_SW5 0x8F
#define CS25_SW5 0x90
#define CS26_SW5 0x91
#define CS27_SW5 0x92
#define CS28_SW5 0x93
#define CS29_SW5 0x94
#define CS30_SW5 0x95

#define CS1_SW6 0x96
#define CS2_SW6 0x97
#define CS3_SW6 0x98
#define CS4_SW6 0x99
#define CS5_SW6 0x9A
#define CS6_SW6 0x9B
#define CS7_SW6 0x9C
#define CS8_SW6 0x9D
#define CS9_SW6 0x9E
#define CS10_SW6 0x9F
#define CS11_SW6 0xA0
#define CS12_SW6 0xA1
#define CS13_SW6 0xA2
#define CS14_SW6 0xA3
#define CS15_SW6 0xA4
#define CS16_SW6 0xA5
#define CS17_SW6 0xA6
#define CS18_SW6 0xA7
#define CS19_SW6 0xA8
#define CS20_SW6 0xA9
#define CS21_SW6 0xAA
#define CS22_SW6 0xAB
#define CS23_SW6 0xAC
#define CS24_SW6 0xAD
#define CS25_SW6 0xAE
#define CS26_SW6 0xAF
#define CS27_SW6 0xB0
#define CS28_SW6 0xB1
#define CS29_SW6 0xB2
#define CS30_SW6 0xB3

#define CS1_SW7 0xB4
#define CS2_SW7 0xB5
#define CS3_SW7 0xB6
#define CS4_SW7 0xB7
#define CS5_SW7 0xB8
#define CS6_SW7 0xB9
#define CS7_SW7 0xBA
#define CS8_SW7 0xBB
#define CS9_SW7 0xBC
#define CS10_SW7 0xBD
#define CS11_SW7 0xBE
#define CS12_SW7 0xBF
#define CS13_SW7 0xC0
#define CS14_SW7 0xC1
#define CS15_SW7 0xC2
#define CS16_SW7 0xC3
#define CS17_SW7 0xC4
#define CS18_SW7 0xC5
#define CS19_SW7 0xC6
#define CS20_SW7 0xC7
#define CS21_SW7 0xC8
#define CS22_SW7 0xC9
#define CS23_SW7 0xCA
#define CS24_SW7 0xCB
#define CS25_SW7 0xCC
#define CS26_SW7 0xCD
#define CS27_SW7 0xCE
#define CS28_SW7 0xCF
#define CS29_SW7 0xD0
#define CS30_SW7 0xD1

#define CS1_SW8 0xD2
#define CS2_SW8 0xD3
#define CS3_SW8 0xD4
#define CS4_SW8 0xD5
#define CS5_SW8 0xD6
#define CS6_SW8 0xD7
#define CS7_SW8 0xD8
#define CS8_SW8 0xD9
#define CS9_SW8 0xDA
#define CS10_SW8 0xDB
#define CS11_SW8 0xDC
#define CS12_SW8 0xDD
#define CS13_SW8 0xDE
#define CS14_SW8 0xDF
#define CS15_SW8 0xE0
#define CS16_SW8 0xE1
#define CS17_SW8 0xE2
#define CS18_SW8 0xE3
#define CS19_SW8 0xE4
#define CS20_SW8 0xE5
#define CS21_SW8 0xE6
#define CS22_SW8 0xE7
#define CS23_SW8 0xE8
#define CS24_SW8 0xE9
#define CS25_SW8 0xEA
#define CS26_SW8 0xEB
#define CS27_SW8 0xEC
#define CS28_SW8 0xED
#define CS29_SW8 0xEE
#define CS30_SW8 0xEF

#define CS1_SW9 0xF0
#define CS2_SW9 0xF1
#define CS3_SW9 0xF2
#define CS4_SW9 0xF3
#define CS5_SW9 0xF4
#define CS6_SW9 0xF5
#define CS7_SW9 0xF6
#define CS8_SW9 0xF7
#define CS9_SW9 0xF8
#define CS10_SW9 0xF9
#define CS11_SW9 0xFA
#define CS12_SW9 0xFB
#define CS13_SW9 0xFC
#define CS14_SW9 0xFD
#define CS15_SW9 0xFE
#define CS16_SW9 0xFF
#define CS17_SW9 0x100
#define CS18_SW9 0x101
#define CS19_SW9 0x102
#define CS20_SW9 0x103
#define CS21_SW9 0x104
#define CS22_SW9 0x105
#define CS23_SW9 0x106
#define CS24_SW9 0x107
#define CS25_SW9 0x108
#define CS26_SW9 0x109
#define CS27_SW9 0x10A
#define CS28_SW9 0x10B
#define CS29_SW9 0x10C
#define CS30_SW9 0x10D

#define CS31_SW1 0x10E
#define CS32_SW1 0x10F
#define CS33_SW1 0x110
#define CS34_SW1 0x111
#define CS35_SW1 0x112
#define CS36_SW1 0x113
#define CS37_SW1 0x114
#define CS38_SW1 0x115
#define CS39_SW1 0x116

#define CS31_SW2 0x117
#define CS32_SW2 0x118
#define CS33_SW2 0x119
#define CS34_SW2 0x11A
#define CS35_SW2 0x11B
#define CS36_SW2 0x11C
#define CS37_SW2 0x11D
#define CS38_SW2 0x11E
#define CS39_SW2 0x11F

#define CS31_SW3 0x120
#define CS32_SW3 0x121
#define CS33_SW3 0x122
#define CS34_SW3 0x123
#define CS35_SW3 0x124
#define CS36_SW3 0x125
#define CS37_SW3 0x126
#define CS38_SW3 0x127
#define CS39_SW3 0x128

#define CS31_SW4 0x129
#define CS32_SW4 0x12A
#define CS33_SW4 0x12B
#define CS34_SW4 0x12C
#define CS35_SW4 0x12D
#define CS36_SW4 0x12E
#define CS37_SW4 0x12F
#define CS38_SW4 0x130
#define CS39_SW4 0x131

#define CS31_SW5 0x132
#define CS32_SW5 0x133
#define CS33_SW5 0x134
#define CS34_SW5 0x135
#define CS35_SW5 0x136
#define CS36_SW5 0x137
#define CS37_SW5 0x138
#define CS38_SW5 0x139
#define CS39_SW5 0x13A

#define CS31_SW6 0x13B
#define CS32_SW6 0x13C
#define CS33_SW6 0x13D
#define CS34_SW6 0x13E
#define CS35_SW6 0x13F
#define CS36_SW6 0x140
#define CS37_SW6 0x141
#define CS38_SW6 0x142
#define CS39_SW6 0x143

#define CS31_SW7 0x144
#define CS32_SW7 0x145
#define CS33_SW7 0x146
#define CS34_SW7 0x147
#define CS35_SW7 0x148
#define CS36_SW7 0x149
#define CS37_SW7 0x14A
#define CS38_SW7 0x14B
#define CS39_SW7 0x14C

#define CS31_SW8 0x14D
#define CS32_SW8 0x14E
#define CS33_SW8 0x14F
#define CS34_SW8 0x150
#define CS35_SW8 0x151
#define CS36_SW8 0x152
#define CS37_SW8 0x153
#define CS38_SW8 0x154
#define CS39_SW8 0x155

#define CS31_SW9 0x156
#define CS32_SW9 0x157
#define CS33_SW9 0x158
#define CS34_SW9 0x159
#define CS35_SW9 0x15A
#define CS36_SW9 0x15B
#define CS37_SW9 0x15C
#define CS38_SW9 0x15D
#define CS39_SW9 0x15E
