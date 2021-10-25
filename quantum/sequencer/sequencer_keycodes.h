/* Copyright 2021 Rodolphe Belouin
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

#define SQ_R(n) ((n << 16) + SQ_RES)
#define SQ_S(n) ((n << 16) + SQ_STEP)
#define SQ_T(n) ((n << 16) + SQ_TRACK)

// clang-format off
#define sequencer_get_keycodes_48( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, \
    k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, \
    k24, k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, \
    k36, k37, k38, k39, k40, k41, k42, k43, k44, k45, k46, k47) \
    (k00 & 0xFFFF), (k01 & 0xFFFF), (k02 & 0xFFFF), (k03 & 0xFFFF), (k04 & 0xFFFF), (k05 & 0xFFFF), (k06 & 0xFFFF), (k07 & 0xFFFF), (k08 & 0xFFFF), (k09 & 0xFFFF), (k10 & 0xFFFF), (k11 & 0xFFFF), \
    (k12 & 0xFFFF), (k13 & 0xFFFF), (k14 & 0xFFFF), (k15 & 0xFFFF), (k16 & 0xFFFF), (k17 & 0xFFFF), (k18 & 0xFFFF), (k19 & 0xFFFF), (k20 & 0xFFFF), (k21 & 0xFFFF), (k22 & 0xFFFF), (k23 & 0xFFFF), \
    (k24 & 0xFFFF), (k25 & 0xFFFF), (k26 & 0xFFFF), (k27 & 0xFFFF), (k28 & 0xFFFF), (k29 & 0xFFFF), (k30 & 0xFFFF), (k31 & 0xFFFF), (k32 & 0xFFFF), (k33 & 0xFFFF), (k34 & 0xFFFF), (k35 & 0xFFFF), \
    (k36 & 0xFFFF), (k37 & 0xFFFF), (k38 & 0xFFFF), (k39 & 0xFFFF), (k40 & 0xFFFF), (k41 & 0xFFFF), (k42 & 0xFFFF), (k43 & 0xFFFF), (k44 & 0xFFFF), (k45 & 0xFFFF), (k46 & 0xFFFF), (k47 & 0xFFFF)

#define sequencer_get_indices_48( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k10, k11, \
    k12, k13, k14, k15, k16, k17, k18, k19, k20, k21, k22, k23, \
    k24, k25, k26, k27, k28, k29, k30, k31, k32, k33, k34, k35, \
    k36, k37, k38, k39, k40, k41, k42, k43, k44, k45, k46, k47) \
    (k00 >> 16), (k01 >> 16), (k02 >> 16), (k03 >> 16), (k04 >> 16), (k05 >> 16), (k06 >> 16), (k07 >> 16), (k08 >> 16), (k09 >> 16), (k10 >> 16), (k11 >> 16), \
    (k12 >> 16), (k13 >> 16), (k14 >> 16), (k15 >> 16), (k16 >> 16), (k17 >> 16), (k18 >> 16), (k19 >> 16), (k20 >> 16), (k21 >> 16), (k22 >> 16), (k23 >> 16), \
    (k24 >> 16), (k25 >> 16), (k26 >> 16), (k27 >> 16), (k28 >> 16), (k29 >> 16), (k30 >> 16), (k31 >> 16), (k32 >> 16), (k33 >> 16), (k34 >> 16), (k35 >> 16), \
    (k36 >> 16), (k37 >> 16), (k38 >> 16), (k39 >> 16), (k40 >> 16), (k41 >> 16), (k42 >> 16), (k43 >> 16), (k44 >> 16), (k45 >> 16), (k46 >> 16), (k47 >> 16)
// clang-format on
