 /* Copyright 2021 cest73 
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

/* This a shortcut to help you visually see your layout.
 * The first section contains "names" for physical keys of the keyboard
 * and defines their position on the board.
 * The second section defines position of the keys on the switch matrix
 * (where COLUMNS and ROWS crosses). 
 This looks so much better in an terminal window :-(*/
 /*
 * ┌───┬───┬───┬───┐ ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐ ┌───┬───┐
 * │Fn │PSc│Scr│Pse│ │Esc│ │F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12│ │Hme│PgU│
 * └───┴───┴───┴───┘ └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘ └───┴───┘
 *
 * ┌───┬───┬───┬───┐ ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐ ┌───┐
 * │ - │ * │ / │Num│ │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │Bsl│Bsp│ │Ins│
 * ├───┼───┼───┼───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤ ├───┤
 * │ + │ 9 │ 8 │ 7 │ │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \  │ │Del│
 * ├───┼───┼───┼───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬────│ ├───┤
 * │ = │ 6 │ 5 │ 4 │ │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │Etl│ Ent│ │PgD│
 * ├───┼───┼───┼───┤ ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┴┬───┘ ├───┤
 * │Tab│ 3 │ 2 │ 1 │ │Shft│Shl│ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │ Shift│┌───┐│End│
 * ├───┼───┼───┼───┤ ├────┼───┼───┴┬──┴───┴───┴───┴───┴───┴─┬─┴─┬─┴─┬─┴──┬───┘│ ↑ │└───┘
 * │Ent│ . │ , │ 0 │ │Ctrl│GUI│Alt │                        │Alt│Mnu│Ctrl│┌───┼───┼───┐
 * └───┴───┴───┴───┘ └────┴───┴────┴────────────────────────┴───┴───┴────┘│ ← │ ↓ │ → │
 *                                                                        └───┴───┴───┘
 */
// due to a nasty PCB layout bug the R1.03 board has "6" and "7" keyboard coulmns swapped...

#define LAYOUT_all( \
    k00, k10, k01, k11,    k02,      k12, k03, k13, k04, k14, k15, k05, k06, k16, k07, k17, k08,    k18, k09, \
\
    k20, k30, k21, k31,    k22, k32, k23, k33, k24, k34, k35, k25, k26, k36, k27, k37, k28, k19, k38,    k29, \
    k40, k50, k41, k51,    k42, k52, k43, k53, k44, k54, k55, k45, k46, k56, k47, k57, k48, k58,         k49, \
    k60, k70, k61, k71,    k62, k72, k63, k73, k64, k74, k75, k65, k66, k76, k67, k77, k68, k78,         k69, \
    k39, k90, k81, k91,    k82, k92, k83, k93, k84, k94, k95, k85, k86, k96, k87, k97, k88,       k98,   k89, \
    k80, kA0, k59, kA1,    kA2, kA3, kA4,                kA5,                kA6, kA7, kA8,  kA9, k99, k79 \
) { \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09 }, \
    { k10, k11, k12, k13, k14, k15, k16, k17, k18, k19 }, \
    { k20, k21, k22, k23, k24, k25, k26, k27, k28, k29 }, \
    { k30, k31, k32, k33, k34, k35, k36, k37, k38, k39 }, \
    { k40, k41, k42, k43, k44, k45, k46, k47, k48, k49 }, \
    { k50, k51, k52, k53, k54, k55, k56, k57, k58, k59 }, \
    { k60, k61, k62, k63, k64, k65, k66, k67, k68, k69 }, \
    { k70, k71, k72, k73, k74, k75, k76, k77, k78, k79 }, \
    { k80, k81, k82, k83, k84, k85, k86, k87, k88, k89 }, \
    { k90, k91, k92, k93, k94, k95, k96, k97, k98, k99 }, \
    { kA0, kA1, kA2, kA3, kA4, kA5, kA6, kA7, kA8, kA9 } \
}
