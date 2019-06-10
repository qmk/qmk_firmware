/* Copyright 2017 Clueboard <info@clueboard.co>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#pragma once
#include "quantum.h"

/*
 * These are shortcuts to help you work with the various layout options. If your 
 * keymap works with one of the LAYOUT_...() macros you are encouraged to use that
 * and to contribute your keymap to the corresponding layout in 
 * `qmk_firmware/layouts/community`.
 */

/* Clueboard matrix layout
 * ,-----------------------------------------------------------.  ,---.
 * | 00| 01| 02| 03| 04| 05| 06| 07| 50| 51| 52| 53| 54|   56  |  | 57|
 * |-----------------------------------------------------------|  |---|
 * |   10| 11| 12| 13| 14| 15| 16| 17| 60| 61| 62| 63| 64|   65|  | 67|
 * |-----------------------------------------------------------|  `---'
 * |    20| 21| 22| 23| 24| 25| 26| 27| 70| 71| 72| 73|      75|
 * |--------------------------------------------------------------.
 * |  30    | 32| 33| 34| 35| 36| 37| 80| 81| 82| 83|      85  |86|
 * |------------------------------------------------------------------.
 * |  40| 41|  42|        45|       46|   90|  92|  93|  94| 95|96| 97|
 * `------------------------------------------------------------------'
 * ,-----------------------------------------------------------.  ,---.
 * |  `|  1|  2|  3|  4|  5|  6|  7|  8|  9|  0|  -|  =|Backsp |  |Ins|
 * |-----------------------------------------------------------|  |---|
 * |Tab  |  Q|  W|  E|  R|  T|  Y|  U|  I|  O|  P|  [|  ]|    \|  |Del|
 * |-----------------------------------------------------------|  `---'
 * |Caps  |  A|  S|  D|  F|  G|  H|  J|  k|  L|  ;|  '|Enter   |
 * |--------------------------------------------------------------.
 * |Shift   |  Z|  X|  C|  V|  B|  N|  M|  ,|  .|  /|    Shift| Up|
 * |------------------------------------------------------------------.
 * |Ctrl|Alt|Gui |     Space|  Space|Gui |Alt |Fn  |Ctrl|Left|Down|Rgt|
 * `------------------------------------------------------------------'
 */
// The first section contains all of the arguments
// The second converts the arguments into a two-dimensional array

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54,    k55,   k57, \
    k10, k11, k12, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65,      k67, \
    k20, k21, k22, k23, k24, k25, k26, k27, k70, k71, k72, k73,    k75, \
    k30,      k32, k33, k34, k35, k36, k37, k80, k81, k82, k83,      k85, k86, \
    k40, k41, k42,           k45, k46,      k90,      k92, k93, k94, k95, k96, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, KC_NO, KC_NO, k45, k46, KC_NO }, \
    { k50, k51, k52, k53, k54, k55, KC_NO, k57 }, \
    { k60, k61, k62, k63, k64, k65, KC_NO, k67 }, \
    { k70, k71, k72, k73, KC_NO, k75, KC_NO, KC_NO }, \
    { k80, k81, k82, k83, KC_NO, k85, k86, KC_NO }, \
    { k90, KC_NO, k92, k93, k94, k95, k96, k97 }  \
}

#define LAYOUT_66_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k50, k51, k52, k53, k54,    k55,   k57, \
    k10, k11, k12, k13, k14, k15, k16, k17, k60, k61, k62, k63, k64, k65,      k67, \
    k20, k21, k22, k23, k24, k25, k26, k27, k70, k71, k72, k73,    k75, \
    k30,      k32, k33, k34, k35, k36, k37, k80, k81, k82, k83,    k85,   k86, \
    k40, k41, k42,                k46,                k92, k93, k94, k95, k96, k97 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27 }, \
    { k30, KC_NO, k32, k33, k34, k35, k36, k37 }, \
    { k40, k41, k42, KC_NO, KC_NO, KC_NO, k46, KC_NO }, \
    { k50, k51, k52, k53, k54, k55, KC_NO, k57 }, \
    { k60, k61, k62, k63, k64, k65, KC_NO, k67 }, \
    { k70, k71, k72, k73, KC_NO, k75, KC_NO, KC_NO }, \
    { k80, k81, k82, k83, KC_NO, k85, k86, KC_NO }, \
    { KC_NO, KC_NO, k92, k93, k94, k95, k96, k97 }  \
}
