/* Copyright 2018 Jason Williams (Wilba)
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

// Right switch of split backspace is at 2,13 and is the only switch
// whose physical position doesn't match switch matrix position :-(
// However, it also makes no sense to view the physical as 16 columns,
// so the numbering goes 00 to 14. Deal with it.
//
// 0,15 exists on PCB but is blocked by the 7V blocker so until someone
// designs a case that uses it, we can just forget it exists.

#define LAYOUT_all( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014,       \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       K215, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,             K315, \
    K400, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412,             K413,       \
    K500, K501, K502,                   K506,                   K510, K511,       K512, K513, K515  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, ____, K014, ____ }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, K115 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, ____, K215 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, ____, ____, K315 }, \
    { K400, ____, K402, K403, K404, K405, K406, K407, K408, K409, K410, K411, K412, K413, ____, ____ }, \
    { K500, K501, K502, ____, ____, ____, K506, ____, ____, ____, K510, K511, K512, K513, ____, K515 }  \
}

