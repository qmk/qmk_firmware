/* Copyright 2019 takashiski
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

/* This a shortcut to help you visually see your layout.
 *
 * The first section contains all of the arguments representing the physical
 * layout of the board and position of the keys.
 *
 * The second converts the arguments into a two-dimensional array which
 * represents the switch matrix.
 */

#define LAYOUT(\
L00,L01,L02,L03,L04,L05,L06,    R00,R01,R02,R03,R04,R05,R06,R07,\
L10,L11,L12,L13,L14,L15,L16,    R10,R11,R12,R13,R14,R15,R16,R17,\
L20,L21,L22,L23,L24,L25,        R20,R21,R22,R23,R24,R25,R26,    \
L30,L31,L32,L33,L34,L35,        R30,R31,R32,R33,R34,R35,R36,R37,\
L40,L41,L42,L43,L44,L45,        R40,R41,R42,R43,R44,R45,R46,R47\
) {\
{L00,L01,L02,L03,L04,L05,L06,KC_NO},\
{L10,L11,L12,L13,L14,L15,L16,KC_NO},\
{L20,L21,L22,L23,L24,L25,KC_NO,KC_NO},\
{L30,L31,L32,L33,L34,L35,KC_NO,KC_NO},\
{L40,L41,L42,L43,L44,L45,KC_NO,KC_NO},\
{R00,R01,R02,R03,R04,R05,R06,R07},\
{R10,R11,R12,R13,R14,R15,R16,R17},\
{R20,R21,R22,R23,R24,R25,R26,KC_NO},\
{R30,R31,R32,R33,R34,R35,R36,R37},\
{R40,R41,R42,R43,R44,R45,R46,R47}\
}
/*
#define LAYOUT(\
	L00,L01,L02,L03,L04,L05,L06,	R07,R06,R05,R04,R03,R02,R01,R00,\
	L10,L11,L12,L13,L14,L15,L16,	R17,R16,R15,R14,R13,R12,R11,R10,\
	L20,L21,L22,L23,L24,L25,					R26,R25,R24,R23,R22,R21,R20,\
	L30,L31,L32,L33,L34,L35,			R37,R36,R35,R34,R33,R32,R31,R30,\
	L40,L41,L42,L43,L44,L45,			R47,R46,R45,R44,R43,R42,R41,R40\
) \
{\
	{L00,L01,L02,L03,L04,L05,L06,KC_NO},\
	{L10,L11,L12,L13,L14,L15,L16,KC_NO},\
	{L20,L21,L22,L23,L24,L25,KC_NO,KC_NO},\
	{L30,L31,L32,L33,L34,L35,KC_NO,KC_NO},\
	{L40,L41,L42,L43,L44,L45,KC_NO,KC_NO},\
	{R00,R01,R02,R03,R04,R05,R06,R07},\
	{R10,R11,R12,R13,R14,R15,R16,R17},\
	{R20,R21,R22,R23,R24,R25,R26,KC_NO},\
	{R30,R31,R32,R33,R34,R35,R36,R37},\
	{R40,R41,R42,R43,R44,R45,R46,R47}\
}
*/
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)
#define _________________QWERTY_L1_________________        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T
#define _________________QWERTY_L2_________________        KC_A,    KC_S,    KC_D,    KC_F,    KC_G
#define _________________QWERTY_L3_________________        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B

#define _________________QWERTY_R1_________________        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P
#define _________________QWERTY_R2_________________        KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN
#define _________________QWERTY_R3_________________        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLASH

#define ________________NUMBER_LEFT________________       KC_1,    KC_2,    KC_3,    KC_4,    KC_5
#define ________________NUMBER_RIGHT_______________       KC_6,    KC_7,    KC_8,    KC_9,    KC_0
#define _________________FUNC_LEFT_________________       KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5
#define _________________FUNC_RIGHT________________       KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10
