/* Copyright 2020 Rozakiin
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

// readability
#define ____ KC_NO

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

/*
 * LAYOUT OPTIONS
 *
 * Not all of these options are supported by the plates offered during the
 * October 2017 group buy, but all of them are supported by the PCB.
 *
 * See the pull request for more information:
 *   https://github.com/qmk/qmk_firmware/pull/3426
 *
 *
 * Backspace
 *   - Split Backspace = K013 and K014
 *   - 2u Backspace = K014, delete K013
 *
 * Enter
 *   - ANSI Enter = K214, delete K212 (KC_NUHS)
 *   - ISO Enter = K214, delete K114 (ANSI Backslash)
 *
 * Left Shift
 *   - ANSI 2.25u: K300, delete K301 (KC_NUBS)
 *   - ISO 1.25u: K300, K301 is KC_NUBS
 *
 * Right Shift:
 *   - Full 2.75u = K313, delete K312 and K314
 *   - Split 1.75u + 1u = K312 and K314, delete K313
 *
 * Right Ctrl
 *   - K412 in the default keymap, but not supported with the plates offered
 *     during the October 2017 group buy.
 *
 */

#define LAYOUT_all( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315, \
    K400, K401, K402,                   K406,                   K410, K411, K412, K413, K414, K415  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, K013, K014, K015 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, ____, K114, K115 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214, K215 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, K313, K314, K315 }, \
    { K400, K401, K402, ____, ____, ____, K406, ____, ____, ____, K410, K411, K412, K413, K414, K415 }  \
}

#define LAYOUT_iso( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,             K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212,       K214, K215, \
    K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K314, K315, \
    K400, K401, K402,                   K406,                   K410, K411,       K413, K414, K415  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, ____, K014, K015 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, ____, ____, K115 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, K212, ____, K214, K215 }, \
    { K300, K301, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, ____, K314, K315 }, \
    { K400, K401, K402, ____, ____, ____, K406, ____, ____, ____, K410, K411, ____, K413, K414, K415 }  \
}

#define LAYOUT_ansi( \
    K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012,       K014, K015, \
    K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112,       K114, K115, \
    K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211,             K214, K215, \
    K300,       K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312,       K314, K315, \
    K400, K401, K402,                   K406,                   K410, K411,       K413, K414, K415  \
) { \
    { K000, K001, K002, K003, K004, K005, K006, K007, K008, K009, K010, K011, K012, ____, K014, K015 }, \
    { K100, K101, K102, K103, K104, K105, K106, K107, K108, K109, K110, K111, K112, ____, K114, K115 }, \
    { K200, K201, K202, K203, K204, K205, K206, K207, K208, K209, K210, K211, ____, ____, K214, K215 }, \
    { K300, ____, K302, K303, K304, K305, K306, K307, K308, K309, K310, K311, K312, ____, K314, K315 }, \
    { K400, K401, K402, ____, ____, ____, K406, ____, ____, ____, K410, K411, ____, K413, K414, K415 }  \
}
