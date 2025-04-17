// Copyright 2022 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Define the matrix dimensions for a 1x8 key matrix
#define MATRIX_ROWS 1
#define MATRIX_COLS 8

// Define the GPIO pins used for the 8 keys (each connected to a separate GPIO pin)
#define DIRECT_PINS { \
    { GP0, GP1, GP2, GP3, GP4, GP5, GP6, GP7 } \
}

// Define the diode direction (COL2ROW or ROW2COL based on your wiring)
#define DIODE_DIRECTION COL2ROW

// If you're using RGB lighting, enable it and set the timeout for turning off RGB after a period of inactivity
#ifdef RGBLIGHT_ENABLE
#    define PICA40_RGBLIGHT_TIMEOUT 5 // turn RGB off after 5 minutes of inactivity
#endif
