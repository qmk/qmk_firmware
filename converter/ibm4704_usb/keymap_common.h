/*
Copyright 2011,2012,2013 Jun Wako <wakojun@gmail.com>

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
#ifndef KEYMAP_COMMON_H
#define KEYMAP_COMMON_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "action.h"
#include "action_macro.h"
#include "report.h"
#include "print.h"
#include "debug.h"
#include "keymap.h"


// 32*8(256) byte array which converts PS/2 code into USB code
extern const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS];
extern const uint16_t fn_actions[];


/* 107-key */
#define KEYMAP( \
    K46,K64,     K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,   K6A,K6B,K6C,    K47,K48,K49,K4A, \
    K56,K66,     K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,       K6D,K6E,K6F,    K4B,K4C,K4D,K4E, \
    K71,K77,     K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,       K70,K65,K72,    K50,K51,K52,K53, \
    K44,K45,     K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,       K74,K75,K76,    K5E,K58,K59,K5A, \
    K54,K55,     K31,K41,K3F,        K40,                        K42,K2F,       K78,K67,K79,    K5B,K5C,K5D,K57  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_NO    }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_NO,    KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_NO,    KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_NO,    KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_NO,    KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_NO    }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_NO,    KC_NO,    KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_##K6F }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_NO,    KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_##K78, KC_##K79, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
}

/* 77-key */
#define KEYMAP_77( \
    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,   K6A,K6B,K6C, \
    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,       K6D,K6E,K6F, \
    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,       K70,K65,K72, \
    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,       K74,K75,K76, \
    K31,K41,K3F,        K40,                        K42,K2F,       K78,K67,K79  \
) KEYMAP( \
    F1,  F2,    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,    K6A,K6B,K6C,    NLCK,PSLS,PAST,PMNS, \
    F3,  F4,    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,        K6D,K6E,K6F,    P7,  P8,  P9,  PPLS, \
    F5,  F6,    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,        K70,K65,K72,    P4,  P5,  P6,  PPLS, \
    F7,  F8,    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,        K74,K75,K76,    P1,  P2,  P3,  PENT, \
    F9,  F10,   K31,K41,K3F,        K40,                        K42,K2F,        K78,K67,K79     P0,  P0,  PDOT,PENT  \
)

/* 62-key */
#define KEYMAP_62( \
    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E, \
    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D, \
    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D, \
    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D, \
    K31,K41,K3F,        K40,                        K42,K2F  \
) KEYMAP( \
    F1,  F2,    K00,K18,K19,K1A,K10,K11,K12,K08,K09,K0A,K0F,K1F,K0D,K0C,K0E,   INS, HOME,PGUP,     NLCK,PSLS,PAST,PMNS, \
    F3,  F4,    K04,K05,K06,K13,K14,K15,K16,K17,K01,K02,K03,K1B,K1C,K1D,       DEL, END, PGDN,     P7,  P8,  P9,  PPLS, \
    F5,  F6,    K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,K2A,K2B,K2C,K2D,       PSCR,SLCK,PAUS,     P4,  P5,  P6,  PPLS, \
    F7,  F8,    K30,K3E,K32,K33,K34,K35,K36,K37,K38,K39,K3A,K3B,K3C,K3D,       F11, UP,  F12,      P1,  P2,  P3,  PENT, \
    F9,  F10,   K31,K41,K3F,        K40,                        K42,K2F,       LEFT,DOWN,RGHT,     P0,  P0,  PDOT,PENT  \
)

/* 50-key */
#define KEYMAP_50( \
    K00,K01,K02,    K03,K04,K05,    K20,K21,K22,K23, \
    K08,K09,K0A,    K0B,K0C,K0D,    K28,K29,K2A,K35, \
    K10,K11,K12,    K13,K14,K15,    K30,K31,K32,K36, \
    K18,K19,K1A,    K1B,K1C,K1D,    K38,K39,K3A,K37, \
    K16,K1E,K0E,    K0F,K1F,K17,    K33,K3B,K2B,K3F  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_NO,    KC_NO,   }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_NO,    KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_NO,    KC_NO,    KC_NO,    KC_##K3F }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }  \
}

/* Alps 102-key */
#define KEYMAP_ALPS102( \
    K00, K0F, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D, K0E,   K44, K45, K46,   K43, K41, K42, K4A, \
    K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,      K1E,   K54, K55, K56,   K50, K51, K52, K5A, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D,      K2E,   K64, K65, K66,   K60, K61, K62, K6B, \
    K30, K32, K33, K34, K35, K36, K37, K38, K39, K3A, K3B, K3C, K3D,           K3E,   K74, K75, K76,   K70, K71, K72, K7B, \
    K31, K47, K3F,                 K40,               K4F, K48,                K2F,   K77, K67, K57,   K73, K63, K53, K4E  \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_NO,   }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_NO,    KC_##K4A, KC_NO,    KC_NO,    KC_NO,    KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_NO,    KC_NO,    KC_##K5A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K6B, KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_##K74, KC_##K75, KC_##K76, KC_##K77 }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_##K7B, KC_NO,    KC_NO,    KC_NO,    KC_NO,   }  \
}


#endif
