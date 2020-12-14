/* Copyright 2019 @haswellep
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

#define AUTO_SHIFT_TIMEOUT 190
#define TAPPING_TERM 200    // TapからHoldに切り替わるまでの押下時間(ms)。デフォルト値は200。
#define PERMISSIVE_HOLD     // TAPPING_TERM経過前に他のキーを押すと、Holdとして扱われるようになる。キーの同時押しが速い ひとにおすすめ。
//#define RETRO_TAPPING       // TAPPING_TERMを経過しても、他のキーを押していなければTapとして扱われるようになる。
                            // TAPPING_TERMが短くてTapのつもりがHold扱いになってしまう場合の対策になるが、好み次第。
                            // TAPPING_TERMを500以上に設定していると、自動的に有効になる。
//#define TAPPING_FORCE_HOLD  // Mod Tap keyをTap後にすぐにHoldしたときに、Holdとして扱われるようになる
//#define IGNORE_MOD_TAP_INTERRUPT    // Mod Tap keyと通常キーを連続して高速に押したとき、両方のキーをTapとして扱うよう になる。



#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 8
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF



/*
#define LED_LAYOUT( \
    L01, L02, L03, L04, L05, L06,              R01, R02, R03, R04, R05, R06, R28, R07, R35, \
    L07, L08, L09, L10, L11, L12,              R08, R09, R10, R11, R12, R13, R34, R14, \
    L13, L14, L15, L16, L17, L18,              R15, R16, R17, R18, R19, R20, R21,  \
    L19, L20, L21, L22, L23, L24, L25,    R22, R23, R24, R25, R26, R27,        R29, \
                   L26, L27, L28, L29,    R30, R31, R32, R33                      \
    ) \
    { \
        L19, L13, L07,L07,L01,\
        L02,L08,L14,L20,\
        L21,L15,L09,L03, \
        L04,L10,L16,L22,L26,\
        L27,L23,L17,L11,L05, \
        L06, L12,L18,L24,L28,\
        L29,L25,\
        R22,R30, \
        R31,R23, R15,R08,R01,\
        R02,R09,R16,R24, R32,\
        R33,R25,R17,R10, R03,\
        R04,R11,R18,R26,\
        R27,R19,R12,R05,\
        R06,R13,R20,\
        R29,R21,R34,R28,\
        R07,R14,R35 \
    }

#define RGBLIGHT_LED_MAP LED_LAYOUT( \
    01, 02, 03, 04, 05, 06,               7, 8, 9, 10, 11, 12, 13, 14, 15,\
    16, 17, 18, 19, 20, 21,              22, 23, 24, 25, 26, 27, 28, 29,\
    30, 31, 32, 33, 34, 35,              36, 37, 38, 39, 40, 41,     42, \
    43, 44, 45, 46, 47, 48, 49,          50, 51, 52, 53, 54, 55,     56, \
                57, 58, 59, 60,      61, 62, 63, 64                    \
)
*/

/*
#define RGBLIGHT_LED_MAP ( \
0	, 1	, 2	, 3	,4 	, 5	, 6	, 7 	, 8	, 9	,\
20	, 21	, 22	, 23	, 24	, 25	, 26	, 27	, 28	, 29	,\
30	, 31	, 32	, 33	, 34	, 35	, 36	, 37	, 38	, 39	,\
40	, 41	, 42	, 43	, 44	, 45	, 46	, 47	, 48	, 49	,\
50	, 51	, 52	, 53	, 54	, 55	, 56	, 57	, 58	, 59	,\
60	, 61	, 62	,  63	\
)
*/
