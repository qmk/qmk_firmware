
 /* Copyright 2022 Charlotte Brolan   
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
/*
 * K23 = ANSI Backslash, ISO row 1u
 * K34 = ANSI return, ISO return
 * K35 = ANSI left shift, ISO left shift
 * K36 = ISO extra R4 1u
 */
#define LAYOUT( \
    K00, K01, K02, K03, K04, K05, K06, K07, K08, K0A, K0B, K0C, K10,  K11, \
    K12,  K13, K14, K15, K16, K17, K18, K1A, K1B, K1C, K20, K21, K22, K23, \
    K24,   K25, K26, K27, K28, K2A, K2B, K2C, K30, K31, K32, K33,   K34,   \
    K35,    K36, K37, K38, K3A, K3B, K3C, K40, K41, K42, K43, K44,   K45,  \
          K46,   K47,          K48,           K4A,     K4B                 \
    ) { \
	{ K00,   K01,   K02,   K03,   K04,   K05,   K06,   K07,   K08,  K0A,  K0B,  K0C }, \
	{ K10,   K11,   K12,   K13,   K14,   K15,   K16,   K17,   K18,  K1A,  K1B,  K1C }, \
	{ K20,   K21,   K22,   K23,   K24,   K25,   K26,   K27,   K28,  K2A,  K2B,  K2C }, \
	{ K30,   K31,   K32,   K33,   K34,   K35,   K36,   K37,   K38,  K3A,  K3B,  K3C }, \
	{ K40,   K41,   K42,   K43,   K44,   K45,   K46,   K47,   K48,  K4A,  K4B,  KC_NO }, \
}
