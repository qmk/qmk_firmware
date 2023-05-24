/* Copyright 2020 marksard
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

#include "rev1.h"

// Optional override functions below.
// You can leave any or all of these undefined.
// These are only required if you want to perform custom actions.

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
    {  10,  11,  12,  13,   0 },
    {   9,  18,  19,  14,   1 },
    {   8,  17,  16,  15,   2 },
    {   7,   6,   5,   4,   3 },
    {  30,  31,  32,  33,  20 },
    {  29,  38,  39,  34,  21 },
    {  28,  37,  36,  35,  22 },
    {  27,  26,  25,  24,  23 }
}, {
    { 100,   0 }, { 100,  21 }, { 100,  43 }, { 100,  64 },
    {  75,  64 }, {  50,  64 }, {  25,  64 }, {   0,  64 },
    {   0,  43 }, {   0,  21 }, {   0,   0 },
    {  25,   0 }, {  50,   0 }, {  75,   0 },
    {  75,  21 }, {  75,  43 },
    {  50,  43 }, {  25,  43 },
    {  25,  21 }, {  50,  21 },
    { 125,   0 }, { 125,  21 }, { 125,  43 }, { 125,  64 },
    { 150,  64 }, { 175,  64 }, { 200,  64 }, { 225,  64 },
    { 225,  43 }, { 225,  21 }, { 225,   0 },
    { 200,   0 }, { 175,   0 }, { 150,   0 },
    { 150,  21 }, { 150,  43 },
    { 175,  43 }, { 200,  43 },
    { 200,  21 }, { 150,  21 }
}, {
    4, 4, 4, 1,
    1, 1, 1, 1,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 1,
    1, 1, 1, 1,
    4, 4, 4, 4,
    4, 4, 4, 4,
    4, 4, 4, 4
} };
#endif
