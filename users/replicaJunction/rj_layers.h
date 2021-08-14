/* Copyright 2021 Joshua T.
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

enum rj_layers {
    L_BASE,

#ifdef USER_INCLUDE_QWERTY
    L_QWERTY,
#endif

#ifdef USER_INCLUDE_GAMING_LAYER
    L_GAMING,
#endif

    L_NUMBERS,
    L_SYMBOLS,
    L_NAVIGATION,
    L_FN,

#ifdef USER_INCLUDE_MACRO_LAYER
    L_MACROS,
#endif

    _LAYER_SAFE_RANGE
};
