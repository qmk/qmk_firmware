/* Copyright 2021 @ Teimor Epstein
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

// clang-format off

enum layers {
    MAC_BASE,
    MAC_FN,
    WIN_BASE,
    WIN_FN
};

// clang-format on

// Tap dance enums
enum {
    MAC_CAPS_LANGUAGE_CHANGE,
    WIN_CAPS_LANGUAGE_CHANGE,
};

#define KX_LGMAC TD(MAC_CAPS_LANGUAGE_CHANGE)
#define KX_LGWIN TD(WIN_CAPS_LANGUAGE_CHANGE)
#define KX_MACFN MO(MAC_FN)
#define KX_WINFN MO(WIN_FN)
