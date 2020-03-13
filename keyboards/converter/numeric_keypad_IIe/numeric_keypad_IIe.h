/* Copyright Adam Newbold <adam@neatnik.net>
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

#define LAYOUT( \
    K_ESC,   K_7, K_8,     K_9,   K_LEFT_PARENS, K_RIGHT_PARENS, \
    K_LEFT,  K_4, K_5,     K_6,   K_MINUS,       K_DIVIDE,       \
    K_RIGHT, K_1, K_2,     K_3,   K_PLUS,        K_MULTIPLY,     \
    K_SPACE, K_0, K_COMMA, K_DOT, K_RETURN,      K_PRINT         \
){ \
    { K_RIGHT_PARENS, K_ESC,   K_4,           K_5,     K_6,      K_7     },\
    { K_DIVIDE,       K_LEFT,  K_0,           K_1,     K_2,      K_3     },\
    { K_PRINT,        K_SPACE, K_LEFT_PARENS, K_MINUS, K_RETURN, K_COMMA },\
    { K_MULTIPLY,     K_RIGHT, K_8,           K_9,     K_DOT,    K_PLUS  },\
}
