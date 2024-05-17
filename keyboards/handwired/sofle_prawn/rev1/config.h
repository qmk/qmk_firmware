// Copyright 2024 Vincent Su (@FlattestPrawn)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET              // Activates the double-tap behavior
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U // Timeout window in ms in which the double tap can occur.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP16     // Specify a optional status led by GPIO number which blinks when entering the bootloader

//Handedness is defined by EEPROM. When flashing, add "-bl uf2-split-left" and right
#define EE_HANDS

//Sets the serial communication pins
#define SERIAL_USART_FULL_DUPLEX // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP0   // USART TX pin
#define SERIAL_USART_RX_PIN GP1   // USART RX pin

#define MATRIX_ROWS 5
#define MATRIX_COLS 6

#define MATRIX_ROW_PINS { GP15, GP26, GP27, GP28, GP29 }
#define MATRIX_COL_PINS { GP4, GP5, GP6, GP7, GP8, GP9 }
#define DIODE_DIRECTION COL2ROW

//Adds optional Backlight at GP11
#define BACKLIGHT_PIN GP11
#define BACKLIGHT_LEVELS 5

//Default USB polling rate is 10ms
#define USB_POLLING_INTERVAL_MS 10

//config.h doc says ARM based Split KB must use this at present
//SPLIT_TRANSPORT = custom

#define ENCODERS_PAD_A { GP13 }
#define ENCODERS_PAD_B { GP14 }
#define ENCODER_RESOLUTION 2

