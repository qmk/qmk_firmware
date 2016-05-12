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

#include "keymap_common.h"


const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    /* 0: plain Qwerty without layer switching
     *         ,---------------. ,---------------. ,---------------.
     *         |F13|F14|F15|F16| |F17|F18|F19|F20| |F21|F22|F23|F24|
     * ,---.   |---------------| |---------------| |---------------| ,-----------. ,---------------. ,-------.
     * |Esc|   |F1 |F2 |F3 |F4 | |F5 |F6 |F7 |F8 | |F9 |F10|F11|F12| |PrS|ScL|Pau| |VDn|VUp|Mut|Pwr| | Help  |
     * `---'   `---------------' `---------------' `---------------' `-----------' `---------------' `-------'
     * ,-----------------------------------------------------------. ,-----------. ,---------------. ,-------.
     * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|JPY|Bsp| |Ins|Hom|PgU| |NmL|  /|  *|  -| |Stp|Agn|
     * |-----------------------------------------------------------| |-----------| |---------------| |-------|
     * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|  \  | |Del|End|PgD| |  7|  8|  9|  +| |Mnu|Und|
     * |-----------------------------------------------------------| `-----------' |---------------| |-------|
     * |CapsL |  A|  S|  D|  F|  G|  H|  J|  K|  L|  ;|  :|  #|Retn|               |  4|  5|  6|KP,| |Sel|Cpy|
     * |-----------------------------------------------------------|     ,---.     |---------------| |-------|
     * |Shft|  <|  Z|  X|  C|  V|  B|  N|  M|  ,|  ,|  /| RO|Shift |     |Up |     |  1|  2|  3|KP=| |Exe|Pst|
     * |-----------------------------------------------------------| ,-----------. |---------------| |-------|
     * |Ctl|Gui|Alt|MHEN|HNJ| Space  |H/E|HENK|KANA|Alt|Gui|App|Ctl| |Lef|Dow|Rig| |  0    |  .|Ent| |Fnd|Cut|
     * `-----------------------------------------------------------' `-----------' `---------------' `-------'
     */
    KEYMAP_ALL(
              F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,    VOLD,VOLU,MUTE,PWR,     HELP,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,    STOP,AGIN,
    TAB, Q,   W,   E,   R,   T,   Y,   U,   I,   O,   P,   LBRC,RBRC,     BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,    MENU,UNDO,
    CAPS,A,   S,   D,   F,   G,   H,   J,   K,   L,   SCLN,QUOT,     NUHS,ENT,                         P4,  P5,  P6,  PCMM,    SLCT,COPY,
    LSFT,NUBS,Z,   X,   C,   V,   B,   N,   M,   COMM,DOT, SLSH,     RO,  RSFT,          UP,           P1,  P2,  P3,  PEQL,    EXEC,PSTE,
    LCTL,LGUI,LALT,MHEN,HANJ,     SPC,      HAEN,HENK,KANA,RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT,    FIND,CUT
    ),

#if 0
    /* Colemak http://colemak.com
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
    KEYMAP_ALL(
              F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,    VOLD,VOLU,MUTE,PWR,     HELP,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,    STOP,AGIN,
    TAB, Q,   W,   F,   P,   G,   J,   L,   U,   Y,   SCLN,LBRC,RBRC,     BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,    MENU,UNDO,
    BSPC,A,   R,   S,   T,   D,   H,   N,   E,   I,   O,   QUOT,     NUHS,ENT,                         P4,  P5,  P6,  PCMM,    SLCT,COPY,
    LSFT,NUBS,Z,   X,   C,   V,   B,   K,   M,   COMM,DOT, SLSH,     RO,  RSFT,          UP,           P1,  P2,  P3,  PEQL,    EXEC,PSTE,
    LCTL,LGUI,LALT,MHEN,HANJ,     SPC,      HAEN,HENK,KANA,RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT,    FIND,CUT
    ),

    /* Dvorak http://en.wikipedia.org/wiki/Dvorak_Simplified_Keyboard
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
    KEYMAP_ALL(
              F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,    VOLD,VOLU,MUTE,PWR,     HELP,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   LBRC,RBRC,JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,    STOP,AGIN,
    TAB, QUOT,COMM,DOT, P,   Y,   F,   G,   C,   R,   L,   SLSH,EQL,      BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,    MENU,UNDO,
    CAPS,A,   O,   E,   U,   I,   D,   H,   T,   N,   S,   MINS,     NUHS,ENT,                         P4,  P5,  P6,  PCMM,    SLCT,COPY,
    LSFT,NUBS,SCLN,Q,   J,   K,   X,   B,   M,   W,   V,   Z,        RO,  RSFT,          UP,           P1,  P2,  P3,  PEQL,    EXEC,PSTE,
    LCTL,LGUI,LALT,MHEN,HANJ,     SPC,      HAEN,HENK,KANA,RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT,    FIND,CUT
    ),

    /* Workman http://viralintrospection.wordpress.com/2010/09/06/a-different-philosophy-in-designing-keyboard-layouts/
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
    KEYMAP_ALL(
              F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
    ESC,      F1,  F2,  F3,  F4,  F5,  F6,  F7,  F8,  F9,  F10, F11, F12,           PSCR,SLCK,PAUS,    VOLD,VOLU,MUTE,PWR,     HELP,
    GRV, 1,   2,   3,   4,   5,   6,   7,   8,   9,   0,   MINS,EQL, JYEN,BSPC,     INS, HOME,PGUP,    NLCK,PSLS,PAST,PMNS,    STOP,AGIN,
    TAB, Q,   D,   R,   W,   B,   J,   F,   U,   P,   SCLN,LBRC,RBRC,     BSLS,     DEL, END, PGDN,    P7,  P8,  P9,  PPLS,    MENU,UNDO,
    CAPS,A,   S,   H,   T,   G,   Y,   N,   E,   O,   I,   QUOT,     NUHS,ENT,                         P4,  P5,  P6,  PCMM,    SLCT,COPY,
    LSFT,NUBS,Z,   X,   M,   C,   V,   K,   L,   COMM,DOT, SLSH,     RO,  RSFT,          UP,           P1,  P2,  P3,  PEQL,    EXEC,PSTE,
    LCTL,LGUI,LALT,MHEN,HANJ,     SPC,      HAEN,HENK,KANA,RALT,RGUI,APP, RCTL,     LEFT,DOWN,RGHT,    P0,       PDOT,PENT,    FIND,CUT
    ),
#endif
};

const uint16_t fn_actions[] PROGMEM = {};
