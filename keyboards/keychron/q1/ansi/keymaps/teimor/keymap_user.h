/* Copyright 2022 @ Teimor Epstein
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

#ifdef TAP_DANCE_ENABLE
#   define KC_LGMAC TD(MAC_CAPS_LANGUAGE_CHANGE)
#   define KC_LGWIN TD(WIN_CAPS_LANGUAGE_CHANGE)
#else
#   define KC_LGMAC KC_CAPS
#   define KC_LGWIN KC_CAPS
#endif
#define KC_MACFN MO(MAC_FN)
#define KC_WINFN MO(WIN_FN)
#define KC_LMAC C(G(KC_Q))
#define KC_MACPS G(S(KC_5))
#define KC_TASK G(KC_TAB)
#define KC_FLXP G(KC_E)
