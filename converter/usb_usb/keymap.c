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

#include <avr/pgmspace.h>
#include "keycode.h"
#include "util.h"
#include "keymap.h"


#define KEYMAP( \
    K29,K3A,K3B,K3C,K3D,K3E,K3F,K40,K41,K42,K43,K44,K45,     K46,K47,K48,                   \
    K35,K1E,K1F,K20,K21,K22,K23,K24,K25,K26,K27,K2D,K2E,K2A, K49,K4A,K4B,  K53,K54,K55,K56, \
    K2B,K14,K1A,K08,K15,K17,K1C,K18,K0C,K12,K13,K2F,K30,K31, K4C,K4D,K4E,  K5F,K60,K61,     \
    K39,K04,K16,K07,K09,K0A,K0B,K0D,K0E,K0F,K33,K34,    K28,               K5C,K5D,K5E,K57, \
    KE1,K1D,K1B,K06,K19,K05,K11,K10,K36,K37,K38,        KE5,     K52,      K59,K5A,K5B,     \
    KE0,KE3,KE2,        K2C,                KE6,KE7,K65,KE4, K50,K51,K4F,  K62,    K63,K58  \
) { \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, /* 00-07 */ \
    { KC_##K08, KC_##K09, KC_##K0A, KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, /* 08-0F */ \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, /* 10-17 */ \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, /* 18-1F */ \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, /* 20-27 */ \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, /* 28-2F */ \
    { KC_##K30, KC_##K31, KC_NO,    KC_##K33, KC_##K34, KC_##K35, KC_##K36, KC_##K37 }, /* 30-37 */ \
    { KC_##K38, KC_##K39, KC_##K3A, KC_##K3B, KC_##K3C, KC_##K3D, KC_##K3E, KC_##K3F }, /* 38-3F */ \
    { KC_##K40, KC_##K41, KC_##K42, KC_##K43, KC_##K44, KC_##K45, KC_##K46, KC_##K47 }, /* 40-47 */ \
    { KC_##K48, KC_##K49, KC_##K4A, KC_##K4B, KC_##K4C, KC_##K4D, KC_##K4E, KC_##K4F }, /* 48-4F */ \
    { KC_##K50, KC_##K51, KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, /* 50-57 */ \
    { KC_##K58, KC_##K59, KC_##K5A, KC_##K5B, KC_##K5C, KC_##K5D, KC_##K5E, KC_##K5F }, /* 58-5F */ \
    { KC_##K60, KC_##K61, KC_##K62, KC_##K63, KC_NO,    KC_##K65, KC_NO,    KC_NO    }, /* 60-67 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 68-6F */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 70-77 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 78-7F */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 80-87 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 88-8F */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 90-97 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* 98-9F */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* A0-A7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* A8-AF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* B0-B7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* B8-BF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* C0-C7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* C8-CF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* D0-D7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* D8-DF */ \
    { KC_##KE0, KC_##KE1, KC_##KE2, KC_##KE3, KC_##KE4, KC_##KE5, KC_##KE6, KC_##KE7 }, /* E0-E7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* E8-EF */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* F0-F7 */ \
    { KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, /* F8-FF */ \
}


// Layers to switch by holding Fn key(0-7)
static const uint8_t PROGMEM fn_layer[] =   { 5,       6,       5,       0,       0,       0,       0,       0     };

// Codes to register by clicking Fn key(0-7)
static const uint8_t PROGMEM fn_keycode[] = { KC_SCLN, KC_SLSH, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO };

static const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* 0: default
     * ,---.   ,---------------. ,---------------. ,---------------. ,-----------.     ,-----------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau|     |Pwr|Slp|Wak|
     * `---'   `---------------' `---------------' `---------------' `-----------'     `-----------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa| |Ins|Hom|PgU| |NmL|  /|  *|  -|
     * |-----------------------------------------------------------| |-----------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \| |Del|End|PgD| |  7|  8|  9|   |
     * |-----------------------------------------------------------| `-----------' |-----------|  +|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |               |  4|  5|  6|   |
     * |-----------------------------------------------------------|     ,---.     |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |     |Up |     |  1|  2|  3|   |
     * |-----------------------------------------------------------| ,-----------. |-----------|Ent|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl| |Lef|Dow|Rig| |      0|  .|   |
     * `-----------------------------------------------------------' `-----------' `---------------'
     * ; = Fn0(to Layer 5)
     * / = Fn1(to Layer 6)
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    FN2, A,   S,   D,   F,   G,   H,   J,   K,   L,   FN0, QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,FN2, FN2, GRV,      LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 1: plain Qwerty without layer switching
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 2: Colemak http://colemak.com
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  W|  F|  P|  G|  J|  L|  U|  Y|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |BackSp|  A|  R|  S|  T|  D|  H|  N|  E|  I|  O|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  K|  M|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 3: Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  [|  ]|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  '|  ,|  .|  P|  Y|  F|  G|  C|  R|  L|  /|  =|    \|
     * |-----------------------------------------------------------|
     * |BackSp|  A|  O|  E|  U|  I|  D|  H|  T|  N|  S|  -|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  ;|  Q|  J|  K|  X|  B|  M|  Wl  V|  Z|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL, BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    CAPS,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,             RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 4: Workman http://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
     * ,-----------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |  Q|  D|  R|  W|  B|  J|  F|  U|  P|  ;|  [|  ]|    \|
     * |-----------------------------------------------------------|
     * |CapsLo|  A|  S|  H|  T|  G|  Y|  N|  E|  O|  I|  '|Return  |
     * |-----------------------------------------------------------|
     * |Shift   |  Z|  X|  M|  C|  V|  K|  L|  ,|  ,|  /|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    TAB, Q,   D,   R,   W,   B,   J,   F,   U,   P,   SCLN,LBRC,RBRC,BSLS,     DEL, END, PGDN,    P7,  P8,  P9,
    BSPC,A,   S,   H,   T,   G,   Y,   N,   E,   O,   I,   QUOT,     ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   M,   C,   V,   K,   L,   COMM,DOT, SLSH,          RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 5: Mouse keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |MwL|MwU|McU|WwU|WwR|MwL|MwD|MwU|MwR|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |McL|McD|McR|   |McL|McD|McU|McR|Fn0|   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |VoD|VoU|Mut|Mb2|Mb3|Mb2|Mb1|VoD|VoU|Mut|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Mb1           |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     * Mc = mouse cursor, Mw = mouse wheel, Mb = mouse button
     * Vo = Volume, Mut = Mute
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, DEL,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    CAPS,NO,  NO,  NO,  NO,  NO,  WH_L,WH_D,WH_U,WH_R,PSCR,SLCK,PAUS,INS,      DEL, END, PGDN,    P7,  P8,  P9,
    FN2, VOLD,VOLU,MUTE,NO,  NO,  MS_L,MS_D,MS_U,MS_R,FN0, NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  BTN3,BTN2,BTN1,NO,  NO,  NO,            RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          BTN1,                    RALT,FN2, FN2, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
    ),

    /* 6: Cursor keys
     * ,-----------------------------------------------------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Backspa|
     * |-----------------------------------------------------------|
     * |Tab  |Hom|PgU| Up|PgU|End|Hom|PgD|PgU|End|   |   |   |    \|
     * |-----------------------------------------------------------|
     * |CapsLo|   |Lef|Dow|Rig|   |Lef|Dow| Up|Rig|   |   |Return  |
     * |-----------------------------------------------------------|
     * |Shift   |   |   |   |   |   |Hom|PgD|PgU|End|Fn1|Shift     |
     * |-----------------------------------------------------------|
     * |Ctrl |Gui |Alt |         Space         |Alt |Gui |Menu|Ctrl|
     * `-----------------------------------------------------------'
     */
    KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F8,  F10, F11, F12, DEL,      INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,
    CAPS,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,  NO,  NO,  INS,      DEL, END, PGDN,    P7,  P8,  P9,
    LCTL,NO,  NO,  NO,  NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       ENT,                         P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, FN1,           RSFT,          UP,           P1,  P2,  P3,
    LCTL,LGUI,LALT,          SPC,                     RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT
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
