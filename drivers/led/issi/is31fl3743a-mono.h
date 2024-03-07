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

#define IS31FL3743A_REG_ID 0xFC

#define IS31FL3743A_REG_COMMAND 0xFD

#define IS31FL3743A_COMMAND_PWM 0x00
#define IS31FL3743A_COMMAND_SCALING 0x01
#define IS31FL3743A_COMMAND_FUNCTION 0x02

#define IS31FL3743A_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3743A_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3743A_FUNCTION_REG_PULLDOWNUP 0x02
#define IS31FL3743A_FUNCTION_REG_TEMPERATURE 0x24
#define IS31FL3743A_FUNCTION_REG_SPREAD_SPECTRUM 0x25
#define IS31FL3743A_FUNCTION_REG_RESET 0x2F

#define IS31FL3743A_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3743A_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3743A_I2C_ADDRESS_GND_GND 0x20
#define IS31FL3743A_I2C_ADDRESS_GND_SCL 0x21
#define IS31FL3743A_I2C_ADDRESS_GND_SDA 0x22
#define IS31FL3743A_I2C_ADDRESS_GND_VCC 0x23
#define IS31FL3743A_I2C_ADDRESS_SCL_GND 0x24
#define IS31FL3743A_I2C_ADDRESS_SCL_SCL 0x25
#define IS31FL3743A_I2C_ADDRESS_SCL_SDA 0x26
#define IS31FL3743A_I2C_ADDRESS_SCL_VCC 0x27
#define IS31FL3743A_I2C_ADDRESS_SDA_GND 0x28
#define IS31FL3743A_I2C_ADDRESS_SDA_SCL 0x29
#define IS31FL3743A_I2C_ADDRESS_SDA_SDA 0x2A
#define IS31FL3743A_I2C_ADDRESS_SDA_VCC 0x2B
#define IS31FL3743A_I2C_ADDRESS_VCC_GND 0x2C
#define IS31FL3743A_I2C_ADDRESS_VCC_SCL 0x2D
#define IS31FL3743A_I2C_ADDRESS_VCC_SDA 0x2E
#define IS31FL3743A_I2C_ADDRESS_VCC_VCC 0x2F

#if defined(LED_MATRIX_IS31FL3743A)
#    define IS31FL3743A_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3743A_I2C_ADDRESS_4)
#    define IS31FL3743A_DRIVER_COUNT 4
#elif defined(IS31FL3743A_I2C_ADDRESS_3)
#    define IS31FL3743A_DRIVER_COUNT 3
#elif defined(IS31FL3743A_I2C_ADDRESS_2)
#    define IS31FL3743A_DRIVER_COUNT 2
#elif defined(IS31FL3743A_I2C_ADDRESS_1)
#    define IS31FL3743A_DRIVER_COUNT 1
#endif

typedef struct is31fl3743a_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED is31fl3743a_led_t;

extern const is31fl3743a_led_t PROGMEM g_is31fl3743a_leds[IS31FL3743A_LED_COUNT];

void is31fl3743a_init_drivers(void);
void is31fl3743a_init(uint8_t index);
void is31fl3743a_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3743a_select_page(uint8_t index, uint8_t page);

void is31fl3743a_set_value(int index, uint8_t value);
void is31fl3743a_set_value_all(uint8_t value);

void is31fl3743a_set_scaling_register(uint8_t index, uint8_t value);

void is31fl3743a_update_pwm_buffers(uint8_t index);
void is31fl3743a_update_scaling_registers(uint8_t index);

void is31fl3743a_flush(void);

#define IS31FL3743A_PDR_0_OHM 0b000          // No pull-down resistor
#define IS31FL3743A_PDR_0K5_OHM_SW_OFF 0b001 // 0.5 kOhm resistor in SWx off time
#define IS31FL3743A_PDR_1K_OHM_SW_OFF 0b010  // 1 kOhm resistor in SWx off time
#define IS31FL3743A_PDR_2K_OHM_SW_OFF 0b011  // 2 kOhm resistor in SWx off time
#define IS31FL3743A_PDR_1K_OHM 0b100         // 1 kOhm resistor
#define IS31FL3743A_PDR_2K_OHM 0b101         // 2 kOhm resistor
#define IS31FL3743A_PDR_4K_OHM 0b110         // 4 kOhm resistor
#define IS31FL3743A_PDR_8K_OHM 0b111         // 8 kOhm resistor

#define IS31FL3743A_PUR_0_OHM 0b000          // No pull-up resistor
#define IS31FL3743A_PUR_0K5_OHM_CS_OFF 0b001 // 0.5 kOhm resistor in CSy off time
#define IS31FL3743A_PUR_1K_OHM_CS_OFF 0b010  // 1 kOhm resistor in CSy off time
#define IS31FL3743A_PUR_2K_OHM_CS_OFF 0b011  // 2 kOhm resistor in CSy off time
#define IS31FL3743A_PUR_1K_OHM 0b100         // 1 kOhm resistor
#define IS31FL3743A_PUR_2K_OHM 0b101         // 2 kOhm resistor
#define IS31FL3743A_PUR_4K_OHM 0b110         // 4 kOhm resistor
#define IS31FL3743A_PUR_8K_OHM 0b111         // 8 kOhm resistor

#define IS31FL3743A_SYNC_NONE 0b00
#define IS31FL3743A_SYNC_SLAVE 0b10
#define IS31FL3743A_SYNC_MASTER 0b11

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

#define SW2_CS1 0x12
#define SW2_CS2 0x13
#define SW2_CS3 0x14
#define SW2_CS4 0x15
#define SW2_CS5 0x16
#define SW2_CS6 0x17
#define SW2_CS7 0x18
#define SW2_CS8 0x19
#define SW2_CS9 0x1A
#define SW2_CS10 0x1B
#define SW2_CS11 0x1C
#define SW2_CS12 0x1D
#define SW2_CS13 0x1E
#define SW2_CS14 0x1F
#define SW2_CS15 0x20
#define SW2_CS16 0x21
#define SW2_CS17 0x22
#define SW2_CS18 0x23

#define SW3_CS1 0x24
#define SW3_CS2 0x25
#define SW3_CS3 0x26
#define SW3_CS4 0x27
#define SW3_CS5 0x28
#define SW3_CS6 0x29
#define SW3_CS7 0x2A
#define SW3_CS8 0x2B
#define SW3_CS9 0x2C
#define SW3_CS10 0x2D
#define SW3_CS11 0x2E
#define SW3_CS12 0x2F
#define SW3_CS13 0x30
#define SW3_CS14 0x31
#define SW3_CS15 0x32
#define SW3_CS16 0x33
#define SW3_CS17 0x34
#define SW3_CS18 0x35

#define SW4_CS1 0x36
#define SW4_CS2 0x37
#define SW4_CS3 0x38
#define SW4_CS4 0x39
#define SW4_CS5 0x3A
#define SW4_CS6 0x3B
#define SW4_CS7 0x3C
#define SW4_CS8 0x3D
#define SW4_CS9 0x3E
#define SW4_CS10 0x3F
#define SW4_CS11 0x40
#define SW4_CS12 0x41
#define SW4_CS13 0x42
#define SW4_CS14 0x43
#define SW4_CS15 0x44
#define SW4_CS16 0x45
#define SW4_CS17 0x46
#define SW4_CS18 0x47

#define SW5_CS1 0x48
#define SW5_CS2 0x49
#define SW5_CS3 0x4A
#define SW5_CS4 0x4B
#define SW5_CS5 0x4C
#define SW5_CS6 0x4D
#define SW5_CS7 0x4E
#define SW5_CS8 0x4F
#define SW5_CS9 0x50
#define SW5_CS10 0x51
#define SW5_CS11 0x52
#define SW5_CS12 0x53
#define SW5_CS13 0x54
#define SW5_CS14 0x55
#define SW5_CS15 0x56
#define SW5_CS16 0x57
#define SW5_CS17 0x58
#define SW5_CS18 0x59

#define SW6_CS1 0x5A
#define SW6_CS2 0x5B
#define SW6_CS3 0x5C
#define SW6_CS4 0x5D
#define SW6_CS5 0x5E
#define SW6_CS6 0x5F
#define SW6_CS7 0x60
#define SW6_CS8 0x61
#define SW6_CS9 0x62
#define SW6_CS10 0x63
#define SW6_CS11 0x64
#define SW6_CS12 0x65
#define SW6_CS13 0x66
#define SW6_CS14 0x67
#define SW6_CS15 0x68
#define SW6_CS16 0x69
#define SW6_CS17 0x6A
#define SW6_CS18 0x6B

#define SW7_CS1 0x6C
#define SW7_CS2 0x6D
#define SW7_CS3 0x6E
#define SW7_CS4 0x6F
#define SW7_CS5 0x70
#define SW7_CS6 0x71
#define SW7_CS7 0x72
#define SW7_CS8 0x73
#define SW7_CS9 0x74
#define SW7_CS10 0x75
#define SW7_CS11 0x76
#define SW7_CS12 0x77
#define SW7_CS13 0x78
#define SW7_CS14 0x79
#define SW7_CS15 0x7A
#define SW7_CS16 0x7B
#define SW7_CS17 0x7C
#define SW7_CS18 0x7D

#define SW8_CS1 0x7E
#define SW8_CS2 0x7F
#define SW8_CS3 0x80
#define SW8_CS4 0x81
#define SW8_CS5 0x82
#define SW8_CS6 0x83
#define SW8_CS7 0x84
#define SW8_CS8 0x85
#define SW8_CS9 0x86
#define SW8_CS10 0x87
#define SW8_CS11 0x88
#define SW8_CS12 0x89
#define SW8_CS13 0x8A
#define SW8_CS14 0x8B
#define SW8_CS15 0x8C
#define SW8_CS16 0x8D
#define SW8_CS17 0x8E
#define SW8_CS18 0x8F

#define SW9_CS1 0x90
#define SW9_CS2 0x91
#define SW9_CS3 0x92
#define SW9_CS4 0x93
#define SW9_CS5 0x94
#define SW9_CS6 0x95
#define SW9_CS7 0x96
#define SW9_CS8 0x97
#define SW9_CS9 0x98
#define SW9_CS10 0x99
#define SW9_CS11 0x9A
#define SW9_CS12 0x9B
#define SW9_CS13 0x9C
#define SW9_CS14 0x9D
#define SW9_CS15 0x9E
#define SW9_CS16 0x9F
#define SW9_CS17 0xA0
#define SW9_CS18 0xA1

#define SW10_CS1 0xA2
#define SW10_CS2 0xA3
#define SW10_CS3 0xA4
#define SW10_CS4 0xA5
#define SW10_CS5 0xA6
#define SW10_CS6 0xA7
#define SW10_CS7 0xA8
#define SW10_CS8 0xA9
#define SW10_CS9 0xAA
#define SW10_CS10 0xAB
#define SW10_CS11 0xAC
#define SW10_CS12 0xAD
#define SW10_CS13 0xAE
#define SW10_CS14 0xAF
#define SW10_CS15 0xB0
#define SW10_CS16 0xB1
#define SW10_CS17 0xB2
#define SW10_CS18 0xB3

#define SW11_CS1 0xB4
#define SW11_CS2 0xB5
#define SW11_CS3 0xB6
#define SW11_CS4 0xB7
#define SW11_CS5 0xB8
#define SW11_CS6 0xB9
#define SW11_CS7 0xBA
#define SW11_CS8 0xBB
#define SW11_CS9 0xBC
#define SW11_CS10 0xBD
#define SW11_CS11 0xBE
#define SW11_CS12 0xBF
#define SW11_CS13 0xC0
#define SW11_CS14 0xC1
#define SW11_CS15 0xC2
#define SW11_CS16 0xC3
#define SW11_CS17 0xC4
#define SW11_CS18 0xC5
