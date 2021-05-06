/* Copyright 2019 Stephen Peery
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
 *no
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "k66.h"
#ifdef RGB_MATRIX_ENABLE

#include "rgb_matrix.h"
#include "config_led.h"
/* clang-format off */
led_config_t g_led_config = { {
    #if 0
{ 0  , 1   , 2  , 3      , 4      , 5  , 6      , 7      , 8  , 9  , 10 , 11 , 12 , 13 } ,
{ 14 , 15  , 16 , 17     , 18     , 19 , 20     , 21     , 22 , 23 , 24 , 25 , 26 , 27 } ,
{ 28 , 29  , 30 , 31     , 32     , 33 , 34     , 35     , 36 , 37 , 38 , 39 , 40 , 41 } ,
{ 42 , 43  , 44 , 45     , 46     , 47 , 48     , 49     , 50 , 51 , 52 , 53 , 54 , 55 } ,
{ 56 , 57  , 58 , NO_LED , NO_LED , 59 , NO_LED , NO_LED , 60 , 61 , 62 , 63 , 64 , 65 }
// #else
// { 0  , NO_LED   , NO_LED  , NO_LED      , NO_LED      , NO_LED  , NO_LED      , NO_LED      , NO_LED  , NO_LED  , NO_LED , NO_LED , NO_LED , NO_LED } ,
// { 14 , NO_LED  , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED } ,
// { 28 , NO_LED  , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED } ,
// { 42 , NO_LED  , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED     , NO_LED     , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED } ,
// { 56 , NO_LED  , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED , NO_LED }
// #endif
#else
{ 0  , 1   , 2  , 3      , 4      , 5  , 6      , 7      , 8  , 9  , 10 , 11 , 12 , 13 } ,
{ 14 , 15  , 16 , 17     , 18     , 19 , 20     , 21     , 22 , 23 , 24 , 25 , 26 , 27 } ,
{ 28 , 29  , 30 , 31     , 32     , 33 , 34     , 35     , 36 , 37 , 38 , 39 , 40 , 41 } ,
{ 42 , 43  , 44 , 45     , 46     , 47 , 48     , 49     , 50 , 51 , 52 , 53 , 54 , 55 } ,
{ 56 , 57  , 58 , NO_LED , NO_LED , 59 , NO_LED , NO_LED , 60 , 61 , 62 , 63 , 64 , 65 }
#endif
}    , {
{7   , 0}  ,{21  , 0}  ,{36  , 0}  ,{50  , 0}  ,{64  , 0}  ,{78  , 0}  ,{92  , 0}  ,{107 , 0}  ,{121 , 0}  ,{135 , 0}  ,{149 , 0}  ,{164 , 0}  ,{178 , 0}  ,{199 , 0}  ,
{11  , 16} ,{28  , 16} ,{43  , 16} ,{57  , 16} ,{71  , 16} ,{85  , 16} ,{100 , 16} ,{114 , 16} ,{128 , 16} ,{142 , 16} ,{156 , 16} ,{171 , 16} ,{185 , 16} ,{203 , 16} ,
{12  , 32} ,{32  , 32} ,{46  , 32} ,{60  , 32} ,{75  , 32} ,{89  , 32} ,{103 , 32} ,{117 , 32} ,{132 , 32} ,{146 , 32} ,{160 , 32} ,{174 , 32} ,{197 , 32} ,{224 , 0 } ,
{16  , 48} ,{39  , 48} ,{53  , 48} ,{68  , 48} ,{82  , 48} ,{96  , 48} ,{110 , 48} ,{124 , 48} ,{139 , 48} ,{153 , 48} ,{167 , 48} ,{188 , 48} ,{210 , 48} ,{224 , 16} ,
{9   , 64} ,{25  , 64} ,{41  , 64}                         ,{96  , 64}                         ,{164 , 64} ,{180 , 64} ,{196 , 64} ,{210 , 64} ,{224 , 64} ,
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4,
} };

#endif
/* clang-format on */
void matrix_init_kb(void) {
    // matrix_init_user();
}

