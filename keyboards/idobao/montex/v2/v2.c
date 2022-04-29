/* Copyright 2022 IBNobody & vinorodrigues
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see &lt;http://www.gnu.org/licenses/&gt;.
 */

#include "v2.h"

#ifdef RGB_MATRIX_ENABLE

#define __ NO_LED

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
    // underglow
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
