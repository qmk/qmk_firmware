// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#define MATRIX_COLS 16
#define MATRIX_ROWS 8

#define DRIVER_COUNT 2
#define DRIVER_ADDR_1 0b0100000
#define DRIVER_ADDR_2 0b0100011
#define DRIVER_1_LED_TOTAL 48
#define DRIVER_2_LED_TOTAL 49
#define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
#define ISSI_CONFIGURATION 0x21 // Enable only the first 9 SW and disable software shutdown

// Limit current to ensure max current draw is just about 500mA
// when white att 100% brightness
#define ISSI_GLOBALCURRENT 104
