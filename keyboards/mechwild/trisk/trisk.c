// Copyright 2023 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  0,  1,  2,  3,  4 },
    {  5,  6,  7,  8,  9 },
    {  10, 11, 12, NO_LED, NO_LED}
}, {
	{0,0}, {56,0}, {112,0}, {168,0}, {224,0}, {224,32}, {224,64}, {180,64}, {135,64}, {90,64}, {44,64}, {0,64}, {0,32}
}, {
    1, 4, 4, 4, 4, 4, 4,4, 4, 4, 4, 4, 1, 2, 2, 2, 2
} };
#endif
