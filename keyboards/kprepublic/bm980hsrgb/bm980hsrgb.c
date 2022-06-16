/* Copyright 2021 peepeetee
 * Copyright 2021 bdtc123
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
#include "bm980hsrgb.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
  {  0,      1,      2,      3,      4,      5,      6,      7,      8,      9,     10,     11,     12,  NO_LED,    13 },
  { 17,     18,     19,     20,     21,     22,     23,     24,     25,     26,     27,     28,     29,     30,     31 },
  { 35,     36,     37,     38,     39,     40,     41,     42,     43,     44,     45,     46,     47,     48,     49 },
  { 53,     54,     55,     56,     57,     58,     59,     60,     61,     62,     63,     64,  NO_LED,    65,     66 },
  { 69, NO_LED,     70,     71,     72,     73,     74,     75,     76,     77,     78,     79,     80,     81,     82 },
  { 86,     87,     88,     96,     97,     85,     89,     84,     83,     90,     91,     92,     93,     94,     95 },
  { NO_LED, NO_LED, 34,     50,     51,     52,     16,     68,     67,     33,     15,     32,  NO_LED,    14, NO_LED }


}, {
    // LED Index to Physical Position
    {   0,   0 },  {  15,   0 },  {  30,   0 },  {  45,   0 },  {  60,   0 },  {  75,   0 },  {  90,   0 },  { 105,   0 },  { 120,   0 },  { 135,   0 },  { 150,   0 },  { 165,   0 },  { 180,   0 }, { 195,   0 },  { 202,   0 },  { 212,   0 }, { 224,   0 },
    {   0,   20 }, {  15,   20 }, {  30,   20 }, {  45,   20 }, {  60,   20 }, {  75,   20 }, {  90,   20 }, { 105,   20 }, { 120,   20 }, { 135,   20 }, { 150,   20 }, { 165,   20 }, { 180,   20 },{ 195,   20 }, { 202,   20 }, { 212,   20 },{ 220,   20 },{ 224,   20 },
    {   8,   30 }, {  15,   30 }, {  30,   30 }, {  45,   30 }, {  60,   30 }, {  75,   30 }, {  90,   30 }, { 105,   30 }, { 120,   30 }, { 135,   30 }, { 150,   30 }, { 165,   30 }, { 180,   30 },{ 195,   30 }, { 202,   30 }, { 212,   30 },{ 220,   30 },{ 224,   30 },
    {   9,   40 }, {  15,   40 }, {  30,   40 }, {  45,   40 }, {  60,   40 }, {  75,   40 }, {  90,   40 }, { 105,   40 }, { 120,   40 }, { 135,   40 }, { 150,   40 }, { 165,   40 }, { 180,   40 },{ 195,   40 }, { 202,   40 }, { 212,   40 },
    {   12,  50 }, {  15,   50 }, {  30,   50 }, {  45,   50 }, {  60,   50 }, {  75,   50 }, {  90,   50 }, { 105,   50 }, { 120,   50 }, { 135,   50 }, { 150,   50 }, { 165,   50 }, { 180,   50 },{ 195,   50 }, { 202,   50 }, { 212,   50 },{ 224,   50 },
    {   2,   60 }, {  17,   60 }, {  34,   60 },  { 77,   60 }, { 120,   60 }, { 135,   60 }, {  150,   60 }, { 165,  60 }, { 177,   60 }, { 182,   60 }, { 197,   60 }, { 212,   60 },

}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 9/*scroll lock*/, 1,1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,             1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,             4, 4, 4, 1,
    9/*caps lock*/, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,   4, 4, 4,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,            1,     4, 4, 4, 1,
     1, 1, 1, 4, 1, 1, 1,                       1, 1, 1,     4, 4
} };


#endif
