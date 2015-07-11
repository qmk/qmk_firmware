/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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



const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    /* International keyboard
     * M0110                                                       M0120
     * ,---------------------------------------------------------. ,---------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs| |Nlk|  -|  +|  *|
     * |---------------------------------------------------------| |---------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|Ret| |  7|  8|  9|  /|
     * |------------------------------------------------------,  | |---------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  '|  \|  | |  4|  5|  6|  ,|
     * |---------------------------------------------------------| |---------------|
     * |Shif|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /|        | |  1|  2|  3|   |
     * `---------------------------------------------------------' |-----------|Ent|
     *      |Opt|Mac |         Space               |Fn  |   |      |      0|  .|   |
     *      `-----------------------------------------------'      `---------------'
     */
    [0] = KEYMAP_INTL(
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,    NLCK,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,ENT,     P7,  P8,  P9,  PMNS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,BSLS,         P4,  P5,  P6,  PPLS,
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,              P1,  P2,  P3,  PENT,
         LALT,LGUI,               SPC,                     FN0,               P0,       PDOT
    ),
    /* Cursor Layer
     * ,---------------------------------------------------------. ,---------------.
     * |Esc| F1| F2| F3| F4| F5| F6| F7| F8| F9|F10|F11|F12|Delet| |Nlk|  -|  +|  *|
     * |---------------------------------------------------------| |---------------|
     * |Caps |Hom| Up|PgU|   |   |   |   |Psc|Slk|Pau|Up |   |Ret| |  7|  8|  9|  /|
     * |------------------------------------------------------,  | |---------------|
     * |Ctrl  |Lef|Dow|Rig|   |   |   |   |Hom|PgU|Lef|Rig|Ins|  | |  4|  5|  6|  ,|
     * |---------------------------------------------------------| |---------------|
     * |Shif|  <|End|   |PgD|   |   |   |   |End|PgD|Dow|        | |  1|  2|  3|   |
     * `---------------------------------------------------------' |-----------|Ent|
     *      |Opt|Mac |         Space               |Fn  |   |      |      0|  .|   |
     *      `-----------------------------------------------'      `---------------'
     */
    [1] = KEYMAP_INTL(
    ESC, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,HOME,UP,  PGUP,NO,  NO,  NO,  NO,  PSCR,SLCK,PAUS,UP,  NO,  ENT,     P7,  P8,  P9,  PMNS,
    LCTL,LEFT,DOWN,RGHT,NO,  NO,  NO,  NO,  HOME,PGUP,LEFT,RGHT,INS,          P4,  P5,  P6,  PPLS,
    LSFT,NO,  END, NO,  PGDN,NO,  NO,  NO,  NO,  END, PGDN,DOWN,              P1,  P2,  P3,  PENT,
         LALT,LGUI,               SPC,                     FN0,               P0,       PDOT
    ),
};


/*
 * Fn action definition
 */
const uint16_t fn_actions[] PROGMEM = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
};
