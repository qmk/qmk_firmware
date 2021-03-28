/* Copyright 2019 zvecr<git@zvecr.com>
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
#define LAYOUT_alice_split_bs( \
  K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
  K100, K101, K102, K103, K104, K105, K106,       K108, K109, K110, K111, K112, K113, K114, K115, \
  K200, K201, K202, K203, K204, K205, K206,       K208, K209, K210, K211, K212, K213,      K215,  \
        K301, K302, K303, K304, K305, K306,       K308, K309, K310, K311, K312, K313, K314, K315, \
        K401,       K403,       K405, K406,             K409,       K411,                K414 \
) \
{ \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015}, \
    { K100, K101, K102, K103, K104, K105, K106, ____, K108, K109, K110, K111, K112, K113, K114, K115}, \
    { K200, K201, K202, K203, K204, K205, K206, ____, K208, K209, K210, K211, K212, K213, ____, K215}, \
    { ____, K301, K302, K303, K304, K305, K306, ____, K308, K309, K310, K311, K312, K313, K314, K315}, \
    { ____, K401, ____, K403, ____, K405, K406, ____, ____, K409, ____, K411, ____, ____, K414, ____}, \
}

#define LAYOUT_alice( \
  K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,       K015, \
  K100, K101, K102, K103, K104, K105, K106,       K108, K109, K110, K111, K112, K113, K114, K115, \
  K200, K201, K202, K203, K204, K205, K206,       K208, K209, K210, K211, K212, K213,      K215,  \
        K301, K302, K303, K304, K305, K306,       K308, K309, K310, K311, K312, K313, K314, K315, \
        K401,       K403,       K405, K406,             K409,       K411,                K414 \
) \
{ \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, ____, K015}, \
    { K100, K101, K102, K103, K104, K105, K106, ____, K108, K109, K110, K111, K112, K113, K114, K115}, \
    { K200, K201, K202, K203, K204, K205, K206, ____, K208, K209, K210, K211, K212, K213, ____, K215}, \
    { ____, K301, K302, K303, K304, K305, K306, ____, K308, K309, K310, K311, K312, K313, K314, K315}, \
    { ____, K401, ____, K403, ____, K405, K406, ____, ____, K409, ____, K411, ____, ____, K414, ____}, \
}

#define LAYOUT_default LAYOUT_alice_split_bs
