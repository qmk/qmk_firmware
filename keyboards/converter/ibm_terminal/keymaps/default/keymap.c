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
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "ibm_terminal.h"


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
const uint8_t PROGMEM fn_layer[] = {
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
const uint8_t PROGMEM fn_keycode[] = {
    KC_NO,          // Fn0
    KC_NO,          // Fn1
    KC_NO,          // Fn2
    KC_NO,          // Fn3
    KC_NO,          // Fn4
    KC_NO,          // Fn5
    KC_NO,          // Fn6
    KC_NO           // Fn7
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|  \|BS | |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  #|Retu|               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shif|  \|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `----'    `---------------------------------------'    `----' `-----------' `---------------'
     */
/*
    KEYMAP(
                     F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    PSCR,ESC,   GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    SLCK,INT4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,  DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    PAUS,INT5,  CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,        UP,         P4,  P5,  P6,  PCMM,
    APP, INT6,  LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,  LEFT,INT2,RGHT,  P1,  P2,  P3,  PENT,
    RGUI,LGUI,  LCTL,     LALT,               SPC,                          RALT,     RCTL,       DOWN,       NO,  P0,  PDOT,NO
    ),
*/
    // pseudo ANSI
    KEYMAP(
                     F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
                     F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,

    PSCR,ESC,   ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, NO,  BSPC,  INS, HOME,PGUP,  NLCK,PSLS,PAST,PMNS,
    SLCK,INT4,  TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     NO,    DEL, END, PGDN,  P7,  P8,  P9,  PPLS,
    PAUS,INT5,  LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     BSLS,ENT,        UP,         P4,  P5,  P6,  PCMM,
    APP, INT6,  LSFT,LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     NO,  RSFT,  LEFT,INT2,RGHT,  P1,  P2,  P3,  PENT,
    RGUI,LGUI,  LCTL,     LALT,               SPC,                          LGUI,     GRV,        DOWN,       NO,  P0,  PDOT,NO
    ),

/* 101-key keymaps
 */
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl|    |Alt |          Space              |Alt |    |Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `----'    `---------------------------------------'    `----' `-----------' `---------------'
     */
/*
    KEYMAP_101(
     ESC,       F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9, F10, F11, F12,     PSCR,SLCK, BRK,

     GRV,   1,   2,   3,   4,   5,   6,   7,   8,   9,   0,MINS, EQL,BSPC,      INS,HOME,PGUP,     NLCK,PSLS,PAST,PMNS,
     TAB,   Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,LBRC,RBRC,BSLS,      DEL, END,PGDN,       P7,  P8,  P9,
    CAPS,   A,   S,   D,   F,   G,   H,   J,   K,   L,SCLN,QUOT,      ENT,                           P4,  P5,  P6,PPLS,
    LSFT,        Z,   X,   C,   V,   B,   N,   M,COMM, DOT,SLSH,     RSFT,            UP,            P1,  P2,  P3,
    LCTL,     LALT,                SPC,                    RALT,     RCTL,     LEFT,DOWN,RGHT,       P0,     PDOT,PENT
    ),
*/
};
