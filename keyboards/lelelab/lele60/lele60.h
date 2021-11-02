/* Copyright 2021 LeleLab
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

#define LAYOUT( \
	k11,k12,k13,k14,k15,k16,k17,k18,k19,k110,k111,k112,k113,k114,\
	k21,k22,k23,k24,k25,k26,k27,k28,k29,k210,k211,k212,k213,k214,\
	k31,k32,k33,k34,k35,k36,k37,k38,k39,k310,k311,k312,k313,k314,\
	k41,k42,k43,k44,k45,k46,k47,k48,k49,k410,k411,k413,k414,\
	k51,k52,k53,k54,k56,k57,k58,k510,k511,k512,k513,k514\
) \
{ \
	{k11,k12,k13,k14,k15,k16,k17,k18,k19,k110,k111,k112,k113,k114},\
	{k21,k22,k23,k24,k25,k26,k27,k28,k29,k210,k211,k212,k213,k214},\
	{k31,k32,k33,k34,k35,k36,k37,k38,k39,k310,k311,k312,k313,k314},\
	{k41,k42,k43,k44,k45,k46,k47,k48,k49,k410,k411,KC_NO,k413,k414},\
	{k51,k52,k53,k54,KC_NO,k56,k57,k58,KC_NO,k510,k511,k512,k513,k514}\
}

