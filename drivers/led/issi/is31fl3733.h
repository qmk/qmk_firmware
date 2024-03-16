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

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef DRIVER_ADDR_1
#    define IS31FL3733_I2C_ADDRESS_1 DRIVER_ADDR_1
#endif
#ifdef DRIVER_ADDR_2
#    define IS31FL3733_I2C_ADDRESS_2 DRIVER_ADDR_2
#endif
#ifdef DRIVER_ADDR_3
#    define IS31FL3733_I2C_ADDRESS_3 DRIVER_ADDR_3
#endif
#ifdef DRIVER_ADDR_4
#    define IS31FL3733_I2C_ADDRESS_4 DRIVER_ADDR_4
#endif
#ifdef DRIVER_SYNC_1
#    define IS31FL3733_SYNC_1 DRIVER_SYNC_1
#endif
#ifdef DRIVER_SYNC_2
#    define IS31FL3733_SYNC_2 DRIVER_SYNC_2
#endif
#ifdef DRIVER_SYNC_3
#    define IS31FL3733_SYNC_3 DRIVER_SYNC_3
#endif
#ifdef DRIVER_SYNC_4
#    define IS31FL3733_SYNC_4 DRIVER_SYNC_4
#endif
#ifdef ISSI_TIMEOUT
#    define IS31FL3733_I2C_TIMEOUT ISSI_TIMEOUT
#endif
#ifdef ISSI_PERSISTENCE
#    define IS31FL3733_I2C_PERSISTENCE ISSI_PERSISTENCE
#endif
#ifdef ISSI_PWM_FREQUENCY
#    define IS31FL3733_PWM_FREQUENCY ISSI_PWM_FREQUENCY
#endif
#ifdef ISSI_SWPULLUP
#    define IS31FL3733_SW_PULLUP ISSI_SWPULLUP
#endif
#ifdef ISSI_CSPULLUP
#    define IS31FL3733_CS_PULLDOWN ISSI_CSPULLUP
#endif
#ifdef ISSI_GLOBALCURRENT
#    define IS31FL3733_GLOBAL_CURRENT ISSI_GLOBALCURRENT
#endif

#define is31_led is31fl3733_led_t
#define g_is31_leds g_is31fl3733_leds

#define PUR_0R IS31FL3733_PUR_0_OHM
#define PUR_05KR IS31FL3733_PUR_1K_OHM
#define PUR_3KR IS31FL3733_PUR_2K_OHM
#define PUR_4KR IS31FL3733_PUR_4K_OHM
#define PUR_8KR IS31FL3733_PUR_8K_OHM
#define PUR_16KR IS31FL3733_PUR_16K_OHM
#define PUR_32KR IS31FL3733_PUR_32K_OHM
// ========

#define IS31FL3733_REG_INTERRUPT_MASK 0xF0
#define IS31FL3733_REG_INTERRUPT_STATUS 0xF1

#define IS31FL3733_REG_COMMAND 0xFD

#define IS31FL3733_COMMAND_LED_CONTROL 0x00
#define IS31FL3733_COMMAND_PWM 0x01
#define IS31FL3733_COMMAND_AUTO_BREATH 0x02
#define IS31FL3733_COMMAND_FUNCTION 0x03

#define IS31FL3733_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3733_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3733_FUNCTION_REG_SW_PULLUP 0x0F
#define IS31FL3733_FUNCTION_REG_CS_PULLDOWN 0x10
#define IS31FL3733_FUNCTION_REG_RESET 0x11

#define IS31FL3733_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3733_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3733_I2C_ADDRESS_GND_GND 0x50
#define IS31FL3733_I2C_ADDRESS_GND_SCL 0x51
#define IS31FL3733_I2C_ADDRESS_GND_SDA 0x52
#define IS31FL3733_I2C_ADDRESS_GND_VCC 0x53
#define IS31FL3733_I2C_ADDRESS_SCL_GND 0x54
#define IS31FL3733_I2C_ADDRESS_SCL_SCL 0x55
#define IS31FL3733_I2C_ADDRESS_SCL_SDA 0x56
#define IS31FL3733_I2C_ADDRESS_SCL_VCC 0x57
#define IS31FL3733_I2C_ADDRESS_SDA_GND 0x58
#define IS31FL3733_I2C_ADDRESS_SDA_SCL 0x59
#define IS31FL3733_I2C_ADDRESS_SDA_SDA 0x5A
#define IS31FL3733_I2C_ADDRESS_SDA_VCC 0x5B
#define IS31FL3733_I2C_ADDRESS_VCC_GND 0x5C
#define IS31FL3733_I2C_ADDRESS_VCC_SCL 0x5D
#define IS31FL3733_I2C_ADDRESS_VCC_SDA 0x5E
#define IS31FL3733_I2C_ADDRESS_VCC_VCC 0x5F

#if defined(RGB_MATRIX_IS31FL3733)
#    define IS31FL3733_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3733_I2C_ADDRESS_4)
#    define IS31FL3733_DRIVER_COUNT 4
#elif defined(IS31FL3733_I2C_ADDRESS_3)
#    define IS31FL3733_DRIVER_COUNT 3
#elif defined(IS31FL3733_I2C_ADDRESS_2)
#    define IS31FL3733_DRIVER_COUNT 2
#elif defined(IS31FL3733_I2C_ADDRESS_1)
#    define IS31FL3733_DRIVER_COUNT 1
#endif

typedef struct is31fl3733_led_t {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED is31fl3733_led_t;

extern const is31fl3733_led_t PROGMEM g_is31fl3733_leds[IS31FL3733_LED_COUNT];

void is31fl3733_init_drivers(void);
void is31fl3733_init(uint8_t index);
void is31fl3733_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3733_select_page(uint8_t index, uint8_t page);

void is31fl3733_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void is31fl3733_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void is31fl3733_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3733_update_pwm_buffers(uint8_t index);
void is31fl3733_update_led_control_registers(uint8_t index);

void is31fl3733_flush(void);

#define IS31FL3733_PDR_0_OHM 0b000   // No pull-down resistor
#define IS31FL3733_PDR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3733_PDR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3733_PDR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3733_PDR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3733_PDR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3733_PDR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3733_PDR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3733_PUR_0_OHM 0b000   // No pull-up resistor
#define IS31FL3733_PUR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3733_PUR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3733_PUR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3733_PUR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3733_PUR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3733_PUR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3733_PUR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3733_PWM_FREQUENCY_8K4_HZ 0b000
#define IS31FL3733_PWM_FREQUENCY_4K2_HZ 0b001
#define IS31FL3733_PWM_FREQUENCY_26K7_HZ 0b010
#define IS31FL3733_PWM_FREQUENCY_2K1_HZ 0b011
#define IS31FL3733_PWM_FREQUENCY_1K05_HZ 0b100

#define IS31FL3733_SYNC_NONE 0b00
#define IS31FL3733_SYNC_MASTER 0b01
#define IS31FL3733_SYNC_SLAVE 0b10

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

#define SW2_CS1 0x10
#define SW2_CS2 0x11
#define SW2_CS3 0x12
#define SW2_CS4 0x13
#define SW2_CS5 0x14
#define SW2_CS6 0x15
#define SW2_CS7 0x16
#define SW2_CS8 0x17
#define SW2_CS9 0x18
#define SW2_CS10 0x19
#define SW2_CS11 0x1A
#define SW2_CS12 0x1B
#define SW2_CS13 0x1C
#define SW2_CS14 0x1D
#define SW2_CS15 0x1E
#define SW2_CS16 0x1F

#define SW3_CS1 0x20
#define SW3_CS2 0x21
#define SW3_CS3 0x22
#define SW3_CS4 0x23
#define SW3_CS5 0x24
#define SW3_CS6 0x25
#define SW3_CS7 0x26
#define SW3_CS8 0x27
#define SW3_CS9 0x28
#define SW3_CS10 0x29
#define SW3_CS11 0x2A
#define SW3_CS12 0x2B
#define SW3_CS13 0x2C
#define SW3_CS14 0x2D
#define SW3_CS15 0x2E
#define SW3_CS16 0x2F

#define SW4_CS1 0x30
#define SW4_CS2 0x31
#define SW4_CS3 0x32
#define SW4_CS4 0x33
#define SW4_CS5 0x34
#define SW4_CS6 0x35
#define SW4_CS7 0x36
#define SW4_CS8 0x37
#define SW4_CS9 0x38
#define SW4_CS10 0x39
#define SW4_CS11 0x3A
#define SW4_CS12 0x3B
#define SW4_CS13 0x3C
#define SW4_CS14 0x3D
#define SW4_CS15 0x3E
#define SW4_CS16 0x3F

#define SW5_CS1 0x40
#define SW5_CS2 0x41
#define SW5_CS3 0x42
#define SW5_CS4 0x43
#define SW5_CS5 0x44
#define SW5_CS6 0x45
#define SW5_CS7 0x46
#define SW5_CS8 0x47
#define SW5_CS9 0x48
#define SW5_CS10 0x49
#define SW5_CS11 0x4A
#define SW5_CS12 0x4B
#define SW5_CS13 0x4C
#define SW5_CS14 0x4D
#define SW5_CS15 0x4E
#define SW5_CS16 0x4F

#define SW6_CS1 0x50
#define SW6_CS2 0x51
#define SW6_CS3 0x52
#define SW6_CS4 0x53
#define SW6_CS5 0x54
#define SW6_CS6 0x55
#define SW6_CS7 0x56
#define SW6_CS8 0x57
#define SW6_CS9 0x58
#define SW6_CS10 0x59
#define SW6_CS11 0x5A
#define SW6_CS12 0x5B
#define SW6_CS13 0x5C
#define SW6_CS14 0x5D
#define SW6_CS15 0x5E
#define SW6_CS16 0x5F

#define SW7_CS1 0x60
#define SW7_CS2 0x61
#define SW7_CS3 0x62
#define SW7_CS4 0x63
#define SW7_CS5 0x64
#define SW7_CS6 0x65
#define SW7_CS7 0x66
#define SW7_CS8 0x67
#define SW7_CS9 0x68
#define SW7_CS10 0x69
#define SW7_CS11 0x6A
#define SW7_CS12 0x6B
#define SW7_CS13 0x6C
#define SW7_CS14 0x6D
#define SW7_CS15 0x6E
#define SW7_CS16 0x6F

#define SW8_CS1 0x70
#define SW8_CS2 0x71
#define SW8_CS3 0x72
#define SW8_CS4 0x73
#define SW8_CS5 0x74
#define SW8_CS6 0x75
#define SW8_CS7 0x76
#define SW8_CS8 0x77
#define SW8_CS9 0x78
#define SW8_CS10 0x79
#define SW8_CS11 0x7A
#define SW8_CS12 0x7B
#define SW8_CS13 0x7C
#define SW8_CS14 0x7D
#define SW8_CS15 0x7E
#define SW8_CS16 0x7F

#define SW9_CS1 0x80
#define SW9_CS2 0x81
#define SW9_CS3 0x82
#define SW9_CS4 0x83
#define SW9_CS5 0x84
#define SW9_CS6 0x85
#define SW9_CS7 0x86
#define SW9_CS8 0x87
#define SW9_CS9 0x88
#define SW9_CS10 0x89
#define SW9_CS11 0x8A
#define SW9_CS12 0x8B
#define SW9_CS13 0x8C
#define SW9_CS14 0x8D
#define SW9_CS15 0x8E
#define SW9_CS16 0x8F

#define SW10_CS1 0x90
#define SW10_CS2 0x91
#define SW10_CS3 0x92
#define SW10_CS4 0x93
#define SW10_CS5 0x94
#define SW10_CS6 0x95
#define SW10_CS7 0x96
#define SW10_CS8 0x97
#define SW10_CS9 0x98
#define SW10_CS10 0x99
#define SW10_CS11 0x9A
#define SW10_CS12 0x9B
#define SW10_CS13 0x9C
#define SW10_CS14 0x9D
#define SW10_CS15 0x9E
#define SW10_CS16 0x9F

#define SW11_CS1 0xA0
#define SW11_CS2 0xA1
#define SW11_CS3 0xA2
#define SW11_CS4 0xA3
#define SW11_CS5 0xA4
#define SW11_CS6 0xA5
#define SW11_CS7 0xA6
#define SW11_CS8 0xA7
#define SW11_CS9 0xA8
#define SW11_CS10 0xA9
#define SW11_CS11 0xAA
#define SW11_CS12 0xAB
#define SW11_CS13 0xAC
#define SW11_CS14 0xAD
#define SW11_CS15 0xAE
#define SW11_CS16 0xAF

#define SW12_CS1 0xB0
#define SW12_CS2 0xB1
#define SW12_CS3 0xB2
#define SW12_CS4 0xB3
#define SW12_CS5 0xB4
#define SW12_CS6 0xB5
#define SW12_CS7 0xB6
#define SW12_CS8 0xB7
#define SW12_CS9 0xB8
#define SW12_CS10 0xB9
#define SW12_CS11 0xBA
#define SW12_CS12 0xBB
#define SW12_CS13 0xBC
#define SW12_CS14 0xBD
#define SW12_CS15 0xBE
#define SW12_CS16 0xBF

// DEPRECATED - DO NOT USE

#define A_1 SW1_CS1
#define A_2 SW1_CS2
#define A_3 SW1_CS3
#define A_4 SW1_CS4
#define A_5 SW1_CS5
#define A_6 SW1_CS6
#define A_7 SW1_CS7
#define A_8 SW1_CS8
#define A_9 SW1_CS9
#define A_10 SW1_CS10
#define A_11 SW1_CS11
#define A_12 SW1_CS12
#define A_13 SW1_CS13
#define A_14 SW1_CS14
#define A_15 SW1_CS15
#define A_16 SW1_CS16

#define B_1 SW2_CS1
#define B_2 SW2_CS2
#define B_3 SW2_CS3
#define B_4 SW2_CS4
#define B_5 SW2_CS5
#define B_6 SW2_CS6
#define B_7 SW2_CS7
#define B_8 SW2_CS8
#define B_9 SW2_CS9
#define B_10 SW2_CS10
#define B_11 SW2_CS11
#define B_12 SW2_CS12
#define B_13 SW2_CS13
#define B_14 SW2_CS14
#define B_15 SW2_CS15
#define B_16 SW2_CS16

#define C_1 SW3_CS1
#define C_2 SW3_CS2
#define C_3 SW3_CS3
#define C_4 SW3_CS4
#define C_5 SW3_CS5
#define C_6 SW3_CS6
#define C_7 SW3_CS7
#define C_8 SW3_CS8
#define C_9 SW3_CS9
#define C_10 SW3_CS10
#define C_11 SW3_CS11
#define C_12 SW3_CS12
#define C_13 SW3_CS13
#define C_14 SW3_CS14
#define C_15 SW3_CS15
#define C_16 SW3_CS16

#define D_1 SW4_CS1
#define D_2 SW4_CS2
#define D_3 SW4_CS3
#define D_4 SW4_CS4
#define D_5 SW4_CS5
#define D_6 SW4_CS6
#define D_7 SW4_CS7
#define D_8 SW4_CS8
#define D_9 SW4_CS9
#define D_10 SW4_CS10
#define D_11 SW4_CS11
#define D_12 SW4_CS12
#define D_13 SW4_CS13
#define D_14 SW4_CS14
#define D_15 SW4_CS15
#define D_16 SW4_CS16

#define E_1 SW5_CS1
#define E_2 SW5_CS2
#define E_3 SW5_CS3
#define E_4 SW5_CS4
#define E_5 SW5_CS5
#define E_6 SW5_CS6
#define E_7 SW5_CS7
#define E_8 SW5_CS8
#define E_9 SW5_CS9
#define E_10 SW5_CS10
#define E_11 SW5_CS11
#define E_12 SW5_CS12
#define E_13 SW5_CS13
#define E_14 SW5_CS14
#define E_15 SW5_CS15
#define E_16 SW5_CS16

#define F_1 SW6_CS1
#define F_2 SW6_CS2
#define F_3 SW6_CS3
#define F_4 SW6_CS4
#define F_5 SW6_CS5
#define F_6 SW6_CS6
#define F_7 SW6_CS7
#define F_8 SW6_CS8
#define F_9 SW6_CS9
#define F_10 SW6_CS10
#define F_11 SW6_CS11
#define F_12 SW6_CS12
#define F_13 SW6_CS13
#define F_14 SW6_CS14
#define F_15 SW6_CS15
#define F_16 SW6_CS16

#define G_1 SW7_CS1
#define G_2 SW7_CS2
#define G_3 SW7_CS3
#define G_4 SW7_CS4
#define G_5 SW7_CS5
#define G_6 SW7_CS6
#define G_7 SW7_CS7
#define G_8 SW7_CS8
#define G_9 SW7_CS9
#define G_10 SW7_CS10
#define G_11 SW7_CS11
#define G_12 SW7_CS12
#define G_13 SW7_CS13
#define G_14 SW7_CS14
#define G_15 SW7_CS15
#define G_16 SW7_CS16

#define H_1 SW8_CS1
#define H_2 SW8_CS2
#define H_3 SW8_CS3
#define H_4 SW8_CS4
#define H_5 SW8_CS5
#define H_6 SW8_CS6
#define H_7 SW8_CS7
#define H_8 SW8_CS8
#define H_9 SW8_CS9
#define H_10 SW8_CS10
#define H_11 SW8_CS11
#define H_12 SW8_CS12
#define H_13 SW8_CS13
#define H_14 SW8_CS14
#define H_15 SW8_CS15
#define H_16 SW8_CS16

#define I_1 SW9_CS1
#define I_2 SW9_CS2
#define I_3 SW9_CS3
#define I_4 SW9_CS4
#define I_5 SW9_CS5
#define I_6 SW9_CS6
#define I_7 SW9_CS7
#define I_8 SW9_CS8
#define I_9 SW9_CS9
#define I_10 SW9_CS10
#define I_11 SW9_CS11
#define I_12 SW9_CS12
#define I_13 SW9_CS13
#define I_14 SW9_CS14
#define I_15 SW9_CS15
#define I_16 SW9_CS16

#define J_1 SW10_CS1
#define J_2 SW10_CS2
#define J_3 SW10_CS3
#define J_4 SW10_CS4
#define J_5 SW10_CS5
#define J_6 SW10_CS6
#define J_7 SW10_CS7
#define J_8 SW10_CS8
#define J_9 SW10_CS9
#define J_10 SW10_CS10
#define J_11 SW10_CS11
#define J_12 SW10_CS12
#define J_13 SW10_CS13
#define J_14 SW10_CS14
#define J_15 SW10_CS15
#define J_16 SW10_CS16

#define K_1 SW11_CS1
#define K_2 SW11_CS2
#define K_3 SW11_CS3
#define K_4 SW11_CS4
#define K_5 SW11_CS5
#define K_6 SW11_CS6
#define K_7 SW11_CS7
#define K_8 SW11_CS8
#define K_9 SW11_CS9
#define K_10 SW11_CS10
#define K_11 SW11_CS11
#define K_12 SW11_CS12
#define K_13 SW11_CS13
#define K_14 SW11_CS14
#define K_15 SW11_CS15
#define K_16 SW11_CS16

#define L_1 SW12_CS1
#define L_2 SW12_CS2
#define L_3 SW12_CS3
#define L_4 SW12_CS4
#define L_5 SW12_CS5
#define L_6 SW12_CS6
#define L_7 SW12_CS7
#define L_8 SW12_CS8
#define L_9 SW12_CS9
#define L_10 SW12_CS10
#define L_11 SW12_CS11
#define L_12 SW12_CS12
#define L_13 SW12_CS13
#define L_14 SW12_CS14
#define L_15 SW12_CS15
#define L_16 SW12_CS16
