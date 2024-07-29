// Copyright 2022 Danny Nguyen (@nooges)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { NO_LED, NO_LED, NO_LED, NO_LED },
}, {
    // LED Index to Physical Position
    //through switch
    { 26, 10 }, { 4, 10 }, { 3, 49 }, { 23, 49 },
    { 69, 49 }, { 68, 10 }, { 90, 10 }, { 89, 49 },
    { 134, 49 }, { 132, 10 }, { 155, 10 }, { 155, 49 },
    { 199, 49 }, { 199, 10 }, { 219, 10 }, { 219, 49 },

    //underglow
    { 218, 62 }, { 188, 62 }, { 159, 62 }, { 123, 62 }, //bottom right
    { 100, 62 }, { 59, 62 }, { 35, 62 }, { 5, 62 }, //bottom left
    { 6, 6 }, { 35, 6 }, { 59, 6 }, { 100, 6 }, //top left
    { 123, 6 }, { 159, 6 }, { 188, 6 }, { 218, 6 } //top right
}, {
    // LED Index to Flag
    4, 4, 4, 4, 
    4, 4, 4, 4, 
    4, 4, 4, 4,
    4, 4, 4, 4, 
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2,
    2, 2, 2, 2 
} };



#endif