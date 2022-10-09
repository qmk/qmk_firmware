/*
Copyright 2022 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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
#pragma once

#include "quantum.h"

#define LAYOUT_all( \
    k00, k01, k11, k02, k12, k03, k13, k04, k14, k05, k15, k06, k16, k07, k18, k08, \
    k20, k30, k21, k31, k22, k32, k23, k33, k24, k34, k25, k35, k26, k36, k27, k37, k28, k38, \
    k40, k50, k41, k51, k42, k52, k43, k53, k44, k54, k45, k55, k46, k56, k47, k48, k58, \
    k60, k70, k61, k71, k62, k72, k63, k73, k64, k74, k65, k75, k66, k76,  \
    k80, k90, k81, k91, k82, k92, k83, k93, k84, k94, k85, k95, k86, k96, k98, \
    ka0, ka1, kb1,      kb2, kb3, kb4,      kb5, ka6, kb6,      ka7, kb8, ka8 \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06, k07, k08}, \
    {KC_NO, k11, k12, k13, k14, k15, k16, KC_NO, k18}, \
    {k20, k21, k22, k23, k24, k25, k26, k27, k28}, \
    {k30, k31, k32, k33, k34, k35, k36, k37, k38}, \
    {k40, k41, k42, k43, k44, k45, k46, k47, k48}, \
    {k50, k51, k52, k53, k54, k55, k56, KC_NO, k58}, \
    {k60, k61, k62, k63, k64, k65, k66, KC_NO, KC_NO}, \
    {k70, k71, k72, k73, k74, k75, k76, KC_NO, KC_NO}, \
    {k80, k81, k82, k83, k84, k85, k86, KC_NO, KC_NO}, \
    {k90, k91, k92, k93, k94, k95, k96, KC_NO, k98},  \
    {ka0, ka1, KC_NO, KC_NO, KC_NO, KC_NO, ka6, ka7, ka8}, \
    {KC_NO, kb1, kb2, kb3, kb4, kb5, kb6, KC_NO, kb8} \
}
