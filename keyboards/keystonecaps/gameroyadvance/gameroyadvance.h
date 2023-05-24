/*
Copyright 2022 @RoyMeetsWorld

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "quantum.h"

/**
 * The layout macro for ANSI boards, with illustrative grid of a typical assignment.
 *   ┌───┬───┬───┬───┬───┬───┬───┐                              ┌───┬───┬───┬───┬───┬───┬───────┐
 *   │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │                              │ 7 │ 8 │ 9 │ 0 │ - │ + │ BACK  │
 * ┌─┴───┼───┼───┼───┼───┼───┼───┤┌───┬───┐        ┌───┬───┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─────┤
 * │ TAB │ Q │ W │ E │ R │ T │ Y ││F1 │F2 │        │F7 │F8 │  │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘├───┼───┤        ├───┼───┤  └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │ CAPS │ A │ S │ D │ F │ G │   │F3 │F4 │        │F9 │F10│   │ H │ J │ K │ L │ ; │ ' │  Enter │
 * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐ ├───┼───┤        ├───┼───┤ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────────┤
 * │ LSHIFT │ Z │ X │ C │ V │ B │ │F5 │F6 │        │F11│F12│ │ B │ N │ M │ , │ . │ / │  RSHIFT  │
 * ├────┬───┴┬──┴─┬─┴──┬┴───┼───┴┬┴───┼───┘        └───┼───┴┬┴───┼───┴───┴──┬┴───┼───┴┬────┬────│
 * │LCTL│LGUI│LALT│ FN │    │SPC │MUTE│                │MUTE│SPCE│          │RALT│ FN │RGUI│RCTL│
 * └────┴────┴────┴────┘    └────┼────┤                ├────┼────┘          └────┴────┴────┴────┘
 *                               │ENTR│                │ENTR│
 *                               └────┘                └────┘
 */
#define LAYOUT(                                                                                            \
	L00, L01, L02, L03, L04, L05, L06,                        R00, R01, R02, R03, R04, R05,      R07,      \
	L10, L11, L12, L13, L14, L15, L16, L17, L18,    R10, R11, R12, R13, R14, R15, R16, R17, R18,      R28, \
	L20, L21, L22, L23, L24, L25,      L27, L28,    R20, R21, R22, R23, R24, R25, R26, R27,      R38,      \
	L30,      L31, L32, L33, L34, L35, L37, L38,    R30, R31, R32, R33, R34, R35, R36, R37,      R46,      \
	L40, L41, L42, L43,           L45, L48,              R40, R42,                     R43, R44, R45, R47, \
	                                   L47,              R41                                               \
) \
{ \
	{ L00,   L01,   L02,   L03,   L04,   L05,   L06,   KC_NO, KC_NO }, \
	{ L10,   L11,   L12,   L13,   L14,   L15,   L16,   L17,   L18   }, \
	{ L20,   L21,   L22,   L23,   L24,   L25,   KC_NO, L27,   L28   }, \
	{ L30,   L31,   L32,   L33,   L34,   L35,   KC_NO, L37,   L38   }, \
	{ L40,   L41,   L42,   L43,   KC_NO, L45,   KC_NO, L47,   L48   }, \
	{ R00,   R01,   R02,   R03,   R04,   R05,   KC_NO, R07,   KC_NO }, \
	{ R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17,   R18   }, \
	{ R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27,   R28   }, \
	{ R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37,   R38   }, \
	{ R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47,   KC_NO }  \
}

/**
 * The layout macro for split-key boards, with illustrative grid of a typical assignment.
 *
 * Backspace has two options with three distinct pads:
 *     - center pad (regular 2u backspace)
 *     - left pad + right pad (split backspace)
 *
 * You may wish to set the unused pad(s) to KC_NO or XXXXXX, as they will be ignored.
 *                                                                                      ┌───────┐
 *                                                                                      │ BACK  │   (R07)
 *                                                                                      └───────┘
 *                                                                                          | 
 *   ┌───┬───┬───┬───┬───┬───┬───┐                              ┌───┬───┬───┬───┬───┬───┬───┬───┐
 *   │ESC│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │                              │ 7 │ 8 │ 9 │ 0 │ - │ + │ \ │BCK│ (R06 R08)
 * ┌─┴───┼───┼───┼───┼───┼───┼───┤┌───┬───┐        ┌───┬───┐  ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴───┤
 * │ TAB │ Q │ W │ E │ R │ T │ Y ││F1 │F2 │        │F7 │F8 │  │ Y │ U │ I │ O │ P │ [ │ ] │  \  │
 * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┘├───┼───┤        ├───┼───┤  └┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴─────┤
 * │ CAPS │ A │ S │ D │ F │ G │   │F3 │F4 │        │F9 │F10│   │ H │ J │ K │ L │ ; │ ' │  Enter │
 * ├────┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┐ ├───┼───┤        ├───┼───┤ ┌─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴────┬───┤
 * │LSFT│ \ │ Z │ X │ C │ V │ B │ │F5 │F6 │        │F11│F12│ │ B │ N │ M │ , │ . │ / │RSHIFT│PSC│
 * ├────┼───┴┬──┴─┬─┴──┬┴───┼───┴┬┴───┼───┘        └───┼───┴┬┴───┼───┴───┴──┬┴───┼───┴┬────┬┴───│
 * │LCTL│LGUI│LALT│ FN │    │SPC │MUTE│                │MUTE│SPCE│          │RALT│ FN │RGUI│RCTL│
 * └────┴────┴────┴────┘    └────┼────┤                ├────┼────┘          └────┴────┴────┴────┘
 *                               │ENTR│                │ENTR│
 *                               └────┘                └────┘
 */
#define LAYOUT_all(                                                                                        \
	L00, L01, L02, L03, L04, L05, L06,                        R00, R01, R02, R03, R04, R05, R06, R07, R08, \
	L10, L11, L12, L13, L14, L15, L16, L17, L18,    R10, R11, R12, R13, R14, R15, R16, R17, R18,      R28, \
	L20, L21, L22, L23, L24, L25,      L27, L28,    R20, R21, R22, R23, R24, R25, R26, R27,      R38,      \
	L30, L44, L31, L32, L33, L34, L35, L37, L38,    R30, R31, R32, R33, R34, R35, R36, R37,      R46, R48, \
	L40, L41, L42, L43,           L45, L48,              R40, R42,                R43, R44,      R45, R47, \
	                                   L47,              R41                                               \
) \
{ \
	{ L00,   L01,   L02,   L03,   L04,   L05,   L06,   KC_NO, KC_NO }, \
	{ L10,   L11,   L12,   L13,   L14,   L15,   L16,   L17,   L18   }, \
	{ L20,   L21,   L22,   L23,   L24,   L25,   KC_NO, L27,   L28   }, \
	{ L30,   L31,   L32,   L33,   L34,   L35,   KC_NO, L37,   L38   }, \
	{ L40,   L41,   L42,   L43,   L44,   L45,   KC_NO, L47,   L48   }, \
	{ R00,   R01,   R02,   R03,   R04,   R05,   R06,   R07,   R08   }, \
	{ R10,   R11,   R12,   R13,   R14,   R15,   R16,   R17,   R18   }, \
	{ R20,   R21,   R22,   R23,   R24,   R25,   R26,   R27,   R28   }, \
	{ R30,   R31,   R32,   R33,   R34,   R35,   R36,   R37,   R38   }, \
	{ R40,   R41,   R42,   R43,   R44,   R45,   R46,   R47,   R48   }  \
}
