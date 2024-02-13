/* Copyright 2021 Jasper Chan (Gigahawk)
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
#include "gpio.h"
#include "util.h"

// ======== DEPRECATED DEFINES - DO NOT USE ========
#ifdef AW_SCALING_MAX
#    define AW20216S_SCALING_MAX AW_SCALING_MAX
#endif
#ifdef AW_GLOBAL_CURRENT_MAX
#    define AW20216S_GLOBAL_CURRENT_MAX AW_GLOBAL_CURRENT_MAX
#endif
#ifdef AW_SPI_MODE
#    define AW20216S_SPI_MODE AW_SPI_MODE
#endif
#ifdef AW_SPI_DIVISOR
#    define AW20216S_SPI_DIVISOR AW_SPI_DIVISOR
#endif
#ifdef DRIVER_1_CS
#    define AW20216S_CS_PIN_1 DRIVER_1_CS
#endif
#ifdef DRIVER_2_CS
#    define AW20216S_CS_PIN_2 DRIVER_2_CS
#endif
#ifdef DRIVER_1_EN
#    define AW20216S_EN_PIN_1 DRIVER_1_EN
#endif
#ifdef DRIVER_2_EN
#    define AW20216S_EN_PIN_2 DRIVER_2_EN
#endif

#define aw_led aw20216s_led_t
#define g_aw_leds g_aw20216s_leds
// ========

#define AW20216S_ID (0b1010 << 4)
#define AW20216S_WRITE 0
#define AW20216S_READ 1

#define AW20216S_PAGE_FUNCTION (0x00 << 1)
#define AW20216S_PAGE_PWM (0x01 << 1)
#define AW20216S_PAGE_SCALING (0x02 << 1)
#define AW20216S_PAGE_PATTERN_CHOICE (0x03 << 1)
#define AW20216S_PAGE_PWM_SCALING (0x04 << 1)

#define AW20216S_FUNCTION_REG_CONFIGURATION 0x00
#define AW20216S_CONFIGURATION_SWSEL_1_12 (0b1011 << 4)
#define AW20216S_CONFIGURATION_CHIPEN (0b1 << 0)

#define AW20216S_FUNCTION_REG_GLOBAL_CURRENT 0x01

#define AW20216S_FUNCTION_REG_RESET 0x2F
#define AW20216S_RESET_MAGIC 0xAE

#define AW20216S_FUNCTION_REG_MIX_FUNCTION 0x46
#define AW20216S_MIX_FUNCTION_LPEN (0b1 << 1)

#if defined(RGB_MATRIX_AW20216S)
#    define AW20216S_LED_COUNT RGB_MATRIX_LED_COUNT
#endif

#if defined(AW20216S_CS_PIN_2)
#    define AW20216S_DRIVER_COUNT 2
#elif defined(AW20216S_CS_PIN_1)
#    define AW20216S_DRIVER_COUNT 1
#endif

typedef struct aw20216s_led_t {
    uint8_t driver : 2;
    uint8_t r;
    uint8_t g;
    uint8_t b;
} PACKED aw20216s_led_t;

extern const aw20216s_led_t PROGMEM g_aw20216s_leds[AW20216S_LED_COUNT];

void aw20216s_init_drivers(void);
void aw20216s_init(pin_t cs_pin, pin_t en_pin);
void aw20216s_set_color(int index, uint8_t red, uint8_t green, uint8_t blue);
void aw20216s_set_color_all(uint8_t red, uint8_t green, uint8_t blue);
void aw20216s_update_pwm_buffers(pin_t cs_pin, uint8_t index);

void aw20216s_flush(void);

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

#define SW5_CS1 0x48
#define SW5_CS2 0x49
#define SW5_CS3 0x4A
#define SW5_CS4 0x4B
#define SW5_CS5 0x4C
#define SW5_CS6 0x4D
#define SW5_CS7 0x4E
#define SW5_CS8 0x4F
#define SW5_CS9 0x50
#define SW5_CS10 0x51
#define SW5_CS11 0x52
#define SW5_CS12 0x53
#define SW5_CS13 0x54
#define SW5_CS14 0x55
#define SW5_CS15 0x56
#define SW5_CS16 0x57
#define SW5_CS17 0x58
#define SW5_CS18 0x59

#define SW6_CS1 0x5A
#define SW6_CS2 0x5B
#define SW6_CS3 0x5C
#define SW6_CS4 0x5D
#define SW6_CS5 0x5E
#define SW6_CS6 0x5F
#define SW6_CS7 0x60
#define SW6_CS8 0x61
#define SW6_CS9 0x62
#define SW6_CS10 0x63
#define SW6_CS11 0x64
#define SW6_CS12 0x65
#define SW6_CS13 0x66
#define SW6_CS14 0x67
#define SW6_CS15 0x68
#define SW6_CS16 0x69
#define SW6_CS17 0x6A
#define SW6_CS18 0x6B

#define SW7_CS1 0x6C
#define SW7_CS2 0x6D
#define SW7_CS3 0x6E
#define SW7_CS4 0x6F
#define SW7_CS5 0x70
#define SW7_CS6 0x71
#define SW7_CS7 0x72
#define SW7_CS8 0x73
#define SW7_CS9 0x74
#define SW7_CS10 0x75
#define SW7_CS11 0x76
#define SW7_CS12 0x77
#define SW7_CS13 0x78
#define SW7_CS14 0x79
#define SW7_CS15 0x7A
#define SW7_CS16 0x7B
#define SW7_CS17 0x7C
#define SW7_CS18 0x7D

#define SW8_CS1 0x7E
#define SW8_CS2 0x7F
#define SW8_CS3 0x80
#define SW8_CS4 0x81
#define SW8_CS5 0x82
#define SW8_CS6 0x83
#define SW8_CS7 0x84
#define SW8_CS8 0x85
#define SW8_CS9 0x86
#define SW8_CS10 0x87
#define SW8_CS11 0x88
#define SW8_CS12 0x89
#define SW8_CS13 0x8A
#define SW8_CS14 0x8B
#define SW8_CS15 0x8C
#define SW8_CS16 0x8D
#define SW8_CS17 0x8E
#define SW8_CS18 0x8F

#define SW9_CS1 0x90
#define SW9_CS2 0x91
#define SW9_CS3 0x92
#define SW9_CS4 0x93
#define SW9_CS5 0x94
#define SW9_CS6 0x95
#define SW9_CS7 0x96
#define SW9_CS8 0x97
#define SW9_CS9 0x98
#define SW9_CS10 0x99
#define SW9_CS11 0x9A
#define SW9_CS12 0x9B
#define SW9_CS13 0x9C
#define SW9_CS14 0x9D
#define SW9_CS15 0x9E
#define SW9_CS16 0x9F
#define SW9_CS17 0xA0
#define SW9_CS18 0xA1

#define SW10_CS1 0xA2
#define SW10_CS2 0xA3
#define SW10_CS3 0xA4
#define SW10_CS4 0xA5
#define SW10_CS5 0xA6
#define SW10_CS6 0xA7
#define SW10_CS7 0xA8
#define SW10_CS8 0xA9
#define SW10_CS9 0xAA
#define SW10_CS10 0xAB
#define SW10_CS11 0xAC
#define SW10_CS12 0xAD
#define SW10_CS13 0xAE
#define SW10_CS14 0xAF
#define SW10_CS15 0xB0
#define SW10_CS16 0xB1
#define SW10_CS17 0xB2
#define SW10_CS18 0xB3

#define SW11_CS1 0xB4
#define SW11_CS2 0xB5
#define SW11_CS3 0xB6
#define SW11_CS4 0xB7
#define SW11_CS5 0xB8
#define SW11_CS6 0xB9
#define SW11_CS7 0xBA
#define SW11_CS8 0xBB
#define SW11_CS9 0xBC
#define SW11_CS10 0xBD
#define SW11_CS11 0xBE
#define SW11_CS12 0xBF
#define SW11_CS13 0xC0
#define SW11_CS14 0xC1
#define SW11_CS15 0xC2
#define SW11_CS16 0xC3
#define SW11_CS17 0xC4
#define SW11_CS18 0xC5

#define SW12_CS1 0xC6
#define SW12_CS2 0xC7
#define SW12_CS3 0xC8
#define SW12_CS4 0xC9
#define SW12_CS5 0xCA
#define SW12_CS6 0xCB
#define SW12_CS7 0xCC
#define SW12_CS8 0xCD
#define SW12_CS9 0xCE
#define SW12_CS10 0xCF
#define SW12_CS11 0xD0
#define SW12_CS12 0xD1
#define SW12_CS13 0xD2
#define SW12_CS14 0xD3
#define SW12_CS15 0xD4
#define SW12_CS16 0xD5
#define SW12_CS17 0xD6
#define SW12_CS18 0xD7

// DEPRECATED - DO NOT USE

#define CS1_SW1 SW1_CS1
#define CS2_SW1 SW1_CS2
#define CS3_SW1 SW1_CS3
#define CS4_SW1 SW1_CS4
#define CS5_SW1 SW1_CS5
#define CS6_SW1 SW1_CS6
#define CS7_SW1 SW1_CS7
#define CS8_SW1 SW1_CS8
#define CS9_SW1 SW1_CS9
#define CS10_SW1 SW1_CS10
#define CS11_SW1 SW1_CS11
#define CS12_SW1 SW1_CS12
#define CS13_SW1 SW1_CS13
#define CS14_SW1 SW1_CS14
#define CS15_SW1 SW1_CS15
#define CS16_SW1 SW1_CS16
#define CS17_SW1 SW1_CS17
#define CS18_SW1 SW1_CS18

#define CS1_SW2 SW2_CS1
#define CS2_SW2 SW2_CS2
#define CS3_SW2 SW2_CS3
#define CS4_SW2 SW2_CS4
#define CS5_SW2 SW2_CS5
#define CS6_SW2 SW2_CS6
#define CS7_SW2 SW2_CS7
#define CS8_SW2 SW2_CS8
#define CS9_SW2 SW2_CS9
#define CS10_SW2 SW2_CS10
#define CS11_SW2 SW2_CS11
#define CS12_SW2 SW2_CS12
#define CS13_SW2 SW2_CS13
#define CS14_SW2 SW2_CS14
#define CS15_SW2 SW2_CS15
#define CS16_SW2 SW2_CS16
#define CS17_SW2 SW2_CS17
#define CS18_SW2 SW2_CS18

#define CS1_SW3 SW3_CS1
#define CS2_SW3 SW3_CS2
#define CS3_SW3 SW3_CS3
#define CS4_SW3 SW3_CS4
#define CS5_SW3 SW3_CS5
#define CS6_SW3 SW3_CS6
#define CS7_SW3 SW3_CS7
#define CS8_SW3 SW3_CS8
#define CS9_SW3 SW3_CS9
#define CS10_SW3 SW3_CS10
#define CS11_SW3 SW3_CS11
#define CS12_SW3 SW3_CS12
#define CS13_SW3 SW3_CS13
#define CS14_SW3 SW3_CS14
#define CS15_SW3 SW3_CS15
#define CS16_SW3 SW3_CS16
#define CS17_SW3 SW3_CS17
#define CS18_SW3 SW3_CS18

#define CS1_SW4 SW4_CS1
#define CS2_SW4 SW4_CS2
#define CS3_SW4 SW4_CS3
#define CS4_SW4 SW4_CS4
#define CS5_SW4 SW4_CS5
#define CS6_SW4 SW4_CS6
#define CS7_SW4 SW4_CS7
#define CS8_SW4 SW4_CS8
#define CS9_SW4 SW4_CS9
#define CS10_SW4 SW4_CS10
#define CS11_SW4 SW4_CS11
#define CS12_SW4 SW4_CS12
#define CS13_SW4 SW4_CS13
#define CS14_SW4 SW4_CS14
#define CS15_SW4 SW4_CS15
#define CS16_SW4 SW4_CS16
#define CS17_SW4 SW4_CS17
#define CS18_SW4 SW4_CS18

#define CS1_SW5 SW5_CS1
#define CS2_SW5 SW5_CS2
#define CS3_SW5 SW5_CS3
#define CS4_SW5 SW5_CS4
#define CS5_SW5 SW5_CS5
#define CS6_SW5 SW5_CS6
#define CS7_SW5 SW5_CS7
#define CS8_SW5 SW5_CS8
#define CS9_SW5 SW5_CS9
#define CS10_SW5 SW5_CS10
#define CS11_SW5 SW5_CS11
#define CS12_SW5 SW5_CS12
#define CS13_SW5 SW5_CS13
#define CS14_SW5 SW5_CS14
#define CS15_SW5 SW5_CS15
#define CS16_SW5 SW5_CS16
#define CS17_SW5 SW5_CS17
#define CS18_SW5 SW5_CS18

#define CS1_SW6 SW6_CS1
#define CS2_SW6 SW6_CS2
#define CS3_SW6 SW6_CS3
#define CS4_SW6 SW6_CS4
#define CS5_SW6 SW6_CS5
#define CS6_SW6 SW6_CS6
#define CS7_SW6 SW6_CS7
#define CS8_SW6 SW6_CS8
#define CS9_SW6 SW6_CS9
#define CS10_SW6 SW6_CS10
#define CS11_SW6 SW6_CS11
#define CS12_SW6 SW6_CS12
#define CS13_SW6 SW6_CS13
#define CS14_SW6 SW6_CS14
#define CS15_SW6 SW6_CS15
#define CS16_SW6 SW6_CS16
#define CS17_SW6 SW6_CS17
#define CS18_SW6 SW6_CS18

#define CS1_SW7 SW7_CS1
#define CS2_SW7 SW7_CS2
#define CS3_SW7 SW7_CS3
#define CS4_SW7 SW7_CS4
#define CS5_SW7 SW7_CS5
#define CS6_SW7 SW7_CS6
#define CS7_SW7 SW7_CS7
#define CS8_SW7 SW7_CS8
#define CS9_SW7 SW7_CS9
#define CS10_SW7 SW7_CS10
#define CS11_SW7 SW7_CS11
#define CS12_SW7 SW7_CS12
#define CS13_SW7 SW7_CS13
#define CS14_SW7 SW7_CS14
#define CS15_SW7 SW7_CS15
#define CS16_SW7 SW7_CS16
#define CS17_SW7 SW7_CS17
#define CS18_SW7 SW7_CS18

#define CS1_SW8 SW8_CS1
#define CS2_SW8 SW8_CS2
#define CS3_SW8 SW8_CS3
#define CS4_SW8 SW8_CS4
#define CS5_SW8 SW8_CS5
#define CS6_SW8 SW8_CS6
#define CS7_SW8 SW8_CS7
#define CS8_SW8 SW8_CS8
#define CS9_SW8 SW8_CS9
#define CS10_SW8 SW8_CS10
#define CS11_SW8 SW8_CS11
#define CS12_SW8 SW8_CS12
#define CS13_SW8 SW8_CS13
#define CS14_SW8 SW8_CS14
#define CS15_SW8 SW8_CS15
#define CS16_SW8 SW8_CS16
#define CS17_SW8 SW8_CS17
#define CS18_SW8 SW8_CS18

#define CS1_SW9 SW9_CS1
#define CS2_SW9 SW9_CS2
#define CS3_SW9 SW9_CS3
#define CS4_SW9 SW9_CS4
#define CS5_SW9 SW9_CS5
#define CS6_SW9 SW9_CS6
#define CS7_SW9 SW9_CS7
#define CS8_SW9 SW9_CS8
#define CS9_SW9 SW9_CS9
#define CS10_SW9 SW9_CS10
#define CS11_SW9 SW9_CS11
#define CS12_SW9 SW9_CS12
#define CS13_SW9 SW9_CS13
#define CS14_SW9 SW9_CS14
#define CS15_SW9 SW9_CS15
#define CS16_SW9 SW9_CS16
#define CS17_SW9 SW9_CS17
#define CS18_SW9 SW9_CS18

#define CS1_SW10 SW10_CS1
#define CS2_SW10 SW10_CS2
#define CS3_SW10 SW10_CS3
#define CS4_SW10 SW10_CS4
#define CS5_SW10 SW10_CS5
#define CS6_SW10 SW10_CS6
#define CS7_SW10 SW10_CS7
#define CS8_SW10 SW10_CS8
#define CS9_SW10 SW10_CS9
#define CS10_SW10 SW10_CS10
#define CS11_SW10 SW10_CS11
#define CS12_SW10 SW10_CS12
#define CS13_SW10 SW10_CS13
#define CS14_SW10 SW10_CS14
#define CS15_SW10 SW10_CS15
#define CS16_SW10 SW10_CS16
#define CS17_SW10 SW10_CS17
#define CS18_SW10 SW10_CS18

#define CS1_SW11 SW11_CS1
#define CS2_SW11 SW11_CS2
#define CS3_SW11 SW11_CS3
#define CS4_SW11 SW11_CS4
#define CS5_SW11 SW11_CS5
#define CS6_SW11 SW11_CS6
#define CS7_SW11 SW11_CS7
#define CS8_SW11 SW11_CS8
#define CS9_SW11 SW11_CS9
#define CS10_SW11 SW11_CS10
#define CS11_SW11 SW11_CS11
#define CS12_SW11 SW11_CS12
#define CS13_SW11 SW11_CS13
#define CS14_SW11 SW11_CS14
#define CS15_SW11 SW11_CS15
#define CS16_SW11 SW11_CS16
#define CS17_SW11 SW11_CS17
#define CS18_SW11 SW11_CS18

#define CS1_SW12 SW12_CS1
#define CS2_SW12 SW12_CS2
#define CS3_SW12 SW12_CS3
#define CS4_SW12 SW12_CS4
#define CS5_SW12 SW12_CS5
#define CS6_SW12 SW12_CS6
#define CS7_SW12 SW12_CS7
#define CS8_SW12 SW12_CS8
#define CS9_SW12 SW12_CS9
#define CS10_SW12 SW12_CS10
#define CS11_SW12 SW12_CS11
#define CS12_SW12 SW12_CS12
#define CS13_SW12 SW12_CS13
#define CS14_SW12 SW12_CS14
#define CS15_SW12 SW12_CS15
#define CS16_SW12 SW12_CS16
#define CS17_SW12 SW12_CS17
#define CS18_SW12 SW12_CS18
