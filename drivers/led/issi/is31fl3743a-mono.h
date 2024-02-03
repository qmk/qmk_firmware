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
void is31fl3743a_init(uint8_t addr, uint8_t sync);
void is31fl3743a_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void is31fl3743a_select_page(uint8_t addr, uint8_t page);

void is31fl3743a_set_value(int index, uint8_t value);
void is31fl3743a_set_value_all(uint8_t value);

void is31fl3743a_set_scaling_register(uint8_t index, uint8_t value);

void is31fl3743a_update_pwm_buffers(uint8_t addr, uint8_t index);
void is31fl3743a_update_scaling_registers(uint8_t addr, uint8_t index);

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

#define CS1_SW2 0x12
#define CS2_SW2 0x13
#define CS3_SW2 0x14
#define CS4_SW2 0x15
#define CS5_SW2 0x16
#define CS6_SW2 0x17
#define CS7_SW2 0x18
#define CS8_SW2 0x19
#define CS9_SW2 0x1A
#define CS10_SW2 0x1B
#define CS11_SW2 0x1C
#define CS12_SW2 0x1D
#define CS13_SW2 0x1E
#define CS14_SW2 0x1F
#define CS15_SW2 0x20
#define CS16_SW2 0x21
#define CS17_SW2 0x22
#define CS18_SW2 0x23

#define CS1_SW3 0x24
#define CS2_SW3 0x25
#define CS3_SW3 0x26
#define CS4_SW3 0x27
#define CS5_SW3 0x28
#define CS6_SW3 0x29
#define CS7_SW3 0x2A
#define CS8_SW3 0x2B
#define CS9_SW3 0x2C
#define CS10_SW3 0x2D
#define CS11_SW3 0x2E
#define CS12_SW3 0x2F
#define CS13_SW3 0x30
#define CS14_SW3 0x31
#define CS15_SW3 0x32
#define CS16_SW3 0x33
#define CS17_SW3 0x34
#define CS18_SW3 0x35

#define CS1_SW4 0x36
#define CS2_SW4 0x37
#define CS3_SW4 0x38
#define CS4_SW4 0x39
#define CS5_SW4 0x3A
#define CS6_SW4 0x3B
#define CS7_SW4 0x3C
#define CS8_SW4 0x3D
#define CS9_SW4 0x3E
#define CS10_SW4 0x3F
#define CS11_SW4 0x40
#define CS12_SW4 0x41
#define CS13_SW4 0x42
#define CS14_SW4 0x43
#define CS15_SW4 0x44
#define CS16_SW4 0x45
#define CS17_SW4 0x46
#define CS18_SW4 0x47

#define CS1_SW5 0x48
#define CS2_SW5 0x49
#define CS3_SW5 0x4A
#define CS4_SW5 0x4B
#define CS5_SW5 0x4C
#define CS6_SW5 0x4D
#define CS7_SW5 0x4E
#define CS8_SW5 0x4F
#define CS9_SW5 0x50
#define CS10_SW5 0x51
#define CS11_SW5 0x52
#define CS12_SW5 0x53
#define CS13_SW5 0x54
#define CS14_SW5 0x55
#define CS15_SW5 0x56
#define CS16_SW5 0x57
#define CS17_SW5 0x58
#define CS18_SW5 0x59

#define CS1_SW6 0x5A
#define CS2_SW6 0x5B
#define CS3_SW6 0x5C
#define CS4_SW6 0x5D
#define CS5_SW6 0x5E
#define CS6_SW6 0x5F
#define CS7_SW6 0x60
#define CS8_SW6 0x61
#define CS9_SW6 0x62
#define CS10_SW6 0x63
#define CS11_SW6 0x64
#define CS12_SW6 0x65
#define CS13_SW6 0x66
#define CS14_SW6 0x67
#define CS15_SW6 0x68
#define CS16_SW6 0x69
#define CS17_SW6 0x6A
#define CS18_SW6 0x6B

#define CS1_SW7 0x6C
#define CS2_SW7 0x6D
#define CS3_SW7 0x6E
#define CS4_SW7 0x6F
#define CS5_SW7 0x70
#define CS6_SW7 0x71
#define CS7_SW7 0x72
#define CS8_SW7 0x73
#define CS9_SW7 0x74
#define CS10_SW7 0x75
#define CS11_SW7 0x76
#define CS12_SW7 0x77
#define CS13_SW7 0x78
#define CS14_SW7 0x79
#define CS15_SW7 0x7A
#define CS16_SW7 0x7B
#define CS17_SW7 0x7C
#define CS18_SW7 0x7D

#define CS1_SW8 0x7E
#define CS2_SW8 0x7F
#define CS3_SW8 0x80
#define CS4_SW8 0x81
#define CS5_SW8 0x82
#define CS6_SW8 0x83
#define CS7_SW8 0x84
#define CS8_SW8 0x85
#define CS9_SW8 0x86
#define CS10_SW8 0x87
#define CS11_SW8 0x88
#define CS12_SW8 0x89
#define CS13_SW8 0x8A
#define CS14_SW8 0x8B
#define CS15_SW8 0x8C
#define CS16_SW8 0x8D
#define CS17_SW8 0x8E
#define CS18_SW8 0x8F

#define CS1_SW9 0x90
#define CS2_SW9 0x91
#define CS3_SW9 0x92
#define CS4_SW9 0x93
#define CS5_SW9 0x94
#define CS6_SW9 0x95
#define CS7_SW9 0x96
#define CS8_SW9 0x97
#define CS9_SW9 0x98
#define CS10_SW9 0x99
#define CS11_SW9 0x9A
#define CS12_SW9 0x9B
#define CS13_SW9 0x9C
#define CS14_SW9 0x9D
#define CS15_SW9 0x9E
#define CS16_SW9 0x9F
#define CS17_SW9 0xA0
#define CS18_SW9 0xA1

#define CS1_SW10 0xA2
#define CS2_SW10 0xA3
#define CS3_SW10 0xA4
#define CS4_SW10 0xA5
#define CS5_SW10 0xA6
#define CS6_SW10 0xA7
#define CS7_SW10 0xA8
#define CS8_SW10 0xA9
#define CS9_SW10 0xAA
#define CS10_SW10 0xAB
#define CS11_SW10 0xAC
#define CS12_SW10 0xAD
#define CS13_SW10 0xAE
#define CS14_SW10 0xAF
#define CS15_SW10 0xB0
#define CS16_SW10 0xB1
#define CS17_SW10 0xB2
#define CS18_SW10 0xB3

#define CS1_SW11 0xB4
#define CS2_SW11 0xB5
#define CS3_SW11 0xB6
#define CS4_SW11 0xB7
#define CS5_SW11 0xB8
#define CS6_SW11 0xB9
#define CS7_SW11 0xBA
#define CS8_SW11 0xBB
#define CS9_SW11 0xBC
#define CS10_SW11 0xBD
#define CS11_SW11 0xBE
#define CS12_SW11 0xBF
#define CS13_SW11 0xC0
#define CS14_SW11 0xC1
#define CS15_SW11 0xC2
#define CS16_SW11 0xC3
#define CS17_SW11 0xC4
#define CS18_SW11 0xC5
