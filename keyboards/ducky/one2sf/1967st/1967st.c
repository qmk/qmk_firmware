/* Copyright 2019 /u/KeepItUnder
 * Copyright 2023 Hayley Hughes
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

#include "config.h"
#include "quantum.h"

led_config_t g_led_config = { {
	// Key Matrix to LED Index
    { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, NO_LED},
    { 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, NO_LED},
    { 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, NO_LED, 42, 43, NO_LED},
    { 44, NO_LED, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, NO_LED, NO_LED},
    { 57, 58, 59, 60, NO_LED, 61, NO_LED, 62, NO_LED, 63, 64, 65, 66, 67, 68, NO_LED},
}, {
    { 0, 0 }, { 16, 0 }, { 32, 0 }, { 48, 0 }, { 64, 0 }, { 80, 0 }, { 96, 0 }, { 112, 0 }, { 128, 0 }, { 144, 0 }, { 160, 0 }, { 176, 0 }, { 192, 0 }, { 208, 0 }, { 224, 0 },
    { 0, 16 }, { 16, 16 }, { 32, 16 }, { 48, 16 }, { 64, 16 }, { 80, 16 }, { 96, 16 }, { 112, 16 }, { 128, 16 }, { 144, 16 }, { 160, 16 }, { 176, 16 }, { 192, 16 }, { 208, 16 }, { 224, 16 },
    { 0, 32 }, { 16, 32 }, { 32, 32 }, { 48, 32 }, { 64, 32 }, { 80, 32 }, { 96, 32 }, { 112, 32 }, { 128, 32 }, { 144, 32 }, { 160, 32 }, { 176, 32 }, { 208, 32 }, { 224, 32 },
    { 0, 48 }, { 32, 48 }, { 48, 48 }, { 64, 48 }, { 80, 48 }, { 96, 48 }, { 112, 48 }, { 128, 48 }, { 144, 48 }, { 160, 48 }, { 176, 48 }, { 192, 48 }, { 208, 48 },
    { 0, 64 }, { 16, 64 }, { 32, 64 }, { 48, 64 }, { 80, 64 }, { 112, 64 }, { 144, 64 }, { 160, 64 }, { 176, 64 }, { 192, 64 }, { 208, 64 }, { 224, 64 }
}, {
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    5, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4, 4,
    5,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 5, 4,
    5, 5, 5, 4,    4,    4,    5, 5, 5, 4, 4, 4
} };

