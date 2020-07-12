/* Copyright 2020 B. Fletcher (toraifu) <typefast@kyaa.gg>
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

/* All keys in matrix active: 
 * - Split Backspace
 * - Split Right Shift
 */
#define LAYOUT_all( \
    K100,   K000, K001, K002, K003, K004, K005, K006,       K007, K008, K009, K010, K011, K012, K013, K014, \
    K200,   K101, K102, K103, K104, K105, K106,       K107, K108, K109, K110, K111, K112, K113, K114, \
    K300,   K201, K202, K203, K204, K205, K206,       K207, K208, K209, K210, K211, K212,       K214, \
            K301, K302, K303, K304, K305, K306,       K307, K308, K309, K310, K311, K312, K313, K314, \
            K401,       K403,       K405, K406,             K408,       K410,                   K414  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314 }, \
    { KC_NO, K401,  KC_NO, K403,  KC_NO, K405,  K406,  KC_NO, K408,  KC_NO, K410,  KC_NO, KC_NO, KC_NO, K414 }  \
}

/* Disable position 013 and 314 for:
 * - Full size Backspace
 * - Full size Right Shift
 */
#define LAYOUT_default( \
    K100,   K000, K001, K002, K003, K004, K005, K006,       K007, K008, K009, K010, K011, K012,       K014, \
    K200,   K101, K102, K103, K104, K105, K106,       K107, K108, K109, K110, K111, K112, K113, K114, \
    K300,   K201, K202, K203, K204, K205, K206,       K207, K208, K209, K210, K211, K212,       K214, \
            K301, K302, K303, K304, K305, K306,       K307, K308, K309, K310, K311, K312, K313, K314, \
            K401,       K403,       K405, K406,             K408,       K410,                   K414  \
) { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  KC_NO, K014 }, \
    { K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  KC_NO, K214 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  K314 }, \
    { KC_NO, K401,  KC_NO, K403,  KC_NO, K405,  K406,  KC_NO, K408,  KC_NO, K410,  KC_NO, KC_NO, KC_NO, K414 }  \
}
