// Copyright 2022 xerootg
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#undef DEVICE_VER
#define DEVICE_VER      0x0101 // added 1 for the rev1 + proton c

// wiring of each half
#undef MATRIX_ROW_PINS
#define MATRIX_ROW_PINS { B5, B3, B2, B1, B0 }
#undef MATRIX_COL_PINS
#define MATRIX_COL_PINS { A1, A0, B8, B13, B14, B15, B9 }

// //we are using hardware serial, so lets undef the softserial used otherwise

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
/* 
   Because the rev1 config defines SOFT_SERIAL_PIN, we need to undef it, redefine it, and also assign 
   it to avoid a redefine error.
 */
#undef SOFT_SERIAL_PIN
#define SOFT_SERIAL_PIN B6     // USART TX pin

#define SERIAL_USART_RX_PIN B7     // USART RX pin
#define SERIAL_USART_TX_PIN SOFT_SERIAL_PIN     // USART TX pin

#define SERIAL_USART_PIN_SWAP    // Swap TX and RX pins if keyboard is master halve.
                                   // Check if this feature is necessary with your keyboard design and available on the mcu.
#define SELECT_SOFT_SERIAL_SPEED 1 // or 0, 2, 3, 4, 5
                                   //  0: 460800 baud
                                   //  1: 230400 baud (default)
                                   //  2: 115200 baud
                                   //  3: 57600 baud
                                   //  4: 38400 baud
                                   //  5: 19200 baud
#define SERIAL_USART_DRIVER SD1    // USART driver of TX and RX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20

/* ws2812 RGB LED */
#undef RGB_DI_PIN
#define RGB_DI_PIN A9

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
