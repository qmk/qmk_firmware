/* Copyright 2019 HnahKB
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

#include "hnah108.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index
        {     18,     17,     16, NO_LED,     15,     14, NO_LED, NO_LED,     13,     12, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {     19, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
        {     20, NO_LED, NO_LED, NO_LED, NO_LED,     24, NO_LED, NO_LED,     26, NO_LED, NO_LED },
        {     21,     22,     23,     25,     27, NO_LED,     28,     29, NO_LED,      0,      1 },
        {     11,     10, NO_LED,      9, NO_LED,      8, NO_LED,      7,      6, NO_LED,      5 },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,      4 },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,      3 },
        { NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED, NO_LED,      2 }
    }, {
        // LED Index to Physical Position
        {   0,   0 }, {  18,   0 }, {  37,   0 }, {  56,   0 }, {  74,   0 }, {  93,   0 }, { 112,   0 }, { 130,   0 }, { 149,   0 }, { 168,   0 }, { 186,   0 }, { 205,   0 }, { 224,   0 },
        {   0,  25 },                                                                                                                                                           { 224,  25 },
        {   0,  51 },                                                                                                                                                           { 224,  51 },
        {   0,  63 }, {  18,  63 }, {  37,  63 }, {  56,  63 }, {  74,  63 }, {  93,  63 }, { 112,  63 }, { 130,  63 }, { 149,  63 }, { 168,  63 }, { 186,  63 }, { 205,  63 }, { 224,  63 }
    }, {
        // LED Index to Flag
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
        1,                                  1,
        1,                                  1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
    }
};
#endif
