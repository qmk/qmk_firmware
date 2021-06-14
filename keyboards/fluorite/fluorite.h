/* Copyright 2019 Mafuyu Ihotsuno
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06, L07,          R00, R01, R02, R03, R04, R05, R06, R07, \
  L10, L11, L12, L13, L14, L15, L16, L17,          R10, R11, R12, R13, R14, R15, R16, R17, \
L20, L21, L22, L23, L24, L25, L26, L27, L28,          R20, R21, R22, R23, R24, R25, R26, R27, R28, \
L30, L31, L32, L33, L34, L35, L36, L37, L38,          R30, R31, R32, R33, R34, R35, R36, R37, R38, \
L40, L41, L42, L43, L44, L45, L46, L47, L48,          R40, R41, R42, R43, R44, R45, R46, R47, R48, \
L50, L51, L52, L53, L54, L55, L56, L57, L58,          R50, R51, R52, R53, R54, R55, R56, R57, R58, \
L60, L61, L62, L63, L64, L65, L66, L67, L68,          R60, R61, R62, R63, R64, R65, R66, R67, R68, \
L70, L71, L72, L73, L74, L75, L76, L77, L78,          R70, R71, R72, R73, R74, R75, R76, R77, R78 \
) \
{ \
  { KC_NO, L00, L01, L02, L03, L04, L05, L06, L07 }, \
  { KC_NO, L10, L11, L12, L13, L14, L15, L16, L17 }, \
  { L20, L21, L22, L23, L24, L25, L26, L27, L28 }, \
  { L30, L31, L32, L33, L34, L35, L36, L37, L38 }, \
  { L40, L41, L42, L43, L44, L45, L46, L47, L48 }, \
  { L50, L51, L52, L53, L54, L55, L56, L57, L58 }, \
  { L60, L61, L62, L63, L64, L65, L66, L67, L68 }, \
  { L70, L71, L72, L73, L74, L75, L76, L77, L78 }, \
  { KC_NO, R07, R06, R05, R04, R03, R02, R01, R00 }, \
  { KC_NO, R17, R16, R15, R14, R13, R12, R11, R10 }, \
  { R28, R27, R26, R25, R24, R23, R22, R21, R20 }, \
  { R38, R37, R36, R35, R34, R33, R32, R31, R30 }, \
  { R48, R47, R46, R45, R44, R43, R42, R41, R40 }, \
  { R58, R57, R56, R55, R54, R53, R52, R51, R50 }, \
  { R68, R67, R66, R65, R64, R63, R62, R61, R60 }, \
  { R78, R77, R76, R75, R74, R73, R72, R71, R70 }, \
}
