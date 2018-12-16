/* Copyright 2017 Mathias Andersson <wraul@dbox.se>
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
#ifndef KMAC_H
#define KMAC_H

#include "quantum.h"

// Keymap for the winkey version of the PCB.
#define LAYOUT(                                                                                                                           \
    K00, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G,                                                       \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G,                                                  \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G,                                                  \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,                                                                      \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4F,                                                                      \
    K50, K51, K52, K55, K58, K5A, K5C, K5D, K5E, K5F, K5G)                                                                                \
    {                                                                                                                                     \
        /*        0      1      2      3      4      5      6      7      8      9      A      B      C      D      E      F      G    */ \
        /* 0 */ {K00, KC_NO, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G},                                  \
            /* 1 */ {K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G},                                \
            /* 2 */ {K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G},                                \
            /* 3 */ {K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, KC_NO, K3D, KC_NO, KC_NO, KC_NO},                        \
            /* 4 */ {K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, KC_NO, KC_NO, K4D, KC_NO, K4F, KC_NO},                        \
        /* 5 */ { K50, K51, K52, KC_NO, KC_NO, K55, KC_NO, KC_NO, K58, KC_NO, K5A, KC_NO, K5C, K5D, K5E, K5F, K5G }                       \
    }

// Keymap for the winkeyless version of the PCB.
#define LAYOUT_WKL(                                                                                                                               \
    K00, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G,                                                               \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G,                                                          \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G,                                                          \
    K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,                                                                              \
    K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4F,                                                                              \
    K50, K51, K52, K55, K58, K5A, K5D, K5E, K5F, K5G) LAYOUT(K00, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E, K0F, K0G,      \
                                                             K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D, K1E, K1F, K1G, \
                                                             K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D, K2E, K2F, K2G, \
                                                             K30, K31, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3D,                     \
                                                             K40, K41, K42, K43, K44, K45, K46, K47, K48, K49, K4A, K4D, K4F,                     \
                                                             K50, K51, K52, K55, K58, K5A, KC_NO, K5D, K5E, K5F, K5G)

#endif
