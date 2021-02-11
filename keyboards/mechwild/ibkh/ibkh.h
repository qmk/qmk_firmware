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

#define LAYOUT( \
	 K00,  K01,  K02,  K03,  K04,  K05,        K07,  K08,  K09,  K0A,   K0B,  K0C, \
	 K10,        K12,  K13,  K14,                    K18,  K19,  K1A,   K1B,  K1C, \
	                   K23,  K24,        K26,        K28,  K29                     \
) { \
    {K00,  K01,  K02,  K03,  K04,  K05},   \
    {K10,  ___,  K12,  K13,  K14,  ___},   \
    {K23,  K24,  K26,  K28,  K29,  ___},   \
	{K0C,  K0B,  K0A,  K09,  K08,  K07},   \
    {K1C,  K1B,  K1A,  K19,  K18,  ___}    \
}
