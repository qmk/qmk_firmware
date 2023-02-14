// Copyright 2023 Robert Mills (@robcmills)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

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

/* Top left key on left half */
#define BOOTMAGIC_LITE_ROW    0
#define BOOTMAGIC_LITE_COLUMN 1
/* Top right key on right half */
#define BOOTMAGIC_LITE_ROW_RIGHT    4
#define BOOTMAGIC_LITE_COLUMN_RIGHT 4

// Equivalent to zmk behavior-hold-tap tap-preferred flavor
// Do not force the mod-tap key press to be handled as a modifier
// if any other key was pressed while the mod-tap key is held down.
#define IGNORE_MOD_TAP_INTERRUPT_PER_KEY

// Equivalent to zmk behavior-hold-tap hold-preferred flavor
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY

