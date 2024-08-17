/* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#if defined(RGB_MATRIX_SN3734_SPI)
#    define SN3734_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

typedef struct sn3734_led_t {
    uint8_t  driver : 2;
    uint16_t r : 9;
    uint16_t g : 9;
    uint16_t b : 9;
} PACKED sn3734_led_t;

extern const sn3734_led_t PROGMEM g_sn3734_leds[SN3734_LED_COUNT];

void sn3734_init_drivers(void);
void sn3734_init(uint8_t index);
bool sn3734_write_register(uint8_t index, uint8_t page, uint8_t reg, uint8_t data);
bool sn3734_write_pwm_buffer(uint8_t index, uint8_t *pwm_buffer);

void sn3734_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void sn3734_set_color_all(uint8_t red, uint8_t green, uint8_t blue);

void sn3734_update_pwm_buffers(uint8_t index);
void sn3734_set_pwm_buffer(const sn3734_led_t *pled, uint8_t red, uint8_t green, uint8_t blue);

void sn3734_flush(void);
void sn3734_shutdown(void);
void sn3734_exit_shutdown(void);
void sn3734_sw_return_normal(uint8_t index);
void sn3734_sw_shutdown(uint8_t index);

// Registers Pages
#define SN3734_PWM_PAGE 0x00
#define SN3734_FUNC_PAGE 0x01

// Registers 
#define SN3734_PWM_PAGE_PWM_START 0x01  // 0x01 ~ 0xFC
#define SN3734_FUNC_PAGE_PWM_START 0x01  // 0x01 ~ 0x48
#define SN3734_SCALING_START 0x49
#define SN3734_FUNC_REG_CONFIGURATION 0x60
#define SN3734_FUNC_REG_GLOBAL_CURRENT 0x61
#define SN3734_FUNC_REG_PULLDOWNUP 0x62
#define SN3734_FUNC_REG_SRS 0x63
#define SN3734_FUNC_REG_CS_PULLUP 0x91
#define SN3734_FUNC_REG_RESET 0xDF
#define SN3734_FUNC_REG_PWM_UPDATE 0xFD

#define SN3734_PWM_PAGE_REGISTER_COUNT 252
#define SN3734_FUNC_PAGE_REGISTER_COUNT 72
#define SN3734_PWM_REGISTER_COUNT (SN3734_PWM_PAGE_REGISTER_COUNT + SN3734_FUNC_PAGE_REGISTER_COUNT)
#define SCALING_REG_LEN 18

// Configuration Register
#define SN3734_SHUT_DOWN_MODE (0x0 << 0)
#define SN3734_NORMAL_MODE (0x1 << 0)

#define SN3734_PWM_MODE_6_2 (0b00 << 1)
#define SN3734_PWM_MODE_8 (0b01 << 1)
#define SN3734_PWM_MODE_8_4 (0b10 << 1)
#define SN3734_PWM_MODE_12 (0b11 << 1)

#define SN3734_SWS_ALL (0b0000 << 4)
#define SN3734_SWS_11 (0b0001 << 4)
#define SN3734_SWS_10 (0b0010 << 4)
#define SN3734_SWS_9 (0b0011 << 4)
#define SN3734_SWS_8 (0b0100 << 4)
#define SN3734_SWS_7 (0b0101 << 4)
#define SN3734_SWS_6 (0b0110 << 4)
#define SN3734_SWS_5 (0b0111 << 4)
#define SN3734_SWS_4 (0b1000 << 4)
#define SN3734_SWS_3 (0b1001 << 4)
#define SN3734_SWS_2 (0b1010 << 4)
#define SN3734_SWS_ALL_2SW (0b1011 << 4)
#define SN3734_SWS_10_2SW (0b1100 << 4)
#define SN3734_SWS_ALL_3SW (0b1101 << 4)
#define SN3734_SWS_ALL_4SW (0b1110 << 4)
#define SN3734_SWS_ALL_6SW (0b1111 << 4)

// Pull Down/Up Resistor Selection Register
#define SN3734_SWPDR_FLOATING 0b000 // Floating
#define SN3734_SWPDR_3V2 0b001      // 3.2V
#define SN3734_SWPDR_2V8 0b010      // 2.8V
#define SN3734_SWPDR_2V4 0b011      // 2.4V
#define SN3734_SWPDR_2V0 0b100      // 2.0V
#define SN3734_SWPDR_1V6 0b101      // 1.6V
#define SN3734_SWPDR_1V2 0b110      // 1.2V
#define SN3734_SWPDR_GND 0b111      // GND

#define SN3734_CSPUR_FLOATING (0b000 << 4)       // Floating
#define SN3734_CSPUR_PVCC_MINUS_3V2 (0b001 << 4) // PVCC-3.2V
#define SN3734_CSPUR_PVCC_MINUS_2V8 (0b010 << 4) // PVCC-2.8V
#define SN3734_CSPUR_PVCC_MINUS_2V4 (0b011 << 4) // PVCC-2.4V
#define SN3734_CSPUR_PVCC_MINUS_2V0 (0b100 << 4) // PVCC-2.0V
#define SN3734_CSPUR_PVCC_MINUS_1V6 (0b101 << 4) // PVCC-1.6V
#define SN3734_CSPUR_PVCC_MINUS_1V2 (0b110 << 4) // PVCC-1.2V
#define SN3734_CSPUR_PVCC (0b111 << 4)           // PVCC

#define SN3734_PHASE_180_DEGREE (0x01 << 7)

// SRS Enable Register

// Scan rate frequency of 8 bit
#define SN3734_PWM_FREQUENCY_6K_HZ 0b000
#define SN3734_PWM_FREQUENCY_8k_HZ 0b001
#define SN3734_PWM_FREQUENCY_1K5_HZ 0b010
#define SN3734_PWM_FREQUENCY_750_HZ 0b011
#define SN3734_PWM_FREQUENCY_375_HZ 0b100
#define SN3734_PWM_FREQUENCY_188HZ 0b101

// PWM register address mappings
#define CS1_SW1 0x00
#define CS1_SW2 0x01
#define CS1_SW3 0x03
#define CS1_SW4 0x04
#define CS1_SW5 0x06
#define CS1_SW6 0x07
#define CS1_SW7 0x09
#define CS1_SW8 0x0A
#define CS1_SW9 0x0C
#define CS1_SW10 0x0D
#define CS1_SW11 0x0F
#define CS1_SW12 0x10

#define CS2_SW1 0x12
#define CS2_SW2 0x13
#define CS2_SW3 0x15
#define CS2_SW4 0x16
#define CS2_SW5 0x18
#define CS2_SW6 0x19
#define CS2_SW7 0x1B
#define CS2_SW8 0x1C
#define CS2_SW9 0x1E
#define CS2_SW10 0x1F
#define CS2_SW11 0x21
#define CS2_SW12 0x22

#define CS3_SW1 0x24
#define CS3_SW2 0x25
#define CS3_SW3 0x27
#define CS3_SW4 0x28
#define CS3_SW5 0x2A
#define CS3_SW6 0x2B
#define CS3_SW7 0x2D
#define CS3_SW8 0x2E
#define CS3_SW9 0x30
#define CS3_SW10 0x31
#define CS3_SW11 0x33
#define CS3_SW12 0x34

#define CS4_SW1 0x36
#define CS4_SW2 0x37
#define CS4_SW3 0x39
#define CS4_SW4 0x3A
#define CS4_SW5 0x3C
#define CS4_SW6 0x3D
#define CS4_SW7 0x3F
#define CS4_SW8 0x40
#define CS4_SW9 0x42
#define CS4_SW10 0x43
#define CS4_SW11 0x45
#define CS4_SW12 0x46

#define CS5_SW1 0x48
#define CS5_SW2 0x49
#define CS5_SW3 0x4B
#define CS5_SW4 0x4C
#define CS5_SW5 0x4E
#define CS5_SW6 0x4F
#define CS5_SW7 0x51
#define CS5_SW8 0x52
#define CS5_SW9 0x54
#define CS5_SW10 0x55
#define CS5_SW11 0x57
#define CS5_SW12 0x58

#define CS6_SW1 0x5A
#define CS6_SW2 0x5B
#define CS6_SW3 0x5D
#define CS6_SW4 0x5E
#define CS6_SW5 0x60
#define CS6_SW6 0x61
#define CS6_SW7 0x63
#define CS6_SW8 0x64
#define CS6_SW9 0x66
#define CS6_SW10 0x67
#define CS6_SW11 0x69
#define CS6_SW12 0x6A

#define CS7_SW1 0x6C
#define CS7_SW2 0x6D
#define CS7_SW3 0x6F
#define CS7_SW4 0x70
#define CS7_SW5 0x72
#define CS7_SW6 0x73
#define CS7_SW7 0x75
#define CS7_SW8 0x76
#define CS7_SW9 0x78
#define CS7_SW10 0x79
#define CS7_SW11 0x7B
#define CS7_SW12 0x7C

#define CS8_SW1 0x7E
#define CS8_SW2 0x7F
#define CS8_SW3 0x81
#define CS8_SW4 0x82
#define CS8_SW5 0x84
#define CS8_SW6 0x85
#define CS8_SW7 0x87
#define CS8_SW8 0x88
#define CS8_SW9 0x8A
#define CS8_SW10 0x8B
#define CS8_SW11 0x8D
#define CS8_SW12 0x8E

#define CS9_SW1 0x90
#define CS9_SW2 0x91
#define CS9_SW3 0x93
#define CS9_SW4 0x94
#define CS9_SW5 0x96
#define CS9_SW6 0x97
#define CS9_SW7 0x99
#define CS9_SW8 0x9A
#define CS9_SW9 0x9C
#define CS9_SW10 0x9D
#define CS9_SW11 0x9F
#define CS9_SW12 0xA0

#define CS10_SW1 0xA2
#define CS10_SW2 0xA3
#define CS10_SW3 0xA5
#define CS10_SW4 0xA6
#define CS10_SW5 0xA8
#define CS10_SW6 0xA9
#define CS10_SW7 0xAB
#define CS10_SW8 0xAC
#define CS10_SW9 0xAE
#define CS10_SW10 0xAF
#define CS10_SW11 0xB1
#define CS10_SW12 0xB2

#define CS11_SW1 0xB4
#define CS11_SW2 0xB5
#define CS11_SW3 0xB7
#define CS11_SW4 0xB8
#define CS11_SW5 0xBA
#define CS11_SW6 0xBB
#define CS11_SW7 0xBD
#define CS11_SW8 0xBE
#define CS11_SW9 0xC0
#define CS11_SW10 0xC1
#define CS11_SW11 0xC3
#define CS11_SW12 0xC4

#define CS12_SW1 0xC6
#define CS12_SW2 0xC7
#define CS12_SW3 0xC9
#define CS12_SW4 0xCA
#define CS12_SW5 0xCC
#define CS12_SW6 0xCD
#define CS12_SW7 0xCF
#define CS12_SW8 0xD0
#define CS12_SW9 0xD2
#define CS12_SW10 0xD3
#define CS12_SW11 0xD5
#define CS12_SW12 0xD6

#define CS13_SW1 0xD8
#define CS13_SW2 0xD9
#define CS13_SW3 0xDB
#define CS13_SW4 0xDC
#define CS13_SW5 0xDE
#define CS13_SW6 0xDF
#define CS13_SW7 0xE1
#define CS13_SW8 0xE2
#define CS13_SW9 0xE4
#define CS13_SW10 0xE5
#define CS13_SW11 0xE7
#define CS13_SW12 0xE8

#define CS14_SW1 0xEA
#define CS14_SW2 0xEB
#define CS14_SW3 0xED
#define CS14_SW4 0xEE
#define CS14_SW5 0xF0
#define CS14_SW6 0xF1
#define CS14_SW7 0xF3
#define CS14_SW8 0xF4
#define CS14_SW9 0xF6
#define CS14_SW10 0xF7
#define CS14_SW11 0xF9
#define CS14_SW12 0xFA

#define CS15_SW1 (0x00 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW2 (0x01 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW3 (0x03 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW4 (0x04 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW5 (0x06 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW6 (0x07 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW7 (0x09 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW8 (0x0A + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW9 (0x0C + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW10 (0x0D + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW11 (0x0F + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS15_SW12 (0x10 + SN3734_PWM_PAGE_REGISTER_COUNT)

#define CS16_SW1 (0x12 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW2 (0x13 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW3 (0x15 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW4 (0x16 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW5 (0x18 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW6 (0x19 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW7 (0x1B + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW8 (0x1C + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW9 (0x1E + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW10 (0x1F + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW11 (0x21 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS16_SW12 (0x22 + SN3734_PWM_PAGE_REGISTER_COUNT)

#define CS17_SW1 (0x24 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW2 (0x25 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW3 (0x27 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW4 (0x28 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW5 (0x2A + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW6 (0x2B + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW7 (0x2D + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW8 (0x2E + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW9 (0x30 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW10 (0x31 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW11 (0x33 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS17_SW12 (0x34 + SN3734_PWM_PAGE_REGISTER_COUNT)

#define CS18_SW1 (0x36 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW2 (0x37 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW3 (0x39 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW4 (0x3A + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW5 (0x3C + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW6 (0x3D + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW7 (0x3F + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW8 (0x40 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW9 (0x42 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW10 (0x43 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW11 (0x45 + SN3734_PWM_PAGE_REGISTER_COUNT)
#define CS18_SW12 (0x46 + SN3734_PWM_PAGE_REGISTER_COUNT)
