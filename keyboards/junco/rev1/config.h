// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Split Keyboard Stuff
#define EE_HANDS                 // Sets the keyboard’s handedness using EEPROM
#define SERIAL_USART_FULL_DUPLEX // Use full duplex communication (TRRS)
#define SERIAL_USART_TX_PIN GP0  // USART TX pin
#define SERIAL_USART_RX_PIN GP1  // USART RX pin

/* RGB Stuff */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_MATRIX_LED_COUNT 74
#    define RGB_MATRIX_SPLIT \
        { 37, 37 } // 37 LEDs on each side

#endif
