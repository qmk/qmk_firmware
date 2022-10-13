/* Copyright 2020 zvecr <git@zvecr.com>
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

/*
 *                                          optional encoder (404│406)
 *                                                             \   /
 * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───────┬───┐
 * │000│001│002│003│004│005│006│007│008│009│010│011│012│013    │014│
 * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┼───┤
 * │100  │101│102│103│104│105│106│107│108│109│110│111│112│113  │114│
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤
 * │200   │201│202│203│204│205│206│207│208│209│210│211│213     │214│
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤
 * │300     │301│302│303│304│305│306│307│308│309│310│312   │313│314│
 * ├────┬───┴┬──┴─┬─┴───┴──┬┴───┴─┬─┴───┴──┬┴───┼───┴┬─┬───┼───┼───┤
 * │400 │401 │402 │403     │405   │407     │409 │410 │ │412│413│414│
 * └────┴────┴────┴────────┴──────┴────────┴────┴────┘ └───┴───┴───┘
 * ┌────┬────┬────┬────────────────────────┬────┬────┐
 * │400 │401 │402 │405                     │409 │410 │ Standard
 * └────┴────┴────┴────────────────────────┴────┴────┘
 */

#define LAYOUT_all( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013,   K404, K014, K406, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213, K214, \
    K300,       K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K312, K313, K314, \
    K400, K401, K402,             K403, K405, K407,       K409, K410,       K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, ____, K213, K214 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, ____, K312, K313, K314 }, \
    { K400, K401, K402, K403, K404, K405, K406, K407, ____, K409, K410, ____, K412, K413, K414 }  \
}

#define LAYOUT( \
	K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, \
	K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
	K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,       K213, K214, \
	K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310,       K312, K313, K314, \
	K400, K401, K402, K403, K404, K405, K406, K407,       K409, K410,       K412, K413, K414  \
) { \
	{ K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
	{ K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
	{ K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, ____, K213, K214 }, \
	{ K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, ____, K312, K313, K314 }, \
	{ K400, K401, K402, K403, K404, K405, K406, K407, ____, K409, K410, ____, K412, K413, K414 }  \
}



#ifdef RGB_MATRIX_ENABLE
#   define URGB_K KC_F24
#else
#   define URGB_K KC_TRNS
#endif

#define LOCK_GUI KC_F23
