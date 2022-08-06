// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Board Versions:
// https://megamind4089.github.io/STeMCell/pinout/
// 1.0.0 - STEMCELL_VERSION=1
// 1.0.1 - STEMCELL_VERSION=2 (Default)

// Left side (front)
#ifdef STEMCELL_UART_SWAP
#    define D3 PAL_LINE(GPIOA, 2)
#    define D2 PAL_LINE(GPIOA, 3)
#else
#    define D3 PAL_LINE(GPIOA, 3)
#    define D2 PAL_LINE(GPIOA, 2)
#endif
//      GND
//      GND
#ifdef STEMCELL_I2C_SWAP
#    define D1 PAL_LINE(GPIOB, 6)
#    define D0 PAL_LINE(GPIOB, 7)
#else
#    define D1 PAL_LINE(GPIOB, 7)
#    define D0 PAL_LINE(GPIOB, 6)
#endif

#define D4 PAL_LINE(GPIOA, 15)
#define C6 PAL_LINE(GPIOB, 3)
#define D7 PAL_LINE(GPIOB, 4)
#define E6 PAL_LINE(GPIOB, 5)
#define B4 PAL_LINE(GPIOB, 8)
#define B5 PAL_LINE(GPIOB, 9)

// Right side (front)
//      RAW
//      GND
//      RESET
//      VCC
#define F4 PAL_LINE(GPIOB, 10)
#define F5 PAL_LINE(GPIOB, 2)
#define F6 PAL_LINE(GPIOB, 1)
#define F7 PAL_LINE(GPIOB, 0)

#if STEMCELL_VERSION == 1
#    define B1 PAL_LINE(GPIOA, 7)
#    define B3 PAL_LINE(GPIOA, 6)
#    define B2 PAL_LINE(GPIOA, 5)
#else
#    define B1 PAL_LINE(GPIOA, 5)
#    define B3 PAL_LINE(GPIOA, 6)
#    define B2 PAL_LINE(GPIOA, 7)
#endif

#define B6 PAL_LINE(GPIOA, 4)

// TX/RX pins of promicro
#define D5 PAL_LINE(GPIOA, 8)
#define B0 PAL_LINE(GPIOA, 9) // unconnected pin

#define I2C1_SCL_PIN D0
#define I2C1_SDA_PIN D1
