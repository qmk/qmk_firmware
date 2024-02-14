/* Copyright 2017 Jason Williams
 * Copyright 2018 Jack Humbert
 * Copyright 2019 Clueboard
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
#ifdef LED_DRIVER_ADDR_1
#    define IS31FL3731_I2C_ADDRESS_1 LED_DRIVER_ADDR_1
#endif
#ifdef LED_DRIVER_ADDR_2
#    define IS31FL3731_I2C_ADDRESS_2 LED_DRIVER_ADDR_2
#endif
#ifdef LED_DRIVER_ADDR_3
#    define IS31FL3731_I2C_ADDRESS_3 LED_DRIVER_ADDR_3
#endif
#ifdef LED_DRIVER_ADDR_4
#    define IS31FL3731_I2C_ADDRESS_4 LED_DRIVER_ADDR_4
#endif
#ifdef ISSI_TIMEOUT
#    define IS31FL3731_I2C_TIMEOUT ISSI_TIMEOUT
#endif
#ifdef ISSI_PERSISTENCE
#    define IS31FL3731_I2C_PERSISTENCE ISSI_PERSISTENCE
#endif
#ifdef ISSI_3731_DEGHOST
#    define IS31FL3731_DEGHOST ISSI_3731_DEGHOST
#endif

#define is31_led is31fl3731_led_t
#define g_is31_leds g_is31fl3731_leds
// ========

#define IS31FL3731_REG_COMMAND 0xFD
#define IS31FL3731_COMMAND_FRAME_1 0x00
#define IS31FL3731_COMMAND_FRAME_2 0x01
#define IS31FL3731_COMMAND_FRAME_3 0x02
#define IS31FL3731_COMMAND_FRAME_4 0x03
#define IS31FL3731_COMMAND_FRAME_5 0x04
#define IS31FL3731_COMMAND_FRAME_6 0x05
#define IS31FL3731_COMMAND_FRAME_7 0x06
#define IS31FL3731_COMMAND_FRAME_8 0x07
#define IS31FL3731_COMMAND_FUNCTION 0x0B

#define IS31FL3731_FUNCTION_REG_CONFIG 0x00
#define IS31FL3731_CONFIG_MODE_PICTURE 0x00
#define IS31FL3731_CONFIG_MODE_AUTO_PLAY 0x08
#define IS31FL3731_CONFIG_MODE_AUDIO_PLAY 0x18

#define IS31FL3731_FUNCTION_REG_PICTURE_DISPLAY 0x01
#define IS31FL3731_FUNCTION_REG_AUDIO_SYNC 0x06
#define IS31FL3731_FUNCTION_REG_SHUTDOWN 0x0A

// Not defined in the datasheet -- See AN for IC
#define IS31FL3731_FUNCTION_REG_GHOST_IMAGE_PREVENTION 0xC2
#define IS31FL3731_GHOST_IMAGE_PREVENTION_GEN 0x10

#define IS31FL3731_I2C_ADDRESS_GND 0x74
#define IS31FL3731_I2C_ADDRESS_SCL 0x75
#define IS31FL3731_I2C_ADDRESS_SDA 0x76
#define IS31FL3731_I2C_ADDRESS_VCC 0x77

#if defined(LED_MATRIX_IS31FL3731)
#    define IS31FL3731_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#if defined IS31FL3731_I2C_ADDRESS_4
#    define IS31FL3731_DRIVER_COUNT 4
#elif defined IS31FL3731_I2C_ADDRESS_3
#    define IS31FL3731_DRIVER_COUNT 3
#elif defined IS31FL3731_I2C_ADDRESS_2
#    define IS31FL3731_DRIVER_COUNT 2
#elif defined IS31FL3731_I2C_ADDRESS_1
#    define IS31FL3731_DRIVER_COUNT 1
#endif

typedef struct is31fl3731_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED is31fl3731_led_t;

extern const is31fl3731_led_t PROGMEM g_is31fl3731_leds[IS31FL3731_LED_COUNT];

void is31fl3731_init_drivers(void);
void is31fl3731_init(uint8_t addr);
void is31fl3731_write_register(uint8_t addr, uint8_t reg, uint8_t data);
void is31fl3731_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void is31fl3731_set_value(int index, uint8_t value);
void is31fl3731_set_value_all(uint8_t value);

void is31fl3731_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void is31fl3731_update_pwm_buffers(uint8_t addr, uint8_t index);
void is31fl3731_update_led_control_registers(uint8_t addr, uint8_t index);

void is31fl3731_flush(void);

#define C1_1 0x24
#define C1_2 0x25
#define C1_3 0x26
#define C1_4 0x27
#define C1_5 0x28
#define C1_6 0x29
#define C1_7 0x2A
#define C1_8 0x2B

#define C1_9 0x2C
#define C1_10 0x2D
#define C1_11 0x2E
#define C1_12 0x2F
#define C1_13 0x30
#define C1_14 0x31
#define C1_15 0x32
#define C1_16 0x33

#define C2_1 0x34
#define C2_2 0x35
#define C2_3 0x36
#define C2_4 0x37
#define C2_5 0x38
#define C2_6 0x39
#define C2_7 0x3A
#define C2_8 0x3B

#define C2_9 0x3C
#define C2_10 0x3D
#define C2_11 0x3E
#define C2_12 0x3F
#define C2_13 0x40
#define C2_14 0x41
#define C2_15 0x42
#define C2_16 0x43

#define C3_1 0x44
#define C3_2 0x45
#define C3_3 0x46
#define C3_4 0x47
#define C3_5 0x48
#define C3_6 0x49
#define C3_7 0x4A
#define C3_8 0x4B

#define C3_9 0x4C
#define C3_10 0x4D
#define C3_11 0x4E
#define C3_12 0x4F
#define C3_13 0x50
#define C3_14 0x51
#define C3_15 0x52
#define C3_16 0x53

#define C4_1 0x54
#define C4_2 0x55
#define C4_3 0x56
#define C4_4 0x57
#define C4_5 0x58
#define C4_6 0x59
#define C4_7 0x5A
#define C4_8 0x5B

#define C4_9 0x5C
#define C4_10 0x5D
#define C4_11 0x5E
#define C4_12 0x5F
#define C4_13 0x60
#define C4_14 0x61
#define C4_15 0x62
#define C4_16 0x63

#define C5_1 0x64
#define C5_2 0x65
#define C5_3 0x66
#define C5_4 0x67
#define C5_5 0x68
#define C5_6 0x69
#define C5_7 0x6A
#define C5_8 0x6B

#define C5_9 0x6C
#define C5_10 0x6D
#define C5_11 0x6E
#define C5_12 0x6F
#define C5_13 0x70
#define C5_14 0x71
#define C5_15 0x72
#define C5_16 0x73

#define C6_1 0x74
#define C6_2 0x75
#define C6_3 0x76
#define C6_4 0x77
#define C6_5 0x78
#define C6_6 0x79
#define C6_7 0x7A
#define C6_8 0x7B

#define C6_9 0x7C
#define C6_10 0x7D
#define C6_11 0x7E
#define C6_12 0x7F
#define C6_13 0x80
#define C6_14 0x81
#define C6_15 0x82
#define C6_16 0x83

#define C7_1 0x84
#define C7_2 0x85
#define C7_3 0x86
#define C7_4 0x87
#define C7_5 0x88
#define C7_6 0x89
#define C7_7 0x8A
#define C7_8 0x8B

#define C7_9 0x8C
#define C7_10 0x8D
#define C7_11 0x8E
#define C7_12 0x8F
#define C7_13 0x90
#define C7_14 0x91
#define C7_15 0x92
#define C7_16 0x93

#define C8_1 0x94
#define C8_2 0x95
#define C8_3 0x96
#define C8_4 0x97
#define C8_5 0x98
#define C8_6 0x99
#define C8_7 0x9A
#define C8_8 0x9B

#define C8_9 0x9C
#define C8_10 0x9D
#define C8_11 0x9E
#define C8_12 0x9F
#define C8_13 0xA0
#define C8_14 0xA1
#define C8_15 0xA2
#define C8_16 0xA3

#define C9_1 0xA4
#define C9_2 0xA5
#define C9_3 0xA6
#define C9_4 0xA7
#define C9_5 0xA8
#define C9_6 0xA9
#define C9_7 0xAA
#define C9_8 0xAB

#define C9_9 0xAC
#define C9_10 0xAD
#define C9_11 0xAE
#define C9_12 0xAF
#define C9_13 0xB0
#define C9_14 0xB1
#define C9_15 0xB2
#define C9_16 0xB3
