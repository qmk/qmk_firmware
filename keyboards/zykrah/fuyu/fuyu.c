/*
Copyright 2022 Zykrah

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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
    }, {
        // LED Index to Physical Position
        {112,  32}, {138,  17}, {112,   2}, { 86,  17}, { 86,  47}, {112,  62}, {138, 47}, // SNOWFLAKE
        {  0,   0}, { 16,   0}, { 32,   0}, { 48,   0}, { 64,   0}, { 80,   0}, { 96,  0}, {112,   0}, {128,   0}, {144,   0}, {160,   0}, {176,   0}, {192,  0}, {208,   0}, // UNDERGLOW
        {208,  16}, {208,  32}, {208,  48},                                                                                                                                   // UNDERGLOW
        {208,  64}, {192,  64}, {176,  64}, {160,  64}, {144,  64}, {128,  64}, {112, 64}, { 96,  64}, { 80,  64}, { 64,  64}, { 48,  64}, { 32,  64}, { 16, 64}, {  0,  64}, // UNDERGLOW
        {  0,  48}, {  0,  32}, {  0,  16}                                                                                                                                    // UNDERGLOW
    }, {
        // LED Index to Flag
        8, 8, 8, 8, 8, 8, 8, // SNOWFLAKE
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  // UNDERGLOW
        2, 2, 2,                                   // UNDERGLOW
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  // UNDERGLOW
        2, 2, 2                                    // UNDERGLOW
    }
};
#endif
