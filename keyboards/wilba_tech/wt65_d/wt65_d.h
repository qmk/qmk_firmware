// Copyright 2022 Jason Williams (@wilba)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

#define ____ KC_NO

/*
 *              ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┐    ┌───────┐
 *              │000│003│002│001│004│005│006│007│008│009│012│011│010│013│213│014│    │013    │ 2u Backspace
 *              ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┼───┤    └─┬─────┤
 *              │100  │101│102│103│104│105│106│107│108│109│110│111│112│113  │114│      │     │
 *  2.25u       ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┼───┤   ┌──┴┐113 │ ISO Enter
 *  LShift      │200   │201│202│203│204│205│206│207│208│209│210│211│212     │214│   │212│    │
 * ┌────────┐   ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┼───┤   └───┴────┘
 * │300     │   │300 │301│302│303│304│305│306│307│308│309│310│311│312   │313│314│
 * └────────┘   ├────┼───┼───┴┬──┴───┴───┴───┴───┴───┴┬──┴─┬─┴─┬─┴──┬───┼───┼───┤
 *              │400 │401│402 │403                    │409 │410│411 │412│413│414│
 *              └────┴───┴────┴───────────────────────┴────┴───┴────┴───┴───┴───┘
 *              ┌─────┬─────┬───────────────────────────┬─────┬─────┐
 *              │400  │402  │403                        │409  │411  │ WKL
 *              └─────┴─────┴───────────────────────────┴─────┴─────┘
 */

#define LAYOUT_all( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K213, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,             K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K313, K314, \
    K400, K401, K402,                   K403,             K409, K410, K411,       K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214 }, \
	{ K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, K401, K402, K403, ____, ____, ____, ____, ____, K409, K410, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_ansi( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, \
    K400, K401, K402,                   K403,             K409, K410, K411, K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214 }, \
    { K300, ____, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, K401, K402, K403, ____, ____, ____, ____, ____, K409, K410, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_ansi_split_bs( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K213, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,             K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K313, K314, \
    K400, K401, K402,                   K403,             K409, K410, K411,       K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214 }, \
    { K300, ____, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, K401, K402, K403, ____, ____, ____, ____, ____, K409, K410, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_ansi_wkl( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, \
    K400,       K402,                   K403,             K409,       K411, K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214 }, \
    { K300, ____, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, ____, K402, K403, ____, ____, ____, ____, ____, K409, ____, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_ansi_wkl_split_bs( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K213, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113,       K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,             K214, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K313, K314, \
    K400,       K402,                   K403,             K409,       K411,       K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214 }, \
    { K300, ____, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, ____, K402, K403, ____, ____, ____, ____, ____, K409, ____, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_iso( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K113, K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, \
    K400, K401, K402,                   K403,             K409, K410, K411, K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, K401, K402, K403, ____, ____, ____, ____, ____, K409, K410, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_iso_split_bs( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K213, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,             K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K113,       K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K313, K314, \
    K400, K401, K402,                   K403,             K409, K410, K411,       K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K213, K214 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, K401, K402, K403, ____, ____, ____, ____, ____, K409, K410, K411, K412, K413, K414 }  \
}

#define LAYOUT_65_iso_wkl( \
    K000, K003, K002, K001, K004, K005, K006, K007, K008, K009, K012, K011, K010, K013, K014, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, K113, K214, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, \
    K400,       K402,                   K403,             K409,       K411, K412, K413, K414  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, K113, K114 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314 }, \
    { K400, ____, K402, K403, ____, ____, ____, ____, ____, K409, ____, K411, K412, K413, K414 }  \
}
