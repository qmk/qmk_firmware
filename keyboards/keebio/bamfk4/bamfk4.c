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
    { 26.6, 10 }, { 4.3, 10 }, { 3.8, 49.3 }, { 23.3, 49.3 },
    { 69.4, 49.3 }, { 68.9, 10 }, { 90.6, 10 }, { 89.5, 49.3 },
    { 134, 49.3 }, { 132.9, 10 }, { 155.7, 10 }, { 155.1, 49.3 },
    { 199.6, 49.3 }, { 199.6, 10 }, { 219.1, 10 }, { 219.1, 49.3 },

    //underglow
    { 218, 62.2 }, { 188.7, 62.2 }, { 159.5, 62.2 }, { 123.7, 62.2 }, //bottom right
    { 100.3, 62.2 }, { 59.1, 62.2 }, { 35.3, 62.2 }, { 5.4, 62.2 }, //bottom left
    { 6, 6.4 }, { 35.3, 6.4 }, { 59.1, 6.4 }, { 100.3, 6.4 }, //top left
    { 123.7, 6.4 }, { 159.5, 6.4 }, { 188.7, 6.4 }, { 218, 6.4 } //top right
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