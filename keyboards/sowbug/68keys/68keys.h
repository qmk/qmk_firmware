/* Copyright 2021 Mike Tsao
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

// 68keys.h

#pragma once

#include "quantum.h"

#define LAYOUT_default( A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15, B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15, C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, E0, E1, E2, E3, E4, E5, E6, E7, E8, E9) \
{ \
    { A0, A1, A2, A3, A4, A5, A6, A7, A8, A9, A10, A11, A12, A13, A14, A15 }, \
    { B0, B1, B2, B3, B4, B5, B6, B7, B8, B9, B10, B11, B12, B13, B14, B15 }, \
    { C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11, C12, KC_NO, KC_NO, KC_NO }, \
    { D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11, D12, KC_NO, KC_NO, KC_NO }, \
    { E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO } \
}

#define LAYOUT LAYOUT_default
