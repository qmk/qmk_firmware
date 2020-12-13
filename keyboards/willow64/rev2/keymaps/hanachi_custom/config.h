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

