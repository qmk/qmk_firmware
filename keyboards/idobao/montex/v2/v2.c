// Copyright 2022 IBNobody (@IBNobody)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"

#define __ NO_LED

#ifdef RGB_MATRIX_ENABLE

/* Under-, Per-key
 * ┌───┬───┬───┬───┬───┐
 * │ 4 │ 3 │ 2 │ 1 │ 0 │
 * ├───┼───┼───┼───┼───┤
 * │ 5 │ 6 │ 7 │ 8 │ 9 │
 * ├───┼───┼───┼───┼───┤
 * │14 │13 │12 │11 │   │
 * ├───┼───┼───┼───┤10 │
 * │15 │16 │17 │18 │   │
 * ├───┼───┼───┼───┼───┤
 * │23 │22 │21 │20 │   │
 * ├───┼───┴───┼───┤19 │
 * │24 │  25   │26 │   │
 * └───┴───────┴───┴───┘
 *
 * Underglow (from top / [Esc] = top left)
 * ┌─────────┬─────────┐
 * │         │         │
 * │         │         │
 * │   29    │   30    │
 * │         │         │
 * │         │         │
 * ├─────────┼─────────┤
 * │         │         │
 * │         │         │
 * │   28    │   27    │
 * │         │         │
 * │         │         │
 * └─────────┴─────────┘
 */

led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // Montex v2 WS2812 are laid in a Z-shape with index 0 = top-right
    // Based on: https://xelus.netlify.app/guides/KLE_to_RGB_parser
    { 4,  3,  2,  1,  0},
    { 5,  6,  7,  8,  9},
    { 14, 13, 12, 11, 10},
    { 15, 16, 17, 18, __},
    { 23, 22, 21, 20, __},
    { 24, 25, 26, 19, __}
}, {
    // LED Index to Physical Position
    // per-key
    // Based on: https://xelus.netlify.app/guides/KLE_to_RGB_parser
    {224,0  }, {168,0  }, {112,0  }, { 56,0  }, {  0,0  },  // top row
    {  0,17 }, { 56,17 }, {112,17 }, {168,17 }, {224,17 },  // num-lk & /*- (reversed)
    {224,35 }, {168,29 }, {112,29 }, { 56,29 }, {  0,29 },  // 789+
    {  0,41 }, { 56,41 }, {112,41 }, {168,41 },             // 456  (reversed)
    {224,58 }, {168,52 }, {112,52 }, { 56,52 },             // 123
    {  0,52 }, {  0,64 }, { 84,64 }, {168,64 }              // 0. & enter (reversed)
    // underglow LEDs (positions pushed to nearest edge to match edge key colors)
    #ifndef ID27_DISABLE_UNDERGLOW
    , {224,64 }, {  0,64  },
      {  0,0  }, { 224,0  }
    #endif
}, {
    // LED Index to Flag
    // LED_FLAG_MODIFIER 0x01, LED_FLAG_UNDERGLOW 0x02, LED_FLAG_KEYLIGHT 0x04, LED_FLAG_INDICATOR 0x08
    // per-key
    1, 1, 1, 1, 1,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4
    // underglow
    #ifndef ID27_DISABLE_UNDERGLOW
    , 2, 2, 2, 2
    #endif
} };

#endif
