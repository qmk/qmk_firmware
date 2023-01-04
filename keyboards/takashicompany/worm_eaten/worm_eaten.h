// Copyright 2023 takashicompany (@takashicompany)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    l00, l01, l02, l03, l04, r00, r01, r02, r03, r04, \
    l05, l06, l07, l08, l09, r05, r06, r07, r08, r09, \
    l10, l11, l12, l13, l14, r10, r11, r12, r13, r14, \
    l15, l16, l17, l18, l19, r15, r16, r17, r18, r19  \
) { \
    { l00, l01, l02, l03, l04 }, \
    { l05, l06, l07, l08, l09 }, \
    { l10, l11, l12, l13, l14 }, \
    { l15, l16, l17, l18, l19 }, \
    { r00, r01, r02, r03, r04 }, \
    { r05, r06, r07, r08, r09 }, \
    { r10, r11, r12, r13, r14 }, \
    { r15, r16, r17, r18, r19 }  \
}

/*

 "matrix_pins": {
        "cols": [
            "F4",
            "F5",
            "F6",
            "F7",
            "B1",
            "B3",
            "B2",
            "B6",
            "B5",
            "B4"
        ],
        "rows": [
            "D4",
            "C6",
            "D7",
            "E6"
        ]
    },
*/

/*

"layouts": {
        "LAYOUT": {
            "layout": [
                {
                    "matrix": [
                        0,
                        0
                    ],
                    "x": 0,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        1
                    ],
                    "x": 1,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        2
                    ],
                    "x": 2,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        3
                    ],
                    "x": 3,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        4
                    ],
                    "x": 4,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        5
                    ],
                    "x": 6,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        6
                    ],
                    "x": 7,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        7
                    ],
                    "x": 8,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        8
                    ],
                    "x": 9,
                    "y": 0
                },
                {
                    "matrix": [
                        0,
                        9
                    ],
                    "x": 10,
                    "y": 0
                },
                {
                    "matrix": [
                        1,
                        0
                    ],
                    "x": 0,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        1
                    ],
                    "x": 1,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        2
                    ],
                    "x": 2,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        3
                    ],
                    "x": 3,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        4
                    ],
                    "x": 4,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        5
                    ],
                    "x": 6,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        6
                    ],
                    "x": 7,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        7
                    ],
                    "x": 8,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        8
                    ],
                    "x": 9,
                    "y": 1
                },
                {
                    "matrix": [
                        1,
                        9
                    ],
                    "x": 10,
                    "y": 1
                },
                {
                    "matrix": [
                        2,
                        0
                    ],
                    "x": 0,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        1
                    ],
                    "x": 1,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        2
                    ],
                    "x": 2,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        3
                    ],
                    "x": 3,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        4
                    ],
                    "x": 4,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        5
                    ],
                    "x": 6,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        6
                    ],
                    "x": 7,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        7
                    ],
                    "x": 8,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        8
                    ],
                    "x": 9,
                    "y": 2
                },
                {
                    "matrix": [
                        2,
                        9
                    ],
                    "x": 10,
                    "y": 2
                },
                {
                    "matrix": [
                        3,
                        0
                    ],
                    "x": 0,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        1
                    ],
                    "x": 1,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        2
                    ],
                    "x": 2,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        3
                    ],
                    "x": 3,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        4
                    ],
                    "x": 4,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        5
                    ],
                    "x": 6,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        6
                    ],
                    "x": 7,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        7
                    ],
                    "x": 8,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        8
                    ],
                    "x": 9,
                    "y": 3
                },
                {
                    "matrix": [
                        3,
                        9
                    ],
                    "x": 10,
                    "y": 3
                }
            ]
        }
    }
*/