/* Copyright 2020 jagdpietr
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

#pragma once

#include "quantum.h"

#define XXX KC_NO

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */


/* LAYOUT_ansi
 * ,---------------------------------------------------------.     .---. 
 * |00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |0A |0B |0C |0D|2D|     |5C |
 * |---------------------------------------------------------| ,-----------.
 * |10  |11 |12 |13 |14 |15 |16 |17 |18 |19 |1A |1B |1C |1D  | |5A |5D |59 |
 * |---------------------------------------------------------| `-----------'
 * |20   |21 |22 |23 |24 |25 |26 |27 |28 |29 |2A |2B |2C     |     |5B |
 * |---------------------------------------------------------.     `---'
 * |30    |31 |32 |33 |34 |35 |36 |37 |38 |39 |3A |3B |  |3C |
 * |--------------------------------------------------'--`---'---.
 * |40 |41 |42 |   43                     |49 |4A |  |4B |4C |4D |
 * `----------------------------------------------'  `-----------'
 */

#define LAYOUT_ansi( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D,      K5C,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K5A, K5D, K59, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,                K5B,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C,                     \
    K40, K41, K42, K43,                          K49, K4A,      K4B, K4C, K4D                 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  XXX  }, \
    { K40,  K41,  K42,  K43,  XXX,  XXX,  XXX,  XXX,  XXX,  K49,  K4A,  K4B,  K4C,  K4D  }, \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K59,  K5A,  K5B,  K5C,  K5D  }  \
}

/* LAYOUT_wkl
 * ,---------------------------------------------------------.     .---. 
 * |00 |01 |02 |03 |04 |05 |06 |07 |08 |09 |0A |0B |0C |0D|2D|     |5C |
 * |---------------------------------------------------------| ,-----------.
 * |10  |11 |12 |13 |14 |15 |16 |17 |18 |19 |1A |1B |1C |1D  | |5A |5D |59 |
 * |---------------------------------------------------------| `-----------'
 * |20   |21 |22 |23 |24 |25 |26 |27 |28 |29 |2A |2B |2C     |     |5B |
 * |---------------------------------------------------------.     `---'
 * |30    |31 |32 |33 |34 |35 |36 |37 |38 |39 |3A |3B |  |3C |
 * |--------------------------------------------------'--`---'---.
 * |40 |   |42 |   43                     |49 |4A |  |4B |4C |4D |
 * `----------------------------------------------'  `-----------'
 */

#define LAYOUT_wkl( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K2D,      K5C,      \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K5A, K5D, K59, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C,                K5B,      \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B,      K3C,                     \
    K40,      K42, K43,                          K49, K4A,      K4B, K4C, K4D                 \
) \
{ \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D  }, \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1D  }, \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D  }, \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  K3C,  XXX  }, \
    { K40,  XXX,  K42,  K43,  XXX,  XXX,  XXX,  XXX,  XXX,  K49,  K4A,  K4B,  K4C,  K4D  }, \
    { XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  XXX,  K59,  K5A,  K5B,  K5C,  K5D  }  \
} 
