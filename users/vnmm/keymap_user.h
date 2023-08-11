/* Copyright 2021
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

#ifdef DYNAMIC_KEYMAP_LAYER_COUNT
#undef DYNAMIC_KEYMAP_LAYER_COUNT
#endif
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

#define WIN_F MO(WIN_FN)
#define MAC_F MO(MAC_FN)
#define EXT_F MO(EXTRA_FN)

#define DF_WIN DF(WIN_BASE)
#define DF_MAC DF(MAC_BASE)

// clang-format off

enum layers {
    WIN_BASE,
    MAC_BASE,
    WIN_FN,
    MAC_FN,
    EXTRA_FN
};

// clang-format on
