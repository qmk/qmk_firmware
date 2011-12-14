/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/* 
 * Keymap for ADB keyboard
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "usb_keyboard.h"
#include "usb_keycodes.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))

// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
// TODO: layout for M0110A
/* M0110 */
#define KEYMAP( \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,K2A, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,             \
        K3A,K37,        K31,                K34              \
) { \
    { KB_##K00, KB_##K01, KB_##K02, KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K08, KB_##K09, KB_NO,    KB_##K0B, KB_##K0C, KB_##K0D, KB_##K0E, KB_##K0F }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_##K18, KB_##K19, KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_##K1F }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_##K27 }, \
    { KB_##K28, KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_##K2F }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_NO,    KB_NO,    KB_##K37 }, \
    { KB_##K38, KB_##K39, KB_##K3A, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }  \
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
    /* Default Layer: plain keymap
     * ,---------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Bacpa|
     * |---------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|
     * |---------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return|
     * |---------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift   |
     * `---------------------------------------------------------'
     *      |Opt|Alt |         Space               |Alt |Opt|
     *      `-----------------------------------------------'
     */
    KEYMAP(
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,
         LGUI,LALT,          SPC,                     RALT
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_layer[biton(fn_bits)]);
}

uint8_t keymap_fn_keycode(uint8_t fn_bits)
{
    return pgm_read_byte(&fn_keycode[(biton(fn_bits))]);
}
