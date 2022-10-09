/* Copyright 2022 rooski15
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

#include "ac980mini.h"

#ifdef RGB_MATRIX_ENABLE
// LED location configuration
led_config_t g_led_config = { {
	
	{  63,     64,     65,     66,     67,     68,     69,     70,     71,     72,     73,     74,     75,         76,    77,     78,     79,        80 },   
	{  46,     47,     48,     49,     50,     51,     52,     53,     54,     55,     56,     57,     58,         59,    60,     61,     62,    NO_LED },   
	{  29,     30,     31,     32,     33,     34,     35,     36,     37,     38,     39,     40,     NO_LED,     41,    42,     43,     44,        45 },   
	{  13,     14,     15,     16,     17,     18,     19,     20,     21,     22,     23,     NO_LED, 24,         25,    26,     27,     28,    NO_LED },   
	{  0,      1,      2,  NO_LED, NO_LED,      3, NO_LED, NO_LED, NO_LED,      4,      5,      6,      7,          8,     9,     10,     11,        12 }
	
},{
		
	// Physical X,Y coordinates of each LED, starting with LED 0 above.	
	{ 1 , 64 }, { 16 , 64 }, { 31 , 64 },                            { 75 , 64 },                                         { 123 , 64 }, { 132 , 64 }, { 144 , 64 }, { 159 , 64 }, { 171 , 64 }, { 183 , 64 },   { 198 , 64 }, { 210 , 64 }, { 224 , 64 },
	{ 7 , 48 }, { 27 , 48 }, { 39 , 48 }, { 51 , 48 }, {  63 , 48 }, { 75 , 48 }, { 87 , 48 }, { 99 , 48 }, { 111 , 48 }, { 123 , 48 }, { 135 , 48 }, { 151 , 48 },               { 171 , 48 },   { 186 , 48 }, { 198 , 48 }, { 210 , 48 },	
	{ 4 , 36 }, { 20 , 36 }, { 32 , 36 }, { 44 , 36 }, {  56 , 36 }, { 68 , 36 }, { 80 , 36 }, { 92 , 36 }, { 104 , 36 }, { 116 , 36 }, { 128 , 36 }, { 140 , 36 }, { 160 , 36 },                 { 186 , 36 }, { 198 , 36 }, { 210 , 36 }, { 224 , 36 },
	{ 3 , 16 }, { 18 , 16 }, { 30 , 16 }, { 42 , 16 }, {  54 , 16 }, { 66 , 16 }, { 78 , 16 }, { 90 , 16 }, { 102 , 16 }, { 114 , 16 }, { 126 , 16 }, { 138 , 16 }, { 150 , 16 }, { 165 , 16 },   { 186 , 16 }, { 198 , 16 }, { 210 , 16 },
	{ 0 ,  0 }, { 12 ,  0 }, { 24 ,  0 }, { 36 ,  0 }, {  48 ,  0 }, { 60 ,  0 }, { 72 ,  0 }, { 84 ,  0 }, {  96 ,  0 }, { 108 ,  0 }, { 120 ,  0 }, { 132 ,  0 }, { 144 ,  0 }, { 162 ,  0 },   { 186 ,  0 }, { 198 ,  0 }, { 210 ,  0 }, { 224 ,  0 },

},{
	// "Flag Assignment" of each key
	// 4 = Alpha
	// 1 = Mod
	// See https://docs.qmk.fm/#/feature_rgb_matrix?id=flags
	// No Caps / Num indicators
	1,1,1,    1,      1,1,1, 1,1,1,  4,4,1,
	1,4,4,4,4,4,4,4,4,4,4,1,   1,  4,4,4,
	1,4,4,4,4,4,4,4,4,4,4,4,1,     4,4,4,1,
	1,4,4,4,4,4,4,4,4,4,4,4,4,4,   4,4,4,
	1,4,4,4,4,4,4,4,4,4,4,4,4,1,   1,1,1,1

} };
/*

*/
#endif