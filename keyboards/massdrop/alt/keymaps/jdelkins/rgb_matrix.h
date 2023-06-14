/*
  Copyright 2020 Joel Elkins <joel@elkins.com>

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

/* RGB LED Layout on the Massdrop ALT
 *
 *  ┌────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┐
 *  │                                                                                                                                                │
 *  │              100        99       98       97       96       95       94       93       92       91        90        89        88               │
 *  │    101                                                                                                                                  87     |
 *  │         ┌───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬───────┬────────────┬───────┐         │
 *  │         │       │       │       │       │       │       │       │       │       │       │       │       │       │            │       │         │
 *  │         │   `   │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │   0   │   -   │   =   │ BackSpace  │ Home  │         │
 *  │         │   1   │   2   │   3   │   4   │   5   │   6   │   7   │   8   │   9   │  10   │  11   │  12   │  13   │    14      │  15   │         │
 *  │  102    ├───────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬─────────┼───────┤    86   │
 *  │         │          │       │       │       │       │       │       │       │       │       │       │       │       │         │       │         │
 *  │         │    Tab   │   Q   │   W   │   E   │   R   │   T   │   Y   │   U   │   I   │   O   │   P   │   [   │   ]   │    \    │  Del  │         │
 *  │         │    16    │  17   │  18   │  19   │  20   │  21   │  22   │  23   │  24   │  25   │  26   │  27   │  28   │   29    │  30   │         │
 *  │  103    ├──────────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─┬─────┴─────────┼───────┤    85   │
 *  │         │            │       │       │       │       │       │       │       │       │       │       │       │               │       │         │
 *  │         │  Ctrl/Esc  │   A   │   S   │   D   │   F   │   G   │   H   │   J   │   K   │   L   │   ;   │   '   │    Return     │ PgUp  │         │
 *  │         │     31     │  32   │  33   │  34   │  35   │  36   │  37   │  38   │  39   │  40   │  41   │  42   │      43       │  44   │         │
 *  │  104    ├────────────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴──┬────┴───────┬───────┼───────┤    84   │
 *  │         │               │       │       │       │       │       │       │       │       │       │       │            │       │       │         │
 *  │         │     Shift     │   Z   │   X   │   C   │   V   │   B   │   N   │   M   │   ,   │   .   │   /   │   Shift    │  Up   │ PgDn  │         │
 *  │         │      45       │  46   │  47   │  48   │  49   │  50   │  51   │  52   │  53   │  54   │  55   │    56      │  57   │  58   │         │
 *  │  105    ├─────────┬─────┴───┬───┴─────┬─┴───────┴───────┴───────┴───────┴───────┴─────┬─┴───────┼───────┴─┬──┬───────┼───────┼───────┤    83   │
 *  │         │         │         │         │                                               │         │         │▒▒│       │       │       │         │
 *  │         │  Ctrl   │   GUI   │   Alt   │                     Space                     │   Alt   │  Func   │▒▒│ Left  │ Down  │ Right │         │
 *  │         │   59    │   60    │   61    │                      62                       │   63    │   64    │▒▒│  65   │  66   │  67   │         │
 *  │         └─────────┴─────────┴─────────┴───────────────────────────────────────────────┴─────────┴─────────┴──┴───────┴───────┴───────┘         │
 *  │    68                                                                                                                                   82     │
 *  │               69        70       71       72       73       74       75       76       77       78        79        80        81               │
 *  │                                                                                                                                                │
 *  └────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────────┘
 */

enum layer_rgb_type {
    type_hsv,
    type_rgb,
};

#define RGB_LINK_TO_LAYER(layer) (layer + RGB_MATRIX_EFFECT_MAX)

struct layer_rgb {
    uint8_t type;
    led_flags_t flags;
    uint8_t mode;
    union {
        HSV hsv;
        RGB rgb[RGB_MATRIX_LED_COUNT];
    };
};

#define LAYOUT_rgb(_flags, _mode, \
        R101,  R100, R99,  R98,  R97,  R96,  R95,  R94,  R93,  R92,  R91,  R90,  R89,  R88,  R87, \
        R102,   R1,  R2,  R3,  R4,  R5,  R6,  R7,  R8,  R9,  R10, R11, R12, R13, R14, R15,   R86, \
        R103,   R16, R17, R18, R19, R20, R21, R22, R23, R24, R25, R26, R27, R28, R29, R30,   R85, \
                R31, R32, R33, R34, R35, R36, R37, R38, R39, R40, R41, R42,    R43,   R44,        \
        R104,   R45, R46, R47, R48, R49, R50, R51, R52, R53, R54, R55,    R56,   R57, R58,   R84, \
        R105,   R59, R60, R61,                R62,                R63, R64, R65, R66, R67,   R83, \
        R68,   R69,  R70,  R71,  R72,  R73,  R74,  R75,  R76,  R77,  R78,  R79,  R80,  R81,  R82 \
    ) (struct layer_rgb) { .type = type_rgb, .flags = _flags, .mode = _mode, .rgb = { \
        R1, R2, R3, R4, R5, R6, R7, R8, R9, R10, R11, R12, R13, R14, R15, R16, R17, R18, R19, R20, R21, \
        R22, R23, R24, R25, R26, R27, R28, R29, R30, R31, R32, R33, R34, R35, R36, R37, R38, R39, R40,  \
        R41, R42, R43, R44, R45, R46, R47, R48, R49, R50, R51, R52, R53, R54, R55, R56, R57, R58, R59,  \
        R60, R61, R62, R63, R64, R65, R66, R67, R68, R69, R70, R71, R72, R73, R74, R75, R76, R77, R78,  \
        R79, R80, R81, R82, R83, R84, R85, R86, R87, R88, R89, R90, R91, R92, R93, R94, R95, R96, R97,  \
        R98, R99, R100, R101, R102, R103, R104, R105 \
    }}

#define LAYOUT_hsv(_flags, _mode, _hsv) \
    (struct layer_rgb) { \
        .type = type_hsv, \
        .flags = _flags, \
        .mode = _mode, \
        .hsv = {_hsv} \
    }

