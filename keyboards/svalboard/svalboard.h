/*
Copyright 2023 Morgan Venable @_claussen

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

//Layout for svalboard v0 (different from lalboard_v2)
//1 2 3 4 5
//S E D N W
//Both Thumbs (these are same as lalboard_v2)
//OL OU D IL MODE DOUBLE
#define LAYOUT( r1d, r1n, r1e, r1s, r1w, \
    r2d, r2n, r2e, r2s, r2w, \
    r3d, r3n, r3e, r3s, r3w, \
    r4d, r4n, r4e, r4s, r4w, \
    l1d, l1n, l1e, l1s, l1w, \
    l2d, l2n, l2e, l2s, l2w, \
    l3d, l3n, l3e, l3s, l3w, \
    l4d, l4n, l4e, l4s, l4w, \
    rtd, rti, rtu, rtuo, rtlo, rtdd, \
    ltd, lti, ltu, ltuo, ltlo, ltdd) \
{ \
    {ltlo,ltuo,ltd, lti, ltu, ltdd}, \
    {l1s, l1e, l1d, l1n, l1w, KC_NO}, \
    {l2s, l2e, l2d, l2n, l2w, KC_NO}, \
    {l3s, l3e, l3d, l3n, l3w, KC_NO}, \
    {l4s, l4e, l4d, l4n, l4w, KC_NO}, \
    \
    {rtlo,rtuo,rtd, rti, rtu, rtdd}, \
    {r1s, r1e, r1d, r1n, r1w, KC_NO}, \
    {r2s, r2e, r2d, r2n, r2w, KC_NO}, \
    {r3s, r3e, r3d, r3n, r3w, KC_NO}, \
    {r4s, r4e, r4d, r4n, r4w, KC_NO} }

