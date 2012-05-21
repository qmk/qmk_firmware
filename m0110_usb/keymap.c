/*
Copyright 2011,2012 Jun Wako <wakojun@gmail.com>

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
/* M0110A Support was contributed by skagon@github */

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

#define KEYMAP( \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33,  K47,K68,K6D,K62, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,      K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24,  K56,K57,K58,K66, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K4D,  K53,K54,K55,K4C, \
    K3A,K37,            K31,            K34,K2A,K46,K42,K48,  K52,    K41      \
) { \
    { KB_##K00, KB_##K01, KB_##K02, KB_##K03, KB_##K04, KB_##K05, KB_##K06, KB_##K07 }, \
    { KB_##K08, KB_##K09, KB_NO,    KB_##K0B, KB_##K0C, KB_##K0D, KB_##K0E, KB_##K0F }, \
    { KB_##K10, KB_##K11, KB_##K12, KB_##K13, KB_##K14, KB_##K15, KB_##K16, KB_##K17 }, \
    { KB_##K18, KB_##K19, KB_##K1A, KB_##K1B, KB_##K1C, KB_##K1D, KB_##K1E, KB_##K1F }, \
    { KB_##K20, KB_##K21, KB_##K22, KB_##K23, KB_##K24, KB_##K25, KB_##K26, KB_##K27 }, \
    { KB_##K28, KB_##K29, KB_##K2A, KB_##K2B, KB_##K2C, KB_##K2D, KB_##K2E, KB_##K2F }, \
    { KB_##K30, KB_##K31, KB_##K32, KB_##K33, KB_##K34, KB_NO,    KB_NO,    KB_##K37 }, \
    { KB_##K38, KB_##K39, KB_##K3A, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_NO    }, \
    { KB_NO,    KB_##K41, KB_##K42, KB_NO,    KB_NO,    KB_NO,    KB_##K46, KB_##K47 }, \
    { KB_##K48, KB_NO,    KB_NO,    KB_NO,    KB_##K4C, KB_##K4D, KB_##K4E, KB_NO    }, \
    { KB_NO,    KB_NO,    KB_##K52, KB_##K53, KB_##K54, KB_##K55, KB_##K56, KB_##K57 }, \
    { KB_##K58, KB_##K59, KB_NO,    KB_##K5B, KB_##K5C, KB_NO,    KB_NO,    KB_NO    }, \
    { KB_NO,    KB_NO,    KB_##K62, KB_NO,    KB_NO,    KB_NO,    KB_##K66, KB_NO    }, \
    { KB_##K68, KB_NO,    KB_NO,    KB_NO,    KB_NO,    KB_##K6D, KB_NO,    KB_NO    }, \
}


// Assign Fn key(0-7) to a layer to which switch with the Fn key pressed.
static const uint8_t PROGMEM fn_layer[] = {
    1,              // Fn0
    2,              // Fn1
    3,              // Fn2
    1,              // Fn3
    0,              // Fn4
    0,              // Fn5
    0,              // Fn6
    0               // Fn7
};

// Assign Fn key(0-7) to a keycode sent when release Fn key without use of the layer.
// See layer.c for details.
static const uint8_t PROGMEM fn_keycode[] = {
#ifndef HASU
    KB_ESC,         // Fn0
    KB_NO,          // Fn1
    KB_NO,          // Fn2
    KB_NO,          // Fn3
#else
    KB_NO,          // Fn0
    KB_SCOLON,      // Fn1
    KB_SLASH,       // Fn2
    KB_UP,          // Fn3
#endif
    KB_NO,          // Fn4
    KB_NO,          // Fn5
    KB_NO,          // Fn6
    KB_NO           // Fn7
};

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 
     * The keymap works with both M0110 and M0110A keyboards. As you can see, the M0110A is a superset
     * of the M0110 keyboard, with only one exception: 'Enter' in M0110 does not exist
     * on the M0110A, but since it generates a unique scan code which is not used for some other key in
     * the M0110A, they are totally interchangeable.  In fact, the M0110A is functionally (almost)
     * identical to the combination of the M0110 along with the M0120 keypad. The only difference
     * (which is causing some problems as you will read below) is that the M0110+M0120 don't have
     * dedicated arrow keys, while the M0110A does. However, the M0120 did have arrow keys, which
     * doubled as the [comma], [/], [*] and [+] keys, when used with the [Shift] key. The M0110A has
     * substituted the [comma] key with the [=] key, however its scancode is the same.
     *
     * Default:
     * ,---------------------------------------------------------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Gui|  =|  /|  *|
     * |---------------------------------------------------------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
     * |-----------------------------------------------------'   | |---------------|
     * |Fn0   |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return| |  4|  5|  6|  +|
     * |---------------------------------------------------------| |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
     * |---------------------------------------------------------| |-----------|Ent|
     * |Ctrl |Alt    |         Space         |Gui|  \|Lft|Rgt|Dn | |      0|  .|   |
     * `---------------------------------------------------------' `---------------'
     *
     * HHKB/WASD/Mouse Layer(Fn0):
     * ,---------------------------------------------------------. ,---------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|Mb1|Mb3|Mb2|
     * |---------------------------------------------------------| |---------------|
     * |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |Ins|   | |MwD|McU|MwU|MwU|
     * |-----------------------------------------------------'   | |---------------|
     * |Fn0   |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Return| |McL|McD|McR|MwD|
     * |---------------------------------------------------------| |---------------|
     * |Shift   |End|   |PgD|   |VoD|VoU|Mut|End|PgD|Dow|Shif|Up | |MwL|McD|MwR|   |
     * |---------------------------------------------------------| |-----------|Mb2|
     * |Ctrl |Alt    |         Space        |Gui |  \|Lft|Rgt|Dn | |    Mb1|Mb3|   |
     * `---------------------------------------------------------' `---------------'
     * Mb: Mouse Button / Mc: Mouse Cursor / Mw: Mouse Wheel
     *
     * NOTE: You can register Esc by hitting(press&release) Fn0 quickly.
     * NOTE: Gui between Space and \ is Enter on M0110 not exists on M0110A.
     * NOTE: LShift and RShift are logically same key. (M0110, M0110A)
     * NOTE: LOption and ROption are logically same key. (M0110)
     */
#ifndef HASU
    KEYMAP(
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,    LGUI,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,         P7,  P8,  P9,  PMNS,
    FN0, A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,     P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          UP,      P1,  P2,  P3,  PENT,
    LCTL,LALT,               SPC,                LGUI,BSLS,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
    // HHKB & WASD
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,BTN1,BTN3,BTN2,
    CAPS,HOME,UP,  PGUP,NO,  NO,  NO,  NO,  PSCR,SLCK,BRK, UP,  INS,          WH_D,MS_U,WH_U,WH_U,
    FN0, LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,     ENT,     MS_L,MS_D,MS_R,WH_D,
    LSFT,END, NO,  PGDN,NO,  VOLD,VOLU,MUTE,END, PGDN,DOWN,          UP,      WH_L,MS_D,WH_R,BTN2,
    LCTL,LALT,               SPC,                LGUI,BSLS,LEFT,RGHT,DOWN,    BTN1,     BTN3
    ),
#else
    // hasu's keymap
    // To enable use this 'make' option: make EXTRAFLAGS=-DHASU
    KEYMAP(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,    LGUI,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,         P7,  P8,  P9,  PMNS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN1, QUOT,     ENT,     P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN2,           FN3,     P1,  P2,  P3,  PENT,
    LCTL,LALT,               SPC,                LGUI,BSLS,LEFT,RGHT,DOWN,    LGUI,     PDOT
    ),
    // HHKB & WASD
    KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,HOME,UP,  PGUP,NO,  NO,  NO,  NO,  PSCR,SLCK,BRK, UP,  INS,          P7,  P8,  P9,  PMNS,
    LCTL,LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,     ENT,     P4,  P5,  P6,  PPLS,
    LSFT,END, NO,  PGDN,NO,  VOLD,VOLU,MUTE,END, PGDN,DOWN,          FN3,     P1,  P2,  P3,  PENT,
    LCTL,LALT,               SPC,                LGUI,BSLS,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
    // vi mousekeys
    KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,NO,  NO,  NO,           P7,  P8,  P9,  PMNS,
    NO,  VOLD,VOLU,MUTE,NO,  NO,  MS_L,MS_D,MS_U,MS_R,FN1, NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,NO,  NO,  NO,            UP,      P1,  P2,  P3,  PENT,
    LCTL,LALT,               BTN1,               LGUI,BSLS,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
    // vi cusorkeys
    KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,           P7,  P8,  P9,  PMNS,
    NO,  NO,  NO,  NO,  NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN2,           UP,      P1,  P2,  P3,  PENT,
    LCTL,LALT,               SPC,                LGUI,BSLS,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
#endif
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
