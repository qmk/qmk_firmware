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

/* SONY NEWS NWP-5461 */
#define KEYMAP( \
    K7A,    K01,K02,K03,K04,K05,  K06,K07,K08,K09,K0A,  K68,K69,          K64,K65,K52, \
    K0B,K0C,K0D,K0E,K0F,K10,K11,K12,K13,K14,K15,K16,K17,K18,K19, K6A, K4B,K4C,K4D,K4E, \
    K1A,K1B,K1C,K1D,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,     K6B, K4F,K50,K51,K56, \
    K28,K29,K2A,K2B,K2C,K2D,K2E,K2F,K30,K31,K32,K33,K34,    K35, K6C, K53,K54,K55,K5A, \
    K36,K37,K38,K39,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,        K42, K6D, K57,K59,K58,     \
    K43,K44,K45,        K46,        K47,            K48,K49,K4A, K6E, K66,K5B,K5C,K5D  \
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
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K64, KC_##K65, KC_##K66, KC_NO    }, \
    { KC_##K68, KC_##K69, KC_##K6A, KC_##K6B, KC_##K6C, KC_##K6D, KC_##K6E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,   }, \
    { KC_NO,    KC_NO,    KC_##K7A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }  \
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
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,GRV,      ENT,    CLR,    P1,  P2,  P3,  PENT,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,RO,            RSFT,   PGUP,   P0,  PDOT,UP,
    LALT,CAPS,LALT,          SPC,      ERAS,                    RALT,RGUI,RCTL,   PGDN,   TAB, LEFT,DOWN,RGHT
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
