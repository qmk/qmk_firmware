/*
Copyright 2019 Markus Fritsche <fritsche.markus@gmail.com>

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

#ifndef IBMPC_USB_H
#define IBMPC_USB_H

#include "quantum.h"
#define XXX KC_NO

void matrix_init_user(void);

/*
   This is the mapping for a 102 key board using codeset 2.
   The code in matrix.c supports codeset 1 and codeset 3,
   but the mapping is not finished yet.
*/

/*
                   F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24.
                   F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12.

RST, ESC,     GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   -,     =, STB,BSP,    INS, HOM, PUP,   NLK, SLS, AST, MNS,
SLK, MPL,     TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   [,   ],      STB     DEL, END, PDN,   7,   8,   9,   PLS,
BRK, INT5,    CLK,   A,   S,   D,   F,   G,   H,   J,   K    L,   ;,   ',   \,     ENT,         UP,         4,   5,   6,   COM,
APP, PSC,     LSF, <,   Z,   X,   C,   V,   B,   N,   M,   ,,   .,   /,   STB      RSF,    LFT, SHT, RGT,   1,   2,   3,   ENT,
RGU, LGU,     LCL,      LAT,                     SPC,           RAT,               RCL,         DN,         STB, 0,   STB, DOT

*/
#define LAYOUT(\
                   K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, \
                   K0D, K0E, K0F, K10, K11, K12, K13, K14, K15, K16, K17, K18, \
\
K19, K1A,   K1B, K1C, K1D, K1E, K1F, K20, K21, K22, K23, K24, K25, K26, K27, K28, K29,   K2A, K2B, K2C,   K2D, K2E, K2F, K30, \
K31, K32,   K33,  K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D, K3E, K3F,     K40,   K41, K42, K43,   K44, K45, K46, K47, \
K48, K49,   K4A,   K4B, K4C, K4D, K4E, K4F, K50, K51, K52, K53, K54, K55, K56,    K57,        K58,        K59, K5A, K5B, K5C, \
K5D, K5E,   K5F, K60, K61, K62, K63, K64, K65, K66, K67, K68, K69, K6A,  K6B,     K6C,   K6D, K6E, K6F,   K70, K71, K72, K73, \
K74, K75,   K76,       K77,               K78,                        K79,        K7A,        K7B,        K7C, K7D, K7E, K7F  \
) { \
 { XXX, K01, K02, K03, K04, K05, K06, K07 }, \
 { K08, K09, K0A, K0B, K0C, K0D, K0E, K0F }, \
 { K10, K11, K12, K13, K14, K15, K16, K17 }, \
 { K18, K19, K1A, K1B, K1C, K1D, K1E, K1F }, \
 { K20, K21, K22, K23, K24, K25, K26, K27 }, \
 { K28, K29, K2A, K2B, K2C, K2D, K2E, K2F }, \
 { K30, K31, K32, K33, K34, K35, K36, K37 }, \
 { K38, K39, K3A, K3B, K3C, K3D, K3E, K3F }, \
 { K40, K41, K42, K43, K44, K45, K46, K47 }, \
 { K48, K49, K4A, K4B, K4C, K4D, K4E, K4F }, \
 { K50, K51, K52, K53, K54, K55, K56, K57 }, \
 { K58, K59, K5A, K5B, K5C, K5D, K5E, K5F }, \
 { K60, K61, K62, K63, K64, K65, K66, K67 }, \
 { K68, K69, K6A, K6B, K6C, K6D, K6E, K6F }, \
 { K70, K71, K72, K73, K74, K75, K76, K77 }, \
 { K78, K79, K7A, K7B, K7C, K7D, K7E, K7F } \
}

typedef enum { NONE, PC_XT, PC_AT, PC_TERMINAL, PC_AT_Z150 } keyboard_kind_t;
#define KEYBOARD_KIND_STR(kind) \
    (kind == PC_XT ? "XT" :   \
     kind == PC_AT ? "AT" :   \
     kind == PC_TERMINAL ? "TERMINAL" :   \
     "NONE")

extern uint16_t keyboard_id;
extern keyboard_kind_t keyboard_kind;
extern const uint8_t map_cs1[MATRIX_ROWS][MATRIX_COLS];
extern const uint8_t map_cs2[MATRIX_ROWS][MATRIX_COLS];
extern const uint8_t map_cs3[MATRIX_ROWS][MATRIX_COLS];
#endif
