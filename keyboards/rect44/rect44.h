/* Copyright 2020-2021 koshinoya
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

#define LAYOUT_all( \
      A00, A01, A02, A03, A04,   A05, A06, A07,   A08, A09, A10, A11, A12, \
      B00, B01, B02, B03, B04,   B05, B06, B07,   B08, B09, B10, B11, B12, \
      C00, C01, C02, C03, C04,   C05, C06, C07,   C08, C09, C10, C11, C12, \
      D00, D01, D02, D03,        D05, D06,        D08, D09, D10, D11, D12 \
) \
{ \
    { A00, A01, A02, A03, A04,   A05, A06, A07,   A08, A09, A10, A11, A12 }, \
    { B00, B01, B02, B03, B04,   B05, B06, B07,   B08, B09, B10, B11, B12 }, \
    { C00, C01, C02, C03, C04,   C05, C06, C07,   C08, C09, C10, C11, C12 }, \
    { D00, D01, D02, D03, KC_NO, D05, D06, KC_NO, D08, D09, D10, D11, D12 } \
}

#define LAYOUT_ansi_44key( \
      A00, A01,   A02, A03,   A04,   A05, A06,   A07,   A08,   A09, A10, A11,   A12, \
      B00, B01,   B02, B03,   B04,   B05, B06,   B07,   B08,   B09, B10,        B12, \
      C00,        C02, C03,   C04,   C05, C06,   C07,   C08,   C09, C10,        C12, \
      D00, D01,   D02,               D05,                      D09, D10, D11,   D12 \
) \
{ \
    { A00, A01,   A02, A03,   A04,   A05, A06,   A07,   A08,   A09, A10, A11,   A12 }, \
    { B00, B01,   B02, B03,   B04,   B05, B06,   B07,   B08,   B09, B10, KC_NO, B12 }, \
    { C00, KC_NO, C02, C03,   C04,   C05, C06,   C07,   C08,   C09, C10, KC_NO, C12 }, \
    { D00, D01,   D02, KC_NO, KC_NO, D05, KC_NO, KC_NO, KC_NO, D09, D10, D11,   D12 } \
}

#define LAYOUT_ansi_47key( \
      A00, A01,   A02, A03, A04,   A05,   A06, A07,   A08, A09, A10, A11,   A12, \
      B00, B01,   B02, B03, B04,   B05,   B06, B07,   B08, B09, B10,        B12, \
      C00,        C02, C03, C04,   C05,   C06, C07,   C08, C09, C10, C11,   C12, \
      D00, D01,   D02, D03,               D06,        D08, D09, D10, D11,   D12 \
) \
{ \
    { A00, A01,   A02, A03, A04,   A05,   A06, A07,   A08, A09, A10, A11,   A12 }, \
    { B00, B01,   B02, B03, B04,   B05,   B06, B07,   B08, B09, B10, KC_NO, B12 }, \
    { C00, KC_NO, C02, C03, C04,   C05,   C06, C07,   C08, C09, C10, C11,   C12 }, \
    { D00, D01,   D02, D03, KC_NO, KC_NO, D06, KC_NO, D08, D09, D10, D11,   D12 } \
}

#define LAYOUT_iso_48key( \
      A00, A01, A02, A03, A04,   A05,   A06, A07,   A08, A09, A10, A11,      \
      B00, B01, B02, B03, B04,   B05,   B06, B07,   B08, B09, B10, B11, B12, \
      C00, C01, C02, C03, C04,   C05,   C06, C07,   C08, C09, C10, C11, C12, \
      D00, D01, D02, D03,               D06,        D08, D09, D10, D11, D12 \
) \
{ \
    { A00, A01, A02, A03, A04,   A05,   A06, A07,   A08, A09, A10, A11, KC_NO }, \
    { B00, B01, B02, B03, B04,   B05,   B06, B07,   B08, B09, B10, B11, B12   }, \
    { C00, C01, C02, C03, C04,   C05,   C06, C07,   C08, C09, C10, C11, C12   }, \
    { D00, D01, D02, D03, KC_NO, KC_NO, D06, KC_NO, D08, D09, D10, D11, D12   } \
}
