// Copyright 2022 Tompi
// SPDX-License-Identifier: MIT

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 5

#define DIRECT_PINS {{B0, B1, B15, B13, B12}, \
                     {A7, A6, B3, A5, A15}, \
                     {A4, B4, B5, A2, B6}, \
                     {B7, B8, B9, NO_PIN, NO_PIN}}


// Full duplex WORKS...
//#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
//#define SERIAL_USART_TX_PIN B6     // USART TX pin
//#define SERIAL_USART_RX_PIN B7     // USART RX pin

//#define EE_HANDS

#define SOFT_SERIAL_PIN B14  // D0 or D1, D2, D3, E6
#define SELECT_SOFT_SERIAL_SPEED 2 // or 0, 2, 3, 4, 5
                                   //  0: about 189kbps (Experimental only)
                                   //  1: about 137kbps (default)
                                   //  2: about 75kbps
                                   //  3: about 39kbps
                                   //  4: about 26kbps
                                   //  5: about 20kbps

 #define CRC8_USE_TABLE
 #define CRC8_OPTIMIZE_SPEED
/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 0
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT    4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 4
#define DEVICE_VER      0x0001

//#define AUDIO_PIN A1
//#define AUDIO_PWM_DRIVER PWMD1
//#define AUDIO_PWM_CHANNEL 1
