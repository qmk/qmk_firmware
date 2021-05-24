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

void matrix_init_user(void);

/*
   This is the mapping for a 102 key board using codeset 2.
   The code in matrix.c supports codeset 1 and codeset 3,
   but the mapping is not finished yet.
*/

#define LAYOUT_105( \
    K76,    K05,K06,K04,K0C,K03,K0B,K02,K0A,K01,K09,K78,K07, K7F,K7E,K00,                   \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, K39,K2F,K5E,  K77,K60,K7C,K7B, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,     K37,K27,K56,  K6C,K75,K7D,     \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,K5D,K5A,               K6B,K73,K74,K79, \
    K12,K61,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K59,     K4F,      K69,K72,K7A,     \
    K14,K19,K11,        K29,                K0F,K1F,K5C,K17, K53,K3F,K47,  K70,    K71,K62  \
) { \
    { K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07   }, \
    { KC_NO, K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { KC_NO, K11,   K12,   KC_NO, K14,   K15,   K16,   K17   }, \
    { KC_NO, K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { KC_NO, K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { KC_NO, K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F   }, \
    { KC_NO, K31,   K32,   K33,   K34,   K35,   K36,   K37   }, \
    { KC_NO, K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { KC_NO, K41,   K42,   K43,   K44,   K45,   K46,   K47   }, \
    { KC_NO, K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F   }, \
    { KC_NO, KC_NO, K52,   K53,   K54,   K55,   K56,   KC_NO }, \
    { K58,   K59,   K5A,   K5B,   K5C,   K5D,   K5E,   KC_NO }, \
    { K60,   K61,   K62,   KC_NO, KC_NO, KC_NO, K66,   KC_NO }, \
    { KC_NO, K69,   KC_NO, K6B,   K6C,   KC_NO, KC_NO, KC_NO }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { K78,   K79,   K7A,   K7B,   K7C,   K7D,   K7E,   K7F   }  \
}

#define LAYOUT_122( \
                  K08,K10,K18,K20,K28,K30,K38,K40,K48,K50,K57,K5F,                                         \
                  K07,K0F,K17,K1F,K27,K2F,K37,K3F,K47,K4F,K56,K5E,                                         \
                                                                                                           \
    K05,K06,  K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K5D,K66,  K67,K6E,K6F,  K76,K77,K7E,K7F, \
    K04,K0C,  K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,    K5C,  K64,K65,K6D,  K6C,K75,K7D,K7C, \
    K03,K0B,  K14,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K53,K5A,      K63,      K6B,K73,K74,K7B, \
    K02,K0A,  K12,K13,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,    K51,K59,  K61,K62,K6A,  K69,K72,K7A,K79, \
    K01,K09,  K11,    K19,            K29,                    K39,    K58,      K60,      K68,K70,K71,K78  \
) { \
    { KC_NO, K01,   K02,   K03,   K04,   K05,   K06,   K07   }, \
    { K08,   K09,   K0A,   K0B,   K0C,   K0D,   K0E,   K0F   }, \
    { K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17   }, \
    { K18,   K19,   K1A,   K1B,   K1C,   K1D,   K1E,   K1F   }, \
    { K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27   }, \
    { K28,   K29,   K2A,   K2B,   K2C,   K2D,   K2E,   K2F   }, \
    { K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37   }, \
    { K38,   K39,   K3A,   K3B,   K3C,   K3D,   K3E,   K3F   }, \
    { K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47   }, \
    { K48,   K49,   K4A,   K4B,   K4C,   K4D,   K4E,   K4F   }, \
    { K50,   K51,   K52,   K53,   K54,   K55,   K56,   K57   }, \
    { K58,   K59,   K5A,   K5B,   K5C,   K5D,   K5E,   K5F   }, \
    { K60,   K61,   K62,   K63,   K64,   K65,   K66,   K67   }, \
    { K68,   K69,   K6A,   K6B,   K6C,   K6D,   K6E,   K6F   }, \
    { K70,   K71,   K72,   K73,   K74,   K75,   K76,   K77   }, \
    { K78,   K79,   K7A,   K7B,   K7C,   K7D,   K7E,   K7F   }  \
}

typedef enum { NONE, PC_XT, PC_AT, PC_TERMINAL, PC_AT_Z150 } keyboard_kind_t;
#define KEYBOARD_KIND_STR(kind) \
    (kind == PC_XT ? "XT" :   \
     kind == PC_AT ? "AT" :   \
     kind == PC_TERMINAL ? "TERMINAL" :   \
     kind == PC_AT_Z150 ? "AT_Z150" :  \
     "NONE")

extern uint16_t keyboard_id;
extern keyboard_kind_t keyboard_kind;

#endif
