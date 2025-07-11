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

#if defined(LED_MATRIX_SNLED27351_SPI)
#    define SNLED27351_LED_COUNT LED_MATRIX_LED_COUNT
#endif

#define SNLED27351_DRIVER_COUNT (sizeof(cs_pins) / sizeof(pin_t))
typedef struct snled27351_led_t {
    uint8_t driver : 2;
    uint8_t v;
} PACKED snled27351_led_t;

extern const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT];

void snled27351_init_drivers(void);
void snled27351_init(uint8_t index);
bool snled27351_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data);
bool snled27351_write_pwm_buffer(uint8_t index, uint8_t *pwm_buffer);

void snled27351_set_value(int index, uint8_t value);
void snled27351_set_value_all(uint8_t value);

void snled27351_set_led_control_register(uint8_t index, bool value);

// This should not be called from an interrupt
// (eg. from a timer interrupt).
// Call this while idle (in between matrix scans).
// If the buffer is dirty, it will update the driver with the buffer.
void snled27351_update_pwm_buffers(uint8_t index);
void snled27351_update_led_control_registers(uint8_t index);
void snled27351_flush(void);
void snled27351_shutdown(void);
void snled27351_exit_shutdown(void);
void snled27351_sw_return_normal(uint8_t index);
void snled27351_sw_shutdown(uint8_t index);

// Registers Page Define
#define CONFIGURE_CMD_PAGE 0xFD
#define LED_CONTROL_PAGE 0x00
#define LED_PWM_PAGE 0x01
#define FUNCTION_PAGE 0x03
#define CURRENT_TUNE_PAGE 0x04

// Function Register: address 0x00
#define CONFIGURATION_REG 0x00
#define MSKSW_SHUT_DOWN_MODE (0x0 << 0)
#define MSKSW_NORMAL_MODE (0x1 << 0)

#define DRIVER_ID_REG 0x11
#define SNLED27351_ID 0x8A

#define PDU_REG 0x13
#define MSKSET_CA_CB_CHANNEL 0xAA
#define MSKCLR_CA_CB_CHANNEL 0x00

#define SCAN_PHASE_REG 0x14
#define MSKPHASE_12CHANNEL 0x00
#define MSKPHASE_11CHANNEL 0x01
#define MSKPHASE_10CHANNEL 0x02
#define MSKPHASE_9CHANNEL 0x03
#define MSKPHASE_8CHANNEL 0x04
#define MSKPHASE_7CHANNEL 0x05
#define MSKPHASE_6CHANNEL 0x06
#define MSKPHASE_5CHANNEL 0x07
#define MSKPHASE_4CHANNEL 0x08
#define MSKPHASE_3CHANNEL 0x09
#define MSKPHASE_2CHANNEL 0x0A
#define MSKPHASE_1CHANNEL 0x0B

#define SLEW_RATE_CONTROL_MODE1_REG 0x15
#define MSKPWM_DELAY_PHASE_ENABLE 0x04
#define MSKPWM_DELAY_PHASE_DISABLE 0x00

#define SLEW_RATE_CONTROL_MODE2_REG 0x16
#define MSKDRIVING_SINKING_CHHANNEL_SLEWRATE_ENABLE 0xC0
#define MSKDRIVING_SINKING_CHHANNEL_SLEWRATE_DISABLE 0x00

#define OPEN_SHORT_ENABLE_REG 0x17
#define MSKOPEN_DETECTION_ENABLE (0x01 << 7)
#define MSKOPEN_DETECTION_DISABLE (0x00)

#define MSKSHORT_DETECTION_ENABLE (0x01 << 6)
#define MSKSHORT_DETECTION_DISABLE (0x00)

#define OPEN_SHORT_DUTY_REG 0x18
#define OPEN_SHORT_FLAG_REG 0x19

#define MSKOPEN_DETECTION_INTERRUPT_ENABLE (0x01 << 7)
#define MSKOPEN_DETECTION_INTERRUPT_DISABLE (0x00)

#define MSKSHORT_DETECTION_INTERRUPT_ENABLE (0x01 << 6)
#define MSKSHORT_DETECTION_INTERRUPT_DISABLE (0x00)

#define SOFTWARE_SLEEP_REG 0x1A
#define MSKSLEEP_ENABLE 0x02
#define MSKSLEEP_DISABLE 0x00

// LED Control Registers
#define LED_CONTROL_ON_OFF_FIRST_ADDR 0x0
#define LED_CONTROL_ON_OFF_LAST_ADDR 0x17
#define LED_CONTROL_ON_OFF_LENGTH ((LED_CONTROL_ON_OFF_LAST_ADDR - LED_CONTROL_ON_OFF_FIRST_ADDR) + 1)

#define LED_CONTROL_OPEN_FIRST_ADDR 0x18
#define LED_CONTROL_OPEN_LAST_ADDR 0x2F
#define LED_CONTROL_OPEN_LENGTH ((LED_CONTROL_OPEN_LAST_ADDR - LED_CONTROL_OPEN_FIRST_ADDR) + 1)

#define LED_CONTROL_SHORT_FIRST_ADDR 0x30
#define LED_CONTROL_SHORT_LAST_ADDR 0x47
#define LED_CONTROL_SHORT_LENGTH ((LED_CONTROL_SHORT_LAST_ADDR - LED_CONTROL_SHORT_FIRST_ADDR) + 1)

#define LED_CONTROL_PAGE_LENGTH 0x48

// LED Control Registers
#define LED_PWM_FIRST_ADDR 0x00
#define LED_PWM_LAST_ADDR 0xBF
#define LED_PWM_LENGTH 0xC0

// Current Tune Registers
#define LED_CURRENT_TUNE_FIRST_ADDR 0x00
#define LED_CURRENT_TUNE_LAST_ADDR 0x0B
#define LED_CURRENT_TUNE_LENGTH 0x0C

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
