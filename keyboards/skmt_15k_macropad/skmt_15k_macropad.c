// Copyright 2022 Jimmy Lye (@satorusaka)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "skmt_15k_macropad.h"

#ifdef RGB_MATRIX_ENABLE
    led_config_t g_led_config = { {
    // Key Matrix to LED Index
    {   14, 13, 12, 11, 10 },
    {   9 , 8 , 7 , 6 , 5 },
    {   4 , 3 , 2 , 1 , 0 }
    }, {
    // LED Index to Physical Position
    { 224, 64 }, { 168, 64 }, { 112, 64 }, { 56, 64 }, { 0, 64 },
    { 224, 32 },  { 168, 32 }, { 112, 32 }, { 56, 32 },  { 0, 32 },
    { 224, 0 },  { 168, 0 },  { 112, 0 },  { 56, 0 }, { 0, 0 }
    }, {
    // LED Index to Flag
    4,4,4,4,4,
    4,4,4,4,4,
    4,4,4,4,4
    } };
#endif


