/* 
/ Copyright 2022 quarkeys
/ This program is free software: you can redistribute it and/or modify
/ it under the terms of the GNU General Public License as published by
/ the Free Software Foundation, either version 2 of the License, or
/ (at your option) any later version.
/ This program is distributed in the hope that it will be useful,
/ but WITHOUT ANY WARRANTY; without even the implied warranty of
/ MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
/ GNU General Public License for more details.
/ You should have received a copy of the GNU General Public License
/ along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#pragma once
#include "quantum.h"
#define XXXX KC_NO

/*
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐      ┌───────┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │0D │0E │      │0D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤      └─┬─────┤
 *              │11   │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │1D │1E   │        │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤     ┌──┴┐2E  │ ISO Enter
 *  LShift      │21    │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2C │2E      │     │2D │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤   ┌─┴───┴────┤
 * │30      │   │30  │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B │3C    │3D │   │3C        │ 2.75u RShift
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬┴───┤   └──────────┘
 *              │40  │41  │43  │46                      │4A  │4B  │4C  │4D  │
 *              └────┴────┴────┴────────────────────────┴────┴────┴────┴────┘
 *              ┌─────┬───┬─────┬───────────────────────────┬─────┬───┬─────┐
 *              │40   │41 │43   │46                         │4B   │4C │4D   │ Tsangan/WKL/HHKB
 *              └─────┴───┴─────┴───────────────────────────┴─────┴───┴─────┘
 */

#define LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014,					\
	      K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,	 				\
	      K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214, 					\
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, 						\
	K400, K401,       K403,             K406,                   K410, K411, K412, K413  						\
)  { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
	{ XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
	{ XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  XXXX }, \
	{ K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  K410,  K411,  K412,  K413,  XXXX }  \
}

#define LAYOUT_60_ansi( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,                         \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,                         \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214,                         \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K312,                         \
    K400, K401,       K403,             K406,                   K410, K411, K412, K413                          \
)  { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  XXXX }, \
    { XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  XXXX,  K214 }, \
    { K300,  XXXX,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  XXXX,  XXXX }, \
    { K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  K410,  K411,  K412,  K413,  XXXX }  \
}

#define LAYOUT_60_ansi_split_bs_rshift( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014,                   \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,                         \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214,                         \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,                         \
    K400, K401,       K403,             K406,                   K410, K411, K412, K413                          \
)  { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
    { XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  XXXX,  K214 }, \
    { K300,  XXXX,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  XXXX }, \
    { K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  K410,  K411,  K412,  K413,  XXXX }  \
}

#define LAYOUT_60_ansi_tsangan( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,                         \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114,                         \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214,                         \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K312,                         \
    K400, K401,       K403,             K406,                         K411, K412, K413                          \
)  { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  XXXX }, \
    { XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  K114 }, \
    { XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  XXXX,  K214 }, \
    { K300,  XXXX,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  XXXX,  XXXX }, \
    { K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  XXXX,  K411,  K412,  K413,  XXXX }  \
}

#define LAYOUT_60_iso( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,                         \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,                               \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214,                         \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311,       K312,                         \
    K400, K401,       K403,             K406,                   K410, K411, K412, K413                          \
)  { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  XXXX }, \
    { XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  XXXX }, \
    { XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  XXXX,  XXXX }, \
    { K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  K410,  K411,  K412,  K413,  XXXX }  \
}

#define LAYOUT_60_iso_split_bs_rshift( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014,                   \
    K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,                               \
    K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214,                         \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,                         \
    K400, K401,       K403,             K406,                   K410, K411, K412, K413                          \
)  { \
    { K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014 }, \
    { XXXX,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  XXXX }, \
    { XXXX,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  K214 }, \
    { K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  XXXX }, \
    { K400,  K401,  XXXX,  K403,  XXXX,  XXXX,  K406,  XXXX,  XXXX,  XXXX,  K410,  K411,  K412,  K413,  XXXX }  \
}
