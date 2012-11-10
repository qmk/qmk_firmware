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
 * Keymap for Macway mod
 */
#include <stdint.h>
#include <stdbool.h>
#include <avr/pgmspace.h>
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


// Convert physical keyboard layout to matrix array.
// This is a macro to define keymap easily in keyboard layout form.
/* 
 * Tenkeyless keyboard:
 * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
 * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
 * `---'   `---------------' `---------------' `---------------' `-----------'
 * ,-----------------------------------------------------------. ,-----------.
 * |~  |  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp | |Ins|Hom|PgU|
 * |-----------------------------------------------------------| |-----------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
 * |-----------------------------------------------------------| `-----------'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
 * |-----------------------------------------------------------|     ,---.    
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|Shift     |     |Up |    
 * |-----------------------------------------------------------| ,-----------.
 * |Ctl|Gui|Alt|          Space                |Alt|Gui|App|Ctl| |Lef|Dow|Rig|
 * `-----------------------------------------------------------' `-----------'
 *
 * TODO: You should define follwing macro properly. It won't be compiled until done.
 *
 * Keymap array sapce has 18*8 slot, row is designated with A-Q and col with 0-7.
 * In this macro KA0 means key at row:A/col:0, KR7 means key at rowR/col7.
 * Empty slot of keymap should has KC_NO.For example row:B/col:0 has no key
 * so you must define KC_NO in this slot.(from hid_liber/ansi_iso_jis.c)
 * Esc key locates at row:A/col:1 so fist argument of macro should say KA1.
 * Right arrow key locates at row:Q/col:2 so last argument of macro should say KQ2.
 *
 * NOTE: Except above examples, the rest of macro definition is garbage just for place holder.
 */
#define KEYMAP( \
    KA1,K05,K06,K04,K0C,K03,K0B,K83,K0A,K01,K09,K78,K07,     KFC,K7E,KFE, \
    K0E,K16,K1E,K26,K25,K2E,K36,K3D,K3E,K46,K45,K4E,K55,K66, KF0,KEC,KFD, \
    K0D,K15,K1D,K24,K2D,K2C,K35,K3C,K43,K44,K4D,K54,K5B,K5D, KF1,KE9,KFA, \
    K58,K1C,K1B,K23,K2B,K34,K33,K3B,K42,K4B,K4C,K52,    K5A,              \
    K12,K1A,K22,K21,K2A,K32,K31,K3A,K41,K49,K4A,        K59,     KF5,     \
    K14,K9F,K11,        K29,                K91,KA7,KAF,K94, KEB,KF2,KQ2  \
) { \
    { KC_##KA0, KC_##KA1, KC_##KA2, KC_##KA3, KC_##KA4, KC_##KA5, KC_##KA6, KC_##KA7 }, \
    { KC_NO,    KC_##KB1, KC_##KB2, KC_##KB3, KC_##KB4, KC_##KB5, KC_##KB6, KC_##KB7 }, \
    { KC_##KC0, KC_##KC1, KC_##KC2, KC_##KC3, KC_##KC4, KC_##KC5, KC_##KC6, KC_##KC7 }, \
    { KC_##KD0, KC_##KD1, KC_##KD2, KC_##KD3, KC_##KD4, KC_##KD5, KC_##KD6, KC_##KD7 }, \
    { KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_##KE7 }, \
    { KC_##KF0, KC_##KF1, KC_##KF2, KC_##KF3, KC_##KF4, KC_##KF5, KC_##KF6, KC_##KF7 }, \
    { KC_##KG0, KC_##KG1, KC_##KG2, KC_##KG3, KC_##KG4, KC_##KG5, KC_##KG6, KC_##KG7 }, \
    { KC_##KH0, KC_##KH1, KC_##KH2, KC_##KH3, KC_##KH4, KC_##KH5, KC_##KH6, KC_##KH7 }, \
    { KC_##KI0, KC_##KI1, KC_##KI2, KC_##KI3, KC_##KI4, KC_##KI5, KC_##KI6, KC_##KI7 }, \
    { KC_##KJ0, KC_##KJ1, KC_##KJ2, KC_##KJ3, KC_##KJ4, KC_##KJ5, KC_##KJ6, KC_##KJ7 }, \
    { KC_##KK0, KC_##KK1, KC_##KK2, KC_##KK3, KC_##KK4, KC_##KK5, KC_##KK6, KC_##KK7 }, \
    { KC_##KL0, KC_##KL1, KC_##KL2, KC_##KL3, KC_##KL4, KC_##KL5, KC_##KL6, KC_##KL7 }, \
    { KC_##KM0, KC_##KM1, KC_##KM2, KC_##KM3, KC_##KM4, KC_##KM5, KC_##KM6, KC_##KM7 }, \
    { KC_##KN0, KC_##KN1, KC_##KN2, KC_##KN3, KC_##KN4, KC_##KN5, KC_##KN6, KC_##KN7 }, \
    { KC_##KO0, KC_##KO1, KC_##KO2, KC_##KO3, KC_##KO4, KC_##KO5, KC_##KO6, KC_##KO7 }, \
    { KC_##KP0, KC_##KP1, KC_##KP2, KC_##KP3, KC_##KP4, KC_##KP5, KC_##KP6, KC_##KP7 }, \
    { KC_##KQ0, KC_##KQ1, KC_##KQ2, KC_##KQ3, KC_##KQ4, KC_##KQ5, KC_##KQ6, KC_##KQ7 }, \
    { KC_##KR0, KC_##KR1, KC_##KR2, KC_##KR3, KC_##KR4, KC_##KR5, KC_##KR6, KC_##KR7 }  \
}

#define KEYCODE(layer, row, col) (pgm_read_byte(&keymaps[(layer)][(row)][(col)]))


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

/* See common/keycode.h for short name of key symbol. */
static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: Default Layer
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|
     * `---'   `---------------' `---------------' `---------------' `-----------'
     * ,-----------------------------------------------------------. ,-----------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU|
     * |-----------------------------------------------------------| |-----------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD|
     * |-----------------------------------------------------------| `-----------'
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |              
     * |-----------------------------------------------------------|     ,---.    
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |    
     * |-----------------------------------------------------------| ,-----------.
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl| |Lef|Dow|Rig|
     * `-----------------------------------------------------------' `-----------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,BRK,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                     
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,       
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT
    ),
};


uint8_t keymap_get_keycode(uint8_t layer, uint8_t row, uint8_t col)
{
    return KEYCODE(layer, row, col);
}

uint8_t keymap_fn_layer(uint8_t index)
{
    return pgm_read_byte(&fn_layer[index]);
}

uint8_t keymap_fn_keycode(uint8_t index)
{
    return pgm_read_byte(&fn_keycode[index]);
}
