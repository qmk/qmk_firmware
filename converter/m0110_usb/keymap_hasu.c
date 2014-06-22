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


const uint8_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default:
     * M0110
     * ,---------------------------------------------------------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backs|
     * |---------------------------------------------------------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \|
     * |---------------------------------------------------------|
     * |Ctrl  |  A|  S|  D|  F|  G|  H|  J|  K|  L| Fn|  '|Return|
     * |---------------------------------------------------------|
     * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  ,| Fn|Shift   |
     * `---------------------------------------------------------'
     *      |Fn |alt |           Fn                |Gui |Fn |
     *      `-----------------------------------------------'
     */
    [0] = KEYMAP(
    ESC, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, BSPC,    NLCK,EQL, PSLS,PAST,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,         P7,  P8,  P9,  PMNS,
    LCTL,A,   S,   D,   F,   G,   H,   J,   K,   L,   FN3, QUOT,     ENT,     P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, FN1,           UP,      P1,  P2,  P3,  PENT,
    FN0, LALT,               FN2,                LGUI,BSLS,LEFT,RGHT,DOWN,    P0,       PDOT
    ),
    // IJKL cursor
    [1] = KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,UP,  PGUP,END, NO,  NO,           P7,  P8,  P9,  PMNS,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  HOME,LEFT,DOWN,RGHT,END, NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, NO,            PGUP,    P1,  P2,  P3,  PENT,
    TRNS,LALT,               SPC,                LGUI,BSLS,HOME,END, PGDN,    P0,       PDOT
    ),
    // HJKL cursor
    [2] = KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,UP,  PGUP,END, NO,  NO,           P7,  P8,  P9,  PMNS,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  LEFT,DOWN,UP,  RGHT,NO,  NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,NO,  NO,  NO,  NO,  NO,  HOME,PGDN,PGUP,END, TRNS,          PGUP,    P1,  P2,  P3,  PENT,
    TRNS,LALT,               SPC,                LGUI,BSLS,HOME,END, PGDN,    P0,       PDOT
    ),
    // Mousekey
    [3] = KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,Q,   W,   E,   R,   T,   WH_L,WH_D,MS_U,WH_U,WH_R,WBAK,WFWD,         P7,  P8,  P9,  PMNS,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  BTN2,MS_L,MS_D,MS_R,BTN1,NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   BTN2,BTN1,BTN4,BTN5,NO,            PGUP,    P1,  P2,  P3,  PENT,
    NO,  LALT,               TRNS,               LGUI,BSLS,HOME,END, PGDN,    P0,       PDOT
    ),
    // Mousekey
    [4] = KEYMAP(
    GRV, F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12, DEL,     NLCK,EQL, PSLS,PAST,
    CAPS,Q,   W,   E,   R,   T,   WH_L,WH_D,MS_U,WH_U,WH_R,WBAK,WFWD,         P7,  P8,  P9,  PMNS,
    LCTL,VOLD,VOLU,MUTE,NO,  NO,  BTN2,MS_L,MS_D,MS_R,TRNS,NO,       ENT,     P4,  P5,  P6,  PPLS,
    LSFT,Z,   X,   C,   V,   B,   BTN2,BTN1,BTN4,BTN5,NO,            PGUP,    P1,  P2,  P3,  PENT,
    NO,  LALT,               BTN1,               LGUI,BSLS,HOME,END, PGDN,    P0,       PDOT
    ),
};


/*
 * Fn action definition
 */
const uint16_t fn_actions[] PROGMEM = {
    [0]  = ACTION_LAYER_MOMENTARY(1),
    [1]  = ACTION_LAYER_TAP_KEY(2, KC_SLASH),
    [2]  = ACTION_LAYER_TAP_KEY(3, KC_SPACE),
    [3]  = ACTION_LAYER_TAP_KEY(4, KC_SCOLON),
};
