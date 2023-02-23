// Copyright 2023 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4 },
    {  5,  6,  7,  8,  9 },
    {  10, 11, 12, NO_LED, NO_LED}
}, {
	{ 0,  32 }, { 18,  32 }, { 37,  32 }, { 55,  32 }, {  74,  32 }, {  93,  32 }, { 112,  32 }, { 131,  32 }, { 150,  32 }, { 168,  32 }, {  187,  32 }, {  205,  32 }, {  224,  32 }
}, {
    1, 4, 4, 4, 4, 4, 4,4, 4, 4, 4, 4, 1, 2, 2, 2, 2
} };
#endif