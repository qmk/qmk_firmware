/* Copyright 2020 Swiftrax and Basekeys.com
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    { NO_LED, 70,     61,     52,     43, 34,     24,     14  },
    {     79, 69,     60,     51,     42, 33,     23, NO_LED  },
    { NO_LED, 71,     62,     53,     44, 35,     25,     15  },
    {     78, 68,     59,     50,     41, 32,     22, NO_LED  },
    {     77, 67,     58,     49,     40, 31, NO_LED,     16  },
    { NO_LED, 72,     63,     54,     45, 36,     26, NO_LED  },
    { NO_LED, 73,     64,     55,     46, 37,     27,     17  },
    {     76, 66,     57,     48,     39, 30,     21, NO_LED  },
    { NO_LED, 74,     56, NO_LED, NO_LED, 38,     28,     18  },
    {     75, 65, NO_LED, NO_LED,     47, 29,     20,     19  }
}, {
	// Underglow
    {  218,   7 },  { 214,  45 }, { 180,  47 }, {  147, 50 }, {  94,  62 }, {  37,  51 }, {   4,   8 }, {   36,  15 },
    {  62,   18 },  {  78,   5 }, { 119,   7 }, {  145, 16 }, { 166,   3 }, { 200,  16 }, 
    
    //Per Key
    { 185,  11 },  { 191,  22 }, { 188,  33 }, { 200,  46 }, { 200,  57 }, { 212,  57 }, { 188,  57 }, { 181,  44 },
    { 176,  22 },  { 168,  11 }, { 155,  11 }, { 164,  22 }, { 169,  32 }, { 165,  44 }, { 172,  55 }, { 157,  54 }, 
    { 153,  44 },  { 156,  33 }, { 153,  22 }, { 142,  12 }, { 130,  13 }, { 138,  23 }, { 143,  33 }, { 140,  45 }, 
    { 137,  56 },  { 128,  47 }, { 132,  35 }, { 127,  25 }, { 119,  16 }, { 107,  17 }, { 115,  27 }, { 120,  37 }, 
    { 116,  48 },  { 117,  59 }, { 104,  51 }, { 109,  39 }, { 104,  29 }, {  86,  19 }, {  74,  16 }, {  78,  28 }, 
    {  79,  39 },  {  82,  50 }, {  73,  60 }, {  71,  48 }, {  67,  37 }, {  66,  26 }, {  63,  15 }, {  50,  12 }, 
    {  55,  24 },  {  55,  35 }, {  59,  47 }, {  50,  56 }, {  47,  45 }, {  43,  33 }, {  43,  22 }, {  39,  10 }, 
    {  25,  11 },  {  29,  22 }, {  30,  33 }, {  34,  44 }, {  24,  54 }, {   9,  55 }, {  15,  44 }, {  14,  33 }, 
    {  14,  22 },  {  14,  11 }
}, {
    2, 2, 2, 2, 2, 2, 2, 2, 
    2, 2, 2, 2, 2, 2, 

    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4
} };
#endif