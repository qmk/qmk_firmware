/*
 * Copyright 2018 Jonathan A. Kollasch
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

#ifndef POK3R_H
#define POK3R_H

#include "quantum.h"

#define KEYMAP( \
    K01, K02, K03, K04, K05, K06, K07, K08, K36, K37, K38, K39, K41, K40, /* 14 keys */ \
    K09, K10, K11, K12, K13, K14, K15, K16, K42, K43, K44, K45, K47,      /* 13 keys */ \
    K17, K18, K19, K20, K21, K22, K23, K24, K48, K49, K50, K51, K46, K52, /* 14 keys */ \
    K25, K63, K26, K27, K28, K29, K30, K31, K32, K54, K55, K56, K57, K58, /* 14 keys, 2 dnp */ \
    K33, K34, K35,                K53,                K59, K60, K61, K62, /* 8 keys */  \
                                                      S01, S02, S03, S04  /* dip switches */ \
) { \
    /*           ROW1   ROW2   ROW3   ROW4   ROW5   ROW6   ROW7   ROW8   ROW9 */ \
    /* COL1 */ { K01,   K33,   K09,   K63,   K17,   KC_NO, K25,   KC_NO, S01  }, \
    /* COL2 */ { K02,   K34,   K10,   KC_NO, K18,   KC_NO, K26,   KC_NO, S02  }, \
    /* COL3 */ { K03,   K35,   K11,   K41,   K19,   K47,   K27,   K53,   S03  }, \
    /* COL4 */ { K04,   K36,   K12,   K42,   K20,   K48,   K28,   K54,   K59  }, \
    /* COL5 */ { K05,   K37,   K13,   K43,   K21,   K49,   K29,   K55,   K60  }, \
    /* COL6 */ { K06,   K38,   K14,   K44,   K22,   K50,   K30,   K56,   K61  }, \
    /* COL7 */ { K07,   K39,   K15,   K45,   K23,   K51,   K31,   K57,   S04  }, \
    /* COL8 */ { K08,   K40,   K16,   K46,   K24,   K52,   K32,   K58,   K62  }  \
}

#define LAYOUT_60_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
      k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,       \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_lshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,      \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
      k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,   k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,    k3d, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_lshift_rshift( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e,   \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e,     \
     k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,  k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30, k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c,   k3d,  \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_iso( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e,    \
     k10,  k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20,   k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
      k30,    k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c,       \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e    \
) KEYMAP( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,    k0e,   \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,         \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e,  \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c  ,KC_NO, \
    k40,  k41,  k42,               k47,               k4a,  k4b,  k4c,  k4e,   \
                                                    KC_NO, KC_NO, KC_NO, KC_NO \
)

#endif // POK3R_H
