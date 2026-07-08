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

#define IS31FL3737_REG_INTERRUPT_MASK 0xF0
#define IS31FL3737_REG_INTERRUPT_STATUS 0xF1

#define IS31FL3737_REG_COMMAND 0xFD

#define IS31FL3737_COMMAND_LED_CONTROL 0x00
#define IS31FL3737_COMMAND_PWM 0x01
#define IS31FL3737_COMMAND_AUTO_BREATH 0x02
#define IS31FL3737_COMMAND_FUNCTION 0x03

#define IS31FL3737_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3737_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3737_FUNCTION_REG_SW_PULLUP 0x0F
#define IS31FL3737_FUNCTION_REG_CS_PULLDOWN 0x10
#define IS31FL3737_FUNCTION_REG_RESET 0x11

#define IS31FL3737_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3737_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3737_I2C_ADDRESS_GND 0x50
#define IS31FL3737_I2C_ADDRESS_SCL 0x55
#define IS31FL3737_I2C_ADDRESS_SDA 0x5A
#define IS31FL3737_I2C_ADDRESS_VCC 0x5F

#if defined(LED_MATRIX_IS31FL3737)
#    define IS31FL3737_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3737_I2C_ADDRESS_4)
#    define IS31FL3737_DRIVER_COUNT 4
#elif defined(IS31FL3737_I2C_ADDRESS_3)
#    define IS31FL3737_DRIVER_COUNT 3
#elif defined(IS31FL3737_I2C_ADDRESS_2)
#    define IS31FL3737_DRIVER_COUNT 2
#elif defined(IS31FL3737_I2C_ADDRESS_1)
#    define IS31FL3737_DRIVER_COUNT 1
#endif

typedef struct is31fl3737_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED is31fl3737_led_t;

extern const is31fl3737_led_t PROGMEM g_is31fl3737_leds[IS31FL3737_LED_COUNT];

void is31fl3737_init_drivers(void);
void is31fl3737_init(uint8_t index);
void is31fl3737_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3737_select_page(uint8_t index, uint8_t page);

void is31fl3737_set_value(int index, uint8_t value);
void is31fl3737_set_value_all(uint8_t value);

void is31fl3737_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3737_update_pwm_buffers(uint8_t index);
void is31fl3737_update_led_control_registers(uint8_t index);

void is31fl3737_flush(void);

#define IS31FL3737_PDR_0_OHM 0b000   // No pull-down resistor
#define IS31FL3737_PDR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3737_PDR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3737_PDR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3737_PDR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3737_PDR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3737_PDR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3737_PDR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3737_PUR_0_OHM 0b000   // No pull-up resistor
#define IS31FL3737_PUR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3737_PUR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3737_PUR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3737_PUR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3737_PUR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3737_PUR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3737_PUR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3737_PWM_FREQUENCY_8K4_HZ 0b000
#define IS31FL3737_PWM_FREQUENCY_4K2_HZ 0b001
#define IS31FL3737_PWM_FREQUENCY_26K7_HZ 0b010
#define IS31FL3737_PWM_FREQUENCY_2K1_HZ 0b011
#define IS31FL3737_PWM_FREQUENCY_1K05_HZ 0b100

#define SW1_CS1 0x00
#define SW1_CS2 0x01
#define SW1_CS3 0x02
#define SW1_CS4 0x03
#define SW1_CS5 0x04
#define SW1_CS6 0x05
#define SW1_CS7 0x08
#define SW1_CS8 0x09
#define SW1_CS9 0x0A
#define SW1_CS10 0x0B
#define SW1_CS11 0x0C
#define SW1_CS12 0x0D

#define SW2_CS1 0x10
#define SW2_CS2 0x11
#define SW2_CS3 0x12
#define SW2_CS4 0x13
#define SW2_CS5 0x14
#define SW2_CS6 0x15
#define SW2_CS7 0x18
#define SW2_CS8 0x19
#define SW2_CS9 0x1A
#define SW2_CS10 0x1B
#define SW2_CS11 0x1C
#define SW2_CS12 0x1D

#define SW3_CS1 0x20
#define SW3_CS2 0x21
#define SW3_CS3 0x22
#define SW3_CS4 0x23
#define SW3_CS5 0x24
#define SW3_CS6 0x25
#define SW3_CS7 0x28
#define SW3_CS8 0x29
#define SW3_CS9 0x2A
#define SW3_CS10 0x2B
#define SW3_CS11 0x2C
#define SW3_CS12 0x2D

#define SW4_CS1 0x30
#define SW4_CS2 0x31
#define SW4_CS3 0x32
#define SW4_CS4 0x33
#define SW4_CS5 0x34
#define SW4_CS6 0x35
#define SW4_CS7 0x38
#define SW4_CS8 0x39
#define SW4_CS9 0x3A
#define SW4_CS10 0x3B
#define SW4_CS11 0x3C
#define SW4_CS12 0x3D

#define SW5_CS1 0x40
#define SW5_CS2 0x41
#define SW5_CS3 0x42
#define SW5_CS4 0x43
#define SW5_CS5 0x44
#define SW5_CS6 0x45
#define SW5_CS7 0x48
#define SW5_CS8 0x49
#define SW5_CS9 0x4A
#define SW5_CS10 0x4B
#define SW5_CS11 0x4C
#define SW5_CS12 0x4D

#define SW6_CS1 0x50
#define SW6_CS2 0x51
#define SW6_CS3 0x52
#define SW6_CS4 0x53
#define SW6_CS5 0x54
#define SW6_CS6 0x55
#define SW6_CS7 0x58
#define SW6_CS8 0x59
#define SW6_CS9 0x5A
#define SW6_CS10 0x5B
#define SW6_CS11 0x5C
#define SW6_CS12 0x5D

#define SW7_CS1 0x60
#define SW7_CS2 0x61
#define SW7_CS3 0x62
#define SW7_CS4 0x63
#define SW7_CS5 0x64
#define SW7_CS6 0x65
#define SW7_CS7 0x68
#define SW7_CS8 0x69
#define SW7_CS9 0x6A
#define SW7_CS10 0x6B
#define SW7_CS11 0x6C
#define SW7_CS12 0x6D

#define SW8_CS1 0x70
#define SW8_CS2 0x71
#define SW8_CS3 0x72
#define SW8_CS4 0x73
#define SW8_CS5 0x74
#define SW8_CS6 0x75
#define SW8_CS7 0x78
#define SW8_CS8 0x79
#define SW8_CS9 0x7A
#define SW8_CS10 0x7B
#define SW8_CS11 0x7C
#define SW8_CS12 0x7D

#define SW9_CS1 0x80
#define SW9_CS2 0x81
#define SW9_CS3 0x82
#define SW9_CS4 0x83
#define SW9_CS5 0x84
#define SW9_CS6 0x85
#define SW9_CS7 0x88
#define SW9_CS8 0x89
#define SW9_CS9 0x8A
#define SW9_CS10 0x8B
#define SW9_CS11 0x8C
#define SW9_CS12 0x8D

#define SW10_CS1 0x90
#define SW10_CS2 0x91
#define SW10_CS3 0x92
#define SW10_CS4 0x93
#define SW10_CS5 0x94
#define SW10_CS6 0x95
#define SW10_CS7 0x98
#define SW10_CS8 0x99
#define SW10_CS9 0x9A
#define SW10_CS10 0x9B
#define SW10_CS11 0x9C
#define SW10_CS12 0x9D

#define SW11_CS1 0xA0
#define SW11_CS2 0xA1
#define SW11_CS3 0xA2
#define SW11_CS4 0xA3
#define SW11_CS5 0xA4
#define SW11_CS6 0xA5
#define SW11_CS7 0xA8
#define SW11_CS8 0xA9
#define SW11_CS9 0xAA
#define SW11_CS10 0xAB
#define SW11_CS11 0xAC
#define SW11_CS12 0xAD

#define SW12_CS1 0xB0
#define SW12_CS2 0xB1
#define SW12_CS3 0xB2
#define SW12_CS4 0xB3
#define SW12_CS5 0xB4
#define SW12_CS6 0xB5
#define SW12_CS7 0xB8
#define SW12_CS8 0xB9
#define SW12_CS9 0xBA
#define SW12_CS10 0xBB
#define SW12_CS11 0xBC
#define SW12_CS12 0xBD
