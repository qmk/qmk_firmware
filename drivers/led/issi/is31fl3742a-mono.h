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

#if defined(LED_MATRIX_IS31FL3742A)
#    define IS31FL3742A_LED_COUNT LED_MATRIX_LED_COUNT
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
    uint8_t v;
} PACKED is31fl3742a_led_t;

extern const is31fl3742a_led_t PROGMEM g_is31fl3742a_leds[IS31FL3742A_LED_COUNT];

void is31fl3742a_init_drivers(void);
void is31fl3742a_init(uint8_t index);
void is31fl3742a_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3742a_select_page(uint8_t index, uint8_t page);

void is31fl3742a_set_value(int index, uint8_t value);
void is31fl3742a_set_value_all(uint8_t value);

void is31fl3742a_set_scaling_register(uint8_t index, uint8_t value);

void is31fl3742a_update_pwm_buffers(uint8_t index);
void is31fl3742a_update_scaling_registers(uint8_t index);

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
