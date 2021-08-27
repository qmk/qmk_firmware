/*
Copyright 2021 Danny Nguyen <danny@keeb.io>
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
#include "rev6.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    // Key Matrix to LED Index
    // Left Half
    { 0, 1, 2, 3, 4, 5 },
    { 11, 10, 9, 8, 7, 6 },
    { 12, 13, 14, 15, 16, 17 },
    { 23, 22, 21, 20, 19, 18 },
    { NO_LED, NO_LED, 24, 25, 26, 27 },
    // Right Half
    { 39, 38, 37, 36, 35, 34 },
    { 40, 41, 42, 43, 44, 45 },
    { 51, 50, 49, 48, 47, 46 },
    { 52, 53, 54, 55, 56, 57 },
    { NO_LED, NO_LED, 58, 59, 60, 61 }
}, {
    // LED Index to Physical Position
    // Left Half
    { 0, 5 }, { 16, 5 }, { 32, 2 }, { 48, 0 }, { 64, 2 }, { 80, 3 },
    { 0, 18 }, { 16, 18 }, { 32, 15 }, { 48, 13 }, { 64, 15 }, { 80, 17 },
    { 0, 32 }, { 16, 32 }, { 32, 28 }, { 48, 27 }, { 64, 28 }, { 80, 30 },
    { 0, 45 }, { 16, 45 }, { 32, 42 }, { 48, 40 }, { 64, 42 }, { 80, 43 },
    { 56, 47 }, { 72, 58 }, { 90, 64 }, { 98, 52 },
    // Right Half
    { 224, 5 }, { 208, 5 }, { 192, 2 }, { 176, 0 }, { 160, 2 }, { 144, 3 },
    { 224, 18 }, { 208, 18 }, { 192, 15 }, { 176, 13 }, { 160, 15 }, { 144, 17 },
    { 224, 32 }, { 208, 32 }, { 192, 28 }, { 176, 27 }, { 160, 28 }, { 144, 30 },
    { 224, 45 }, { 208, 45 }, { 192, 42 }, { 176, 40 }, { 160, 42 }, { 144, 43 },
    { 168, 47 }, { 152, 58 }, { 134, 64 }, { 126, 52 }
}, {
    // LED Index to Flag
    // Left Half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
          4, 4, 4, 4,
    2, 2, 2, 2, 2, 2,
    // Right Half
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4, 4,
    4, 4, 4, 4,
    2, 2, 2, 2, 2, 2

} };
#endif
