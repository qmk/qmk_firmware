/*
Copyright 2014 Jun Wako <wakojun@gmail.com>

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
#include "keycode.h"
#include "keymap_common.h"


#ifdef KEYMAP_SECTION_ENABLE
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
#else
const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
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
const uint16_t fn_actions[] PROGMEM = {
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
