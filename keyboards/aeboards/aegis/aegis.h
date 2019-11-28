/* Copyright 2018 Jason Williams (Wilba)
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

#define _____ KC_NO

#define LAYOUT_aegis( \
  K0000, K0100, K0001, K0101,        K0002, K0102, K0003, K0103, K0004, K0104, K0005, K0105, K0006, K0106, K0007, K0107, K0008, \
  K0200, K0300, K0201, K0301,        K0202, K0302, K0203, K0303, K0204, K0304, K0205, K0305, K0206, K0306, K0207, K0307, K0208, K0308, K0108, \
  K0400, K0500, K0401, K0501,        K0402, K0502, K0403, K0503, K0404, K0504, K0405, K0505, K0406, K0506, K0407, K0507, K0408, K0508, \
  K0600, K0700, K0601, K0701,        K0602, K0702, K0603, K0703, K0604, K0704, K0605, K0705, K0606, K0706, K0607, K0707, K0608, \
  K0800, K0900, K0801, K0901,        K0802, K0902, K0803, K0903, K0804, K0904, K0805, K0905, K0806, K0906, K0807, K0907, K0808, K0908, \
  K1000, K1100, K1001,        K1101, K1002, K1102, K1003, K1103,                      K1105,                      K1107, K1008, K1108 \
) { \
  { K0000, K0001, K0002, K0003, K0004, K0005, K0006, K0007, K0008 }, \
  { K0100, K0101, K0102, K0103, K0104, K0105, K0106, K0107, K0108 }, \
  { K0200, K0201, K0202, K0203, K0204, K0205, K0206, K0207, K0208 }, \
  { K0300, K0301, K0302, K0303, K0304, K0305, K0306, K0307, K0308 }, \
  { K0400, K0401, K0402, K0403, K0404, K0405, K0406, K0407, K0408 }, \
  { K0500, K0501, K0502, K0503, K0504, K0505, K0506, K0507, K0508 }, \
  { K0600, K0601, K0602, K0603, K0604, K0605, K0606, K0607, K0608 }, \
  { K0700, K0701, K0702, K0703, K0704, K0705, K0706, K0707, _____ }, \
  { K0800, K0801, K0802, K0803, K0804, K0805, K0806, K0807, K0808 }, \
  { K0900, K0901, K0902, K0903, K0904, K0905, K0906, K0907, K0908 }, \
  { K1000, K1001, K1002, K1003, _____, _____, _____, _____, K1008 }, \
  { K1100, K1101, K1102, K1103, _____, K1105, _____, K1107, K1108 } \
}
