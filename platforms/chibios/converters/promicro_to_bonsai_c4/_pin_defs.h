// Copyright 2022 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Left side (front)
#define D3 PAL_LINE(GPIOB, 7)
#define D2 PAL_LINE(GPIOA, 15)
//      GND
//      GND
#define D1 PAL_LINE(GPIOB, 9)
#define D0 PAL_LINE(GPIOB, 6)
#define D4 PAL_LINE(GPIOA, 4)
#define C6 PAL_LINE(GPIOB, 8)
#define D7 PAL_LINE(GPIOA, 3)
#define E6 PAL_LINE(GPIOB, 10)
#define B4 PAL_LINE(GPIOA, 8)
#define B5 PAL_LINE(GPIOB, 0)

// Right side (front)
//      RAW
//      GND
//      RESET
//      VCC
#define F4 PAL_LINE(GPIOA, 7)
#define F5 PAL_LINE(GPIOA, 6)
#define F6 PAL_LINE(GPIOA, 5)
#define F7 PAL_LINE(GPIOA, 1)
#define B1 PAL_LINE(GPIOB, 13)
#define B3 PAL_LINE(GPIOB, 14)
#define B2 PAL_LINE(GPIOB, 15)
#define B6 PAL_LINE(GPIOB, 1)

// LEDs (only D5/B2 uses an actual LED)
// Setting both RX and TX LEDs to the same pin.
// If this causes any conflict (compile-time or runtime)
// it will need to be resolved on a case-by-case basis
// since there is only one LED available.
#    define B0 PAL_LINE(GPIOB, 2)
#    define D5 PAL_LINE(GPIOB, 2)

