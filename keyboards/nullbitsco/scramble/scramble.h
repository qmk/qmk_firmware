/* Copyright 2021 Jay Greco
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

#include "quantum.h"

#if defined(KEYBOARD_nullbitsco_scramble_v1)
  #include "v1.h"
#elif defined(KEYBOARD_nullbitsco_scramble_v2)
  #include "v2.h"
#endif

// Layout is the same in all revisions
#define LAYOUT( \
    K01, K02, K03, \
    K11, K12, K13  \
) { \
   {K01, K02, K03}, \
   {K11, K12, K13}, \
}
