/* Copyright 2018-2021 James Laird-Wah, Islam Sharabash
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

#include "leds.h"

#define XXX KC_NO

#define LAYOUT_all( \
  L00, L01, L02, L03, L04, L05, L06,           R06,  R05, R04, R03, R02, R01, R00, \
  L10, L11, L12, L13, L14, L15,          R17,  R16,  R15, R14, R13, R12, R11, R10, \
  L20, L21, L22, L23, L24, L25,                R26,  R25, R24, R23, R22, R21, R20, \
  L30, L31, L32, L33, L34, L35, L36,                 R35, R34, R33, R32, R31, R30, \
  L40, L41, L42, L43, L44,                           R45, R44, R43, R42, R41, R40, \
                      L46, L47,                      R47, R46                      \
) { \
		{ L00, L01, L02, L03, L04, L05, L06, XXX }, \
		{ L10, L11, L12, L13, L14, L15, XXX, XXX }, \
		{ L20, L21, L22, L23, L24, L25, XXX, XXX }, \
		{ L30, L31, L32, L33, L34, L35, L36, XXX }, \
		{ L40, L41, L42, L43, L44, XXX, L46, L47 }, \
		{ R00, R01, R02, R03, R04, R05, R06, XXX }, \
		{ R10, R11, R12, R13, R14, R15, R16, R17 }, \
		{ R20, R21, R22, R23, R24, R25, R26, XXX }, \
		{ R30, R31, R32, R33, R34, R35, XXX, XXX }, \
		{ R40, R41, R42, R43, R44, R45, R46, R47 } \
}

#define LAYOUT_ansi( \
  L00, L01, L02, L03, L04, L05, L06,           R06,  R05, R04, R03, R02, R01, R00, \
  L10, L11, L12, L13, L14, L15,          R17,  R16,  R15, R14, R13, R12, R11, R10, \
  L20, L21, L22, L23, L24, L25,                R26,  R25, R24, R23, R22, R21, R20, \
  L31     , L32, L33, L34, L35, L36,                 R35, R34, R33, R32, R31, R30, \
  L40, L41, L42, L43, L44,                           R45, R44, R43, R42, R41, R40, \
                      L46, L47,                      R47, R46                      \
) { \
		{ L00, L01, L02, L03, L04, L05, L06, XXX }, \
		{ L10, L11, L12, L13, L14, L15, XXX, XXX }, \
		{ L20, L21, L22, L23, L24, L25, XXX, XXX }, \
		{ XXX, L31, L32, L33, L34, L35, L36, XXX }, \
		{ L40, L41, L42, L43, L44, XXX, L46, L47 }, \
		{ R00, R01, R02, R03, R04, R05, R06, XXX }, \
		{ R10, R11, R12, R13, R14, R15, R16, R17 }, \
		{ R20, R21, R22, R23, R24, R25, R26, XXX }, \
		{ R30, R31, R32, R33, R34, R35, XXX, XXX }, \
		{ R40, R41, R42, R43, R44, R45, R46, R47 } \
}

#define LAYOUT_iso( \
  L00, L01, L02, L03, L04, L05, L06,           R06,  R05, R04, R03, R02, R01, R00, \
  L10, L11, L12, L13, L14, L15,          R17,  R16,  R15, R14, R13, R12, R11, R10, \
  L20, L21, L22, L23, L24, L25,                R26,  R25, R24, R23, R22, R21, R20, \
  L30, L31, L32, L33, L34, L35, L36,                 R35, R34, R33, R32, R31, R30, \
  L40, L41, L42, L43, L44,                           R45, R44, R43, R42, R41, R40, \
                      L46, L47,                      R47, R46                      \
) { \
		{ L00, L01, L02, L03, L04, L05, L06, XXX }, \
		{ L10, L11, L12, L13, L14, L15, XXX, XXX }, \
		{ L20, L21, L22, L23, L24, L25, XXX, XXX }, \
		{ L30, L31, L32, L33, L34, L35, L36, XXX }, \
		{ L40, L41, L42, L43, L44, XXX, L46, L47 }, \
		{ R00, R01, R02, R03, R04, R05, R06, XXX }, \
		{ R10, R11, R12, R13, R14, R15, R16, R17 }, \
		{ R20, R21, R22, R23, R24, R25, R26, XXX }, \
		{ R30, R31, R32, R33, R34, R35, XXX, XXX }, \
		{ R40, R41, R42, R43, R44, R45, R46, R47 } \
}
