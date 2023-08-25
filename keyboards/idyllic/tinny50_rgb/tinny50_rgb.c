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
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED},
        {NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED}
    }, {
        // LED Index to Physical Position
        {150,  64}, {130,  64}, {110,  64}, { 90,  64}, { 70,  64}, { 50,  64}, { 30,  64},
        {  0,  52}, {  0,  39}, {  0,  26}, {  0,  13},
        { 30,   0}, { 50,   0}, { 70,   0}, { 90,   0}, {110,   0}, {130,   0}, {150,   0}, {170,   0}, {190,   0}, {210,   0}, {230,   0},
        {255,  13}, {255,  26}, {255,  39}, {255,  52},
        {230,  64}, {210,  64}, {190,  64}, {170,  64}
    }, {
        // LED Index to Flag
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  // UNDERGLOW
        2, 2, 2, 2,                       // UNDERGLOW
        2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,  // UNDERGLOW
        2, 2, 2, 2,                       // UNDERGLOW
    }
};
#endif

