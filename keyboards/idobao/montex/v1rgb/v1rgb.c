// Copyright 2022 peepeetee (@peepeetee)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

/* WS2812 indices always start at 0
 * underglow = 0-3
 * note: starting point of 4 and jump from 6 to 7
 * ┌───┌───┐───┬───┬───┐
 * │ 6 │ 5 │ 4 │30 │29 │
 * ├───┼───┘───┼───┼───┤
 * │24 │25 │26 │27 │28 │
 * ├───┼───┼───┼───┼───┤
 * │23 │22 │21 │20 │19 │
 * ├───┼───┼───┼───┤   │
 * │15 │16 │17 │18 │   │
 * ├───┼───┼───┼───┤───┤
 * │14 │13 │12 │11 │10 │
 * ├───┼───┴───┼───┤   │
 * │ 7 │   8   │ 9 │   │
 * └───┴───────┴───┘───┘
 */

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    { 6,  5,  4,  30, 29},
    { 24, 25, 26, 27, 28},
    { 23, 22, 21, 20, 19},
    { 15, 16, 17, 18, NO_LED},
    { 14, 13, 12, 11, NO_LED},
    { 7,  8,  9,  10, NO_LED}
}, {
    // LED Index to Physical Position
    /* underglow: because this is under the kb, you want the colors on the edge (corners) of the acrylic plate */
    { 224,0  }, { 224,64},  {   0,64 }, {  0,0   },              // 0-3 (underglow)
    /* per-key: origins generated from https://xelus.netlify.app/guides/KLE_to_RGB_parser */
    { 112,0  }, {  56,0  }, {   0,0  }, /* ---- */  /* ---- */   // 4-6 (top row middle to left)
    {   0,64 }, {  84,64 }, { 168,64 },                          // 7-9 (jump to bottom left)
    { 224,58 }, { 168,41 }, { 112,41 }, {  56,41 }, {   0,41 },  // 10-14 (flow Z pattern upwards...)
    {   0,29 }, {  56,29 }, { 112,29 }, { 168,29 },              // 15-18
    { 224,35 }, { 168,29 }, { 112,29 }, {  56,29 }, {   0,29 },  // 19-23
    {   0,17 }, {  56,17 }, { 112,17 }, { 168,17 }, { 224,17 },  // 24-28
    /* ---- */  /* ---- */  /* ---- */  { 224,0  }, { 168,0  }   // 29-30 (end at top)
}, {
    // LED Index to Flag
    2, 2, 2, 2,     // 0 1 2 3 (underglow)
    1, 1, 1,        // 4 5 6
    4, 4, 4, 4,     // 7 - 10
    4, 4, 4, 4,     //11 - 14
    4, 4, 4, 4,     //15 - 18
    4, 4, 4, 4, 4,  //19 - 23
    4, 4, 4, 4, 4,  //24 - 28
    1, 1            //29 30
} };

#endif
