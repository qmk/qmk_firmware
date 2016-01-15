/*
Copyright 2016 Jun Wako <wakojun@gmail.com>

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


#ifndef KEYMAP_SECTION_ENABLE
    #error "KEYMAP_SECTION_ENABLE is not defined."
#endif

const uint8_t keymaps[][MATRIX_ROWS][MATRIX_COLS] __attribute__ ((section (".keymap.keymaps"))) = {
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
};

const uint16_t fn_actions[] __attribute__ ((section (".keymap.fn_actions"))) = {
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
    [13] = ACTION_LAYER_TAP_KEY(1, KC_BSLASH),
    [14] = ACTION_LAYER_TAP_KEY(2, KC_TAB),
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
    [31] = ACTION_MODS_TAP_KEY(MOD_RSFT, KC_BSLASH),
};
