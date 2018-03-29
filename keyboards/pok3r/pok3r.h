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

void y2tp_request(uint8_t);

#define KEYMAP(\
    K07,K17,K27,K37,K47,K57,K67,K77,K06,K16,K26,K36,K46,K56,K66, \
     K76, K05,K15,K25,K35,K45,K55,K65,K75,K04,K14,K24,K34, K44,  \
     K54,  K64,K74,K03,K13,K23,K33,K43,K53,K63,K73,K02,   K12,   \
    K22, K32,K42,K52,K62,K72,K01,K11,K21,K31,K41,K51,  K61, K71, \
    K00, K10, K20,           K30,            K40, K50, K60, K70, \
                         K85,K86,K87,                            \
    K90,K91,K92,K93,K94,K95                                      \
) { \
    { K04,  K01,  K02,  K03,  K00,  K05,  K06,  K07  }, \
    { K14,  K11,  K12,  K13,  K10,  K15,  K16,  K17  }, \
    { K24,  K21,  K22,  K23,  K20,  K25,  K26,  K27  }, \
    { K34,  K31,  K32,  K33,  K30,  K35,  K36,  K37  }, \
    { K44,  K41,  K42,  K43,  K40,  K45,  K46,  K47  }, \
    { K54,  K51,  K52,  K53,  K50,  K55,  K56,  K57  }, \
    { K64,  K61,  K62,  K63,  K60,  K65,  K66,  K67  }, \
    { K74,  K71,  K72,  K73,  K70,  K75,  K76,  K77  }, \
    { KC_NO,KC_NO,KC_NO,KC_NO,KC_NO,K85,  K86,  K87  }, \
    { K94,  K91,  K92,  K93,  K90,  K95,  KC_NO,KC_NO}  \
}
//    PA4,  PA5,  PA6,  PA7,  PC12, PC13, PC14, PC15
// PC4
// ...
// PC3

#define LAYOUT_60_ansi(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,   k0e   , \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e  , \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e    , \
      k30   , k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,     k3c      , \
    k40 , k41 , k42 ,              k47               , k4a , k4b , k4c , k4e   \
) KEYMAP(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,KC_NO,k0e, \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e  , \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e    , \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c  ,KC_NO, \
    k40,  k41,  k42,               k47               , k4a , k4b , k4c , k4e , \
                           KC_NO, KC_NO, KC_NO,                                \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO \
)

#define LAYOUT_60_ansi_split_bs_rshift(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e  , \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e    , \
      k30   , k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c   , k3d, \
    k40 , k41 , k42 ,              k47               , k4a , k4b , k4c , k4e   \
) KEYMAP(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0d, k0e, \
     k10 , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c,  k1e  , \
     k20  , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,    k2e    , \
    k30,KC_NO,k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,   k3c   , k3d, \
    k40,  k41,  k42,               k47               , k4a,  k4b,  k4c,  k4e , \
                           KC_NO, KC_NO, KC_NO,                                \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO                                   \
)

#define LAYOUT_60_iso(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c, k0e     , \
    k10  , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c        , \
    k20   , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k1e,  k2e , \
    k30 , k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c         , \
    k40 , k41 , k42 ,               k47             , k4a , k4b , k4c , k4e    \
) KEYMAP(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,KC_NO,k0e, \
    k10  , k11, k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1e   , \
    k20   , k21, k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b,       k2e , \
    k30 , k31, k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b, k3c   ,KC_NO, \
    k40 , k41 , k42 ,               k47             , k4a , k4b , k4c , k4e  , \
                            KC_NO, KC_NO, KC_NO,                               \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO                                   \
)

#endif // POK3R_H
