// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Electrical Wiring Stuff
#define MATRIX_ROW_PINS \
    { GP8, GP9, GP10, GP11, GP12 }
#define MATRIX_COL_PINS \
    { GP2, GP3, GP4, GP5, GP6, GP7 }
#define DIODE_DIRECTION COL2ROW

// Split Keyboard Stuff
#define EE_HANDS                 // Sets the keyboard’s handedness using EEPROM
#define SERIAL_USART_FULL_DUPLEX // Use full duplex communication (TRRS)
#define SERIAL_USART_TX_PIN GP0  // USART TX pin
#define SERIAL_USART_RX_PIN GP1  // USART RX pin

/* RGB Stuff */
#ifdef RGB_MATRIX_ENABLE

#    define RGB_DI_PIN GP15 // Pin for RGB logic
#    define RGB_MATRIX_LED_COUNT 74
#    define RGB_MATRIX_SPLIT \
        { 37, 37 } // 37 LEDs on each side

#endif

/* Rotary Encoders Definition */
// Indexing goes from physical leftmost to rightmost
// 0: left-half left | 1: left-half right | 2: right-half left | 3: right-half right
#ifdef ENCODER_ENABLE

#    define ENCODERS_PAD_A \
        { GP16, GP14 }
#    define ENCODERS_PAD_B \
        { GP17, GP13 }
#    define ENCODERS_PAD_A_RIGHT \
        { GP14, GP16 }
#    define ENCODERS_PAD_B_RIGHT \
        { GP13, GP17 }

#endif
