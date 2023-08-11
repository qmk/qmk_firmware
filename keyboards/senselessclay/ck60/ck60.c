/* Copyright 2022 kb-elmo<mail@elmo.space>
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

#include "quantum.h"

#define __ NO_LED

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    //Key Matrix to LED Index
    {   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,   10,  11,  12,  13  },
    {   27,  26,  25,  24,  23,  22,  21,  20,  19,  18,  17,  16,  15,  14  },
    {   28,  29,  30,  31,  32,  33,  34,  35,  36,  37,  38,  39,  40,  __  },
    {   53,  52,  51,  50,  49,  48,  47,  46,  45,  44,  43,  42,  41,  __  },
    {   54,  55,  56,  __,  __,  __,  57,  __,  __,  __,  58,  59,  60,  61  }
}, {
    //LED Index to Physical Positon
    { 0,   0  }, { 17,  0  }, { 34,  0  }, { 52,  0  }, { 69,  0  }, { 86,  0  }, { 103, 0  }, { 121, 0  }, { 138, 0  }, { 155, 0  }, { 172, 0  }, { 190, 0  }, { 207, 0  }, { 215, 0  },
    { 224, 24 }, { 215, 16 }, { 198, 16 }, { 180, 16 }, { 164, 16 }, { 146, 16 }, { 129, 16 }, { 112, 16 }, { 95,  16 }, { 78,  16 }, { 60,  16 }, { 43,  16 }, { 26 , 16 }, { 0,   16 },
    { 0,   32 }, { 30,  32 }, { 47,  32 }, { 65,  32 }, { 81,  32 }, { 99,  32 }, { 116, 32 }, { 133, 32 }, { 150, 32 }, { 168, 32 }, { 185, 32 }, { 202, 32 }, { 220, 32 },
    { 207, 48 }, { 190, 48 }, { 172, 48 }, { 155, 48 }, { 138, 48 }, { 121, 48 }, { 103, 48 }, { 86,  48 }, { 69,  48 }, { 52,  48 }, { 34,  48 }, { 17,  48 }, { 0,   48 },
    { 0,   64 }, { 17,  64 }, { 34,  64 },                                        { 103, 64 },                                        { 172, 64 }, { 190, 64 }, { 207, 64 }, { 224, 64 }
}, {
    1,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   1,
    1,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   1,
    1,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,
    1,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   4,   1,
    1,   1,   1,                  4,                  1,   1,   1,   1
} };
#endif
