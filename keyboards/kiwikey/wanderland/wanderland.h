/* Copyright 2021 KiwiKey
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

/* Layout Alice split-backspace
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───┬───┐
 * │02 │ │10 │11 │12 │13 │14 │15 │05 │         │06 │16 │17 │18 │19 │1A │1B │1C │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │01 │ │ 20  │21 │22 │23 │24 │25 │         │07 │26 │27 │28 │29 │2A │2B │ 2C  │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │00 │ │  30  │31 │32 │33 │34 │35 │         │36 │37 │38 │39 │3A │3B │   3C   │
 * ├───┤ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │03 │ │   40   │41 │42 │43 │44 │45 │     │46 │47 │48 │49 │4A │4B │  5B  │4C │
 * └───┘ ├──────┬─┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │  50  │    │ 52  │  53   │ 55 │   │    57    │ 59  │           │ 5C  │
 *       └──────┘    └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
#define LAYOUT_alice_split_bs( \
    k02, k10, k11, k12, k13, k14, k15, k05, k06, k16, k17, k18, k19, k1A, k1B, k1C,      \
    k01, k20, k21, k22, k23, k24, k25,      k07, k26, k27, k28, k29, k2A, k2B, k2C,      \
    k00, k30, k31, k32, k33, k34, k35,           k36, k37, k38, k39, k3A, k3B, k3C,      \
    k03, k40, k41, k42, k43, k44, k45,           k46, k47, k48, k49, k4A, k4B, k5B, k4C, \
         k50,      k52,   k53,    k55,                  k57,    k59,           k5C       \
) \
{ \
  { k00,   k01,   k02,   k03,   KC_NO, k05,   k06,   k07,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },   \
  { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C   },   \
  { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   k2C   },   \
  { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   k3C   },   \
  { k40,   k41,   k42,   k43,   k44,   k45,   k46,   k47,   k48,   k49,   k4A,   k4B,   k4C   },   \
  { k50,   KC_NO, k52,   k53,   KC_NO, k55,   KC_NO, k57,   KC_NO, k59,   KC_NO, k5B,   k5C   }    \
}

/* Layout Alice
 * ┌───┐ ┌───┬───┬───┬───┬───┬───┬───┐         ┌───┬───┬───┬───┬───┬───┬───────┐
 * │02 │ │10 │11 │12 │13 │14 │15 │05 │         │06 │16 │17 │18 │19 │1A │  1B   │
 * ├───┤ ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┘       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │01 │ │ 20  │21 │22 │23 │24 │25 │         │07 │26 │27 │28 │29 │2A │2B │ 2C  │
 * ├───┤ ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐        └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │00 │ │  30  │31 │32 │33 │34 │35 │         │36 │37 │38 │39 │3A │3B │   3C   │
 * ├───┤ ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐     ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │03 │ │   40   │41 │42 │43 │44 │45 │     │46 │47 │48 │49 │4A │4B │  5B  │4C │
 * └───┘ ├──────┬─┴──┬┴───┴┬──┴───┴┬──┴─┐   ├───┴───┴──┬┴───┴┬──┴───┴────┬─┴───┤
 *       │  50  │    │ 52  │  53   │ 55 │   │    57    │ 59  │           │ 5C  │
 *       └──────┘    └─────┴───────┴────┘   └──────────┴─────┘           └─────┘
 */
#define LAYOUT_alice( \
    k02, k10, k11, k12, k13, k14, k15, k05, k06, k16, k17, k18, k19, k1A, k1B,           \
    k01, k20, k21, k22, k23, k24, k25,      k07, k26, k27, k28, k29, k2A, k2B, k2C,      \
    k00, k30, k31, k32, k33, k34, k35,           k36, k37, k38, k39, k3A, k3B, k3C,      \
    k03, k40, k41, k42, k43, k44, k45,           k46, k47, k48, k49, k4A, k4B, k5B, k4C, \
         k50,      k52,   k53,    k55,                  k57,    k59,           k5C       \
) \
{ \
  { k00,   k01,   k02,   k03,   KC_NO, k05,   k06,   k07,   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO },   \
  { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   KC_NO },   \
  { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   k2C   },   \
  { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   k3C   },   \
  { k40,   k41,   k42,   k43,   k44,   k45,   k46,   k47,   k48,   k49,   k4A,   k4B,   k4C   },   \
  { k50,   KC_NO, k52,   k53,   KC_NO, k55,   KC_NO, k57,   KC_NO, k59,   KC_NO, k5B,   k5C   }    \
}
