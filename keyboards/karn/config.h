// Copyright 2023 Robert Mills (@robcmills)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define DIRECT_PINS {{NO_PIN, A15,A8, B15, B14, B13}, \
                     {B10,    B1, B0, A7,  A6,  A5 }, \
                     {NO_PIN, B3, B4, B5,  B8,  B9 }, \
                     {A4, A3, A2, NO_PIN, NO_PIN, NO_PIN}}

#define DIRECT_PINS_RIGHT {{B13, B14, B15, A8, A15, NO_PIN}, \
                           {A5,  A6,  A7,  B0, B1,  B10}, \
                           {B9,  B8,  B5,  B4, B3,  NO_PIN}, \
                           {A2, A3, A4, NO_PIN, NO_PIN, NO_PIN}}

#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN B6     // USART TX pin
#define SERIAL_USART_RX_PIN B7     // USART RX pin
