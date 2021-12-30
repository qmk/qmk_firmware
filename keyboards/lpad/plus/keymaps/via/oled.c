/* Copyright 2021 bululau
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

static const char oled_a [] PROGMEM = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x3f, 0x0f, 0xc3, 0xf0, 0x3c, 0x07, 0xc0, 0x00, 0x01, 0x7f, 0x7f, 0x7f, 0x00,
	0x00, 0x00, 0x01, 0x1f, 0x01, 0x00, 0x0f, 0x00, 0x00, 0x87, 0x87, 0x9f, 0x3f, 0x0f, 0xc0, 0xfe,
	0xfc, 0x00, 0x0f, 0x60, 0x00, 0x1c, 0x20, 0x07, 0x07, 0x07, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xf8,
	0x80, 0x01, 0xff, 0xff, 0xff, 0xfc, 0x00, 0x0f, 0xff, 0xff, 0x00, 0x01, 0x00, 0x00, 0xff, 0xe0,
	0x01, 0x3f, 0xfc, 0xf8, 0xc2, 0x00, 0x01, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x01, 0x00, 0x04, 0x3f, 0x03, 0xe0, 0xfc, 0xff, 0xfc, 0xf8, 0xf0, 0x01, 0x00, 0x00,
	0x00, 0xfe, 0x9e, 0x20, 0x00, 0x20, 0x00, 0xc0, 0x78, 0x00, 0x89, 0xcb, 0xe3, 0xe3, 0x53, 0x03,
	0x01, 0xf1, 0xf8, 0xf8, 0xc1, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x01, 0x01, 0x63, 0x43, 0x07,
	0xe7, 0x08, 0x00, 0x8f, 0xbf, 0xff, 0xff, 0xe0, 0x01, 0x7f, 0xc0, 0x00, 0x00, 0xe0, 0xff, 0x1f,
	0x00, 0x00, 0x07, 0xff, 0xff, 0xf0, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xf0, 0x02, 0x00, 0xfe, 0x07, 0xc0, 0xfc, 0xff, 0xff, 0x01, 0x00, 0x3e, 0x00,
	0x00, 0x7c, 0xf8, 0xf9, 0xf9, 0xf9, 0xf9, 0xf8, 0xfc, 0xf2, 0xff, 0xf7, 0xff, 0xff, 0xfe, 0xf8,
	0xf0, 0xf3, 0xe3, 0xe7, 0xe5, 0xc8, 0xc9, 0xc9, 0xca, 0xe0, 0x61, 0x10, 0x80, 0xe0, 0xfc, 0x30,
	0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x1f, 0x0f, 0xfc, 0x00, 0x01, 0xc0, 0x30, 0x0f, 0xc1, 0xf8,
	0x3f, 0x1c, 0x00, 0xff, 0xff, 0xff, 0xfe, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xf8, 0xe0, 0xc6, 0x80, 0x07, 0x3f, 0x7f, 0x7f, 0xfc, 0xf0, 0xe0, 0xc8,
	0x9f, 0xbc, 0x09, 0x13, 0x87, 0xcf, 0x9f, 0x3f, 0x7f, 0xff, 0xff, 0xf3, 0xf3, 0xf7, 0xff, 0xff,
	0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0x9f, 0x9f, 0x01, 0x00, 0x06, 0x03, 0x79, 0x0c, 0x02,
	0xc0, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x80, 0x00, 0x03, 0x20, 0x1c, 0x0c, 0x62, 0x30, 0x0f, 0x01,
	0x20, 0x98, 0x8e, 0xc3, 0xe1, 0x39, 0x00, 0xc0, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'setting128x32', 128x32px
static const char oled_b [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x38, 0x82, 0xc4,
	0xd3, 0xb3, 0xb7, 0xcc, 0xc1, 0xc6, 0x8c, 0x19, 0x33, 0xe7, 0xe7, 0xef, 0xf3, 0xe8, 0x69, 0x09,
	0x09, 0x09, 0x19, 0x11, 0x33, 0x27, 0x63, 0x63, 0xf2, 0xf6, 0xf7, 0xf5, 0xfd, 0xfd, 0xf9, 0xf9,
	0x79, 0x19, 0xc9, 0xe1, 0xf3, 0x7c, 0xba, 0x92, 0xce, 0xfc, 0x7b, 0x3e, 0x8c, 0xe1, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xfc, 0xc3, 0x1f, 0x7f, 0xf8, 0x80, 0x33, 0xe7, 0x9f, 0x7f, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0xc7, 0x9f,
	0x3f, 0x7f, 0xff, 0xff, 0xff, 0x83, 0x3f, 0x3f, 0xcc, 0xf5, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xf8, 0xec, 0xe3, 0xfb, 0xfe, 0xfe, 0xf4, 0xf9, 0xfd, 0xff, 0xff, 0xff, 0xc3,
	0x00, 0xff, 0xff, 0xdf, 0xe2, 0xf7, 0xe1, 0x40, 0xc0, 0x00, 0xe0, 0xa3, 0xff, 0xff, 0xff, 0xff,
	0xfb, 0xc7, 0xbf, 0xff, 0xff, 0xff, 0xfc, 0xf3, 0xff, 0xf9, 0x0f, 0x7f, 0xfe, 0xf8, 0xf3, 0xcf,
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x7f, 0x19, 0xce, 0xe7, 0xfe, 0x7e, 0x7f, 0xbd, 0x93, 0x67, 0x0f, 0x8f, 0xcf,
	0xff, 0x7f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x3f, 0x7f, 0xdf, 0xef, 0xf7, 0xfb,
	0xfe, 0xfc, 0xf9, 0xf3, 0xfb, 0x7f, 0x67, 0x3f, 0x3f, 0x98, 0xc3, 0xcf, 0x80, 0x0f, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xe3, 0x1f, 0xff, 0xff, 0xfd, 0xf9, 0xf3, 0xe6, 0xf8, 0xc3, 0x9f, 0x3f, 0x7f,
	0xfe, 0xf8, 0x87, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0x7f, 0x7f, 0xbf, 0xbf, 0x9f, 0xdf, 0xcf, 0xef, 0xef, 0xf7, 0xf3, 0xfb, 0xfb, 0xf3, 0xeb,
	0xfb, 0x1b, 0xdf, 0xec, 0x2d, 0x6d, 0x26, 0x96, 0xc7, 0xe3, 0xf5, 0xf4, 0xf6, 0xf7, 0xf7, 0x73,
	0xd7, 0x61, 0xd8, 0xee, 0xe6, 0xe6, 0xe0, 0xf6, 0xfb, 0xf9, 0x60, 0x0e, 0x86, 0x84, 0x84, 0x01,
	0x01, 0x01, 0xc8, 0x0c, 0x04, 0x06, 0x3e, 0x3f, 0xbf, 0xbf, 0x9f, 0xdf, 0xdf, 0x8e, 0x24, 0xf0,
	0xf3, 0xe7, 0xc7, 0x9f, 0xff, 0xb8, 0x63, 0xcf, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,
	0xf9, 0xf3, 0xe7, 0xdc, 0x11, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'function128x32', 128x32px
static const char oled_c [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x1f, 0x0f, 0xff, 0xff, 0x03, 0xff, 0xff, 0x0f, 0xf7, 0xf8, 0xed, 0xfa, 0x66, 0x06, 0xd8, 0x3f,
	0x33, 0x0e, 0x27, 0xb7, 0x9f, 0x0f, 0xb7, 0x99, 0xcc, 0x97, 0x99, 0x26, 0x33, 0x1d, 0x27, 0x5f,
	0x37, 0xd9, 0x7e, 0x3f, 0x8f, 0xe3, 0x7e, 0x8f, 0xe0, 0x7f, 0xe7, 0xfe, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0x00, 0xb0, 0xff, 0xff, 0x42, 0xdf, 0x3f, 0x7e, 0xf7, 0x05, 0x19, 0xf9, 0xfc, 0xfe, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xef, 0xcf, 0xcf, 0xf7, 0xff, 0xff, 0xff, 0xfe, 0x7e, 0x5e,
	0xff, 0x7e, 0x38, 0xb8, 0x84, 0xc0, 0xe8, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcf, 0x3e, 0xe0, 0x8f, 0x7f, 0xff, 0xff, 0xff, 0xbf,
	0x7c, 0xc0, 0x3f, 0xff, 0x3e, 0x7f, 0x9f, 0xcf, 0xf3, 0xfc, 0xff, 0xfc, 0xf9, 0xe7, 0xcf, 0x9f,
	0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xbf, 0xff, 0xff, 0xff, 0x7f, 0x7f, 0xbf, 0xce,
	0x74, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x8f, 0xcf, 0xc6, 0xc1, 0x81, 0x83, 0x83, 0x03, 0x07,
	0x06, 0x05, 0x0f, 0x1e, 0x31, 0x63, 0x87, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff,
	0x9f, 0x0e, 0x18, 0x3c, 0x3d, 0x7f, 0x7f, 0xfd, 0xfd, 0xbd, 0x1c, 0xc6, 0x30, 0xde, 0xe7, 0xf9,
	0xfe, 0xff, 0xff, 0xff, 0xfd, 0xfb, 0xf7, 0xff, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xef,
	0xdf, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf
};

static const char oled_d [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0x3f, 0x0f, 0xc3, 0xf0, 0x7c, 0x07, 0xe0, 0x00, 0x0f, 0xff, 0xff, 0x7f, 0x3f,
	0x00, 0x01, 0x03, 0x1f, 0x01, 0x04, 0x0f, 0x00, 0x00, 0xc7, 0x87, 0xbf, 0xbf, 0x3f, 0xc0, 0xff,
	0xff, 0x80, 0x1f, 0x70, 0x02, 0x3e, 0x20, 0x27, 0x1f, 0x0f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0x80, 0x07, 0xff, 0xff, 0xff, 0xff, 0x80, 0x1f, 0xff, 0xff, 0x00, 0x03, 0x00, 0x07, 0xff, 0xfc,
	0x07, 0x3f, 0xfe, 0xf9, 0xe3, 0x00, 0x03, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x01, 0x00, 0xfe, 0x7f, 0x03, 0xe0, 0xfe, 0xff, 0xfe, 0xf8, 0xf8, 0x83, 0x07, 0x00,
	0x00, 0xfe, 0xfe, 0xa0, 0x20, 0x20, 0x81, 0xf0, 0x79, 0x1d, 0x89, 0xcb, 0xeb, 0xeb, 0xfb, 0x1b,
	0x0b, 0xf9, 0xfc, 0xfc, 0xc5, 0x00, 0x00, 0x44, 0x00, 0x00, 0xc8, 0x81, 0x03, 0x73, 0x67, 0x07,
	0xef, 0x4c, 0x01, 0x9f, 0xff, 0xff, 0xff, 0xf0, 0x03, 0xff, 0xff, 0x00, 0x00, 0xfc, 0xff, 0x3f,
	0xe0, 0x80, 0x0f, 0xff, 0xff, 0xff, 0x00, 0x00, 0xe3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xfc, 0xf0, 0x03, 0x80, 0xfe, 0x0f, 0xe1, 0xfe, 0xff, 0xff, 0x03, 0xc0, 0x7f, 0x00,
	0x1c, 0x7c, 0xfd, 0xf9, 0xf9, 0xf9, 0xfd, 0xfc, 0xfe, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc,
	0xf9, 0xf3, 0xf7, 0xe7, 0xe5, 0xed, 0xe9, 0xc9, 0xea, 0xe9, 0xe1, 0x30, 0xc7, 0xf0, 0xfc, 0x70,
	0x03, 0xc1, 0xe0, 0xff, 0xff, 0xff, 0xff, 0x1f, 0xfe, 0x00, 0x13, 0xc0, 0x7c, 0x0f, 0xe3, 0xf8,
	0xff, 0x3f, 0x00, 0xff, 0xff, 0xff, 0xff, 0x00, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xfc, 0xe0, 0xc7, 0x80, 0x8f, 0x3f, 0x7f, 0xff, 0xfe, 0xf0, 0xe0, 0xcc,
	0x9f, 0xbc, 0x59, 0x13, 0xc7, 0xcf, 0x9f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xff, 0xff,
	0xff, 0xff, 0x7f, 0x7f, 0x7f, 0x3f, 0x1f, 0xbf, 0xdf, 0x03, 0xcc, 0x87, 0x03, 0xf9, 0x1c, 0x87,
	0xe1, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x87, 0x7c, 0x03, 0xb0, 0x9e, 0xce, 0x62, 0x39, 0x0f, 0x41,
	0x20, 0x98, 0x8f, 0xc3, 0xe3, 0x79, 0x0c, 0xc0, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'function128x32', 128x32px
static const char oled_e [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfd, 0xfc, 0xfe, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0x19, 0x02, 0xf1,
	0xfe, 0xff, 0x00, 0x1f, 0xbf, 0x9f, 0xc8, 0xe0, 0xe7, 0xef, 0x67, 0x67, 0x60, 0xe1, 0xf3, 0xf8,
	0xfb, 0xfb, 0xf8, 0xf8, 0xfb, 0xfb, 0xf7, 0xf3, 0x70, 0x70, 0x77, 0xe7, 0xe7, 0xe7, 0xe0, 0xc0,
	0x83, 0x30, 0x28, 0xff, 0xff, 0xff, 0xfc, 0xc1, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x67, 0x77, 0xf7, 0xfb, 0xfd, 0x7d, 0x13, 0xc7, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xe3, 0xcf, 0x3f, 0x7f, 0xff, 0x00, 0x80, 0xff,
	0xff, 0xff, 0xe0, 0x07, 0x83, 0x81, 0x01, 0x00, 0x18, 0x18, 0x19, 0x01, 0x03, 0xf3, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x01, 0x01, 0x18, 0x18, 0x18, 0x01, 0x01,
	0x83, 0x8f, 0x8e, 0x7c, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0x07, 0x7f, 0x3f, 0x0f, 0x63, 0x78, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xc3,
	0x9c, 0x7e, 0xfe, 0xfe, 0xf9, 0xfb, 0xfb, 0x7b, 0x33, 0x87, 0xff, 0xfe, 0x04, 0x00, 0xc3, 0xff,
	0x3f, 0x7f, 0xe7, 0x00, 0xc3, 0x8f, 0x7e, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff,
	0xc7, 0x87, 0x77, 0x77, 0x27, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfd, 0xfc, 0xfc, 0x7f,
	0x8f, 0xc7, 0x01, 0x00, 0xc0, 0x01, 0xdf, 0x3f, 0x7f, 0x10, 0x46, 0x9f, 0xbf, 0x3f, 0x7e, 0x7e,
	0xdc, 0x0d, 0xeb, 0xe7, 0xe7, 0xff, 0xc7, 0x93, 0x3b, 0x7b, 0x79, 0x7c, 0x7e, 0x1c, 0xe1, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0xcf, 0xef, 0xef, 0xe7, 0xf3, 0xf9, 0xf9, 0xfb, 0x73, 0x0f,
	0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x83, 0xff, 0x0e, 0x0f, 0xdf,
	0x3c, 0x21, 0xf1, 0xf8, 0x04, 0x83, 0xde, 0xde, 0xe1, 0xe1, 0xf3, 0x1b, 0xc7, 0xe7, 0xcf, 0xcf,
	0x8f, 0x9f, 0x9f, 0xbe, 0x9f, 0x9f, 0xcf, 0xef, 0xe7, 0x07, 0xf7, 0xe3, 0xd9, 0x99, 0xb4, 0x24,
	0x7f, 0xff, 0xa0, 0x0c, 0x87, 0x40, 0x00, 0xfe, 0xfe, 0xfe, 0xf0, 0x03, 0x3f, 0x0e, 0xe4, 0xe8,
	0xe2, 0xf6, 0xff, 0x1f, 0xcf, 0xef, 0xe7, 0xef, 0xcf, 0x9f, 0xbf, 0xbf, 0x3e, 0x7f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

// 'function128x32', 128x32px
static const char oled_f [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0,
	0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0xc0, 0xc0, 0xc0, 0xc0, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x0e, 0x0e, 0x06, 0x03, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x1f, 0x07, 0x01, 0x01, 0x00, 0x01, 0x81,
	0xc1, 0xff, 0xff, 0x3c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0e,
	0x0f, 0x03, 0x01, 0x81, 0x80, 0x81, 0xc1, 0xc1, 0x7f, 0x7f, 0x1c, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xf0, 0xf8, 0x9c, 0x8c, 0x8e, 0x87, 0x83,
	0x81, 0x81, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x78,
	0xf0, 0xc0, 0x80, 0x80, 0x80, 0x81, 0x81, 0xc1, 0xe7, 0xff, 0x3e, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01,
	0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'function128x32', 128x32px
static const char oled_g [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 0xc3, 0xff, 0xfe, 0x3c, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x3f, 0xfe, 0xf0, 0x80, 0x00, 0x00,
	0x00, 0x00, 0x00, 0xe0, 0xfc, 0x7f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xff, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x81, 0x81, 0xc3, 0xff, 0xfe, 0x3c,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x07, 0x3f, 0xfc, 0xf0,
	0xe0, 0xfc, 0x7f, 0x0f, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0xff, 0xff, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x03, 0x01, 0x01, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
	0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'function128x32', 128x32px
static const char oled_h [] PROGMEM = {
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfd, 0xfc, 0xfe, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80, 0x08, 0xff, 0xff, 0xff, 0xff, 0xff, 0x19, 0x02, 0xf1,
	0xfe, 0xff, 0x00, 0x1f, 0xbf, 0x9f, 0xc8, 0xe0, 0xe7, 0xef, 0x67, 0x67, 0x60, 0xe1, 0xf3, 0xf8,
	0xfb, 0xfb, 0xf8, 0xf8, 0xfb, 0xfb, 0xf7, 0xf3, 0x70, 0x70, 0x77, 0xe7, 0xe7, 0xe7, 0xe0, 0xc0,
	0x83, 0x30, 0x28, 0xff, 0xff, 0xff, 0xfc, 0xc1, 0x07, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0x67, 0x77, 0xf7, 0xfb, 0xfd, 0x7d, 0x13, 0xc7, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf8, 0xe3, 0xcf, 0x3f, 0x7f, 0xff, 0x00, 0x80, 0xff,
	0xff, 0xff, 0xe0, 0x07, 0x83, 0x81, 0x01, 0x00, 0x18, 0x18, 0x19, 0x01, 0x03, 0xf3, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0x01, 0x01, 0x18, 0x18, 0x18, 0x01, 0x01,
	0x83, 0x8f, 0x8e, 0x7c, 0x7f, 0xff, 0xff, 0xff, 0xf0, 0x07, 0x7f, 0x3f, 0x0f, 0x63, 0x78, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfe, 0xfe, 0xfc, 0xfc, 0xff, 0xff, 0xff, 0xc3,
	0x9c, 0x7e, 0xfe, 0xfe, 0xf9, 0xfb, 0xfb, 0x7b, 0x33, 0x87, 0xff, 0xfe, 0x04, 0x00, 0xc3, 0xff,
	0x3f, 0x7f, 0xe7, 0x00, 0xc3, 0x8f, 0x7e, 0xfc, 0xfc, 0xfc, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff,
	0xc7, 0x87, 0x77, 0x77, 0x27, 0xc7, 0xff, 0xff, 0xff, 0xff, 0xfc, 0xfc, 0xfd, 0xfc, 0xfc, 0x7f,
	0x8f, 0xc7, 0x01, 0x00, 0xc0, 0x01, 0xdf, 0x3f, 0x7f, 0x10, 0x46, 0x9f, 0xbf, 0x3f, 0x7e, 0x7e,
	0xdc, 0x0d, 0xeb, 0xe7, 0xe7, 0xff, 0xc7, 0x93, 0x3b, 0x7b, 0x79, 0x7c, 0x7e, 0x1c, 0xe1, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0x7f, 0x1f, 0xcf, 0xef, 0xef, 0xe7, 0xf3, 0xf9, 0xf9, 0xfb, 0x73, 0x0f,
	0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xfe, 0xfe, 0xfe, 0xff, 0xff, 0x3f, 0x83, 0xff, 0x0e, 0x0f, 0xdf,
	0x3c, 0x21, 0xf1, 0xf8, 0x04, 0x83, 0xde, 0xde, 0xe1, 0xe1, 0xf3, 0x1b, 0xc7, 0xe7, 0xcf, 0xcf,
	0x8f, 0x9f, 0x9f, 0xbe, 0x9f, 0x9f, 0xcf, 0xef, 0xe7, 0x07, 0xf7, 0xe3, 0xd9, 0x99, 0xb4, 0x24,
	0x7f, 0xff, 0xa0, 0x0c, 0x87, 0x40, 0x00, 0xfe, 0xfe, 0xfe, 0xf0, 0x03, 0x3f, 0x0e, 0xe4, 0xe8,
	0xe2, 0xf6, 0xff, 0x1f, 0xcf, 0xef, 0xe7, 0xef, 0xcf, 0x9f, 0xbf, 0xbf, 0x3e, 0x7f, 0xff, 0xff,
	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
 return OLED_ROTATION_180;
}
void oled_task_user(void) {
    switch (get_highest_layer(layer_state)) {
        case 0:
			oled_write_raw_P(oled_a,1024);
            break;
        case 1:
			oled_write_raw_P(oled_b,1024);
            break;
        case 2:
			oled_write_raw_P(oled_c,1024);
            break;
        case 3:
			oled_write_raw_P(oled_d,1024);
            break;
        case 4:
			oled_write_raw_P(oled_e,1024);
            break;
        case 5:
			oled_write_raw_P(oled_f,1024);
            break;
        case 6:
			oled_write_raw_P(oled_g,1024);
            break;
        case 7:
			oled_write_raw_P(oled_h,1024);
            break;
    }
}
#endif
