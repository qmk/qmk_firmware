/*
Copyright 2012 Jun Wako <wakojun@gmail.com>

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

#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keycodes.h"
#include "util.h"
#include "keymap.h"




// Following macros help you to define a keymap with the form of actual keyboard layout.

/* X68000 Keyboard Scan codes
    ,---. ,---.    ,-------------------,    ,-------------------.  ,-----------. ,---------------.
    | 61| | 62|    | 63| 64| 65| 66| 67|    | 68| 69| 6A| 6B| 6C|  | 5A| 5B| 5C| | 5D| 52| 53| 54|
    `---' `---'    `-------------------'    `-------------------'  `-----------' `---------------'
    ,-----------------------------------------------------------.  ,-----------. ,---------------.
    | 01| 02| 03| 04| 05| 06| 07| 08| 09| 0A| 0B| 0C| 0D| 0E| 0F|  | 36| 5E| 37| | 3F| 40| 41| 42|
    |-----------------------------------------------------------|  |------------ |---------------|
    |  10 | 11| 12| 13| 14| 15| 16| 17| 18| 19| 1A| 1B| 1C|     |  | 38| 39| 3A| | 43| 44| 45| 46|
    |------------------------------------------------------. 1D |  `---=====---' |---------------|
    |  71  | 1E| 1F| 20| 21| 2l| 23| 24| 25| 26| 27| 28| 29|    |   ___| 3C|___  | 47| 48| 49| 4A|
    |-----------------------------------------------------------|  | 3B|---| 3D| |-----------|---|
    |  70    | 2A| 2B| 2C| 2D| 2E| 2F| 30| 31| 32| 33| 34|   70 |  `---| 3E|---' | 4B| 4C| 4D|   |
    `-----------------------------------------------------------|  .---=====---. |-----------| 4E|
           | 5F| 55 | 56 |     35     | 57 | 58 | 59 | 60|         |  72 |  73 | | 4F| 50| 51|   |
           `---------------------------------------------'         `-----------' `---------------'
*/
#define KEYMAP( \
    K61,K62,        K63,K64,K65,K66,K67,    K68,K69,K6A,K6B,K6C,  K5A,K5B,K5C,  K5D,K52,K53,K54, \
    K01,K02,K03,K04,K05,K06,K07,K08,K09,K0A,K0B,K0C,K0D,K0E,K0F,  K36,K5E,K37,  K3F,K40,K41,K42, \
    K10,K11,K12,K13,K14,K15,K16,K17,K18,K19,K1A,K1B,K1C,    K1D,  K38,K39,K3A,  K43,K44,K45,K46, \
    K71,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K28,K29,              K3C,      K47,K48,K49,K4A, \
    K70,K2A,K2B,K2C,K2D,K2E,K2F,K30,K31,K32,K33,K34,              K3B,K3E,K3D,  K4B,K4C,K4D,K4E, \
        K5F,K55,K56,    K35,        K57,K58,K59,K60,              K72,    K73,  K4F,K50,K51      \
) { \
    { KB_NO,    KB_##K01, KB_##K02, KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K08, KB_##K09, KB_##K0A, KB_##K0B, KB_##K0C, KB_##K0D, KB_##K0E, KB_##K0F }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_##K18, KB_##K19, KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_##K1F }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_##K27 }, \
    { KB_##K28, KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_##K2F }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_##K35, KB_##K36, KB_##K37 }, \
    { KB_##K38, KB_##K39, KB_##K3A, KB_##K3B, KB_##K3C, KB_##K3D, KB_##K3E, KB_##K3F }, \
    { KB_##K40, KB_##K41, KB_##K42, KB_##K43, KB_##K44, KB_##K45, KB_##K46, KB_##K47 }, \
    { KB_##K48, KB_##K49, KB_##K4A, KB_##K4B, KB_##K4C, KB_##K4D, KB_##K4E, KB_##K4F }, \
    { KB_##K50, KB_##K51, KB_##K52, KB_##K53, KB_##K54, KB_##K55, KB_##K56, KB_##K57 }, \
    { KB_##K58, KB_##K59, KB_##K5A, KB_##K5B, KB_##K5C, KB_##K5D, KB_##K5E, KB_##K5F }, \
    { KB_##K60, KB_##K61, KB_##K62, KB_##K63, KB_##K64, KB_##K65, KB_##K66, KB_##K67 }, \
    { KB_##K68, KB_##K69, KB_##K6A, KB_##K6B, KB_##K6C, KB_NO,    KB_NO,    KB_NO    }, \
    { KB_##K70, KB_##K71, KB_##K72, KB_##K73, KB_NO,    KB_NO,    KB_NO,    KB_NO,   }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }  \
}


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    0,              // Fn0
    0,              // Fn1
    0,              // Fn2
    0,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
    KB_NO,          // Fn0
    KB_NO,          // Fn1
    KB_NO,          // Fn2
    KB_NO,          // Fn3
    KB_NO,          // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};


static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* X68000 Keyboard Scan codes
    ,---. ,---.    ,-------------------,    ,-------------------.  ,-----------. ,---------------.
    | 61| | 62|    | 63| 64| 65| 66| 67|    | 68| 69| 6A| 6B| 6C|  | 5A| 5B| 5C| | 5D| 52| 53| 54|
    `---' `---'    `-------------------'    `-------------------'  `-----------' `---------------'
    ,-----------------------------------------------------------.  ,-----------. ,---------------.
    | 01| 02| 03| 04| 05| 06| 07| 08| 09| 0A| 0B| 0C| 0D| 0E| 0F|  | 36| 5E| 37| | 3F| 40| 41| 42|
    |-----------------------------------------------------------|  |------------ |---------------|
    |  10 | 11| 12| 13| 14| 15| 16| 17| 18| 19| 1A| 1B| 1C|     |  | 38| 39| 3A| | 43| 44| 45| 46|
    |------------------------------------------------------. 1D |  `---=====---' |---------------|
    |  71  | 1E| 1F| 20| 21| 2l| 23| 24| 25| 26| 27| 28| 29|    |   ___| 3C|___  | 47| 48| 49| 4A|
    |-----------------------------------------------------------|  | 3B|---| 3D| |-----------|---|
    |  70    | 2A| 2B| 2C| 2D| 2E| 2F| 30| 31| 32| 33| 34|   70 |  `---| 3E|---' | 4B| 4C| 4D|   |
    `-----------------------------------------------------------|  .---=====---. |-----------| 4E|
           | 5F| 55 | 56 |     35     | 57 | 58 | 59 | 60|         |  72 |  73 | | 4F| 50| 51|   |
           `---------------------------------------------'         `-----------' `---------------'
*/
    KEYMAP(
    NO,  NO,  F1,  F2,  F3,  F4,  F5,       F6,  F7,  F8,  F9,  F10,              PSCR,SLCK,PAUS,     CAPS,NO,  NO,  NO,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,BSPC,   INS, HOME,PGUP,     NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     ENT,    DEL, END, PGDN,     P7,  P8,  P9,  PPLS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,ENT,                   UP,            P4,  P5,  P6,  PEQL,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,GRV,                   LEFT,DOWN,RGHT,     P1,  P2,  P3,  PENT,
         LGUI,LALT,NO,       SPC,      RALT,RGUI,RCTL,APP,                        NO,       NO,       P0,  PCMM,PDOT
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return pgm_read_byte(&keymaps[(layer)][(row)][(col)]);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
