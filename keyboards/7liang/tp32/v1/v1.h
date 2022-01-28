/* Copyright 2022 SevenLiang(@skyjun)
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

#include "tp32.h"

#include "quantum.h"

#define ___     KC_NO

#define LAYOUT_ortho_3x12(  \
    K00, K01, K02, K03, K04,           K07, K08, K09, K0A, K0B, \
    K10, K11, K12, K13, K14,           K17, K18, K19, K1A, K1B, \
    K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B  \
    ) { \
        { K00, K01, K02, K03, K04, ___, ___, K07, K08, K09, K0A, K0B }, \
        { K10, K11, K12, K13, K14, ___, ___, K17, K18, K19, K1A, K1B }, \
        { K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B }  \
    }
