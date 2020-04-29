/* Copyright 2020 Takeshi Nishio
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

/* This is a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */
#define LAYOUT( \
    L81,    L91,    La1,    L16,    L26,    L36,    L46,    L56,                L86,    L96,    La6,        R46,    R36,    R26,    R16,    Ra1,    R91,    R81,                        R86,    R96,    Ra6, \
            L92,    La2,    L17,    L27,    L37,    L47,    L57,        L67,    L87,    L97,    La7,        R47,    R37,    R27,    R17,    Ra2,    R92,    R82,    R72,        R67,    R87,    R97,    Ra7, \
            L93,    La3,    L18,    L28,    L38,    L48,    L58,        L68,    L78,    L98,    La8,        R48,    R38,    R28,    R18,    Ra3,    R93,    R83,                R68,    R78,    R98,    Ra8, \
            L94,    La4,    L19,    L29,    L39,    L49,    L59,        L69,    L79,    L89,    La9,        R49,    R39,    R29,    R19,    Ra4,    R94,    R84,    R74,        R69,    R79,    R89,    Ra9, \
    L85,    L95,                    L1a,    L2a,    L3a,    L4a,        L6a,            L8a,                R4a,    R2a,    R1a,            Ra5,    R95,    R85,    R75,        R6a,            R8a \
) \
{ \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L81,    L91,    La1 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L92,    La2 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L93,    La3 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L94,    La4 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  L85,    L95,    KC_NO }, \
    { L16,    L26,    L36,    L46,    L56,    KC_NO,  KC_NO,  L86,    L96,    La6 }, \
    { L17,    L27,    L37,    L47,    L57,    L67,    KC_NO,  L87,    L97,    La7 }, \
    { L18,    L28,    L38,    L48,    L58,    L68,    L78,    KC_NO,  L98,    La8 }, \
    { L19,    L29,    L39,    L49,    L59,    L69,    L79,    L89,    KC_NO,  La8 }, \
    { L1a,    L2a,    L3a,    L4a,    KC_NO,  L6a,    KC_NO,  L8a,    KC_NO,  KC_NO }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  R81,    R91,    Ra1 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  R72,    R82,    R92,    Ra2 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  R83,    R93,    Ra3 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  R74,    R84,    R94,    Ra4 }, \
    { KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  R75,    R85,    R95,    Ra5 }, \
    { R16,    R26,    R36,    R46,    KC_NO,  KC_NO,  KC_NO,  R86,    R96,    Ra6 }, \
    { R17,    R27,    R37,    R47,    KC_NO,  R67,    KC_NO,  R87,    R97,    Ra7 }, \
    { R18,    R28,    R38,    R48,    KC_NO,  R68,    R78,    KC_NO,  R98,    Ra8 }, \
    { R19,    R29,    R39,    R49,    KC_NO,  R69,    R79,    R89,    KC_NO,  Ra8 }, \
    { R1a,    R2a,    KC_NO,  R4a,    KC_NO,  R6a,    KC_NO,  R8a,    KC_NO,  KC_NO } \
}
