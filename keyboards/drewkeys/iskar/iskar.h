/* Copyright 2021 Drewkeys
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
// Corresponding changes to the layout names and/or definitions must also be made to info.json

/* Standard arrangement / LAYOUT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │0f │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │1f │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤───┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │2f │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤───┤
 * │31      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │3f │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┬┴───┬┴┬───┼───┤───┤
 * │40  │41  │43  │        46              │4a  │4b  │▓│4d │4e │4f │
 * └────┴────┴────┴────────────────────────┴────┴────┴ ┴───┴───┘───┘
*/
#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F,    \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F,    \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k2F,    \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E,   k3F,    \
    k40, k41, k42,                k46,                k4A, k4B,      k4D, k4E,   k4F     \
) { \
    { k00,   k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0A, k0B, k0C,   k0D, k0E,   k0F }, \
    { k10,   KC_NO, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20,   KC_NO, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { KC_NO, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40,   k41,   k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4A, k4B, KC_NO, k4D, k4E,   k4F }  \
}

/* Standard arrangement / 65 ANSI
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │0f │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │1f │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤───┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │2f │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤───┤
 * │31      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │3f │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┬┴───┬┴┬───┼───┤───┤
 * │40  │41  │43  │        46              │4a  │4b  │ │4d │4e │4f │
 * └────┴────┴────┴────────────────────────┴────┴────┴ ┴───┴───┘───┘
*/
#define LAYOUT_65_ansi( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,        k0E, k0F,    \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k1E, k1F,    \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k2F,    \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D,   k3E, k3F,    \
    k40, k41, k42,                k46,                k4A, k4B,      k4D,   k4E, k4F     \
) { \
    { k00,   k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0A, k0B, k0C,   KC_NO, k0E, k0F }, \
    { k10,   KC_NO, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20,   KC_NO, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { KC_NO, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40,   k41,   k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4A, k4B, KC_NO, k4D, k4E,   k4F }  \
}

/* Standard arrangement / 65 ANSI SPLIT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │0f │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │1f │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤───┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │2f │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤───┤
 * │31      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │3f │
 * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┬┴───┬┴┬───┼───┤───┤
 * │40  │41  │43  │        46              │4a  │4b  │ │4d │4e │4f │
 * └────┴────┴────┴────────────────────────┴────┴────┴ ┴───┴───┘───┘
*/
#define LAYOUT_65_ansi_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F,    \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F,    \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k2F,    \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E,   k3F,    \
    k40, k41, k42,                k46,                k4A, k4B,      k4D, k4E,   k4F     \
) { \
    { k00,   k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0A, k0B, k0C,   k0D, k0E,   k0F }, \
    { k10,   KC_NO, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20,   KC_NO, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { KC_NO, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40,   k41,   k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4A, k4B, KC_NO, k4D, k4E,   k4F }  \
}

/* Standard arrangement / 65 TSANGAN
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0e     │0f │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │1f │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤───┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │2f │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤───┤
 * │31      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │3f │
 * ├─────┬─┴─┬──┴─┬─┴───┴───┴───┴───┴───┴───┴───┬┴───┬┴┬───┼───┤───┤
 * │40   │41 │43  │        46                   │4b  │ │4d │4e │4f │
 * └─────┴───┴────┴─────────────────────────────┴────┴ ┴───┴───┘───┘
*/
#define LAYOUT_65_tsangan( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C,      k0E,  k0F,     \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F,    \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k2F,    \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E,   k3F,    \
    k40, k41, k42,                k46,                     k4B,      k4D, k4E,   k4F     \
) { \
    { k00,   k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0A, k0B, k0C,   KC_NO, k0E, k0F }, \
    { k10,   KC_NO, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20,   KC_NO, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { KC_NO, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40,   k41,   k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, KC_NO, k4B, KC_NO, k4D, k4E, k4F }  \
}

/* Standard arrangement / 65 TSANGAN SPLIT
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐
 * │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0a │0b │0c │0d │0e │0f │
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤───┤
 * │10   │12 │13 │14 │15 │16 │17 │18 │19 │1a │1b │1c │1d │1e   │1f │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤───┤
 * │20    │22 │23 │24 │25 │26 │27 │28 │29 │2a │2b │2c │2d      │2f │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤───┤
 * │31      │32 │33 │34 │35 │36 │37 │38 │39 │3a │3b │3d    │3e │3f │
 * ├─────┬─┴─┬──┴─┬─┴───┴───┴───┴───┴───┴───┴───┬┴───┬┴┬───┼───┤───┤
 * │40   │41 │43  │        46                   │4b  │ │4d │4e │4f │
 * └─────┴───┴────┴─────────────────────────────┴────┴ ┴───┴───┘───┘
*/
#define LAYOUT_65_tsangan_split_bs( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0A, k0B, k0C, k0D, k0E,   k0F,    \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1A, k1B, k1C, k1D, k1E,   k1F,    \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2A, k2B, k2C, k2D,        k2F,    \
         k31, k32, k33, k34, k35, k36, k37, k38, k39, k3A, k3B,      k3D, k3E,   k3F,    \
    k40, k41, k42,                k46,                     k4B,      k4D, k4E,   k4F     \
) { \
    { k00,   k01,   k02, k03,   k04,   k05,   k06, k07,   k08,   k09,   k0A, k0B, k0C,   k0D, k0E,   k0F }, \
    { k10,   KC_NO, k12, k13,   k14,   k15,   k16, k17,   k18,   k19,   k1A, k1B, k1C,   k1D, k1E,   k1F }, \
    { k20,   KC_NO, k22, k23,   k24,   k25,   k26, k27,   k28,   k29,   k2A, k2B, k2C,   k2D, KC_NO, k2F }, \
    { KC_NO, k31,   k32, k33,   k34,   k35,   k36, k37,   k38,   k39,   k3A, k3B, KC_NO, k3D, k3E,   k3F }, \
    { k40,   k41,   k42, KC_NO, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, KC_NO, k4B, KC_NO, k4D, k4E,   k4F }  \
}
