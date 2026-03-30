/*
Copyright 2023 @ Nuphy <https://nuphy.com/>

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

#include <stdint.h>
#define STARRY_INDEX_LEN (160)
#define WAVE_TAB_LEN 112
#define BREATHE_TAB_LEN 128
#define MIXCOLOR_TAB_LEN 144
#define FLOW_COLOR_TAB_LEN 192
#define FIREWORK_INDEX_LEN (158)
#define STARRY_DATA_LEN 96
#define TIDE_DATA_LEN 120
#define CHARGING_SHIFT 1

// disable clangd format
// clang-format off

// Keyboard-specific tables not in common/side_table.h
const uint8_t light_value_tab[101] =
{
	0,		22,		23,		24,
	25,		26,		27,		28,		29,		30,		31,		32,
	33,		34,		36,		37,		39,		40,		42,		43,
	45,		47,		49,		51,		53,		55,		57,		59,
	61,		63,		65,		67,		69,		71,		73,		75,
	77,		79,		81,		83,		85,		87,		89,		91,
	94,		96,		99,		101,	104, 	106,	109,	111,
	114,	116,	119,	121,	124,	126,	129,	131,
	134,	137,	140,	143,	146,	149,	152,	155,
	158,	161,	164,	167,	170,	173,	176,	179,
	182,	185,	188,	191,	194,	197,	200,	203,
	206,	209,	213,	216,	220,	223,	227,	230,
	234,	237,	241,	245,	248,	251,	255,	255,
	255,
};

const uint8_t dual_side_color_lib[3][6] =
{
    {0, 255, 255,      0,   0,  255},
	{0, 0,   255,      255,	0,	160},
	{0, 255, 255,      255, 64, 64 },

};

const uint8_t side_color_lib[9][3] =
{
	{0xff, 0x00, 0x00}, // red
	{0xff, 0x6f, 0x00}, // orange
	{0xff, 0xff, 0x00}, // yellow
	{0x00, 0xff, 0x00}, // green
	{0x00, 0xff, 0xff}, // light-blue
	{0x00, 0x00, 0xff}, // blue
	{0xff, 0x00, 0xa0}, // purple-pink
	{0xff, 0xa0, 0xa0}, // light-pink - skin like
	{0x00, 0x00, 0x00}, // off - zeroes
};
const uint8_t side_color_lib_1[9][3] =
{
	{0x70, 0x00, 0x00},
	{0x70, 0x20, 0x00},
	{0x60, 0x30, 0x00},
	{0x00, 0x70, 0x00},
	{0x00, 0x70, 0x70},
	{0x00, 0x00, 0x70},
	{0x70, 0x00, 0x70},
	{0x40, 0x70, 0x60},
	{0x00, 0x00, 0x00},
};
// clang-format on
