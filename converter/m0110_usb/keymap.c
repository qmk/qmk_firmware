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
#include "keycode.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "keymap.h"


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
 * Physical layout:
 * M0110A
 * ,---------------------------------------------------------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Bcksp| |Clr|  =|  /|  *|
 * |---------------------------------------------------------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
 * |-----------------------------------------------------'   | |---------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter | |  4|  5|  6|  +|
 * |---------------------------------------------------------| |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
 * |---------------------------------------------------------' |-----------|Ent|
 * |Opt  |Mac    |           Space           |  \|Lft|Rgt|Dn | |      0|  .|   |
 * `---------------------------------------------------------' `---------------'
 *
 * M0110                                                       M0120
 * ,---------------------------------------------------------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Clr|  -|  +|  *|
 * |---------------------------------------------------------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \| |  7|  8|  9|  /|
 * |---------------------------------------------------------| |---------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter | |  4|  5|  6|  ,|
 * |---------------------------------------------------------| |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shift   | |  1|  2|  3|   |
 * `---------------------------------------------------------' |-----------|Ent|
 *      |Opt|Mac |         Space               |Ent |Opt|      |      0|  .|   |
 *      `-----------------------------------------------'      `---------------'
 * With Shift keys on M0120 work as curosor.(-:Left *:Right /:Up ,:Down)
 *
 * NOTE: \ is located differently.
 * NOTE: Enter on M0110 is different from Enter on keypad(M0120 and M0110A).
 * NOTE: Left Shift and right Shift are logically same key.
 * NOTE: Left Option and right Option are logically same key.
 */

/* Keymap definition Macro
 * ,---------------------------------------------------------. ,---------------.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Clr|  =|  /|  *|
 * |---------------------------------------------------------| |---------------|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
 * |-----------------------------------------------------'   | |---------------|
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter | |  4|  5|  6|  +|
 * |---------------------------------------------------------| |---------------|
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
 * |---------------------------------------------------------| |-----------|Ent|
 * |Opt  |Mac    |         Space         |Ent|  \|Lft|Rgt|Dn | |      0|  .|   |
 * `---------------------------------------------------------' `---------------'
 * NOTE: Ent between Space and \ means Enter on M0110.
 */
#define KEYMAP( \
    K32,K12,K13,K14,K15,K17,K16,K1A,K1C,K19,K1D,K1B,K18,K33,  K47,K68,K6D,K62, \
    K30,K0C,K0D,K0E,K0F,K11,K10,K20,K22,K1F,K23,K21,K1E,      K59,K5B,K5C,K4E, \
    K39,K00,K01,K02,K03,K05,K04,K26,K28,K25,K29,K27,    K24,  K56,K57,K58,K66, \
    K38,K06,K07,K08,K09,K0B,K2D,K2E,K2B,K2F,K2C,        K4D,  K53,K54,K55,K4C, \
    K3A,K37,            K31,            K34,K2A,K46,K42,K48,  K52,    K41      \
) { \
    { KC_##K00, KC_##K01, KC_##K02, KC_##K03, KC_##K04, KC_##K05, KC_##K06, KC_##K07 }, \
    { KC_##K08, KC_##K09, KC_NO,    KC_##K0B, KC_##K0C, KC_##K0D, KC_##K0E, KC_##K0F }, \
    { KC_##K10, KC_##K11, KC_##K12, KC_##K13, KC_##K14, KC_##K15, KC_##K16, KC_##K17 }, \
    { KC_##K18, KC_##K19, KC_##K1A, KC_##K1B, KC_##K1C, KC_##K1D, KC_##K1E, KC_##K1F }, \
    { KC_##K20, KC_##K21, KC_##K22, KC_##K23, KC_##K24, KC_##K25, KC_##K26, KC_##K27 }, \
    { KC_##K28, KC_##K29, KC_##K2A, KC_##K2B, KC_##K2C, KC_##K2D, KC_##K2E, KC_##K2F }, \
    { KC_##K30, KC_##K31, KC_##K32, KC_##K33, KC_##K34, KC_NO,    KC_NO,    KC_##K37 }, \
    { KC_##K38, KC_##K39, KC_##K3A, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_##K41, KC_##K42, KC_NO,    KC_NO,    KC_NO,    KC_##K46, KC_##K47 }, \
    { KC_##K48, KC_NO,    KC_NO,    KC_NO,    KC_##K4C, KC_##K4D, KC_##K4E, KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K52, KC_##K53, KC_##K54, KC_##K55, KC_##K56, KC_##K57 }, \
    { KC_##K58, KC_##K59, KC_NO,    KC_##K5B, KC_##K5C, KC_NO,    KC_NO,    KC_NO    }, \
    { KC_NO,    KC_NO,    KC_##K62, KC_NO,    KC_NO,    KC_NO,    KC_##K66, KC_NO    }, \
    { KC_##K68, KC_NO,    KC_NO,    KC_NO,    KC_NO,    KC_##K6D, KC_NO,    KC_NO    }, \
}

#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
static const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
#endif
    /* Default:
     * ,---------------------------------------------------------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Clr|  =|  /|  *|
     * |---------------------------------------------------------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|   | |  7|  8|  9|  -|
     * |-----------------------------------------------------'   | |---------------|
     * |Caps  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|Enter | |  4|  5|  6|  +|
     * |---------------------------------------------------------| |---------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|Shft|Up | |  1|  2|  3|   |
     * |---------------------------------------------------------| |-----------|Ent|
     * |Ctl  |Gui    |         Space         |Alt|  \|Lft|Rgt|Dn | |      0|  .|   |
     * `---------------------------------------------------------' `---------------'
     */
    [0] = KEYMAP(
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,    CLR, EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,         P7,  P8,  P9,  PMNS,
    LCAP,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     FN15,    P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,          UP,      P1,  P2,  P3,  PENT,
    LCTL,LGUI,               FN16,               LALT,FN31,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
    /* Cursor Layer(WASD, IJKL)
     * ,---------------------------------------------------------. ,---------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  =|  /|  *|
     * |---------------------------------------------------------| |---------------|
     * |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |Ins|   | |  7|  8|  9|  -|
     * |-----------------------------------------------------'   | |---------------|
     * |Caps  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Enter | |  4|  5|  6|  +|
     * |---------------------------------------------------------| |---------------|
     * |Shift   |End|   |PgD|   |   |   |   |End|PgD|Dow|Shif|PgU| |  1|  2|  3|   |
     * |---------------------------------------------------------| |-----------|Ent|
     * |Ctl  |Gui    |         Space        |Alt |  \|Hom|End|PgD| |      0|  .|   |
     * `---------------------------------------------------------' `---------------'
     */
    [3] = KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,HOME,UP,  PGUP,NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  INS,          P7,  P8,  P9,  PMNS,
    LCAP,LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,     FN15,    P4,  P5,  P6,  PPLS,
    LSFT,END, NO,  PGDN,NO,  NO,  NO,  NO,  END, PGDN,DOWN,          PGUP,    P1,  P2,  P3,  PENT,
    LCTL,LGUI,               FN16,               LALT,FN31,HOME,END, PGDN,    P0,       PDOT
    ),
    [4] = KEYMAP(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,HOME,UP,  PGUP,NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  INS,          P7,  P8,  P9,  PMNS,
    LCAP,LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,     FN15,    P4,  P5,  P6,  PPLS,
    LSFT,END, NO,  PGDN,NO,  NO,  NO,  NO,  END, PGDN,DOWN,          PGUP,    P1,  P2,  P3,  PENT,
    LCTL,LGUI,               FN16,               LALT,FN31,HOME,END, PGDN,    P0,       PDOT
    ),
    [7] = {},
};


/*
 * Fn action definition
 */
#ifdef KEYMAP_SECTION_ENABLE
const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
#else
static const uint16_t fn_actions[] PROGMEM = {
#endif
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_MOMENTARY(2),
    [2]  = ACTION_LAYER_MOMENTARY(3),
    [3]  = ACTION_LAYER_MOMENTARY(4),
    [4]  = ACTION_LAYER_MOMENTARY(5),
    [5]  = ACTION_LAYER_MOMENTARY(6),
    [6]  = ACTION_LAYER_MOMENTARY(7),
    [7]  = ACTION_LAYER_TOGGLE(1),
    [8]  = ACTION_LAYER_TOGGLE(2),
    [9]  = ACTION_LAYER_TOGGLE(3),
    [10] = ACTION_LAYER_TAP_TOGGLE(1),
    [11] = ACTION_LAYER_TAP_TOGGLE(2),
    [12] = ACTION_LAYER_TAP_TOGGLE(3),
    [13] = ACTION_LAYER_TAP_KEY(1, KC_F),
    [14] = ACTION_LAYER_TAP_KEY(2, KC_J),
    [15] = ACTION_LAYER_TAP_KEY(3, KC_ENTER),
    [16] = ACTION_LAYER_TAP_KEY(4, KC_SPACE),
    [17] = ACTION_LAYER_TAP_KEY(5, KC_SCOLON),
    [18] = ACTION_LAYER_TAP_KEY(6, KC_QUOTE),
    [19] = ACTION_LAYER_TAP_KEY(7, KC_SLASH),
    [20] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_SPACE),
    [21] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_SPACE),
    [22] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_QUOTE),
    [23] = ACTION_MODS_TAP_KEY(MOD_RCTL, KC_ENTER),
    [24] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_ESC),
    [25] = ACTION_MODS_TAP_KEY(MOD_LCTL, KC_BSPACE),
    [26] = ACTION_MODS_ONESHOT(MOD_LCTL),
    [27] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_ESC),
    [28] = ACTION_MODS_TAP_KEY(MOD_LSFT, KC_BSPACE),
    [29] = ACTION_MODS_ONESHOT(MOD_LSFT),
    [30] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_GRAVE),
    [31] = ACTION_MODS_TAP_KEY(MOD_RALT, KC_BSLASH),
};



/* translates key to keycode */
uint8_t keymap_key_to_keycode(uint8_t layer, key_t key)
{
    return pgm_read_byte(&keymaps[(layer)][(key.row)][(key.col)]);
}

/* translates Fn index to action */
action_t keymap_fn_to_action(uint8_t keycode)
{
    action_t action;
    action.code = pgm_read_word(&fn_actions[FN_INDEX(keycode)]);
    return action;
}
