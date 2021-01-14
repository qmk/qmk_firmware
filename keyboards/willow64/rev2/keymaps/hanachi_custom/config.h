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

#define AUTO_SHIFT_TIMEOUT 170
#define TAPPING_TERM 120    // TapからHoldに切り替わるまでの押下時間(ms)。デフォルト値は200。
#define PERMISSIVE_HOLD     // TAPPING_TERM経過前に他のキーを押すと、Holdとして扱われるようになる。キーの同時押しが速い ひとにおすすめ。
//#define RETRO_TAPPING       // TAPPING_TERMを経過しても、他のキーを押していなければTapとして扱われるようになる。
                            // TAPPING_TERMが短くてTapのつもりがHold扱いになってしまう場合の対策になるが、好み次第。
                            // TAPPING_TERMを500以上に設定していると、自動的に有効になる。
//#define TAPPING_FORCE_HOLD  // Mod Tap keyをTap後にすぐにHoldしたときに、Holdとして扱われるようになる
//#define IGNORE_MOD_TAP_INTERRUPT    // Mod Tap keyと通常キーを連続して高速に押したとき、両方のキーをTapとして扱うよう になる。


#define RGBLIGHT_LAYERS
#define RGBLIGHT_MAX_LAYERS 8
#define RGBLIGHT_LAYERS_OVERRIDE_RGB_OFF

/* LED POSITION
    03, 04, 11, 12, 21, 22,            35, 36, 45, 46, 53, 54, 60, 61, 63, \
    02, 05, 10, 13, 20, 23,            34, 37, 44, 47, 52, 55, 59,   62,   \
    01, 06, 09, 14, 19, 24,            33, 38, 43, 48, 51, 56,       58,   \
    00, 07, 08, 15, 18, 25, 28,    29, 32, 39, 42, 49, 50,           57,   \
                16, 17, 26, 27,    30, 31, 40, 41                          \
*/

