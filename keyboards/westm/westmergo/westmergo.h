/* Copyright 2021 WestM
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

#define LAYOUT_alice( \
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b,      k0d, k0e, k0f,\
    k10, k11, k12, k13, k14, k15, k16,      k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, \
    k20, k21, k22, k23, k24, k25, k26,      k28, k29, k2a, k2b, k2c, k2d,      k2f, \
         k31, k32, k33, k34, k35, k36,      k38, k39, k3a, k3b, k3c, k3d, k3e, k3f, \
         k41,      k43,      k45, k46,           k49,      k4b,                k4f  \
) \
{ \
    { k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, XXX, k0d, k0e, k0f },\
    { k10, k11, k12, k13, k14, k15, k16, XXX, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f }, \
    { k20, k21, k22, k23, k24, k25, k26, XXX, k28, k29, k2a, k2b, k2c, k2d, XXX, k2f }, \
    { XXX, k31, k32, k33, k34, k35, k36, XXX, k38, k39, k3a, k3b, k3c, k3d, k3e, k3f }, \
    { XXX, k41, XXX, k43, XXX, k45, k46, XXX, XXX, k49, XXX, k4b, XXX, XXX, XXX, k4f },  \
}
