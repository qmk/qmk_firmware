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

// This is a 7-bit address, that gets left-shifted and bit 0
// set to 0 for write, 1 for read (as per I2C protocol)
// The address will vary depending on your wiring:
// 00 <-> GND
// 01 <-> SCL
// 10 <-> SDA
// 11 <-> VCC
// ADDR1 represents A1:A0 of the 7-bit address.
// ADDR2 represents A3:A2 of the 7-bit address.
// The result is: 0b110(ADDR2)(ADDR1)
#ifndef DRIVER_ADDR_1
#    define DRIVER_ADDR_1 0b1100000
#endif

// Set defaults for Spread Spectrum Register
#ifndef ISSI_SSR_1
#    define ISSI_SSR_1 0x00
#endif
#ifndef ISSI_SSR_2
#    define ISSI_SSR_2 0x00
#endif
#ifndef ISSI_SSR_3
#    define ISSI_SSR_3 0x00
#endif
#ifndef ISSI_SSR_4
#    define ISSI_SSR_4 0x00
#endif

// Command Registers
#define ISSI_COMMANDREGISTER_WRITELOCK 0xFE
#define ISSI_COMMANDREGISTER 0xFD
#define ISSI_IDREGISTER 0xFC
#define ISSI_REGISTER_UNLOCK 0xC5

// Response Registers
#define ISSI_PAGE_PWM 0x00
#define ISSI_PAGE_SCALING 0x01
#define ISSI_PAGE_FUNCTION 0x01

// Registers under Function Register
#define ISSI_REG_CONFIGURATION 0x50
#define ISSI_REG_GLOBALCURRENT 0x51
#define ISSI_REG_PULLDOWNUP 0x52
#define ISSI_REG_TEMP 0x5F
#define ISSI_REG_SSR 0x60
#define ISSI_REG_RESET 0x8F
#define ISSI_REG_PWM_ENABLE 0xE0
#define ISSI_REG_PWM_SET 0xE2

// Set defaults for Function Registers
#ifndef ISSI_CONFIGURATION
#    define ISSI_CONFIGURATION 0x01
#endif
#ifndef ISSI_GLOBALCURRENT
#    define ISSI_GLOBALCURRENT 0xFF
#endif
#ifndef ISSI_PULLDOWNUP
#    define ISSI_PULLDOWNUP 0x33
#endif
#ifndef ISSI_TEMP
#    define ISSI_TEMP 0x00
#endif
#ifndef ISSI_PWM_ENABLE
#    define ISSI_PWM_ENABLE 0x00
#endif
#ifndef ISSI_PWM_SET
#    define ISSI_PWM_SET 0x00
#endif

// Set defaults for Scaling registers
#ifndef ISSI_SCAL_RED
#    define ISSI_SCAL_RED 0xFF
#endif
#ifndef ISSI_SCAL_BLUE
#    define ISSI_SCAL_BLUE 0xFF
#endif
#ifndef ISSI_SCAL_GREEN
#    define ISSI_SCAL_GREEN 0xFF
#endif
#define ISSI_SCAL_RED_OFF 0x00
#define ISSI_SCAL_GREEN_OFF 0x00
#define ISSI_SCAL_BLUE_OFF 0x00

#ifndef ISSI_SCAL_LED
#    define ISSI_SCAL_LED 0xFF
#endif
#define ISSI_SCAL_LED_OFF 0x00

// Set buffer sizes
#define ISSI_MAX_LEDS 72
#define ISSI_SCALING_SIZE 72
#define ISSI_PWM_TRF_SIZE 18
#define ISSI_SCALING_TRF_SIZE 18

// Location of 1st bit for PWM and Scaling registers
#define ISSI_PWM_REG_1ST 0x01
#define ISSI_SCL_REG_1ST 0x01

// Map CS SW locations to order in PWM / Scaling buffers
// This matches the ORDER in the Datasheet Register not the POSITION
// It will always count from 0x00 to (ISSI_MAX_LEDS - 1)
#define CS1_SW1 0x00
#define CS2_SW1 0x01
#define CS3_SW1 0x02
#define CS4_SW1 0x03
#define CS5_SW1 0x04
#define CS6_SW1 0x05
#define CS7_SW1 0x06
#define CS8_SW1 0x07
#define CS9_SW1 0x08
#define CS10_SW1 0x09
#define CS11_SW1 0x0A
#define CS12_SW1 0x0B
#define CS13_SW1 0x0C
#define CS14_SW1 0x0D
#define CS15_SW1 0x0E
#define CS16_SW1 0x0F
#define CS17_SW1 0x10
#define CS18_SW1 0x11

#define CS1_SW2 0x12
#define CS2_SW2 0x13
#define CS3_SW2 0x14
#define CS4_SW2 0x15
#define CS5_SW2 0x16
#define CS6_SW2 0x17
#define CS7_SW2 0x18
#define CS8_SW2 0x19
#define CS9_SW2 0x1A
#define CS10_SW2 0x1B
#define CS11_SW2 0x1C
#define CS12_SW2 0x1D
#define CS13_SW2 0x1E
#define CS14_SW2 0x1F
#define CS15_SW2 0x20
#define CS16_SW2 0x21
#define CS17_SW2 0x22
#define CS18_SW2 0x23

#define CS1_SW3 0x24
#define CS2_SW3 0x25
#define CS3_SW3 0x26
#define CS4_SW3 0x27
#define CS5_SW3 0x28
#define CS6_SW3 0x29
#define CS7_SW3 0x2A
#define CS8_SW3 0x2B
#define CS9_SW3 0x2C
#define CS10_SW3 0x2D
#define CS11_SW3 0x2E
#define CS12_SW3 0x2F
#define CS13_SW3 0x30
#define CS14_SW3 0x31
#define CS15_SW3 0x32
#define CS16_SW3 0x33
#define CS17_SW3 0x34
#define CS18_SW3 0x35

#define CS1_SW4 0x36
#define CS2_SW4 0x37
#define CS3_SW4 0x38
#define CS4_SW4 0x39
#define CS5_SW4 0x3A
#define CS6_SW4 0x3B
#define CS7_SW4 0x3C
#define CS8_SW4 0x3D
#define CS9_SW4 0x3E
#define CS10_SW4 0x3F
#define CS11_SW4 0x40
#define CS12_SW4 0x41
#define CS13_SW4 0x42
#define CS14_SW4 0x43
#define CS15_SW4 0x44
#define CS16_SW4 0x45
#define CS17_SW4 0x46
#define CS18_SW4 0x47
