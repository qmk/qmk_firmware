/* Copyright 2021 peepeetee
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

#include "bm80.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
	{ 0,  1, 2,  3,  4,  5,  NO_LED, 6,  7,  8,  9,  10,  11,  12,  13,  14,  15 },
	{ 16,  17,  18,  19,  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32 },
	{ 33,  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49 },
	{ 51,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61,  62,  63,  64,  NO_LED, NO_LED, NO_LED },
	{ 65,  66,  67,  68,  69,  70,  71,  72,  73,  74,  75,  NO_LED, 76,  NO_LED, NO_LED, 77,  NO_LED },
	{ 78,  79,  80,  NO_LED, NO_LED, 81,  NO_LED, NO_LED, NO_LED, 82,  83,  84,  85,  86,  NO_LED, 87,  88 }
}, {
    // LED Index to Physical Position
    {   7,   5 }, {  31,   5 }, {  43,   5 }, {  55,   5 }, {  67,   5 }, {  85,   5 }, {  97,   5 }, { 109,   5 }, { 121,   5 }, { 139,   5 }, { 151,   5 }, { 163,   5 }, { 175,   5 }, { 193,   5 }, { 205,   5 }, { 217,   5 },
    {   7,  20 }, {  19,  20 }, {  31,  20 }, {  43,  20 }, {  55,  20 }, {  67,  20 }, {  79,  20 }, {  91,  20 }, { 103,  20 }, { 115,  20 }, { 127,  20 }, { 139,  20 }, { 151,  20 }, { 169,  20 }, { 193,  20 }, { 205,  20 }, { 217,  20 },
    {  10,  30 }, {  25,  30 }, {  37,  30 }, {  49,  30 }, {  61,  30 }, {  73,  30 }, {  85,  30 }, {  97,  30 }, { 109,  30 }, { 121,  30 }, { 133,  30 }, { 145,  30 }, { 157,  30 }, { 172,  30 }, { 193,  30 }, { 205,  30 }, { 217,  30 },
    {  3,  39 },
    {  11,  39 }, {  28,  39 }, {  40,  39 }, {  52,  39 }, {  64,  39 }, {  76,  39 }, {  88,  39 }, { 100,  39 }, { 112,  39 }, { 124,  39 }, { 136,  39 }, { 148,  39 }, { 168,  39 },
    {  14,  49 }, {  34,  49 }, {  46,  49 }, {  58,  49 }, {  70,  49 }, {  82,  49 }, {  94,  49 }, { 106,  49 }, { 118,  49 }, { 130,  49 }, { 142,  49 }, { 165,  49 }, { 205,  49 },
    {   8,  59 }, {  23,  59 }, {  38,  59 }, {  83,  59 }, { 129,  59 }, { 144,  59 }, { 159,  59 }, { 174,  59 }, { 193,  59 }, { 205,  59 }, { 217,  59 }
}, {
    // LED Index to Flag
    1, 4, 4, 4, 4, 1, 1, 1, 1, 4, 4, 4, 4, 1, 9, 1,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1, 1, 1,
    8,
    9, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,          1,
    1, 1, 1, 4, 1, 1, 1, 1,                    1, 1, 1
} };

/*
HAS_FLAGS(bits, flags)
n/a
Evaluates to true if bits has all flags set
HAS_ANY_FLAGS(bits, flags)
n/a
Evaluates to true if bits has any flags set
LED_FLAG_NONE
0x00
If this LED has no flags
LED_FLAG_ALL
0xFF
If this LED has all flags
LED_FLAG_MODIFIER
0x01
If the LED is on a modifier key
LED_FLAG_UNDERGLOW
0x02
If the LED is for underglow
LED_FLAG_KEYLIGHT
0x04
If the LED is for key backlight
LED_FLAG_INDICATOR
0x08
If the LED is for keyboard state indication
*/
#endif
