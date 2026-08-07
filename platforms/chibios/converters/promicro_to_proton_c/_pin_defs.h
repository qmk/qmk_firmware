// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Left side (front)
#define D3 PAL_LINE(GPIOA, 9)
#define D2 PAL_LINE(GPIOA, 10)
//      GND
//      GND
#define D1 PAL_LINE(GPIOB, 7)
#define D0 PAL_LINE(GPIOB, 6)
#define D4 PAL_LINE(GPIOB, 5)
#define C6 PAL_LINE(GPIOB, 4)
#define D7 PAL_LINE(GPIOB, 3)
#define E6 PAL_LINE(GPIOB, 2)
#define B4 PAL_LINE(GPIOB, 1)
#define B5 PAL_LINE(GPIOB, 0)

// Right side (front)
//      RAW
//      GND
//      RESET
//      VCC
#define F4 PAL_LINE(GPIOA, 2)
#define F5 PAL_LINE(GPIOA, 1)
#define F6 PAL_LINE(GPIOA, 0)
#define F7 PAL_LINE(GPIOB, 8)
#define B1 PAL_LINE(GPIOB, 13)
#define B3 PAL_LINE(GPIOB, 14)
#define B2 PAL_LINE(GPIOB, 15)
#define B6 PAL_LINE(GPIOB, 9)

// LEDs (only D5/C13 uses an actual LED)
#ifdef CONVERT_TO_PROTON_C_RXLED
#    define D5 PAL_LINE(GPIOC, 14)
#    define B0 PAL_LINE(GPIOC, 13)
#else
#    define D5 PAL_LINE(GPIOC, 13)
#    define B0 PAL_LINE(GPIOC, 14)
#endif
