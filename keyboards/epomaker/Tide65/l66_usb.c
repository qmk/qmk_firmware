/* Copyright (C) 2023 Hangsheng Technology Corp., Ltd
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

#include QMK_KEYBOARD_H

#ifdef RGB_MATRIX_ENABLE

// clang-format off

#undef ___
#define ___ NO_LED

led_config_t g_led_config = {
    LAYOUT(
        10,	11,	12,	13,	14,	15,	16,	17,	18,	19,	20,	21,	22,	23,___,	
        9,	43,	42,	41,	40,	39,	38,	37,	36,	35,	34,	33,	32,	31,	24,
        8,	44,	45,	46,	47,	48,	49,	50,	51,	52,	53,	54,		30,	25,
        7,	68,	67,	66,	65,	64,	63,	62,	61,	60,		59,	55,	29,	26,
        6,	5,	4,	3,	2,	1,	0,			58,		57,	56,	28,	27

    ), {
    { 96 , 64 }, // 0
    { 64 , 64 }, // 1
    { 80 ,  64 }, // 2
    { 48 ,  64 }, // 3
    { 32 ,  64 }, // 4
    { 16 ,  64 }, // 5
    { 0 ,  64 }, // 6
    { 0 ,  48 }, // 7
    {  0 ,  32 }, // 8
    {  0 ,  16 }, // 9
    {  0 ,  0 }, // 10
    {  16 ,  0 }, // 11
    { 32 ,  0 }, // 12
    {  48 ,  0 }, // 13
    {  64 ,  0 }, // 14

    {   80 ,  0 }, // 15
    {   96 , 0 }, // 16
    {  112 , 0 }, // 17
    {  128 , 0 }, // 18
    {  144 , 0 }, // 19
    {  160 , 0 }, // 20
    {  176 , 0 }, // 21
    {  192 , 0 }, // 22
    { 208 , 0 }, // 23
    { 224 , 16 }, // 24
    { 224 , 32 }, // 25
    { 224 , 48 }, // 26
    { 224 , 64 }, // 27
    { 208 , 64 }, // 28
    { 208 , 48 }, // 29

    { 208 , 32 }, // 30
    { 208 , 16 }, // 31
    { 192 , 16 }, // 32
    { 176 , 16 }, // 33
    { 160 , 16 }, // 34
    { 144 , 16 }, // 35
    {  128 , 16 }, // 36
    {  112 , 16 }, // 37
    {  96 , 16 }, // 38
    {  80 , 16 }, // 39
    {  64 , 16 }, // 40
    {  48 , 16 }, // 41

    {   32 , 16 }, // 42
    {   16 , 16 }, // 43
    {  16 , 32 }, // 44
    {  32 , 32 }, // 45
    {  48 , 32 }, // 46
    {  64 , 32 }, // 47
    {  80 , 32 }, // 48
    {  96 , 32 }, // 49
    { 112 , 32 }, // 50
    { 128 , 32 }, // 51
    { 144 , 32 }, // 52
    { 160 , 32 }, // 53
    { 176 , 32 }, // 54
    { 192 , 48 }, // 55

    { 192 , 48 }, // 56
    { 176 , 64 }, // 57
    { 144 , 64 }, // 58
    { 176 , 64 }, // 59
    { 144 , 48 }, // 60
    { 128 , 48 }, // 61
    {  112 , 48 }, // 62
    {  96 , 48 }, // 63
    {  80 , 48 }, // 64
    {   64 , 48 }, // 65
    {  48 , 48 }, // 66
    {   32 , 48 }, // 67
    {  16 , 48 }, // 68  
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4,       4,    4, 4, 4, 4
}};

// clang-format on
#endif
