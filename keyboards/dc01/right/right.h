/* Copyright 2018 Yiancar
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
#ifndef RIGHT_H
#define RIGHT_H

#include "quantum.h"

#define XXX KC_NO

// This a shortcut to help you visually see your layout.
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array
#define LAYOUT_ansi( \
         K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16, K17, \
    K20, K21, K22, K23, K24, K25,      K27, \
    K30, K31, K32, K33, K34,           K37, \
    K40, K41, K42, K43, K44, K45            \
) \
{ \
    { XXX, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, XXX, K27 }, \
    { K30, K31, K32, K33, K34, XXX, XXX, K37 }, \
    { K40, K41, K42, K43, K44, K45, XXX, XXX }  \
}

#define LAYOUT_iso( \
         K01, K02, K03, K04, K05, K06, K07, \
    K10, K11, K12, K13, K14, K15, K16,      \
    K20, K21, K22, K23, K24, K25, K26, K27, \
    K30, K31, K32, K33, K34,           K37, \
    K40, K41, K42, K43, K44, K45            \
) \
{ \
    { XXX, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, XXX, XXX, K37 }, \
    { K40, K41, K42, K43, K44, K45, XXX, XXX }  \
}

#define LAYOUT_hhkb_ansi( \
         K01, K02, K03, K04, K05, K06, K07, K00, \
    K10, K11, K12, K13, K14, K15, K16, K17,      \
    K20, K21, K22, K23, K24, K25,      K27,      \
    K30, K31, K32, K33, K34,      K36, K37,      \
    K40, K41, K42, K43, K44, K45                 \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, K17 }, \
    { K20, K21, K22, K23, K24, K25, XXX, K27 }, \
    { K30, K31, K32, K33, K34, XXX, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, XXX, XXX }  \
}

#define LAYOUT_hhkb_iso( \
         K01, K02, K03, K04, K05, K06, K07, K00, \
    K10, K11, K12, K13, K14, K15, K16,           \
    K20, K21, K22, K23, K24, K25, K26, K27,      \
    K30, K31, K32, K33, K34,      K36, K37,      \
    K40, K41, K42, K43, K44, K45                 \
) \
{ \
    { K00, K01, K02, K03, K04, K05, K06, K07 }, \
    { K10, K11, K12, K13, K14, K15, K16, XXX }, \
    { K20, K21, K22, K23, K24, K25, K26, K27 }, \
    { K30, K31, K32, K33, K34, XXX, K36, K37 }, \
    { K40, K41, K42, K43, K44, K45, XXX, XXX }  \
}

#endif
