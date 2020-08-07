/*
Copyright 2020 rupa <rupa@lrrr.us> @rupa

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "unicode.h"

#if defined(UNICODEMAP_ENABLE)
const uint32_t PROGMEM unicode_map[] = {
    [CHEK] = 0x2713, // ✓
    /*
    [DI1]  = 0x2680, // ⚀
    [DI2]  = 0x2681, // ⚁
    [DI3]  = 0x2682, // ⚂
    [DI4]  = 0x2683, // ⚃
    [DI5]  = 0x2684, // ⚄
    [DI6]  = 0x2685, // ⚅
    */
    [HAS]  = 0x262D, // ☭
    [IBNG] = 0x203D, // ‽
    [IRNY] = 0x2E2E, // ⸮
    [M4]   = 0x2669, // ♩
    [M8]   = 0x266A, // ♪
    [M8B]  = 0x266B, // ♫
    [M16]  = 0x266C, // ♬
    [OM]   = 0x0950, // ॐ
    [STB]  = 0x2605, // ★
    [STW]  = 0x2606, // ☆
};
#endif
