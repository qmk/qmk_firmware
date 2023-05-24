/*
Copyright 2021 Stefan Sundin "4pplet" <4pplet@protonmail.com>

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

void setLayerLed(layer_state_t state);

#define LAYOUT_all( \
    k00, k10, k01, k11, k02, k12, k03, k13, k04, k14, k05, k15, k06, k16, k36, \
    k20, k30, k21, k31, k22, k32, k23, k33, k24, k34, k25, k35, k26, k56,\
    k40, k50, k41, k51, k42, k52, k43, k53, k44, k54, k45, k55, k46, k76,\
    k60, k70, k61, k71, k62, k72, k63, k73, k64, k74, k65, k75, k66, k96,\
    k80, k90, k91, k93, k94, k85, k95, k86  \
) \
{ \
    {k00, k01, k02, k03, k04, k05, k06}, \
    {k10, k11, k12, k13, k14, k15, k16}, \
    {k20, k21, k22, k23, k24, k25, k26}, \
    {k30, k31, k32, k33, k34, k35, k36}, \
    {k40, k41, k42, k43, k44, k45, k46}, \
    {k50, k51, k52, k53, k54, k55, k56}, \
    {k60, k61, k62, k63, k64, k65, k66}, \
    {k70, k71, k72, k73, k74, k75, k76}, \
    {k80, KC_NO, KC_NO, KC_NO, KC_NO, k85, k86}, \
    {k90, k91, KC_NO, k93, k94, k95, k96}  \
}
