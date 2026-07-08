// Copyright 2022 xerootg
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// //we are using hardware serial, so lets undef the softserial used otherwise

/* serial.c configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.

#define SERIAL_USART_RX_PIN B7     // USART RX pin
#define SERIAL_USART_TX_PIN B6     // USART TX pin

#define SERIAL_USART_PIN_SWAP    // Swap TX and RX pins if keyboard is master halve.
                                   // Check if this feature is necessary with your keyboard design and available on the mcu.
#define SERIAL_USART_DRIVER SD1    // USART driver of TX and RX pin. default: SD1
#define SERIAL_USART_TX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_RX_PAL_MODE 7 // Pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 7
#define SERIAL_USART_TIMEOUT 20    // USART driver timeout. default 20
