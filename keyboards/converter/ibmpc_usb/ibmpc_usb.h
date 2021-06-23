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
                   F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F10, F12.

PF1, PF2,     GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   -,     =, STB,BSP,    INS, HOM, PUP,   NLK, SLS, AST, MNS,
PF3, PF4,     TAB,  Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   [,   ],              DEL, END, PDN,   7,   8,   9,   PLS,
PF5, PF6,     CLK,   A,   S,   D,   F,   G,   H,   J,   K    L,   ;,   ',   \,     ENT,         UP,         4,   5,   6,   COM,
PF7, PF8,     LSF, <,   Z,   X,   C,   V,   B,   N,   M,   ,,   .,   /,   STB      RSF,    LFT, SHT, RGT,   1,   2,   3,   ENT,
PF9, PF10.    LCL,      LAT,                     SPC,           RAT,               RCL,         DN,         STB, 0,   DOT

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
/*
const uint8_t PROGMEM map_cs1[MATRIX_ROWS][MATRIX_COLS] = {
    { XXX, 0x1A, KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6     },  00-07 */
/*    { KC_7,     KC_8,     KC_9,     KC_0,     KC_MINUS, KC_EQUAL, KC_BSPACE,KC_TAB   },  08-0F */
/*    { KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I     },  10-17 */
/*    { KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_ENTER, KC_LCTL,  KC_A,     KC_S,    },  18-1F */
/*    { KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN  },  20-27 */
/*    { KC_QUOTE, KC_GRAVE, KC_LSHIFT,KC_BSLASH,KC_Z,     KC_X,     KC_C,     KC_V,    },  28-2F */
/*    { KC_B,     KC_N,     KC_M,     KC_COMMA, KC_DOT,   KC_SLASH, KC_RSHIFT,KC_PAST  },  30-37 */
/*    { KC_LALT,  KC_SPACE, KC_CAPS,  0x0D,    KC_F2,    KC_F3,    KC_F4,    KC_F5    },  38-3F */
/*    { KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_NLCK,  KC_SLCK,  KC_P7    },  40-47 */
/*    { KC_P8,    KC_P9,    KC_PMNS,  KC_P4,    KC_P5,    KC_P6,    KC_PPLS,  KC_P1    },  48-4F */
/*    { KC_P2,    KC_P3,    KC_P0,    KC_PDOT,  KC_PSCR,  KC_PAUSE, KC_NUHS,  KC_F11   },  50-57 */
/*    { KC_F12,   KC_PEQL,  KC_LGUI,  KC_RGUI,  KC_APP,   KC_MUTE,  KC_VOLD,  KC_VOLU  },  58-5F */
/*    { KC_UP,    KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_F13,   KC_F14,   KC_F15,   KC_F16   },  60-67 */
/*    { KC_F17,   KC_F18,   KC_F19,   KC_F20,   KC_F21,   KC_F22,   KC_F23,   KC_PENT  },  68-6F */
/*    { KC_KANA,  KC_INSERT,KC_DELETE,KC_RO,    KC_HOME,  KC_END,   KC_F24,   KC_PGUP  },  70-77 */
/*    { KC_PGDN,  KC_HENK,  KC_RCTL,  KC_MHEN,  KC_RALT,  KC_JYEN,  KC_PCMM,  KC_PSLS  },  78-7F */
/*};*/

/*
const uint8_t PROGMEM map_cs3[MATRIX_ROWS][MATRIX_COLS] = {
    { XXX,  0x73, 0x5C, 0x47, 0x30, 0x18, 0x19, 0x00 },  00-07
    { 0x0C, 0x74, 0x5D, 0x48, 0x31, 0x32, 0x1A, 0x01 },  08-0F
    { 0x0D, 0x75, 0x5E, 0x5F, 0x49, 0x33, 0x1B, 0x02 },  10-17
    { 0x0E, 0x76, 0x60, 0x4B, 0x4A, 0x34, 0x1C, 0x03 },  18-1F
    { 0x1F, 0x62, 0x61, 0x4C, 0x35, 0x1E, 0x1D, 0x04 },  20-27
    { 0x10, 0x77, 0x63, 0x4D, 0x37, 0x36, 0x1F, 0x05 },  28-2F
    { 0x11, 0x65, 0x64, 0x4F, 0x4E, 0x38, 0x20, 0x06 },  30-37
    { 0x12, 0x78, 0x66, 0x50, 0x39, 0x21, 0x22, 0x07 },  38-3F
    { 0x13, 0x67, 0x51, 0x3A, 0x3B, 0x24, 0x23, 0x08 },  40-47
    { 0x14, 0x68, 0x69, 0x52, 0x53, 0x3C, 0x25, 0x09 },  48-4F
    { 0x15, 0x6A, 0x54, 0x55, 0x3D, 0x26, 0x0A, 0x16 },  50-57
    { 0x79, 0x6B, 0x56, 0x3E, 0x3F, 0x27, 0x0B, 0x17 },  58-5F
    { 0x7A, 0x6C, 0x6D, 0x57, 0x40, 0x41, 0x28, 0x29 },  60-67
    { 0x7B, 0x6F, 0x6E, 0x58, 0x43, 0x42, 0x2A, 0x2B },  68-6F
    { 0x7C, 0x7D, 0x70, 0x59, 0x5A, 0x44, 0x2C, 0x2D },  70-77
    { 0x7E, 0x72, 0x71, 0x5B, 0x46, 0x45, 0x2E, 0x2F },  78-7F
};
*/
#endif
