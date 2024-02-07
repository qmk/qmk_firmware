/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2018 Yiancar
 * Copyright 2020 MelGeek
 * Copyright 2021 MasterSpoon
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

#define IS31FL3742A_REG_INTERRUPT_MASK 0xF0
#define IS31FL3742A_REG_INTERRUPT_STATUS 0xF1
#define IS31FL3742A_REG_ID 0xFC

#define IS31FL3742A_REG_COMMAND 0xFD

#define IS31FL3742A_COMMAND_PWM 0x00
#define IS31FL3742A_COMMAND_SCALING 0x02
#define IS31FL3742A_COMMAND_FUNCTION 0x04

#define IS31FL3742A_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3742A_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3742A_FUNCTION_REG_PULLDOWNUP 0x02
#define IS31FL3742A_FUNCTION_REG_PWM_FREQUENCY 0x36
#define IS31FL3742A_FUNCTION_REG_RESET 0x3F
#define IS31FL3742A_FUNCTION_REG_SPREAD_SPECTRUM 0x41

#define IS31FL3742A_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3742A_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3742A_I2C_ADDRESS_GND 0x30
#define IS31FL3742A_I2C_ADDRESS_SCL 0x31
#define IS31FL3742A_I2C_ADDRESS_SDA 0x32
#define IS31FL3742A_I2C_ADDRESS_VCC 0x33

#if defined(RGB_MATRIX_IS31FL3742A)
#    define IS31FL3742A_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3742A_I2C_ADDRESS_4)
#    define IS31FL3742A_DRIVER_COUNT 4
#elif defined(IS31FL3742A_I2C_ADDRESS_3)
#    define IS31FL3742A_DRIVER_COUNT 3
#elif defined(IS31FL3742A_I2C_ADDRESS_2)
#    define IS31FL3742A_DRIVER_COUNT 2
#elif defined(IS31FL3742A_I2C_ADDRESS_1)
#    define IS31FL3742A_DRIVER_COUNT 1
#endif

typedef struct is31fl3742a_led_t {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED is31fl3742a_led_t;

extern const is31fl3742a_led_t PROGMEM g_is31fl3742a_leds[IS31FL3742A_LED_COUNT];

void is31fl3742a_init_drivers(void);
void is31fl3742a_init(uint8_t addr);
void is31fl3742a_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void is31fl3742a_select_page(uint8_t addr, uint8_t page);

void is31fl3742a_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void is31fl3742a_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3742a_set_scaling_register(uint8_t index, uint8_t red, uint8_t green, uint8_t blue);

void is31fl3742a_update_pwm_buffers(uint8_t addr, uint8_t index);
void is31fl3742a_update_scaling_registers(uint8_t addr, uint8_t index);

void is31fl3742a_flush(void);

#define IS31FL3742A_PDR_0_OHM 0b000   // No pull-down resistor
#define IS31FL3742A_PDR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3742A_PDR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3742A_PDR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3742A_PDR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3742A_PDR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3742A_PDR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3742A_PDR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3742A_PUR_0_OHM 0b000   // No pull-up resistor
#define IS31FL3742A_PUR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3742A_PUR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3742A_PUR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3742A_PUR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3742A_PUR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3742A_PUR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3742A_PUR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3742A_PWM_FREQUENCY_29K_HZ 0b0000
#define IS31FL3742A_PWM_FREQUENCY_3K6_HZ 0b0011
#define IS31FL3742A_PWM_FREQUENCY_1K8_HZ 0b0111
#define IS31FL3742A_PWM_FREQUENCY_900_HZ 0b1011

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
