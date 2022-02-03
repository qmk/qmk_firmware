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
#define LAYOUT_96_ansi( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214,       K216, K217, K218, K219, \
    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314,       K316, K317, K318,       \
    K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414,       K416, K417, K418, K419, \
    K501,       K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513,       K515, K516, K517, K518,       \
    K601, K602, K603,                       K607,               K611, K612,       K614, K615, K616, K617, K618, K619  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K216, K217, K218, K219 }, \
    { K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K316, K317, K318, K419 }, \
    { K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, ____, K414, K416, K417, K418, ____ }, \
    { K501, ____, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513, K515, K516, K517, K518, K619 }, \
    { K601, K602, K603, ____, ____, K607, K115, ____, K612, ____, K611, K612, K614, K615, K616, K617, K618, ____ }  \
}

#define LAYOUT_96_iso( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214,       K216, K217, K218, K219, \
    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,             K316, K317, K318,       \
    K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414, K415, K416, K417, K418, K419, \
    K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513,       K515, K516, K517, K518,       \
    K601, K602, K603,                       K607,               K611, K612,       K614, K615, K616, K617, K618, K619  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K216, K217, K218, K219 }, \
    { K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, ____, K316, K317, K318, K419 }, \
    { K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K414, K415, K416, K417, K418, ____ }, \
    { K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513, K515, K516, K517, K518, K619 }, \
    { K601, K602, K603, ____, ____, K607, K115, ____, K612, ____, K611, K612, K614, K615, K616, K617, K618, ____ }  \
}

#define LAYOUT_all( \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, K116, K117, K118, K119, \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K215, K216, K217, K218, K219, \
    K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314,       K316, K317, K318, K319, \
    K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,       K414, K415, K416, K417, K418, K419, \
    K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513,       K515, K516, K517, K518, K519, \
    K601, K602, K603,                       K607,               K611, K612,       K614, K615, K616, K617, K618, K619  \
) { \
    { K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K116, K117, K118, K119 }, \
    { K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, K216, K217, K218, K219 }, \
    { K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K316, K317, K318, K319 }, \
    { K401, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K414, K415, K416, K417, K418, K419 }, \
    { K501, K502, K503, K504, K505, K506, K507, K508, K509, K510, K511, K512, K513, K515, K516, K517, K518, K519 }, \
    { K601, K602, K603, K215, ____, K607, K115, ____, K612, K215, K611, ____, K614, K615, K616, K617, K618, K619 }  \
}
