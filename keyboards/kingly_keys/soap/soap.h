/* Copyright 2019 Garret G. (TheRoyalSweatshirt)
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
 * 
 * Note:  Matrix is a little wacky with the rotary encoder click mapping being
 * on the opposite side of the board.  Remember to pay attention to 
 * the 13th column where the lone key mapped for rotary encoder click (K132).
*/

#pragma once

#include "quantum.h"


#define LAYOUT( \
    K00, K01, K02, K03, \
    K10, K11, K12, K13 \
) { \
    { K00, K01, K02, K03 }, \
    { K10, K11, K12, K13 } \
}
