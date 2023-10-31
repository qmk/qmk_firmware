// Copyright 2022 Alexander Lozyuk (@keyzog)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Left Hand
    // { 8,  7,  6,  5,  4,  3,  2,  1,  0 }, // underglow
    {  9, 10, 11, 12, 13, 14, 15 },
    { 22, 21, 20, 19, 18, 17, 16 },
    { 23, 24, 25, 26, 27, 28, 29 },
    { 36, 35, 34, 33, 32, 31, 30 },
    { 37, 38, 39, 40, 41, 42, 43 },

    // Right Hand
    // { 44,  45,  46,  47,  48,  49,  50,  51,  52 }, // underglow
    { 53, 54, 55, 56, 57, 58, 59 },
    { 66, 65, 64, 63, 62, 61, 60 },
    { 67, 68, 69, 70, 71, 72, 73 },
    { 80, 79, 78, 77, 76, 75, 74 },
    { 81, 82, 83, 84, 85, 86, 87 }
}, {
    // Left Hand
    {96, 57},  {112, 44}, {112, 19}, {80, 19}, {48, 19}, {16, 19}, {16, 57}, {48, 57}, {80, 57}, // underglow
    {0, 0},    {17, 0},   {34, 0},   {52, 0},  {69, 0},  {86, 0},  {103, 0},
    {103, 16}, {86, 16},  {69, 16},  {52, 16}, {34, 16}, {17, 16}, {0, 16},
    {0, 32},   {17, 32},  {34, 32},  {52, 32}, {69, 32}, {86, 32}, {103, 32},
    {103, 48}, {86, 48},  {69, 48},  {52, 48}, {34, 48}, {17, 48}, {0, 48},
    {0, 64},   {17, 64},  {34, 64},  {52, 64}, {69, 64}, {86, 64}, {103, 64},

    // Right Hand
    {144, 57}, {128, 44}, {128, 19}, {160, 19}, {192, 19}, {224, 19}, {224, 57}, {192, 57}, {160, 57}, // underglow
    {224, 0},  {207, 0},  {190, 0},  {172, 0},  {155, 0},  {138, 0},  {121, 0},
    {121, 16}, {138, 16}, {155, 16}, {172, 16}, {190, 16}, {207, 16}, {224, 16},
    {224, 32}, {207, 32}, {190, 32}, {172, 32}, {155, 32}, {138, 32}, {121, 32},
    {121, 48}, {138, 48}, {155, 48}, {172, 48}, {190, 48}, {207, 48}, {224, 48},
    {224, 64}, {207, 64}, {190, 64}, {172, 64}, {155, 64}, {138, 64}, {121, 64}
}, {
    // Left Hand
    2, 2, 2, 2, 2, 2, 2, 2, 2, // underglow
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1,

    // Right Hand
    2, 2, 2, 2, 2, 2, 2, 2, 2, // underglow
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 1,
    1, 1, 1, 1, 1, 1, 1
} };
#endif
