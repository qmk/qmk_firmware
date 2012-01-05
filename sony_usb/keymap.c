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

/* SONY NEWS NWP-5461 */
#define KEYMAP( \
    K7A,    K01,K02,K03,K04,K05,  K06,K07,K08,K09,K0A,  K68,K69,          K64,K65,K52, \
    K0B,K0C,K0D,K0E,K0F,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19, K6A, K4B,K4C,K4D,K4E, \
    K1A,K1B,K1C,K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,     K6B, K4F,K50,K51,K56, \
    K28,K29,K2A,K2B,K2C,K2D,K2E,K2F,K30,K31,K32,K33,K34,    K35, K6C, K53,K54,K55,K5A, \
    K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,        K42, K6D, K57,K59,K58,     \
    K43,K44,K45,        K46,        K47,            K48,K49,K4A, K6E, K66,K5B,K5C,K5D  \
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
    { KB_##K58, KB_##K59, KB_##K5A, KB_##K5B, KB_##K5C, KB_##K5D, KB_NO,    KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K64, KB_##K65, KB_##K66, KB_NO    }, \
    { KB_##K68, KB_##K69, KB_##K6A, KB_##K6B, KB_##K6C, KB_##K6D, KB_##K6E, KB_NO    }, \
    { KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO,   }, \
    { KB_NO,    KB_NO,    KB_##K7A, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }  \
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
    /* 0: default
     * ,---.   ,------------------------, ,------------------------. ,---------.
     * |Pow|   | F1 | F2 | F3 | F4 | F5 | | F6 | F7 | F8 | F9 | F10| | F11| F12| ,-----------.
     * `---'   `------------------------' `------------------------' `---------' |  *|  /|  +|
     * ,-------------------------------------------------------------. ,---. ,---------------|
     * |Esc|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|  BS | |Hlp| |  7|  8|  9|  -|
     * |-------------------------------------------------------------| |---| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Del|   | |Ins| |  4|  5|  6|  ,|
     * |---------------------------------------------------------'   | |---| |---------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  `|Return| |Clr| |  1|  2|  3|   |
     * |-------------------------------------------------------------| |---| |-----------|Ent|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|   |Shift   | |PgU| |  0|  .| Up|   |
     * |-------------------------------------------------------------| |---| |---------------|
     * |Alt  |Gui |Alt |         Space     |          |Gui|App|Ctrl  | |PgD| |Tab|Lef|Dow|Rig|
     * `-------------------------------------------------------------' `---' `---------------'
     */
    KEYMAP(
    PWR,      F1,  F2,  F3,  F4,  F5,       F6,  F7,  F8,  F9,  F10,      F11, F12,            PAST,PSLS,PPLS,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSLS,BSPC,   HELP,   P7,  P8,  P9,  PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,DEL,         INS,    P4,  P5,  P6,  PCMM,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV,      ENT,    CLR,    P1,  P2,  P3,  PENT,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,            RSFT,   PGUP,   P0,  PDOT,UP,
    LCTL,LGUI,LALT,          SPC,      ERAS,                    RALT,RGUI,RCTL,   PGDN,   TAB, LEFT,DOWN,RGHT
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
