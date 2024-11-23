/* Copyright 2018 Jason Williams (Wilba)
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
#ifdef ISSI_TIMEOUT
#    define IS31FL3736_I2C_TIMEOUT ISSI_TIMEOUT
#endif
#ifdef ISSI_PERSISTENCE
#    define IS31FL3736_I2C_PERSISTENCE ISSI_PERSISTENCE
#endif
#ifdef ISSI_SWPULLUP
#    define IS31FL3736_SW_PULLUP ISSI_SWPULLUP
#endif
#ifdef ISSI_CSPULLUP
#    define IS31FL3736_CS_PULLDOWN ISSI_CSPULLUP
#endif
#ifdef ISSI_GLOBALCURRENT
#    define IS31FL3736_GLOBAL_CURRENT ISSI_GLOBALCURRENT
#endif

#define is31_led is31fl3736_led_t
#define g_is31_leds g_is31fl3736_leds

#define PUR_0R IS31FL3736_PUR_0_OHM
#define PUR_05KR IS31FL3736_PUR_05K_OHM
#define PUR_1KR IS31FL3736_PUR_1K_OHM
#define PUR_2KR IS31FL3736_PUR_2K_OHM
#define PUR_4KR IS31FL3736_PUR_4K_OHM
#define PUR_8KR IS31FL3736_PUR_8K_OHM
#define PUR_16KR IS31FL3736_PUR_16K_OHM
#define PUR_32KR IS31FL3736_PUR_32K_OHM
// ========

#define IS31FL3736_REG_INTERRUPT_MASK 0xF0
#define IS31FL3736_REG_INTERRUPT_STATUS 0xF1

#define IS31FL3736_REG_COMMAND 0xFD

#define IS31FL3736_COMMAND_LED_CONTROL 0x00
#define IS31FL3736_COMMAND_PWM 0x01
#define IS31FL3736_COMMAND_AUTO_BREATH 0x02
#define IS31FL3736_COMMAND_FUNCTION 0x03

#define IS31FL3736_FUNCTION_REG_CONFIGURATION 0x00
#define IS31FL3736_FUNCTION_REG_GLOBAL_CURRENT 0x01
#define IS31FL3736_FUNCTION_REG_SW_PULLUP 0x0F
#define IS31FL3736_FUNCTION_REG_CS_PULLDOWN 0x10
#define IS31FL3736_FUNCTION_REG_RESET 0x11

#define IS31FL3736_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3736_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3736_I2C_ADDRESS_GND_GND 0x50
#define IS31FL3736_I2C_ADDRESS_GND_SCL 0x51
#define IS31FL3736_I2C_ADDRESS_GND_SDA 0x52
#define IS31FL3736_I2C_ADDRESS_GND_VCC 0x53
#define IS31FL3736_I2C_ADDRESS_SCL_GND 0x54
#define IS31FL3736_I2C_ADDRESS_SCL_SCL 0x55
#define IS31FL3736_I2C_ADDRESS_SCL_SDA 0x56
#define IS31FL3736_I2C_ADDRESS_SCL_VCC 0x57
#define IS31FL3736_I2C_ADDRESS_SDA_GND 0x58
#define IS31FL3736_I2C_ADDRESS_SDA_SCL 0x59
#define IS31FL3736_I2C_ADDRESS_SDA_SDA 0x5A
#define IS31FL3736_I2C_ADDRESS_SDA_VCC 0x5B
#define IS31FL3736_I2C_ADDRESS_VCC_GND 0x5C
#define IS31FL3736_I2C_ADDRESS_VCC_SCL 0x5D
#define IS31FL3736_I2C_ADDRESS_VCC_SDA 0x5E
#define IS31FL3736_I2C_ADDRESS_VCC_VCC 0x5F

#if defined(LED_MATRIX_IS31FL3736)
#    define IS31FL3736_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3736_I2C_ADDRESS_4)
#    define IS31FL3736_DRIVER_COUNT 4
#elif defined(IS31FL3736_I2C_ADDRESS_3)
#    define IS31FL3736_DRIVER_COUNT 3
#elif defined(IS31FL3736_I2C_ADDRESS_2)
#    define IS31FL3736_DRIVER_COUNT 2
#elif defined(IS31FL3736_I2C_ADDRESS_1)
#    define IS31FL3736_DRIVER_COUNT 1
#endif

typedef struct is31fl3736_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED is31fl3736_led_t;

extern const is31fl3736_led_t PROGMEM g_is31fl3736_leds[IS31FL3736_LED_COUNT];

void is31fl3736_init_drivers(void);
void is31fl3736_init(uint8_t index);
void is31fl3736_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3736_select_page(uint8_t index, uint8_t page);

void is31fl3736_set_value(int index, uint8_t value);
void is31fl3736_set_value_all(uint8_t value);

void is31fl3736_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3736_update_pwm_buffers(uint8_t index);
void is31fl3736_update_led_control_registers(uint8_t index);

void is31fl3736_flush(void);

#define IS31FL3736_PDR_0_OHM 0b000   // No pull-down resistor
#define IS31FL3736_PDR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3736_PDR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3736_PDR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3736_PDR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3736_PDR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3736_PDR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3736_PDR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3736_PUR_0_OHM 0b000   // No pull-up resistor
#define IS31FL3736_PUR_0K5_OHM 0b001 // 0.5 kOhm resistor
#define IS31FL3736_PUR_1K_OHM 0b010  // 1 kOhm resistor
#define IS31FL3736_PUR_2K_OHM 0b011  // 2 kOhm resistor
#define IS31FL3736_PUR_4K_OHM 0b100  // 4 kOhm resistor
#define IS31FL3736_PUR_8K_OHM 0b101  // 8 kOhm resistor
#define IS31FL3736_PUR_16K_OHM 0b110 // 16 kOhm resistor
#define IS31FL3736_PUR_32K_OHM 0b111 // 32 kOhm resistor

#define IS31FL3736_PWM_FREQUENCY_8K4_HZ 0b000
#define IS31FL3736_PWM_FREQUENCY_4K2_HZ 0b001
#define IS31FL3736_PWM_FREQUENCY_26K7_HZ 0b010
#define IS31FL3736_PWM_FREQUENCY_2K1_HZ 0b011
#define IS31FL3736_PWM_FREQUENCY_1K05_HZ 0b100

#define SW1_CS1 0x00
#define SW1_CS2 0x02
#define SW1_CS3 0x04
#define SW1_CS4 0x06
#define SW1_CS5 0x08
#define SW1_CS6 0x0A
#define SW1_CS7 0x0C
#define SW1_CS8 0x0E

#define SW2_CS1 0x10
#define SW2_CS2 0x12
#define SW2_CS3 0x14
#define SW2_CS4 0x16
#define SW2_CS5 0x18
#define SW2_CS6 0x1A
#define SW2_CS7 0x1C
#define SW2_CS8 0x1E

#define SW3_CS1 0x20
#define SW3_CS2 0x22
#define SW3_CS3 0x24
#define SW3_CS4 0x26
#define SW3_CS5 0x28
#define SW3_CS6 0x2A
#define SW3_CS7 0x2C
#define SW3_CS8 0x2E

#define SW4_CS1 0x30
#define SW4_CS2 0x32
#define SW4_CS3 0x34
#define SW4_CS4 0x36
#define SW4_CS5 0x38
#define SW4_CS6 0x3A
#define SW4_CS7 0x3C
#define SW4_CS8 0x3E

#define SW5_CS1 0x40
#define SW5_CS2 0x42
#define SW5_CS3 0x44
#define SW5_CS4 0x46
#define SW5_CS5 0x48
#define SW5_CS6 0x4A
#define SW5_CS7 0x4C
#define SW5_CS8 0x4E

#define SW6_CS1 0x50
#define SW6_CS2 0x52
#define SW6_CS3 0x54
#define SW6_CS4 0x56
#define SW6_CS5 0x58
#define SW6_CS6 0x5A
#define SW6_CS7 0x5C
#define SW6_CS8 0x5E

#define SW7_CS1 0x60
#define SW7_CS2 0x62
#define SW7_CS3 0x64
#define SW7_CS4 0x66
#define SW7_CS5 0x68
#define SW7_CS6 0x6A
#define SW7_CS7 0x6C
#define SW7_CS8 0x6E

#define SW8_CS1 0x70
#define SW8_CS2 0x72
#define SW8_CS3 0x74
#define SW8_CS4 0x76
#define SW8_CS5 0x78
#define SW8_CS6 0x7A
#define SW8_CS7 0x7C
#define SW8_CS8 0x7E

#define SW9_CS1 0x80
#define SW9_CS2 0x82
#define SW9_CS3 0x84
#define SW9_CS4 0x86
#define SW9_CS5 0x88
#define SW9_CS6 0x8A
#define SW9_CS7 0x8C
#define SW9_CS8 0x8E

#define SW10_CS1 0x90
#define SW10_CS2 0x92
#define SW10_CS3 0x94
#define SW10_CS4 0x96
#define SW10_CS5 0x98
#define SW10_CS6 0x9A
#define SW10_CS7 0x9C
#define SW10_CS8 0x9E

#define SW11_CS1 0xA0
#define SW11_CS2 0xA2
#define SW11_CS3 0xA4
#define SW11_CS4 0xA6
#define SW11_CS5 0xA8
#define SW11_CS6 0xAA
#define SW11_CS7 0xAC
#define SW11_CS8 0xAE

#define SW12_CS1 0xB0
#define SW12_CS2 0xB2
#define SW12_CS3 0xB4
#define SW12_CS4 0xB6
#define SW12_CS5 0xB8
#define SW12_CS6 0xBA
#define SW12_CS7 0xBC
#define SW12_CS8 0xBE

// DEPRECATED - DO NOT USE

#define A_1 SW1_CS1
#define A_2 SW1_CS2
#define A_3 SW1_CS3
#define A_4 SW1_CS4
#define A_5 SW1_CS5
#define A_6 SW1_CS6
#define A_7 SW1_CS7
#define A_8 SW1_CS8

#define B_1 SW2_CS1
#define B_2 SW2_CS2
#define B_3 SW2_CS3
#define B_4 SW2_CS4
#define B_5 SW2_CS5
#define B_6 SW2_CS6
#define B_7 SW2_CS7
#define B_8 SW2_CS8

#define C_1 SW3_CS1
#define C_2 SW3_CS2
#define C_3 SW3_CS3
#define C_4 SW3_CS4
#define C_5 SW3_CS5
#define C_6 SW3_CS6
#define C_7 SW3_CS7
#define C_8 SW3_CS8

#define D_1 SW4_CS1
#define D_2 SW4_CS2
#define D_3 SW4_CS3
#define D_4 SW4_CS4
#define D_5 SW4_CS5
#define D_6 SW4_CS6
#define D_7 SW4_CS7
#define D_8 SW4_CS8

#define E_1 SW5_CS1
#define E_2 SW5_CS2
#define E_3 SW5_CS3
#define E_4 SW5_CS4
#define E_5 SW5_CS5
#define E_6 SW5_CS6
#define E_7 SW5_CS7
#define E_8 SW5_CS8

#define F_1 SW6_CS1
#define F_2 SW6_CS2
#define F_3 SW6_CS3
#define F_4 SW6_CS4
#define F_5 SW6_CS5
#define F_6 SW6_CS6
#define F_7 SW6_CS7
#define F_8 SW6_CS8

#define G_1 SW7_CS1
#define G_2 SW7_CS2
#define G_3 SW7_CS3
#define G_4 SW7_CS4
#define G_5 SW7_CS5
#define G_6 SW7_CS6
#define G_7 SW7_CS7
#define G_8 SW7_CS8

#define H_1 SW8_CS1
#define H_2 SW8_CS2
#define H_3 SW8_CS3
#define H_4 SW8_CS4
#define H_5 SW8_CS5
#define H_6 SW8_CS6
#define H_7 SW8_CS7
#define H_8 SW8_CS8

#define I_1 SW9_CS1
#define I_2 SW9_CS2
#define I_3 SW9_CS3
#define I_4 SW9_CS4
#define I_5 SW9_CS5
#define I_6 SW9_CS6
#define I_7 SW9_CS7
#define I_8 SW9_CS8

#define J_1 SW10_CS1
#define J_2 SW10_CS2
#define J_3 SW10_CS3
#define J_4 SW10_CS4
#define J_5 SW10_CS5
#define J_6 SW10_CS6
#define J_7 SW10_CS7
#define J_8 SW10_CS8

#define K_1 SW11_CS1
#define K_2 SW11_CS2
#define K_3 SW11_CS3
#define K_4 SW11_CS4
#define K_5 SW11_CS5
#define K_6 SW11_CS6
#define K_7 SW11_CS7
#define K_8 SW11_CS8

#define L_1 SW12_CS1
#define L_2 SW12_CS2
#define L_3 SW12_CS3
#define L_4 SW12_CS4
#define L_5 SW12_CS5
#define L_6 SW12_CS6
#define L_7 SW12_CS7
#define L_8 SW12_CS8
