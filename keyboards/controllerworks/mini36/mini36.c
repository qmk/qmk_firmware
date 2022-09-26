/*
 * Copyright 2022 Kevin Gee <info@controller.works>
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

#include "mini36.h"

#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = {{// Key Matrix to LED Index
                              {23, 18, 17, 10, 9},
                              {22, 19, 16, 11, 8},
                              {21, 20, 15, 12, 7},
                              {14, 13, 6, NO_LED, NO_LED},
                              {36, 37, 44, 45, 50},
                              {35, 38, 43, 46, 49},
                              {34, 39, 42, 47, 48},
                              {33, 40, 41, NO_LED, NO_LED}},
                             {// LED Index to Physical Position
                              // Left half
                              {71, 4},   {32, 2},   {0, 24},   {16, 51},  {63, 58},  {94, 55}, //Backlight LEDs
                              {90, 64},  {79, 39},  {79, 22},  {79, 5},   {61, 2},   {61, 19},
                              {61, 37},  {74, 58},  {53, 55},  {43, 34},  {43, 17},  {43, 0},
                              {25, 2},   {25, 19},  {25, 37},  {7, 41},   {7, 24},   {7, 7},
                              // Right half
                              {153, 4},  {192, 2},  {224, 24},  {204, 53}, {161, 57}, {130, 55}, //Backlight LEDs
                              {134, 64}, {145, 39}, {145, 22}, {145, 5},  {163, 2},  {163, 19},
                              {163, 37}, {150, 58}, {171, 55}, {181, 34}, {181, 17}, {181, 0},
                              {199, 2},  {199, 19}, {199, 37}, {217, 41}, {217, 24}, {217, 7}

                             },
                             {// LED Index to Flag
                              // 0x01 = 1 = modifier key
                              // 0x02 = 2 = underglow
                              // 0x04 = 4 = key backlight
                              // 0x08 = 8 = keyboard state indication
                              // Left half
                              2, 2, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4,
                              // Right half
                              2, 2, 2, 2, 2, 2, 1, 4, 4, 4, 4, 4, 4, 1, 1, 4, 4, 4, 4, 4, 4, 4, 4, 4 }};

#endif // RGB_MATRIX_ENABLE

