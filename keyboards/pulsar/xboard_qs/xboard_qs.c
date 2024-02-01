/* Copyright 2024 Aplusx Inc.
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

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    return process_record_user(keycode, record);
}

void keyboard_pre_init_kb(void) {
    keyboard_pre_init_user();
}

void keyboard_post_init_kb(void) {
    keyboard_post_init_user();
}

void suspend_wakeup_init_kb(void) { // code will run on keyboard wakeup
    clear_keyboard();
}

#ifdef RGB_MATRIX_ENABLE
#define ___ NO_LED
led_config_t g_led_config = {    // 상단에 21개의 더미 LED 추가 됨
    {   { 37, 36, 35,  34,  33,  32,  31,  30,   29,  28,  27,  26,  25,  23,  22,  21 },
        { 38, 39, 40,  41,  42,  43,  44,  45,   46,  47,  48,  49,  50, ___,  51,  54 },
        { 71, 70, 69,  68,  67,  66,  65,  64,   63,  62,  61,  60,  59,  58,  52,  53 },
        { 72, 73, 74,  75,  76,  77,  78,  79,   80,  81,  82,  83, ___,  57,  56,  55 },
        { 97,___, 96,  95,  94,  93,  92,  91,   90,  89,  88,  87, ___,  86,  84,  85 },
        { 98, 99,100, ___, ___, ___, 102, ___,  ___, ___, 104, 105, 106, 107, 108, 109 },
        { 24,16, 17, 19, ___, ___, ___, ___,  ___, ___, ___, ___, ___, ___, ___, 110 },
        {___,___,___, ___, ___, ___, ___, ___,  ___, ___, ___, ___, ___, ___, ___, ___ }
    },
    {   // LED Index to Physical Position  상단에 21개 데코LED 추가, 1줄 더 추가됨, ANSI만 지원
        {0,0}, {9,0}, {18,0}, {27,0}, {36,0}, {45,0}, {54,0}, {63,0}, {72,0}, {81,0}, {90,0}, {99,0}, {108,0}, {117,0}, {126,0}, {135,0}, {144,0}, {153,0}, {162,0}, {171,0}, {180,0},
        {180,11}, {169,11}, {159,11},       {144,11},  {133,11}, {123,11}, {112,11}, {102,11}, {89,11}, {78,11},  {68,11}, {57,11}, {45,11}, {34,11}, {24,11}, {13,11},    {0,11},    
        {0,21}, {10,21}, {21,21}, {31,21}, {42,21}, {52,21}, {63,21}, {73,21}, {83,21}, {94,21}, {104,21}, {115,21}, {125,21},    {139,21},          {159,21}, {169,21}, {180,21},    
        {180,32}, {169,32}, {159,32},       {143,32}, {130,32}, {120,32},  {109,32}, {99,32}, {89,32}, {78,32}, {68,32}, {57,32}, {47,32},  {36,32}, {26,32}, {16,32}, {3,32},                   
        {4,43}, {18,43}, {29,43}, {39,43}, {50,43}, {60,43}, {70,43}, {81,43}, {91,43}, {102,43}, {112,43}, {123,43},           {138,43},                                             
                {169,53},                   {135,53}, {117,53},  {107,53},  {96,53},    {86,53},  {76,53},  {65,53},   {55,53},  {44,53},  {34,53}, {23,53}, {10,53},
        {1,64}, {14,64}, {27,64},                    {50,64},{66,64},{80,64},                 {105,64}, {118,64}, {131,64}, {145,64},                {159,64}, {169,64}, {180,64},        
    },
    {   // RGB LED Index to Flag
        1, 1, 1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1, 1, 1,   1,   4, 4, 4, 4,   1, 1, 1, 1,    4, 4, 4, 4,    1, 
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,    1, 1, 1,
        1, 1, 1,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,   1,             
        1,    1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    1,   
        1, 1, 1,     4,4,4,     1, 1, 1, 1,    1, 1, 1
    }
};
#endif
