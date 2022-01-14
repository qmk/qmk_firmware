/* Copyright 2021 Kyle McCreery 
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

#define ___ KC_NO

#ifndef STACK_SPLIT

#define LAYOUT( \
  K00, K01, K02, K03, K04, K05, K06, K07, K08, K09, K0A, K0B, K0C, K0D,\
  K10, K11, K12, K13, K14, K15, K16, K17, K18, K19, K1A, K1B, K1C, K1D,\
  K20, K21, K22, K23, K24, K25, K26, K27, K28, K29, K2A, K2B, K2C, K2D \
) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06 }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16 }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26 }, \
	{ K0D,   K0C,   K0B,   K0A,   K09,   K08,   K07 }, \
	{ K1D,   K1C,   K1B,   K1A,   K19,   K18,   K17 }, \
	{ K2D,   K2C,   K2B,   K2A,   K29,   K28,   K27 }  \
}

#else

#define LAYOUT( \
  L00, L01, L02, L03, L04, L05, L06, L07, L08, L09, L0A, L0B, L0C, L0D,\
  L10, L11, L12, L13, L14, L15, L16, L17, L18, L19, L1A, L1B, L1C, L1D,\
  L20, L21, L22, L23, L24, L25, L26, L27, L28, L29, L2A, L2B, L2C, L2D, \
  R00, R01, R02, R03, R04, R05, R06, R07, R08, R09, R0A, R0B, R0C, R0D,\
  R10, R11, R12, R13, R14, R15, R16, R17, R18, R19, R1A, R1B, R1C, R1D,\
  R20, R21, R22, R23, R24, R25, R26, R27, R28, R29, R2A, R2B, R2C, R2D \
) { \
	{ L00,   L01,   L02,   L03,   L04,   L05,   L06 }, \
	{ L10,   L11,   L12,   L13,   L14,   L15,   L16 }, \
	{ L20,   L21,   L22,   L23,   L24,   L25,   L26 }, \
	{ L0D,   L0C,   L0B,   L0A,   L09,   L08,   L07 }, \
	{ L1D,   L1C,   L1B,   L1A,   L19,   L18,   L17 }, \
	{ L2D,   L2C,   L2B,   L2A,   L29,   L28,   L27 }, \
    { R00,   R01,   R02,   R03,   R04,   R05,   R06 }, \
	{ R10,   R11,   R12,   R13,   R14,   R15,   R16 }, \
	{ R20,   R21,   R22,   R23,   R24,   R25,   R26 }, \
	{ R0D,   R0C,   R0B,   R0A,   R09,   R08,   R07 }, \
	{ R1D,   R1C,   R1B,   R1A,   R19,   R18,   R17 }, \
	{ R2D,   R2C,   R2B,   R2A,   R29,   R28,   R27 }  \
}

#endif

