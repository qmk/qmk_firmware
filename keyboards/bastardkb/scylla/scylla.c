/*
 * Copyright 2021 Quentin LEBASTARD <qlebastard@gmail.com>
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

#include "scylla.h"

#ifdef RGB_MATRIX_ENABLE
#define LAYOUT_split_4x6_5( \
	k00, k01, k02, k03, k04, k05,			k55, k54, k53, k52, k51, k50, \
	k10, k11, k12, k13, k14, k15,			k65, k64, k63, k62, k61, k60, \
	k20, k21, k22, k23, k24, k25,			k75, k74, k73, k72, k71, k70, \
	k30, k31, k32, k33, k34, k35,			k85, k84, k83, k82, k81, k80, \
	               k43, k44, k41,		    k91, k94, k93, \
	                    k45, k42,           k92, k95 \

{\
	{  0,  7,  8, 15, 16, 20 }, \
	{  1,  6,  9, 14, 17, 21 }, \
	{  2,  5, 10, 13, 18, 22 }, \
	{  3,  4, 11, 12, 19, 23 }, \
	{ NO_LED, 28, 24, 26, 27, 25 }, \
	{ 29, 36, 37, 44, 45, 49 }, \
	{ 30, 35, 38, 43, 46, 50 }, \
	{ 31, 34, 39, 42, 47, 51 }, \
	{ 32, 33, 40, 41, 48, 52 }, \
	{ NO_LED, 57, 53, 55, 56, 54 }, \
}

led_config_t g_led_config = { {
    {  0,  7,  8, 15, 16, 20 },
    {  1,  6,  9, 14, 17, 21 },
    {  2,  5, 10, 13, 18, 22 },
    {  3,  4, 11, 12, 19, 23 },
    { NO_LED, 28, 24, 26, 27, 25 },
    { 29, 36, 37, 44, 45, 49 },
    { 30, 35, 38, 43, 46, 50 },
    { 31, 34, 39, 42, 47, 51 },
    { 32, 33, 40, 41, 48, 52 },
    { NO_LED, 57, 53, 55, 56, 54 }
}, {
    {  20,   0 }, {  20,  16 }, {  20,  32 }, {  20   48 },
    {  }

    {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
    {  85,  39 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  68,  37 }, {  80,  58 },
    {  60,  55 }, {  50,  35 }, {  50,  13 }, {  50,   0 }, {  33,   3 }, {  33,  20 }, {  33,  37 },
    {  16,  42 }, {  16,  24 }, {  16,   7 }, {   0,   7 }, {   0,  24 }, {   0,  41 }, { 139,  16 },
    { 174,  13 }, { 208,  20 }, { 208,  38 }, { 174,  48 }, { 139,  52 }, { 129,  63 }, { 139,  39 },
    { 139,  21 }, { 139,   4 }, { 156,   2 }, { 156,  19 }, { 156,  37 }, { 144,  58 }, { 164,  55 },
    { 174,  35 }, { 174,  13 }, { 174,   0 }, { 191,   3 }, { 191,  20 }, { 191,  37 }, { 208,  42 },
    { 208,  24 }, { 208,   7 }, { 224,   7 }, { 224,  24 }, { 224,  41 }
}, {
    2, 2, 2, 2, 2, 2, 1,
    4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1, 2,
    2, 2, 2, 2, 2, 1, 4,
    4, 4, 4, 4, 4, 1, 1,
    4, 4, 4, 4, 4, 4, 4,
    4, 4, 1, 1, 1
} };
#endif
