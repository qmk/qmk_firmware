/*
 * Copyright (C) 2022 Matt Chan
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "quantum.h"

/*
 * This diagram is based off the QK65 layout but without the blocker.
 *
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    ┌───────┐
 *              │00 │01 │02 │03 │04 │05 │06 │07 │08 │09 │0A │0B │0C │1D │0D │0E │    │0D     │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤    └─┬─────┤
 *              │10   │11 │12 │13 │14 │15 │16 │17 │18 │19 │1A │1B │1C │2C   │1E │      │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤   ┌──┴┐2D  │ ISO Enter
 *  LShift      │20    │21 │22 │23 │24 │25 │26 │27 │28 │29 │2A │2B │2D      │2E │   │2C │    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤ ┌─┴───┴────┤
 * │30      │   │30  │3C │31 │32 │33 │34 │35 │36 │37 │38 │39 │3A │3B    │3D │3E │ │3B        │ 2.75u Shift
 * └────────┘   ├────┼───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┴┬──┴──┬───┼───┼───┤ └──────────┘
 *              │40  │41  │42  │46                      │47   │49   │4C │4D │4E │
 *              └────┴────┴────┴────────────────────────┴─────┴─────┴───┴───┴───┘
 *              1.25u, 1.25u, 1.25u, 6.25u, 1.5u, 1.5u
 *
 *              ┌────┬────┬────┬────────────────────────┬───┬───┬───┐
 *              │40  │41  │42  │46                      │47 │48 │49 │
 *              └────┴────┴────┴────────────────────────┴───┴───┴───┘
 *              1.25u, 1.25u, 1.25u, 6.25u, 1u, 1u, 1u
 *
 *              ┌─────┬─────┬───────────────────────────┬───┬───┬───┐
 *              │40   │42   │46                         │47 │48 │49 │
 *              └─────┴─────┴───────────────────────────┴───┴───┴───┘
 *              1.5u, 1.5u, 7u, 1u, 1u, 1u
 *
 *              ┌─────┬─────┬───────────────────────────┬─────┬─────┐
 *              │40   │42   │46                         │47   │49   │
 *              └─────┴─────┴───────────────────────────┴─────┴─────┘
 *              1.5u, 1.5u, 7u, 1.5u, 1.5u
 */



#define LAYOUT_all( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K115, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213,       K215, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313,       K315, \
	K400, K401, K402,                   K406,             K409, K410, K411, K412, K413, K414  \
) { \
	{ K000,  K001,  K002,  K003,  K004,  K005,  K006,  K007,  K008,  K009,  K010,  K011,  K012,  K013,  K014,  K015 }, \
	{ K100,  K101,  K102,  K103,  K104,  K105,  K106,  K107,  K108,  K109,  K110,  K111,  K112,  K113,  KC_NO, K115 }, \
	{ K200,  K201,  K202,  K203,  K204,  K205,  K206,  K207,  K208,  K209,  K210,  K211,  K212,  K213,  KC_NO, K215 }, \
	{ K300,  K301,  K302,  K303,  K304,  K305,  K306,  K307,  K308,  K309,  K310,  K311,  K312,  K313,  KC_NO, K315 }, \
	{ K400,  K401,  K402,  KC_NO, KC_NO, KC_NO, K406,  KC_NO, KC_NO, K409,  K410,  K411,  K412,  K413,  K414,  KC_NO }  \
}
