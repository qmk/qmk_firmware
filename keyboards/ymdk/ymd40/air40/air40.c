/* Copyright 2022 Dennis Kruyt (dennis@kruyt.org)
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

#include "air40.h"

#if defined(RGB_MATRIX_ENABLE)
led_config_t g_led_config = {
    {
        // Key Matrix to LED Index for center 2u
        {11, 10,  9,  8, 7,  6,  5,  4,  3,  2,  1,  0},
        {23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12},
        {35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24},
        {50, 49, 48, 47, 46, 43, 41, 40, 39, 38, 37, 36}
    }, {
        // LED Index to Physical Position, more positions due to extra leds for other layout options
        {  0,  0}, { 20,  0}, { 40,  0}, {61,  0}, {81,  0}, {101,  0}, {122,  0}, {142,  0}, {162,  0}, {183,  0}, {203,  0}, {224,  0},
        {  0, 21}, { 20, 21}, { 40, 21}, {61, 21}, {81, 21}, {101, 21}, {122, 21}, {142, 21}, {162, 21}, {183, 21}, {203, 21}, {224, 21},
        {  0, 42}, { 20, 42}, { 40, 42}, {61, 42}, {81, 42}, {101, 42}, {122, 42}, {142, 42}, {162, 42}, {183, 42}, {203, 42}, {224, 42},
        {  0, 64}, { 20, 64}, { 40, 64}, {61, 64}, {81, 64}, {85, 64}, {94, 64}, {103, 64}, {112, 64}, {122, 64}, {142, 64}, {162, 64}, {183, 64}, {203, 64}, {224, 64}
    
    }, {
        // LED Index to Flag
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 1,
        1, 1, 1, 1, 1, 1 ,1 ,1, 1, 1, 1, 1, 1, 1, 1 
       
    }
};
#endif
