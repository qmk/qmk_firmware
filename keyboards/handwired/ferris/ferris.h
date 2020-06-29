/*
Copyright 2020 Pierre Chevalier <pierrechevalier83@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"
#include <stdint.h>
#include <stdbool.h>
#include "i2c_master.h"
#include <util/delay.h>

extern i2c_status_t mcp23017_status;
#define I2C_TIMEOUT 1000
#define CPU_PRESCALE(n) (CLKPR = 0x80, CLKPR = (n))
#define CPU_16MHz 0x00

// For a better understanding of the i2c protocol, this is a good read:
// https://www.robot-electronics.co.uk/i2c-tutorial

// I2C address:
// See the datasheet, section 3.3.1 on addressing I2C devices and figure 3-6 for an
// illustration
// http://ww1.microchip.com/downloads/en/devicedoc/20001952c.pdf
// All address pins of the mcp23017 are connected to the ground on the ferris
// | 0  | 1  | 0  | 0  | A2 | A1 | A0 |
// | 0  | 1  | 0  | 0  | 0  | 0  | 0  |
#define I2C_ADDR 0b0100000
#define I2C_ADDR_WRITE ((I2C_ADDR << 1) | I2C_WRITE)
#define I2C_ADDR_READ ((I2C_ADDR << 1) | I2C_READ)

// Register addresses
// See https://github.com/adafruit/Adafruit-MCP23017-Arduino-Library/blob/master/Adafruit_MCP23017.h
#define IODIRA 0x00  // i/o direction register
#define IODIRB 0x01
#define GPPUA 0x0C  // GPIO pull-up resistor register
#define GPPUB 0x0D
#define GPIOA 0x12  // general purpose i/o port register (write modifies OLAT)
#define GPIOB 0x13
#define OLATA 0x14  // output latch register
#define OLATB 0x15

uint8_t init_mcp23017(void);

// clang-format off

/*              left hand                           right hand      */
#define LAYOUT(\
    K0_0, K0_1, K0_2, K0_3, K0_4,       K0_5, K0_6, K0_7, K0_8, K0_9,\
    K1_0, K1_1, K1_2, K1_3, K1_4,       K1_5, K1_6, K1_7, K1_8, K1_9,\
    K2_0, K2_1, K2_2, K2_3, K2_4,       K2_5, K2_6, K2_7, K2_8, K2_9,\
                        K3_3, K3_4,   K3_5, K3_6)\
/* matrix positions */\
{\
    {K0_0,  K0_1,  K0_2,  K0_3,  K0_4},\
    {K1_0,  K1_1,  K1_2,  K1_3,  K1_4},\
    {K2_0,  K2_1,  K2_2,  K2_3,  K2_4},\
    {KC_NO, KC_NO, KC_NO, K3_3,  K3_4},\
	\
	{K0_5,  K0_6,  K0_7,  K0_8,  K0_9},\
	{K1_5,  K1_6,  K1_7,  K1_8,  K1_9},\
	{K2_5,  K2_6,  K2_7,  K2_8,  K2_9},\
	{K3_5,  K3_6, KC_NO,  KC_NO, KC_NO}\
}

// clang-format on
