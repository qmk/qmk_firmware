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

#define IS31FL3746A_REG_ID 0xFC

#define IS31FL3746A_REG_COMMAND 0xFD

#define IS31FL3746A_COMMAND_PWM 0x00
#define IS31FL3746A_COMMAND_SCALING 0x01
#define IS31FL3746A_COMMAND_FUNCTION 0x01

#define IS31FL3746A_FUNCTION_REG_CONFIGURATION 0x50
#define IS31FL3746A_FUNCTION_REG_GLOBAL_CURRENT 0x51
#define IS31FL3746A_FUNCTION_REG_PULLDOWNUP 0x52
#define IS31FL3746A_FUNCTION_REG_TEMPERATURE 0x5F
#define IS31FL3746A_FUNCTION_REG_SPREAD_SPECTRUM 0x60
#define IS31FL3746A_FUNCTION_REG_RESET 0x8F
#define IS31FL3746A_FUNCTION_REG_PWM_ENABLE 0xE0
#define IS31FL3746A_FUNCTION_REG_PWM_FREQUENCY 0xE2

#define IS31FL3746A_REG_COMMAND_WRITE_LOCK 0xFE
#define IS31FL3746A_COMMAND_WRITE_LOCK_MAGIC 0xC5

#define IS31FL3746A_I2C_ADDRESS_GND_GND 0x60
#define IS31FL3746A_I2C_ADDRESS_GND_SCL 0x61
#define IS31FL3746A_I2C_ADDRESS_GND_SDA 0x62
#define IS31FL3746A_I2C_ADDRESS_GND_VCC 0x63
#define IS31FL3746A_I2C_ADDRESS_SCL_GND 0x64
#define IS31FL3746A_I2C_ADDRESS_SCL_SCL 0x65
#define IS31FL3746A_I2C_ADDRESS_SCL_SDA 0x66
#define IS31FL3746A_I2C_ADDRESS_SCL_VCC 0x67
#define IS31FL3746A_I2C_ADDRESS_SDA_GND 0x68
#define IS31FL3746A_I2C_ADDRESS_SDA_SCL 0x69
#define IS31FL3746A_I2C_ADDRESS_SDA_SDA 0x6A
#define IS31FL3746A_I2C_ADDRESS_SDA_VCC 0x6B
#define IS31FL3746A_I2C_ADDRESS_VCC_GND 0x6C
#define IS31FL3746A_I2C_ADDRESS_VCC_SCL 0x6D
#define IS31FL3746A_I2C_ADDRESS_VCC_SDA 0x6E
#define IS31FL3746A_I2C_ADDRESS_VCC_VCC 0x6F

#if defined(LED_MATRIX_IS31FL3746A)
#    define IS31FL3746A_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#if defined(IS31FL3746A_I2C_ADDRESS_4)
#    define IS31FL3746A_DRIVER_COUNT 4
#elif defined(IS31FL3746A_I2C_ADDRESS_3)
#    define IS31FL3746A_DRIVER_COUNT 3
#elif defined(IS31FL3746A_I2C_ADDRESS_2)
#    define IS31FL3746A_DRIVER_COUNT 2
#elif defined(IS31FL3746A_I2C_ADDRESS_1)
#    define IS31FL3746A_DRIVER_COUNT 1
#endif

typedef struct is31fl3746a_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED is31fl3746a_led_t;

extern const is31fl3746a_led_t PROGMEM g_is31fl3746a_leds[IS31FL3746A_LED_COUNT];

void is31fl3746a_init_drivers(void);
void is31fl3746a_init(uint8_t index);
void is31fl3746a_write_register(uint8_t index, uint8_t reg, uint8_t data);
void is31fl3746a_select_page(uint8_t index, uint8_t page);

void is31fl3746a_set_value(int index, uint8_t value);
void is31fl3746a_set_value_all(uint8_t value);

void is31fl3746a_set_scaling_register(uint8_t index, uint8_t value);

void is31fl3746a_update_pwm_buffers(uint8_t index);
void is31fl3746a_update_scaling_registers(uint8_t index);

void is31fl3746a_flush(void);

#define IS31FL3746A_PDR_0_OHM 0b000          // No pull-down resistor
#define IS31FL3746A_PDR_0K5_OHM_SW_OFF 0b001 // 0.5 kOhm resistor in SWx off time
#define IS31FL3746A_PDR_1K_OHM_SW_OFF 0b010  // 1 kOhm resistor in SWx off time
#define IS31FL3746A_PDR_2K_OHM_SW_OFF 0b011  // 2 kOhm resistor in SWx off time
#define IS31FL3746A_PDR_1K_OHM 0b100         // 1 kOhm resistor
#define IS31FL3746A_PDR_2K_OHM 0b101         // 2 kOhm resistor
#define IS31FL3746A_PDR_4K_OHM 0b110         // 4 kOhm resistor
#define IS31FL3746A_PDR_8K_OHM 0b111         // 8 kOhm resistor

#define IS31FL3746A_PUR_0_OHM 0b000          // No pull-up resistor
#define IS31FL3746A_PUR_0K5_OHM_CS_OFF 0b001 // 0.5 kOhm resistor in CSy off time
#define IS31FL3746A_PUR_1K_OHM_CS_OFF 0b010  // 1 kOhm resistor in CSy off time
#define IS31FL3746A_PUR_2K_OHM_CS_OFF 0b011  // 2 kOhm resistor in CSy off time
#define IS31FL3746A_PUR_1K_OHM 0b100         // 1 kOhm resistor
#define IS31FL3746A_PUR_2K_OHM 0b101         // 2 kOhm resistor
#define IS31FL3746A_PUR_4K_OHM 0b110         // 4 kOhm resistor
#define IS31FL3746A_PUR_8K_OHM 0b111         // 8 kOhm resistor

#define IS31FL3746A_PWM_FREQUENCY_29K_HZ 0b000
#define IS31FL3746A_PWM_FREQUENCY_14K5_HZ 0b001
#define IS31FL3746A_PWM_FREQUENCY_7K25_HZ 0b010
#define IS31FL3746A_PWM_FREQUENCY_3K63_HZ 0b011
#define IS31FL3746A_PWM_FREQUENCY_1K81_HZ 0b100
#define IS31FL3746A_PWM_FREQUENCY_906_HZ 0b101
#define IS31FL3746A_PWM_FREQUENCY_453_HZ 0b110

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
