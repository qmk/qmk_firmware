/* Copyright 2021 MTBKeys
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

#define LAYOUT( \
    k00, k10, k20, k30, k40, k50, k60, k70, k80, k90, ka0, kb0, kc0, kd0, ke0, \
         k11, k21, k31, k41, k51, k61, k71, k81, k91, ka1, kb1, kc1, kd1, ke1, \
    k02,      k22, k32, k42, k52, k62, k72, k82, k92, ka2, kb2, kc2, kd2,      \
    k03, k13, k23, k33, k43, k53, k63, k73, k83, k93, ka3, kb3, kc3, kd3, ke3, \
    k04, k14,      k34, k44,      k64,      k84,      ka4, kb4, kc4, kd4, ke4  \
) { \
    { k00,   k10,   k20,   k30, k40, k50,   k60, k70,   k80, k90,   ka0, kb0, kc0, kd0, ke0   }, \
    { KC_NO, k11,   k21,   k31, k41, k51,   k61, k71,   k81, k91,   ka1, kb1, kc1, kd1, ke1   }, \
    { k02,   KC_NO, k22,   k32, k42, k52,   k62, k72,   k82, k92,   ka2, kb2, kc2, kd2, KC_NO }, \
    { k03,   k13,   k23,   k33, k43, k53,   k63, k73,   k83, k93,   ka3, kb3, kc3, kd3, ke3   }, \
    { k04,   k14,   KC_NO, k34, k44, KC_NO, k64, KC_NO, k84, KC_NO, ka4, kb4, kc4, kd4, ke4   }  \
}
