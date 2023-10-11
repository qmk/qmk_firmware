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

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef DRIVER_COUNT
#    define SNLED27351_DRIVER_COUNT DRIVER_COUNT
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

#define MSKPHASE_12CHANNEL SNLED27351_MSKPHASE_12CHANNEL
#define MSKPHASE_11CHANNEL SNLED27351_MSKPHASE_11CHANNEL
#define MSKPHASE_10CHANNEL SNLED27351_MSKPHASE_10CHANNEL
#define MSKPHASE_9CHANNEL SNLED27351_MSKPHASE_9CHANNEL
#define MSKPHASE_8CHANNEL SNLED27351_MSKPHASE_8CHANNEL
#define MSKPHASE_7CHANNEL SNLED27351_MSKPHASE_7CHANNEL
#define MSKPHASE_6CHANNEL SNLED27351_MSKPHASE_6CHANNEL
#define MSKPHASE_5CHANNEL SNLED27351_MSKPHASE_5CHANNEL
#define MSKPHASE_4CHANNEL SNLED27351_MSKPHASE_4CHANNEL
#define MSKPHASE_3CHANNEL SNLED27351_MSKPHASE_3CHANNEL
#define MSKPHASE_2CHANNEL SNLED27351_MSKPHASE_2CHANNEL
#define MSKPHASE_1CHANNEL SNLED27351_MSKPHASE_1CHANNEL

#define ckled2001_led snled27351_led_t
#define g_ckled2001_leds g_snled27351_leds
// ========

#define SNLED27351_I2C_ADDRESS_GND 0x74
#define SNLED27351_I2C_ADDRESS_SCL 0x75
#define SNLED27351_I2C_ADDRESS_SDA 0x76
#define SNLED27351_I2C_ADDRESS_VDDIO 0x77

typedef struct snled27351_led_t {
    uint8_t driver : 2;
    uint8_t v;
} __attribute__((packed)) snled27351_led_t;

extern const snled27351_led_t PROGMEM g_snled27351_leds[LED_MATRIX_LED_COUNT];

void snled27351_init(uint8_t addr);
bool snled27351_write_register(uint8_t addr, uint8_t reg, uint8_t data);
bool snled27351_write_pwm_buffer(uint8_t addr, uint8_t *pwm_buffer);

void snled27351_set_value(int index, uint8_t value);
void snled27351_set_value_all(uint8_t value);

void snled27351_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void snled27351_update_pwm_buffers(uint8_t addr, uint8_t index);
void snled27351_update_led_control_registers(uint8_t addr, uint8_t index);

void snled27351_sw_return_normal(uint8_t addr);
void snled27351_sw_shutdown(uint8_t addr);

// Registers Page Define
#define SNLED27351_REG_CONFIGURE_CMD_PAGE 0xFD
#define SNLED27351_LED_CONTROL_PAGE 0x00
#define SNLED27351_LED_PWM_PAGE 0x01
#define SNLED27351_FUNCTION_PAGE 0x03
#define SNLED27351_CURRENT_TUNE_PAGE 0x04

// Function Register: address 0x00
#define SNLED27351_REG_CONFIGURATION 0x00
#define SNLED27351_MSKSW_SHUT_DOWN_MODE (0x0 << 0)
#define SNLED27351_MSKSW_NORMAL_MODE (0x1 << 0)

#define SNLED27351_REG_DRIVER_ID 0x11
#define SNLED27351_DRIVER_ID 0x8A

#define SNLED27351_REG_PDU 0x13
#define SNLED27351_MSKSET_CA_CB_CHANNEL 0xAA
#define SNLED27351_MSKCLR_CA_CB_CHANNEL 0x00

#define SNLED27351_REG_SCAN_PHASE 0x14
#define SNLED27351_MSKPHASE_12CHANNEL 0x00
#define SNLED27351_MSKPHASE_11CHANNEL 0x01
#define SNLED27351_MSKPHASE_10CHANNEL 0x02
#define SNLED27351_MSKPHASE_9CHANNEL 0x03
#define SNLED27351_MSKPHASE_8CHANNEL 0x04
#define SNLED27351_MSKPHASE_7CHANNEL 0x05
#define SNLED27351_MSKPHASE_6CHANNEL 0x06
#define SNLED27351_MSKPHASE_5CHANNEL 0x07
#define SNLED27351_MSKPHASE_4CHANNEL 0x08
#define SNLED27351_MSKPHASE_3CHANNEL 0x09
#define SNLED27351_MSKPHASE_2CHANNEL 0x0A
#define SNLED27351_MSKPHASE_1CHANNEL 0x0B

#define SNLED27351_REG_SLEW_RATE_CONTROL_MODE1 0x15
#define SNLED27351_MSKPWM_DELAY_PHASE_ENABLE 0x04
#define SNLED27351_MSKPWM_DELAY_PHASE_DISABLE 0x00

#define SNLED27351_REG_SLEW_RATE_CONTROL_MODE2 0x16
#define SNLED27351_MSKDRIVING_SINKING_CHANNEL_SLEWRATE_ENABLE 0xC0
#define SNLED27351_MSKDRIVING_SINKING_CHANNEL_SLEWRATE_DISABLE 0x00

#define SNLED27351_REG_OPEN_SHORT_ENABLE 0x17
#define SNLED27351_MSKOPEN_DETECTION_ENABLE (0x01 << 7)
#define SNLED27351_MSKOPEN_DETECTION_DISABLE (0x00)

#define SNLED27351_MSKSHORT_DETECTION_ENABLE (0x01 << 6)
#define SNLED27351_MSKSHORT_DETECTION_DISABLE (0x00)

#define SNLED27351_REG_OPEN_SHORT_DUTY 0x18
#define SNLED27351_REG_OPEN_SHORT_FLAG 0x19

#define SNLED27351_MSKOPEN_DETECTION_INTERRUPT_ENABLE (0x01 << 7)
#define SNLED27351_MSKOPEN_DETECTION_INTERRUPT_DISABLE (0x00)

#define SNLED27351_MSKSHORT_DETECTION_INTERRUPT_ENABLE (0x01 << 6)
#define SNLED27351_MSKSHORT_DETECTION_INTERRUPT_DISABLE (0x00)

#define SNLED27351_REG_SOFTWARE_SLEEP 0x1A
#define SNLED27351_MSKSLEEP_ENABLE 0x02
#define SNLED27351_MSKSLEEP_DISABLE 0x00

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

#define A_1 0x00
#define A_2 0x01
#define A_3 0x02
#define A_4 0x03
#define A_5 0x04
#define A_6 0x05
#define A_7 0x06
#define A_8 0x07
#define A_9 0x08
#define A_10 0x09
#define A_11 0x0A
#define A_12 0x0B
#define A_13 0x0C
#define A_14 0x0D
#define A_15 0x0E
#define A_16 0x0F

#define B_1 0x10
#define B_2 0x11
#define B_3 0x12
#define B_4 0x13
#define B_5 0x14
#define B_6 0x15
#define B_7 0x16
#define B_8 0x17
#define B_9 0x18
#define B_10 0x19
#define B_11 0x1A
#define B_12 0x1B
#define B_13 0x1C
#define B_14 0x1D
#define B_15 0x1E
#define B_16 0x1F

#define C_1 0x20
#define C_2 0x21
#define C_3 0x22
#define C_4 0x23
#define C_5 0x24
#define C_6 0x25
#define C_7 0x26
#define C_8 0x27
#define C_9 0x28
#define C_10 0x29
#define C_11 0x2A
#define C_12 0x2B
#define C_13 0x2C
#define C_14 0x2D
#define C_15 0x2E
#define C_16 0x2F

#define D_1 0x30
#define D_2 0x31
#define D_3 0x32
#define D_4 0x33
#define D_5 0x34
#define D_6 0x35
#define D_7 0x36
#define D_8 0x37
#define D_9 0x38
#define D_10 0x39
#define D_11 0x3A
#define D_12 0x3B
#define D_13 0x3C
#define D_14 0x3D
#define D_15 0x3E
#define D_16 0x3F

#define E_1 0x40
#define E_2 0x41
#define E_3 0x42
#define E_4 0x43
#define E_5 0x44
#define E_6 0x45
#define E_7 0x46
#define E_8 0x47
#define E_9 0x48
#define E_10 0x49
#define E_11 0x4A
#define E_12 0x4B
#define E_13 0x4C
#define E_14 0x4D
#define E_15 0x4E
#define E_16 0x4F

#define F_1 0x50
#define F_2 0x51
#define F_3 0x52
#define F_4 0x53
#define F_5 0x54
#define F_6 0x55
#define F_7 0x56
#define F_8 0x57
#define F_9 0x58
#define F_10 0x59
#define F_11 0x5A
#define F_12 0x5B
#define F_13 0x5C
#define F_14 0x5D
#define F_15 0x5E
#define F_16 0x5F

#define G_1 0x60
#define G_2 0x61
#define G_3 0x62
#define G_4 0x63
#define G_5 0x64
#define G_6 0x65
#define G_7 0x66
#define G_8 0x67
#define G_9 0x68
#define G_10 0x69
#define G_11 0x6A
#define G_12 0x6B
#define G_13 0x6C
#define G_14 0x6D
#define G_15 0x6E
#define G_16 0x6F

#define H_1 0x70
#define H_2 0x71
#define H_3 0x72
#define H_4 0x73
#define H_5 0x74
#define H_6 0x75
#define H_7 0x76
#define H_8 0x77
#define H_9 0x78
#define H_10 0x79
#define H_11 0x7A
#define H_12 0x7B
#define H_13 0x7C
#define H_14 0x7D
#define H_15 0x7E
#define H_16 0x7F

#define I_1 0x80
#define I_2 0x81
#define I_3 0x82
#define I_4 0x83
#define I_5 0x84
#define I_6 0x85
#define I_7 0x86
#define I_8 0x87
#define I_9 0x88
#define I_10 0x89
#define I_11 0x8A
#define I_12 0x8B
#define I_13 0x8C
#define I_14 0x8D
#define I_15 0x8E
#define I_16 0x8F

#define J_1 0x90
#define J_2 0x91
#define J_3 0x92
#define J_4 0x93
#define J_5 0x94
#define J_6 0x95
#define J_7 0x96
#define J_8 0x97
#define J_9 0x98
#define J_10 0x99
#define J_11 0x9A
#define J_12 0x9B
#define J_13 0x9C
#define J_14 0x9D
#define J_15 0x9E
#define J_16 0x9F

#define K_1 0xA0
#define K_2 0xA1
#define K_3 0xA2
#define K_4 0xA3
#define K_5 0xA4
#define K_6 0xA5
#define K_7 0xA6
#define K_8 0xA7
#define K_9 0xA8
#define K_10 0xA9
#define K_11 0xAA
#define K_12 0xAB
#define K_13 0xAC
#define K_14 0xAD
#define K_15 0xAE
#define K_16 0xAF

#define L_1 0xB0
#define L_2 0xB1
#define L_3 0xB2
#define L_4 0xB3
#define L_5 0xB4
#define L_6 0xB5
#define L_7 0xB6
#define L_8 0xB7
#define L_9 0xB8
#define L_10 0xB9
#define L_11 0xBA
#define L_12 0xBB
#define L_13 0xBC
#define L_14 0xBD
#define L_15 0xBE
#define L_16 0xBF
