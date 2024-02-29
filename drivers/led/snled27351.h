/* Copyright 2021 @ Keychron (https://www.keychron.com)
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
#    define SNLED27351_I2C_ADDRESS_1 DRIVER_ADDR_1
#endif
#ifdef DRIVER_ADDR_2
#    define SNLED27351_I2C_ADDRESS_2 DRIVER_ADDR_2
#endif
#ifdef DRIVER_ADDR_3
#    define SNLED27351_I2C_ADDRESS_3 DRIVER_ADDR_3
#endif
#ifdef DRIVER_ADDR_4
#    define SNLED27351_I2C_ADDRESS_4 DRIVER_ADDR_4
#endif
#ifdef CKLED2001_TIMEOUT
#    define SNLED27351_I2C_TIMEOUT CKLED2001_TIMEOUT
#endif
#ifdef CKLED2001_PERSISTENCE
#    define SNLED27351_I2C_PERSISTENCE CKLED2001_PERSISTENCE
#endif
#ifdef PHASE_CHANNEL
#    define SNLED27351_PHASE_CHANNEL PHASE_CHANNEL
#endif
#ifdef CKLED2001_CURRENT_TUNE
#    define SNLED27351_CURRENT_TUNE CKLED2001_CURRENT_TUNE
#endif

#define MSKPHASE_12CHANNEL SNLED27351_SCAN_PHASE_12_CHANNEL
#define MSKPHASE_11CHANNEL SNLED27351_SCAN_PHASE_11_CHANNEL
#define MSKPHASE_10CHANNEL SNLED27351_SCAN_PHASE_10_CHANNEL
#define MSKPHASE_9CHANNEL SNLED27351_SCAN_PHASE_9_CHANNEL
#define MSKPHASE_8CHANNEL SNLED27351_SCAN_PHASE_8_CHANNEL
#define MSKPHASE_7CHANNEL SNLED27351_SCAN_PHASE_7_CHANNEL
#define MSKPHASE_6CHANNEL SNLED27351_SCAN_PHASE_6_CHANNEL
#define MSKPHASE_5CHANNEL SNLED27351_SCAN_PHASE_5_CHANNEL
#define MSKPHASE_4CHANNEL SNLED27351_SCAN_PHASE_4_CHANNEL
#define MSKPHASE_3CHANNEL SNLED27351_SCAN_PHASE_3_CHANNEL
#define MSKPHASE_2CHANNEL SNLED27351_SCAN_PHASE_2_CHANNEL
#define MSKPHASE_1CHANNEL SNLED27351_SCAN_PHASE_1_CHANNEL

#define ckled2001_led snled27351_led_t
#define g_ckled2001_leds g_snled27351_leds
// ========

#define SNLED27351_REG_COMMAND 0xFD
#define SNLED27351_COMMAND_LED_CONTROL 0x00
#define SNLED27351_COMMAND_PWM 0x01
#define SNLED27351_COMMAND_FUNCTION 0x03
#define SNLED27351_COMMAND_CURRENT_TUNE 0x04

#define SNLED27351_FUNCTION_REG_SOFTWARE_SHUTDOWN 0x00
#define SNLED27351_SOFTWARE_SHUTDOWN_SSD_SHUTDOWN (0x0 << 0)
#define SNLED27351_SOFTWARE_SHUTDOWN_SSD_NORMAL (0x1 << 0)

#define SNLED27351_FUNCTION_REG_ID 0x11
#define SNLED27351_DRIVER_ID 0x8A

#define SNLED27351_FUNCTION_REG_PULLDOWNUP 0x13
#define SNLED27351_PULLDOWNUP_ALL_ENABLED 0xAA

#define SNLED27351_FUNCTION_REG_SCAN_PHASE 0x14
#define SNLED27351_SCAN_PHASE_12_CHANNEL 0x00
#define SNLED27351_SCAN_PHASE_11_CHANNEL 0x01
#define SNLED27351_SCAN_PHASE_10_CHANNEL 0x02
#define SNLED27351_SCAN_PHASE_9_CHANNEL 0x03
#define SNLED27351_SCAN_PHASE_8_CHANNEL 0x04
#define SNLED27351_SCAN_PHASE_7_CHANNEL 0x05
#define SNLED27351_SCAN_PHASE_6_CHANNEL 0x06
#define SNLED27351_SCAN_PHASE_5_CHANNEL 0x07
#define SNLED27351_SCAN_PHASE_4_CHANNEL 0x08
#define SNLED27351_SCAN_PHASE_3_CHANNEL 0x09
#define SNLED27351_SCAN_PHASE_2_CHANNEL 0x0A
#define SNLED27351_SCAN_PHASE_1_CHANNEL 0x0B

#define SNLED27351_FUNCTION_REG_SLEW_RATE_CONTROL_MODE_1 0x15
#define SNLED27351_SLEW_RATE_CONTROL_MODE_1_PDP_ENABLE (0b1 << 2)

#define SNLED27351_FUNCTION_REG_SLEW_RATE_CONTROL_MODE_2 0x16
#define SNLED27351_SLEW_RATE_CONTROL_MODE_2_SSL_ENABLE (0b1 << 6)
#define SNLED27351_SLEW_RATE_CONTROL_MODE_2_DSL_ENABLE (0b1 << 7)

#define SNLED27351_FUNCTION_REG_OPEN_SHORT_ENABLE 0x17
#define SNLED27351_OPEN_SHORT_ENABLE_SDS_ENABLE (0b1 << 6)
#define SNLED27351_OPEN_SHORT_ENABLE_ODS_ENABLE (0b1 << 7)

#define SNLED27351_FUNCTION_REG_OPEN_SHORT_DUTY 0x18

#define SNLED27351_FUNCTION_REG_OPEN_SHORT_FLAG 0x19
#define SNLED27351_OPEN_SHORT_FLAG_OSINT_ENABLE (0b1 << 6)
#define SNLED27351_OPEN_SHORT_FLAG_ODINT_ENABLE (0b1 << 7)

#define SNLED27351_FUNCTION_REG_SOFTWARE_SLEEP 0x1A
#define SNLED27351_SOFTWARE_SLEEP_ENABLE (0b1 << 1)

// LED Control Registers
#define SNLED27351_LED_CONTROL_ON_OFF_FIRST_ADDR 0x0
#define SNLED27351_LED_CONTROL_ON_OFF_LAST_ADDR 0x17
#define SNLED27351_LED_CONTROL_ON_OFF_LENGTH ((SNLED27351_LED_CONTROL_ON_OFF_LAST_ADDR - SNLED27351_LED_CONTROL_ON_OFF_FIRST_ADDR) + 1)

#define SNLED27351_LED_CONTROL_OPEN_FIRST_ADDR 0x18
#define SNLED27351_LED_CONTROL_OPEN_LAST_ADDR 0x2F
#define SNLED27351_LED_CONTROL_OPEN_LENGTH ((SNLED27351_LED_CONTROL_OPEN_LAST_ADDR - SNLED27351_LED_CONTROL_OPEN_FIRST_ADDR) + 1)

#define SNLED27351_LED_CONTROL_SHORT_FIRST_ADDR 0x30
#define SNLED27351_LED_CONTROL_SHORT_LAST_ADDR 0x47
#define SNLED27351_LED_CONTROL_SHORT_LENGTH ((SNLED27351_LED_CONTROL_SHORT_LAST_ADDR - SNLED27351_LED_CONTROL_SHORT_FIRST_ADDR) + 1)

#define SNLED27351_LED_CONTROL_PAGE_LENGTH 0x48

// LED Control Registers
#define SNLED27351_LED_PWM_FIRST_ADDR 0x00
#define SNLED27351_LED_PWM_LAST_ADDR 0xBF
#define SNLED27351_LED_PWM_LENGTH 0xC0

// Current Tune Registers
#define SNLED27351_LED_CURRENT_TUNE_FIRST_ADDR 0x00
#define SNLED27351_LED_CURRENT_TUNE_LAST_ADDR 0x0B
#define SNLED27351_LED_CURRENT_TUNE_LENGTH 0x0C

#define SNLED27351_I2C_ADDRESS_GND 0x74
#define SNLED27351_I2C_ADDRESS_SCL 0x75
#define SNLED27351_I2C_ADDRESS_SDA 0x76
#define SNLED27351_I2C_ADDRESS_VDDIO 0x77

#if defined(RGB_MATRIX_SNLED27351)
#    define SNLED27351_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(SNLED27351_I2C_ADDRESS_4)
#    define SNLED27351_DRIVER_COUNT 4
#elif defined(SNLED27351_I2C_ADDRESS_3)
#    define SNLED27351_DRIVER_COUNT 3
#elif defined(SNLED27351_I2C_ADDRESS_2)
#    define SNLED27351_DRIVER_COUNT 2
#elif defined(SNLED27351_I2C_ADDRESS_1)
#    define SNLED27351_DRIVER_COUNT 1
#endif

typedef struct snled27351_led_t {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED snled27351_led_t;

extern const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT];

void snled27351_init_drivers(void);
void snled27351_init(uint8_t index);
void snled27351_select_page(uint8_t index, uint8_t page);
void snled27351_write_register(uint8_t index, uint8_t reg, uint8_t data);

void snled27351_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void snled27351_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void snled27351_set_led_control_register(uint8_t index, bool red, bool green, bool blue);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void snled27351_update_pwm_buffers(uint8_t index);
void snled27351_update_led_control_registers(uint8_t index);

void snled27351_flush(void);

void snled27351_sw_return_normal(uint8_t index);
void snled27351_sw_shutdown(uint8_t index);

#define CB1_CA1 0x00
#define CB1_CA2 0x01
#define CB1_CA3 0x02
#define CB1_CA4 0x03
#define CB1_CA5 0x04
#define CB1_CA6 0x05
#define CB1_CA7 0x06
#define CB1_CA8 0x07
#define CB1_CA9 0x08
#define CB1_CA10 0x09
#define CB1_CA11 0x0A
#define CB1_CA12 0x0B
#define CB1_CA13 0x0C
#define CB1_CA14 0x0D
#define CB1_CA15 0x0E
#define CB1_CA16 0x0F

#define CB2_CA1 0x10
#define CB2_CA2 0x11
#define CB2_CA3 0x12
#define CB2_CA4 0x13
#define CB2_CA5 0x14
#define CB2_CA6 0x15
#define CB2_CA7 0x16
#define CB2_CA8 0x17
#define CB2_CA9 0x18
#define CB2_CA10 0x19
#define CB2_CA11 0x1A
#define CB2_CA12 0x1B
#define CB2_CA13 0x1C
#define CB2_CA14 0x1D
#define CB2_CA15 0x1E
#define CB2_CA16 0x1F

#define CB3_CA1 0x20
#define CB3_CA2 0x21
#define CB3_CA3 0x22
#define CB3_CA4 0x23
#define CB3_CA5 0x24
#define CB3_CA6 0x25
#define CB3_CA7 0x26
#define CB3_CA8 0x27
#define CB3_CA9 0x28
#define CB3_CA10 0x29
#define CB3_CA11 0x2A
#define CB3_CA12 0x2B
#define CB3_CA13 0x2C
#define CB3_CA14 0x2D
#define CB3_CA15 0x2E
#define CB3_CA16 0x2F

#define CB4_CA1 0x30
#define CB4_CA2 0x31
#define CB4_CA3 0x32
#define CB4_CA4 0x33
#define CB4_CA5 0x34
#define CB4_CA6 0x35
#define CB4_CA7 0x36
#define CB4_CA8 0x37
#define CB4_CA9 0x38
#define CB4_CA10 0x39
#define CB4_CA11 0x3A
#define CB4_CA12 0x3B
#define CB4_CA13 0x3C
#define CB4_CA14 0x3D
#define CB4_CA15 0x3E
#define CB4_CA16 0x3F

#define CB5_CA1 0x40
#define CB5_CA2 0x41
#define CB5_CA3 0x42
#define CB5_CA4 0x43
#define CB5_CA5 0x44
#define CB5_CA6 0x45
#define CB5_CA7 0x46
#define CB5_CA8 0x47
#define CB5_CA9 0x48
#define CB5_CA10 0x49
#define CB5_CA11 0x4A
#define CB5_CA12 0x4B
#define CB5_CA13 0x4C
#define CB5_CA14 0x4D
#define CB5_CA15 0x4E
#define CB5_CA16 0x4F

#define CB6_CA1 0x50
#define CB6_CA2 0x51
#define CB6_CA3 0x52
#define CB6_CA4 0x53
#define CB6_CA5 0x54
#define CB6_CA6 0x55
#define CB6_CA7 0x56
#define CB6_CA8 0x57
#define CB6_CA9 0x58
#define CB6_CA10 0x59
#define CB6_CA11 0x5A
#define CB6_CA12 0x5B
#define CB6_CA13 0x5C
#define CB6_CA14 0x5D
#define CB6_CA15 0x5E
#define CB6_CA16 0x5F

#define CB7_CA1 0x60
#define CB7_CA2 0x61
#define CB7_CA3 0x62
#define CB7_CA4 0x63
#define CB7_CA5 0x64
#define CB7_CA6 0x65
#define CB7_CA7 0x66
#define CB7_CA8 0x67
#define CB7_CA9 0x68
#define CB7_CA10 0x69
#define CB7_CA11 0x6A
#define CB7_CA12 0x6B
#define CB7_CA13 0x6C
#define CB7_CA14 0x6D
#define CB7_CA15 0x6E
#define CB7_CA16 0x6F

#define CB8_CA1 0x70
#define CB8_CA2 0x71
#define CB8_CA3 0x72
#define CB8_CA4 0x73
#define CB8_CA5 0x74
#define CB8_CA6 0x75
#define CB8_CA7 0x76
#define CB8_CA8 0x77
#define CB8_CA9 0x78
#define CB8_CA10 0x79
#define CB8_CA11 0x7A
#define CB8_CA12 0x7B
#define CB8_CA13 0x7C
#define CB8_CA14 0x7D
#define CB8_CA15 0x7E
#define CB8_CA16 0x7F

#define CB9_CA1 0x80
#define CB9_CA2 0x81
#define CB9_CA3 0x82
#define CB9_CA4 0x83
#define CB9_CA5 0x84
#define CB9_CA6 0x85
#define CB9_CA7 0x86
#define CB9_CA8 0x87
#define CB9_CA9 0x88
#define CB9_CA10 0x89
#define CB9_CA11 0x8A
#define CB9_CA12 0x8B
#define CB9_CA13 0x8C
#define CB9_CA14 0x8D
#define CB9_CA15 0x8E
#define CB9_CA16 0x8F

#define CB10_CA1 0x90
#define CB10_CA2 0x91
#define CB10_CA3 0x92
#define CB10_CA4 0x93
#define CB10_CA5 0x94
#define CB10_CA6 0x95
#define CB10_CA7 0x96
#define CB10_CA8 0x97
#define CB10_CA9 0x98
#define CB10_CA10 0x99
#define CB10_CA11 0x9A
#define CB10_CA12 0x9B
#define CB10_CA13 0x9C
#define CB10_CA14 0x9D
#define CB10_CA15 0x9E
#define CB10_CA16 0x9F

#define CB11_CA1 0xA0
#define CB11_CA2 0xA1
#define CB11_CA3 0xA2
#define CB11_CA4 0xA3
#define CB11_CA5 0xA4
#define CB11_CA6 0xA5
#define CB11_CA7 0xA6
#define CB11_CA8 0xA7
#define CB11_CA9 0xA8
#define CB11_CA10 0xA9
#define CB11_CA11 0xAA
#define CB11_CA12 0xAB
#define CB11_CA13 0xAC
#define CB11_CA14 0xAD
#define CB11_CA15 0xAE
#define CB11_CA16 0xAF

#define CB12_CA1 0xB0
#define CB12_CA2 0xB1
#define CB12_CA3 0xB2
#define CB12_CA4 0xB3
#define CB12_CA5 0xB4
#define CB12_CA6 0xB5
#define CB12_CA7 0xB6
#define CB12_CA8 0xB7
#define CB12_CA9 0xB8
#define CB12_CA10 0xB9
#define CB12_CA11 0xBA
#define CB12_CA12 0xBB
#define CB12_CA13 0xBC
#define CB12_CA14 0xBD
#define CB12_CA15 0xBE
#define CB12_CA16 0xBF

// DEPRECATED - DO NOT USE

#define A_1 CB1_CA1
#define A_2 CB1_CA2
#define A_3 CB1_CA3
#define A_4 CB1_CA4
#define A_5 CB1_CA5
#define A_6 CB1_CA6
#define A_7 CB1_CA7
#define A_8 CB1_CA8
#define A_9 CB1_CA9
#define A_10 CB1_CA10
#define A_11 CB1_CA11
#define A_12 CB1_CA12
#define A_13 CB1_CA13
#define A_14 CB1_CA14
#define A_15 CB1_CA15
#define A_16 CB1_CA16

#define B_1 CB2_CA1
#define B_2 CB2_CA2
#define B_3 CB2_CA3
#define B_4 CB2_CA4
#define B_5 CB2_CA5
#define B_6 CB2_CA6
#define B_7 CB2_CA7
#define B_8 CB2_CA8
#define B_9 CB2_CA9
#define B_10 CB2_CA10
#define B_11 CB2_CA11
#define B_12 CB2_CA12
#define B_13 CB2_CA13
#define B_14 CB2_CA14
#define B_15 CB2_CA15
#define B_16 CB2_CA16

#define C_1 CB3_CA1
#define C_2 CB3_CA2
#define C_3 CB3_CA3
#define C_4 CB3_CA4
#define C_5 CB3_CA5
#define C_6 CB3_CA6
#define C_7 CB3_CA7
#define C_8 CB3_CA8
#define C_9 CB3_CA9
#define C_10 CB3_CA10
#define C_11 CB3_CA11
#define C_12 CB3_CA12
#define C_13 CB3_CA13
#define C_14 CB3_CA14
#define C_15 CB3_CA15
#define C_16 CB3_CA16

#define D_1 CB4_CA1
#define D_2 CB4_CA2
#define D_3 CB4_CA3
#define D_4 CB4_CA4
#define D_5 CB4_CA5
#define D_6 CB4_CA6
#define D_7 CB4_CA7
#define D_8 CB4_CA8
#define D_9 CB4_CA9
#define D_10 CB4_CA10
#define D_11 CB4_CA11
#define D_12 CB4_CA12
#define D_13 CB4_CA13
#define D_14 CB4_CA14
#define D_15 CB4_CA15
#define D_16 CB4_CA16

#define E_1 CB5_CA1
#define E_2 CB5_CA2
#define E_3 CB5_CA3
#define E_4 CB5_CA4
#define E_5 CB5_CA5
#define E_6 CB5_CA6
#define E_7 CB5_CA7
#define E_8 CB5_CA8
#define E_9 CB5_CA9
#define E_10 CB5_CA10
#define E_11 CB5_CA11
#define E_12 CB5_CA12
#define E_13 CB5_CA13
#define E_14 CB5_CA14
#define E_15 CB5_CA15
#define E_16 CB5_CA16

#define F_1 CB6_CA1
#define F_2 CB6_CA2
#define F_3 CB6_CA3
#define F_4 CB6_CA4
#define F_5 CB6_CA5
#define F_6 CB6_CA6
#define F_7 CB6_CA7
#define F_8 CB6_CA8
#define F_9 CB6_CA9
#define F_10 CB6_CA10
#define F_11 CB6_CA11
#define F_12 CB6_CA12
#define F_13 CB6_CA13
#define F_14 CB6_CA14
#define F_15 CB6_CA15
#define F_16 CB6_CA16

#define G_1 CB7_CA1
#define G_2 CB7_CA2
#define G_3 CB7_CA3
#define G_4 CB7_CA4
#define G_5 CB7_CA5
#define G_6 CB7_CA6
#define G_7 CB7_CA7
#define G_8 CB7_CA8
#define G_9 CB7_CA9
#define G_10 CB7_CA10
#define G_11 CB7_CA11
#define G_12 CB7_CA12
#define G_13 CB7_CA13
#define G_14 CB7_CA14
#define G_15 CB7_CA15
#define G_16 CB7_CA16

#define H_1 CB8_CA1
#define H_2 CB8_CA2
#define H_3 CB8_CA3
#define H_4 CB8_CA4
#define H_5 CB8_CA5
#define H_6 CB8_CA6
#define H_7 CB8_CA7
#define H_8 CB8_CA8
#define H_9 CB8_CA9
#define H_10 CB8_CA10
#define H_11 CB8_CA11
#define H_12 CB8_CA12
#define H_13 CB8_CA13
#define H_14 CB8_CA14
#define H_15 CB8_CA15
#define H_16 CB8_CA16

#define I_1 CB9_CA1
#define I_2 CB9_CA2
#define I_3 CB9_CA3
#define I_4 CB9_CA4
#define I_5 CB9_CA5
#define I_6 CB9_CA6
#define I_7 CB9_CA7
#define I_8 CB9_CA8
#define I_9 CB9_CA9
#define I_10 CB9_CA10
#define I_11 CB9_CA11
#define I_12 CB9_CA12
#define I_13 CB9_CA13
#define I_14 CB9_CA14
#define I_15 CB9_CA15
#define I_16 CB9_CA16

#define J_1 CB10_CA1
#define J_2 CB10_CA2
#define J_3 CB10_CA3
#define J_4 CB10_CA4
#define J_5 CB10_CA5
#define J_6 CB10_CA6
#define J_7 CB10_CA7
#define J_8 CB10_CA8
#define J_9 CB10_CA9
#define J_10 CB10_CA10
#define J_11 CB10_CA11
#define J_12 CB10_CA12
#define J_13 CB10_CA13
#define J_14 CB10_CA14
#define J_15 CB10_CA15
#define J_16 CB10_CA16

#define K_1 CB11_CA1
#define K_2 CB11_CA2
#define K_3 CB11_CA3
#define K_4 CB11_CA4
#define K_5 CB11_CA5
#define K_6 CB11_CA6
#define K_7 CB11_CA7
#define K_8 CB11_CA8
#define K_9 CB11_CA9
#define K_10 CB11_CA10
#define K_11 CB11_CA11
#define K_12 CB11_CA12
#define K_13 CB11_CA13
#define K_14 CB11_CA14
#define K_15 CB11_CA15
#define K_16 CB11_CA16

#define L_1 CB12_CA1
#define L_2 CB12_CA2
#define L_3 CB12_CA3
#define L_4 CB12_CA4
#define L_5 CB12_CA5
#define L_6 CB12_CA6
#define L_7 CB12_CA7
#define L_8 CB12_CA8
#define L_9 CB12_CA9
#define L_10 CB12_CA10
#define L_11 CB12_CA11
#define L_12 CB12_CA12
#define L_13 CB12_CA13
#define L_14 CB12_CA14
#define L_15 CB12_CA15
#define L_16 CB12_CA16
