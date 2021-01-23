/*
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

#include "quantum.h"

#define XXX KC_NO

#define LAYOUT(                                                                     \
    K00 , K01 , K02 , K03 , K04 , K05 , K06 , K07 ,   K08 , K09,   K0A,K0B,K0C,K0D,K0E,K0F,  \
    K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K1A,K1B,K1C,K1D,K1E,   K50,K51,K52,K53, \
                                                                                    \
    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,K2E,   K54,K55,K56,K57, \
    K30,K31,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,       K58,K59,K5A,K5B, \
    K40,K41,K42,K43,K44,K45,K46,K47,K48,K49,K4A,K4B,K4C,K4D,        K5C , K5D ,     \
                                                                                    \
                            K4E                                                     \
) { \
    {  K32 ,  K46 ,  K44 ,  K34 ,  K23 ,  K35 ,  K36 ,  K37  }, /*  A      B      C      D      E      F      G      H   */ \
    {  K28 ,  K38 ,  K39 ,  K3A ,  K48 ,  K47 ,  K29 ,  K2A  }, /*  I      J      K      L      M      N      O      P   */ \
    {  K21 ,  K24 ,  K33 ,  K25 ,  K27 ,  K45 ,  K22 ,  K43  }, /*  Q      R      S      T      U      V      W      X   */ \
    {  K26 ,  K42 ,  K1A ,  K11 ,  K12 ,  K13 ,  K14 ,  K15  }, /*  Y      Z      0      1      2      3      4      5   */ \
    {  K16 ,  K17 ,  K18 ,  K19 ,  K00 ,  K01 ,  K02 ,  K03  }, /*  6      7      8      9      F1     F2     F3     F4  */ \
    {  K04 ,  K05 ,  K06 ,  K07 ,  K08 ,  K09 ,  K10 ,  K20  }, /*  F5     F6     F7     F8     F9     F10    ESC    TAB */ \
    {  K3D ,  K2E ,  K4D ,  K4E ,  XXX ,  XXX ,  XXX ,  XXX  }, /*  LF     CR     BRK    SPACE*/ \
    {  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX  }, \
    {  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX  }, \
    {  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX  }, \
    {  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX ,  XXX  }, \
    {  XXX ,  XXX ,  K0A ,  K0B ,  K0C ,  K0D ,  K0E ,  K0F  }  /*                ENC+   ENC-   ESHF+  ESHF-  ECTR+  ECTR-*/\
}

