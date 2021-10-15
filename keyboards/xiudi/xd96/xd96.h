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
    { KC_##K101, KC_##K102, KC_##K103, KC_##K104, KC_##K105, KC_##K106, KC_##K107, KC_##K108, KC_##K109, KC_##K110, KC_##K111, KC_##K112, KC_##K113, KC_##K114, KC_##K116, KC_##K117, KC_##K118, KC_##K119 }, \
    { KC_##K201, KC_##K202, KC_##K203, KC_##K204, KC_##K205, KC_##K206, KC_##K207, KC_##K208, KC_##K209, KC_##K210, KC_##K211, KC_##K212, KC_##K213, KC_##K214, KC_##K216, KC_##K217, KC_##K218, KC_##K219 }, \
    { KC_##K301, KC_##K302, KC_##K303, KC_##K304, KC_##K305, KC_##K306, KC_##K307, KC_##K308, KC_##K309, KC_##K310, KC_##K311, KC_##K312, KC_##K313, KC_##K314, KC_##K316, KC_##K317, KC_##K318, KC_##K419 }, \
    { KC_##K401, KC_##K402, KC_##K403, KC_##K404, KC_##K405, KC_##K406, KC_##K407, KC_##K408, KC_##K409, KC_##K410, KC_##K411, KC_##K412,      ____, KC_##K414, KC_##K416, KC_##K417, KC_##K418,      ____ }, \
    { KC_##K501,      ____, KC_##K503, KC_##K504, KC_##K505, KC_##K506, KC_##K507, KC_##K508, KC_##K509, KC_##K510, KC_##K511, KC_##K512, KC_##K513, KC_##K515, KC_##K516, KC_##K517, KC_##K518, KC_##K619 }, \
    { KC_##K601, KC_##K602, KC_##K603,      ____,      ____, KC_##K607, KC_##K611, KC_##K611, KC_##K612,      ____, KC_##K611, KC_##K612, KC_##K614, KC_##K615, KC_##K616, KC_##K617, KC_##K618,      ____ }  \
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
