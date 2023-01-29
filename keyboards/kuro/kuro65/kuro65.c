/* Copyright 2023, Tobias Minn (0x544D)
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
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kuro65.h"

#ifdef RGB_MATRIX_ENABLE


led_config_t g_led_config = { {
    // Key Matrix (16x5) to LED Index
    {     54 ,      55 ,      56 ,      57 ,      58 ,      59 ,      60 ,      61 ,      62 ,      63 ,      64 ,      65 ,      66 ,  NO_LED ,      67 ,      68},
    {     53 ,      52 ,      51 ,      50 ,      49 ,      48 ,      47 ,      46 ,      45 ,      44 ,      43 ,      42 ,      41 ,  NO_LED ,  NO_LED ,      40},
    {     25 ,      26 ,      27 ,      28 ,      29 ,      30 ,      31 ,      32 ,      33 ,      34 ,      35 ,      36 ,      37 ,  NO_LED ,      38 ,      39},
    {     24 ,      20 ,      19 ,      18 ,      17 ,      16 ,      15 ,      14 ,      13 ,      12 ,      11 ,      10 ,       9 ,  NO_LED ,       8 ,       7},
    {     23 ,      22 ,      21 ,  NO_LED ,  NO_LED ,  NO_LED ,       0 ,  NO_LED ,  NO_LED ,  NO_LED ,       1 ,       2 ,       3 ,       4 ,       5 ,       6}
}, {
    // LED Index to Physical Position
    /*  0    ,    1    ,    2    ,    3    ,    4    ,    5    ,    6    ,    7    ,    8    ,    9    ,    10   ,    11   ,    12   ,    13   ,    14   ,    15  */
    /* space ,  alt gr ,   fn    ,   strg  ,   left  ,   down  ,   right ,   func  ,    up   ,  rshift ,   dash  ,   dot   ,  comma  ,    m    ,    n    ,    b   */
    { 96, 64},{150, 64},{165, 64},{180, 64},{195, 64},{210, 64},{224, 64},{224, 48},{210, 48},{189, 48},{169, 48},{154, 48},{139, 48},{124, 48},{109, 48},{ 94, 48},
    /*  16   ,    17   ,    18   ,    19   ,    20   ,    21   ,    22   ,    23   ,    24   ,    25   ,    26   ,    27   ,    28   ,    29   ,    30   ,    31  */
    /*  v    ,    c    ,    x    ,    y    ,    <    ,    alt  ,    OS   ,   strg  ,   shift ,   caps  ,    a    ,    s    ,    d    ,    f    ,    g    ,    h   */
    { 79, 48},{ 64, 48},{ 49, 48},{ 34, 48},{ 19, 48},{ 39, 64},{ 21, 64},{  2, 64},{  2, 48},{  6, 32},{ 26, 32},{ 41, 32},{ 56, 32},{ 71, 32},{ 86, 32},{101, 32},
    /*  32   ,    33   ,    34   ,    35   ,    36   ,    37   ,    38   ,    39   ,    40   ,    41   ,    42   ,    43   ,    44   ,    45   ,    46   ,    47  */
    /*  j    ,    k    ,    l    ,    ö    ,    ä    ,    #    ,    ent  ,   pgdn  ,   pgup  ,    +    ,    ü    ,    p    ,    o    ,    i    ,    u    ,    z   */
    {116, 32},{131, 32},{146, 32},{161, 32},{176, 32},{191, 32},{208, 24},{224, 32},{224, 16},{188, 16},{173, 16},{158, 16},{143, 16},{128, 16},{113, 16},{ 98, 16},
    /*  48   ,    49   ,    50   ,    51   ,    52   ,    53   ,    54   ,    55   ,    56   ,    57   ,    58   ,    59   ,    60   ,    61   ,    62   ,    63  */
    /*  t    ,    r    ,    e    ,    w    ,    q    ,   tab   ,    esc  ,    1    ,    2    ,    3    ,    4    ,    5    ,    6    ,    7    ,    8    ,    9   */
    { 83, 16},{ 68, 16},{ 53, 16},{ 38, 16},{ 23, 16},{  4, 16},{  0,  0},{ 15,  0},{ 30,  0},{ 45,  0},{ 60,  0},{ 75,  0},{ 90,  0},{105,  0},{120,  0},{135,  0},
    /*  64   ,    65   ,    66   ,    67   ,    68   */
    /*  0    ,    ß    ,    ´    ,   bksp  ,    del  */
    {150,  0},{165,  0},{180,  0},{203,  0},{224,  0}
}, {
    // LED Index to Flag
    /*  0    ,    1    ,    2    ,    3    ,    4    ,    5    ,    6    ,    7    ,    8    ,    9    ,    10   ,    11   ,    12   ,    13   ,    14   ,    15  */
    /* space ,  alt gr ,   fn    ,   strg  ,   left  ,   down  ,   right ,   func  ,    up   ,  rshift ,   dash  ,   dot   ,  comma  ,    m    ,    n    ,    b   */
        4    ,    1    ,    1    ,    1    ,    4    ,    4    ,    4    ,    4    ,    4    ,    1    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,
    /*  16   ,    17   ,    18   ,    19   ,    20   ,    21   ,    22   ,    23   ,    24   ,    25   ,    26   ,    27   ,    28   ,    29   ,    30   ,    31  */
    /*  v    ,    c    ,    x    ,    y    ,    <    ,    alt  ,    OS   ,   strg  ,   shift ,   caps  ,    a    ,    s    ,    d    ,    f    ,    g    ,    h   */
        4    ,    4    ,    4    ,    4    ,    4    ,    1    ,    1    ,    1    ,    1    ,    1    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,
    /*  32   ,    33   ,    34   ,    35   ,    36   ,    37   ,    38   ,    39   ,    40   ,    41   ,    42   ,    43   ,    44   ,    45   ,    46   ,    47  */
    /*  j    ,    k    ,    l    ,    ö    ,    ä    ,    #    ,    ent  ,   pgdn  ,   pgup  ,    +    ,    ü    ,    p    ,    o    ,    i    ,    u    ,    z   */
        4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,
    /*  48   ,    49   ,    50   ,    51   ,    52   ,    53   ,    54   ,    55   ,    56   ,    57   ,    58   ,    59   ,    60   ,    61   ,    62   ,    63  */
    /*  t    ,    r    ,    e    ,    w    ,    q    ,   tab   ,    esc  ,    1    ,    2    ,    3    ,    4    ,    5    ,    6    ,    7    ,    8    ,    9   */
        4    ,    4    ,    4    ,    4    ,    4    ,    1    ,    1    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,    4    ,
    /*  64   ,    65   ,    66   ,    67   ,    68   */
    /*  0    ,    ß    ,    ´    ,   bksp  ,    del  */
        4    ,    4    ,    4    ,    4    ,    4    
} };


bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }
    if (host_keyboard_led_state().caps_lock)
    {
        rgb_matrix_set_color(25, 0xFF, 0xFF, 0xFF);
    }
    return true;
}
#endif
