/* Copyright 2020 Sergi Meseguer <zigotica@gmail.com>
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

#include "quantum.h"

/* This a shortcut to help you visually see your layout */

#define ___ KC_NO

#define LAYOUT( \
        L05, L04, L03, L02, L01, R01, R02, R03, R04, R05, \
        L10, L09, L08, L07, L06, R06, R07, R08, R09, R10, \
        L15, L14, L13, L12, L11, R11, R12, R13, R14, R15, \
                       L17, L16, R16, R17                 \
    ) \
    { \
        { L05, L04, L03, L02, L01 }, \
        { L10, L09, L08, L07, L06 }, \
        { L15, L14, L13, L12, L11 }, \
        { L17, L16, ___, ___ , ___}, \
        { R01, R02, R03, R04, R05 }, \
        { R06, R07, R08, R09, R10 }, \
        { R11, R12, R13, R14, R15 }, \
        { R16, R17, ___, ___, ___ }  \
    }

