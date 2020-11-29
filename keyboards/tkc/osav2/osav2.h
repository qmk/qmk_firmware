/* Copyright 2019 jrfhoutx
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/* LAYOUT
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐┌────────┐
 * │10 │ │00 │01 │02 │03 │04 │05 │06 │         │56 │55 │54 │53 │52 │51 │50 │57 ││57      │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤└────────┘
 * │20 │ │11   │12 │13 │14 │15 │16 │         │66 │65 │64 │63 │62 │61 │60 │67   │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │30 │ │21    │22 │23 │24 │25 │26 │         │76 │75 │74 │73 │72 │71 │77      │
 * └───┘ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤┌──────────┐
 *       │31      │32 │33 │34 │35 │36 │     │86 │85 │84 │83 │82 │81 │80    │87 ││87        │
 *       ├─────┬──┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤└──────────┘
 *       │41   │     │43   │45     │46  │   │95        │93   │           │90   │
 *       └─────┘     └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
#define LAYOUT_default_ansi( \
  K10, K00, K01, K02, K03, K04, K05, K06,   K56, K55, K54, K53, K52, K51,      K57, \
  K20, K11, K12, K13, K14, K15, K16,        K66, K65, K64, K63, K62, K61, K60, K67, \
  K30, K21, K22, K23, K24, K25, K26,        K76, K75, K74, K73, K72, K71,      K77, \
       K31, K32, K33, K34, K35, K36,        K86, K85, K84, K83, K82, K81,      K87, \
       K41,      K43,      K45, K46,        K95,           K93,                K90  \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO  }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO  }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO  }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   KC_NO  }, \
    { KC_NO, K41,   KC_NO, K43,   KC_NO, K45,   K46,   KC_NO  }, \
    { KC_NO, K51,   K52,   K53,   K54,   K55,   K56,   K57    }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67    }, \
    { KC_NO, K71,   K72,   K73,   K74,   K75,   K76,   K77    }, \
    { KC_NO, K81,   K82,   K83,   K84,   K85,   K86,   K87    }, \
    { K90,   KC_NO, KC_NO, K93,   KC_NO, K95,   KC_NO, KC_NO  }  \
}
#define LAYOUT_split_backspace( \
  K10, K00, K01, K02, K03, K04, K05, K06,   K56, K55, K54, K53, K52, K51, K50, K57, \
  K20, K11, K12, K13, K14, K15, K16,        K66, K65, K64, K63, K62, K61, K60, K67, \
  K30, K21, K22, K23, K24, K25, K26,        K76, K75, K74, K73, K72, K71,      K77, \
       K31, K32, K33, K34, K35, K36,        K86, K85, K84, K83, K82, K81,      K87, \
       K41,      K43,      K45, K46,        K95,           K93,                K90  \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO  }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO  }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO  }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   KC_NO  }, \
    { KC_NO, K41,   KC_NO, K43,   KC_NO, K45,   K46,   KC_NO  }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57    }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67    }, \
    { KC_NO, K71,   K72,   K73,   K74,   K75,   K76,   K77    }, \
    { KC_NO, K81,   K82,   K83,   K84,   K85,   K86,   K87    }, \
    { K90,   KC_NO, KC_NO, K93,   KC_NO, K95,   KC_NO, KC_NO  }  \
}
#define LAYOUT_split_right_shift( \
  K10, K00, K01, K02, K03, K04, K05, K06,   K56, K55, K54, K53, K52, K51,      K57, \
  K20, K11, K12, K13, K14, K15, K16,        K66, K65, K64, K63, K62, K61, K60, K67, \
  K30, K21, K22, K23, K24, K25, K26,        K76, K75, K74, K73, K72, K71,      K77, \
       K31, K32, K33, K34, K35, K36,        K86, K85, K84, K83, K82, K81, K80, K87, \
       K41,      K43,      K45, K46,        K95,           K93,                K90  \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO  }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO  }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO  }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   KC_NO  }, \
    { KC_NO, K41,   KC_NO, K43,   KC_NO, K45,   K46,   KC_NO  }, \
    { KC_NO, K51,   K52,   K53,   K54,   K55,   K56,   K57    }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67    }, \
    { KC_NO, K71,   K72,   K73,   K74,   K75,   K76,   K77    }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87    }, \
    { K90,   KC_NO, KC_NO, K93,   KC_NO, K95,   KC_NO, KC_NO  }  \
}
#define LAYOUT_all( \
  K10, K00, K01, K02, K03, K04, K05, K06,   K56, K55, K54, K53, K52, K51, K50, K57, \
  K20, K11, K12, K13, K14, K15, K16,        K66, K65, K64, K63, K62, K61, K60, K67, \
  K30, K21, K22, K23, K24, K25, K26,        K76, K75, K74, K73, K72, K71,      K77, \
       K31, K32, K33, K34, K35, K36,        K86, K85, K84, K83, K82, K81, K80, K87, \
       K41,      K43,      K45, K46,        K95,           K93,                K90  \
) \
{ \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   KC_NO  }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   KC_NO  }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   KC_NO  }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   KC_NO  }, \
    { KC_NO, K41,   KC_NO, K43,   KC_NO, K45,   K46,   KC_NO  }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57    }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67    }, \
    { KC_NO, K71,   K72,   K73,   K74,   K75,   K76,   K77    }, \
    { K80,   K81,   K82,   K83,   K84,   K85,   K86,   K87    }, \
    { K90,   KC_NO, KC_NO, K93,   KC_NO, K95,   KC_NO, KC_NO  }  \
}
