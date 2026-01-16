/* Copyright 2023 @ Keychron (https://www.keychron.com)
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

// clang-format off
#ifdef LED_MATRIX_ENABLE
const snled27351_led_t PROGMEM g_snled27351_leds[SNLED27351_LED_COUNT] = {
/* Refer to SNLED27351 manual for these locations
 *   driver
 *   |  LED address
 *   |  |   */
    {0, CB1_CA16},
    {0, CB1_CA15},
    {0, CB1_CA14},
    {0, CB1_CA13},
    {0, CB1_CA12},
    {0, CB1_CA11},
    {0, CB1_CA10},
    {0, CB1_CA9 },
    {0, CB1_CA8 },
    {0, CB1_CA7 },
    {0, CB1_CA6 },
    {0, CB1_CA5 },
    {0, CB1_CA4 },
    {0, CB1_CA2 },
    {0, CB1_CA1 },
    {0, CB7_CA1 },

    {0, CB7_CA2 },
    {0, CB7_CA3 }, // NumLock
    {0, CB7_CA4 }, // Mac
    {0, CB7_CA5 }, // Win

    {0, CB2_CA16},
    {0, CB2_CA15},
    {0, CB2_CA14},
    {0, CB2_CA13},
    {0, CB2_CA12},
    {0, CB2_CA11},
    {0, CB2_CA10},
    {0, CB2_CA9 },
    {0, CB2_CA8 },
    {0, CB2_CA7 },
    {0, CB2_CA6 },
    {0, CB2_CA5 },
    {0, CB2_CA4 },
    {0, CB2_CA3 },
    {0, CB2_CA2 },
    {0, CB2_CA1 },
    {0, CB8_CA1 },
    {0, CB8_CA2 },
    {0, CB8_CA3 },
    {0, CB8_CA4 },
    {0, CB8_CA5 },

    {0, CB3_CA16},
    {0, CB3_CA15},
    {0, CB3_CA14},
    {0, CB3_CA13},
    {0, CB3_CA12},
    {0, CB3_CA11},
    {0, CB3_CA10},
    {0, CB3_CA9 },
    {0, CB3_CA8 },
    {0, CB3_CA7 },
    {0, CB3_CA6 },
    {0, CB3_CA5 },
    {0, CB3_CA4 },
    {0, CB3_CA3 },
    {0, CB3_CA2 },
    {0, CB3_CA1 },
    {0, CB7_CA6 },
    {0, CB7_CA7 },
    {0, CB7_CA8 },
    {0, CB7_CA9 },
    {0, CB7_CA10},

    {0, CB4_CA16},
    {0, CB4_CA15},
    {0, CB4_CA14},
    {0, CB4_CA13},
    {0, CB4_CA12},
    {0, CB4_CA11},
    {0, CB4_CA10},
    {0, CB4_CA9 },
    {0, CB4_CA8 },
    {0, CB4_CA7 },
    {0, CB4_CA6 },
    {0, CB4_CA5 },
    {0, CB4_CA3 },
    {0, CB8_CA7 },
    {0, CB8_CA8 },
    {0, CB8_CA9 },

    {0, CB5_CA16},
    {0, CB5_CA14},
    {0, CB5_CA13},
    {0, CB5_CA12},
    {0, CB5_CA11},
    {0, CB5_CA10},
    {0, CB5_CA9 },
    {0, CB5_CA8 },
    {0, CB5_CA7 },
    {0, CB5_CA6 },
    {0, CB5_CA5 },
    {0, CB5_CA3 },
    {0, CB5_CA1 },
    {0, CB8_CA6 },
    {0, CB8_CA11},
    {0, CB8_CA12},
    {0, CB8_CA10},

    {0, CB6_CA16},
    {0, CB6_CA15},
    {0, CB6_CA14},
    {0, CB6_CA10},
    {0, CB6_CA6 },
    {0, CB6_CA5 },
    {0, CB6_CA4 },
    {0, CB6_CA3 },
    {0, CB6_CA2 },
    {0, CB6_CA1 },
    {0, CB7_CA13},
    {0, CB7_CA11},
    {0, CB7_CA12},
};
#endif //LED_MATRIX_ENABLE
