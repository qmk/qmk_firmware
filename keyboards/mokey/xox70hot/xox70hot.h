/* Copyright 2021 Ocean
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

#define xxx KC_NO

#define LAYOUT_tkl_nofrow_ansi_tsangan(\
    k00, k01, k02, k03, k04, k05, k06, k07, k08, k09, k0a, k0b, k0c,      k0e, k0f, k0g, k0h, \
    k10,      k12, k13, k14, k15, k16, k17, k18, k19, k1a, k1b, k1c, k1d, k1e, k1f, k1g, k1h, \
    k20,      k22, k23, k24, k25, k26, k27, k28, k29, k2a, k2b, k2c, k2d, \
    k30,      k32, k33, k34, k35, k36, k37, k38, k39, k3a, k3b,      k3d,           k3g, \
    k40, k41,      k43,           k46,                k4a, k4b,           k4e, k4f, k4g, k4h \
) \
{ \
    { k00,  k01,   k02,   k03,  k04,  k05,   k06,  k07,   k08,  k09,   k0a,  k0b,  k0c,  KC_NO, k0e,     k0f,   k0g,   k0h }, \
    { k10,  KC_NO, k12,   k13,  k14,  k15,   k16,  k17,   k18,  k19,   k1a,  k1b,  k1c,   k1d,  k1e,     k1f,   k1g,   k1h }, \
    { k20,  KC_NO, k22,   k23,  k24,  k25,   k26,  k27,   k28,  k29,   k2a,  k2b,  k2c,   k2d,  KC_NO,  KC_NO, KC_NO,KC_NO }, \
    { k30,  KC_NO, k32,   k33,  k34,  k35,   k36,  k37,   k38,  k39,   k3a,  k3b,  KC_NO, k3d,  KC_NO,  KC_NO,  k3g, KC_NO }, \
    { k40,  k41,   KC_NO, k43, KC_NO, KC_NO, k46, KC_NO, KC_NO, KC_NO, k4a,  k4b,  KC_NO, KC_NO,k4e,     k4f,   k4g,   k4h }  \
}

