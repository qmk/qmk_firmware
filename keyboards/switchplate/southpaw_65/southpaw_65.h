/* Copyright 2019
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
#define ____ KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT_ansi( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219, \
    K301, K302, K303,       K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316,       K318, K319, \
    K401, K402, K403, K404, K405,       K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419, \
    K501,       K503,       K505, K506, K507,                K510,                K515, K516, K513, K517, K518, K519  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 }, \
    { K301, K302, K303, ____, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, ____, K318, K319 }, \
    { K401, K402, K403, K404, K405, ____, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419 }, \
    { K501, ____, K503, ____, K505, K506, K507, ____, ____, K510, ____, ____, K513, ____, K515, K516, K517, K518, K519 }  \
}

#define LAYOUT_ansi2( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219, \
    K301, K302, K303,       K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316,       K318, K319, \
    K401, K402, K403, K404, K405,       K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419, \
    K501,       K503,       K505, K506, K507,                K510,                K515,       K513, K517, K518, K519  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219 }, \
    { K301, K302, K303, ____, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, ____, K318, K319 }, \
    { K401, K402, K403, K404, K405, ____, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419 }, \
    { K501, ____, K503, ____, K505, K506, K507, ____, ____, K510, ____, ____, K513, ____, K515, ____, K517, K518, K519 }  \
}

#define LAYOUT_iso( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217,       K219, \
    K301, K302, K303,       K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, K319, \
    K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419, \
    K501,       K503,       K505, K506, K507,                K510,                K515, K516, K513, K517, K518, K519  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, ____, K219 }, \
    { K301, K302, K303, ____, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, K319 }, \
    { K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419 }, \
    { K501, ____, K503, ____, K505, K506, K507, ____, ____, K510, ____, ____, K513, ____, K515, K516, K517, K518, K519 }  \
}

#define LAYOUT_iso2( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217,       K219, \
    K301, K302, K303,       K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, K319, \
    K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419, \
    K501,       K503,       K505, K506, K507,                K510,                K515,       K513, K517, K518, K519  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, ____, K219 }, \
    { K301, K302, K303, ____, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, K316, K317, K318, K319 }, \
    { K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, K414, K415, K416, K417, K418, K419 }, \
    { K501, ____, K503, ____, K505, K506, K507, ____, ____, K510, ____, ____, K513, ____, K515, ____, K517, K518, K519 }  \
}
