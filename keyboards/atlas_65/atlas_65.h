/* Copyright 2020 Joshua Nguyen
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

#define XXX KC_NO

/*                                                                        ┌───┐
 *    ┌───┬───┬───┬───┬───┬───┬───┐      ┌───┬───┬───┬───┬───┬───┬───┬───┐│1E │     ┌───────┐
 *    │00 │01 │02 │03 │04 │05 │06 │      │07 │08 │09 │0A │0B │0C │0D │0E │└┬──┴┐    │0D     │ 2u Backspace
 *   ┌┴───┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘     ┌┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬┴──┬┴───┴┐│2E │    └───────┘
 *   │10   │11 │12 │13 │14 │15 │        │16 │17 │18 │19 │1A │1B │1C │1D   │└┬──┴┐
 *  ┌┴─────┼───┼───┼───┼───┼───┤        └─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─────┴┐│3E │
 *  │20    │21 │22 │23 │24 │25 │          │26 │27 │28 │29 │2A │2B │2C      │└───┘
 * ┌┴──────┴┬──┴┬──┴┬──┴┬──┴┬──┴┐       ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┘
 * │30      │31 │32 │33 │34 │35 │       │46 │36 │37 │38 │39 │3A │3B    │┌───┐
 * ├─────┬──┴───┼───┴─┬─┴───┴─┬─┴─┐   ┌─┴───┴───┴┬──┴──┬┴───┴───┴──────┘│3D │
 * │40   │      │42   │44     │45 │   │47        │49   │            ┌───┼───┼───┐
 * └─────┘      └─────┴───────┴───┘   └──────────┴─────┘            │4C │4D │4E │
 *                                                                  └───┴───┴───┘
 */

#define LAYOUT( \
    k00, k01, k02, k03, k04, k05, k06,             k07, k08, k09, k0A, k0B, k0C, k0D,   k1E, \
    k10, k11, k12, k13, k14, k15,             k16, k17, k18, k19, k1A, k1B, k1C, k1D,   k2E, \
    k20, k21, k22, k23, k24, k25,             k26, k27, k28, k29, k2A, k2B,      k2C,   k3E, \
    k30, k31, k32, k33, k34, k35,        k46, k36, k37, k38, k39, k3A, k3B,        k3D,      \
    k40,      k42,      k44, k45,        k47,      k49,                       k4C, k4D, k4E  \
) \
{ \
    { k00,   k01,   k02,   k03,   k04,   k05,   k06,   k07,   k08,   k09,   k0A,   k0B,   k0C,   k0D,   XXX }, \
    { k10,   k11,   k12,   k13,   k14,   k15,   k16,   k17,   k18,   k19,   k1A,   k1B,   k1C,   k1D,   k1E }, \
    { k20,   k21,   k22,   k23,   k24,   k25,   k26,   k27,   k28,   k29,   k2A,   k2B,   k2C,   XXX,   k2E }, \
    { k30,   k31,   k32,   k33,   k34,   k35,   k36,   k37,   k38,   k39,   k3A,   k3B,   XXX,   k3D,   k3E }, \
    { k40,   XXX,   k42,   XXX,   k44,   k45,   k46,   k47,   XXX,   k49,   XXX,   XXX,   k4C,   k4D,   k4E }  \
}
