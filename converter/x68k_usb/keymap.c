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
#include "keycode.h"
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
    { KC_NO,    KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F }, \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_##K64, KC_##K65, KC_##K66, KC_##K67 }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_##K70, KC_##K71, KC_##K72, KC_##K73, KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
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
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_NO,          // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
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
    /* ANSI */
    KEYMAP(
    F16, F17,     F1,  F2,  F3,  F4,  F5,   F6,  F7,  F8,  F9,  F10,              PSCR,SLCK,PAUS,     CAPS,F11, F12, F13,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,BSPC,   HOME,INS, DEL,      NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     ENT,    PGDN,PGUP,END,      P7,  P8,  P9,  PPLS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,F18,                   UP,            P4,  P5,  P6,  PEQL,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,GRV,                   LEFT,DOWN,RGHT,     P1,  P2,  P3,  PENT,
         F19, LGUI,LALT,     SPC,      RALT,RGUI,RCTL,APP,                        F14,      F15,      P0,  PCMM,PDOT
    ),
    /* JIS */
    KEYMAP(
    F16, F17,     F1,  F2,  F3,  F4,  F5,   F6,  F7,  F8,  F9,  F10,              PSCR,SLCK,PAUS,     CAPS,F11, F12, F13,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,   HOME,INS, DEL,      NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     ENT,    PGDN,PGUP,END,      P7,  P8,  P9,  PPLS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,NUHS,                  UP,            P4,  P5,  P6,  PEQL,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,                    LEFT,DOWN,RGHT,     P1,  P2,  P3,  PENT,
         LGUI,LALT,MHEN,     SPC,      HENK,KANA,APP, ZKHK,                       F14,      F15,      P0,  PCMM,PDOT
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return pgm_read_byte(&keymaps[(layer)][(row)][(col)]);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
