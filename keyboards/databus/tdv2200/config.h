// Created/amended by OleVoip 2024.
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Every databus keyboard config needs to begin with this
#include "preconfig.h"

// Gets included when compiling xprintf.s, no enums allowed

#define USB_WAIT_FOR_ENUMERATION 1
#define DEBUG_MATRIX_SCAN_RATE 1

#define BUS_WAIT_CYCLES 2
#define GPIO_INPUT_PIN_DELAY 1

// Sense buffer: connnect 74HC240 pins 1 & 19, remove connection btwn 19 & 20.
/* Output pins */
#define POWER_LED_PIN    D1
#define POWER_LED_ACTIVE 1

#define PIEZO_PIN    C4
#define PIEZO_ACTIVE 1

#define SENSE_OE_PIN    C3
#define SENSE_OE_ACTIVE 0

#define INDICATORS_LE_PIN    C2
#define INDICATORS_LE_ACTIVE 1

#define CAPS_LED_PIN    C1
#define CAPS_LED_ACTIVE 0

#define LOCK_LED_PIN    C0
#define LOCK_LED_ACTIVE 0

#define LAYER_STATE_8BIT true

/** Data-bus port definition
 * Either 8 individual pins, from MSB to LSB:
 * #define BUS_PINS B7,B6,B5,B4,B3,B2,B1,B0
 * or a single letter for the full port (AVR only):
 * #define BUS_PORT B
 */
#define BUS_PORT B

#define DRIVER_ADDR_PORT D
#define DRIVER_ADDR_TRANSF swap_nibbles

// Extensions
#define CONSOLE_ENABLE 1

// .
