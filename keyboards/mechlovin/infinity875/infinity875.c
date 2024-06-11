/* Copyright 2021 Mechlovin' Studio
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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {0,          1,         2,           3,          4,          6,          7,          8,          9,         10,         11,          12,          13,          14,          15,         16,         17},
  {NO_LED, NO_LED,   NO_LED,      NO_LED,      NO_LED,    NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED},
  {NO_LED, NO_LED,    NO_LED,      NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,     NO_LED,      NO_LED,     NO_LED,      NO_LED,      NO_LED,      NO_LED,     NO_LED,     NO_LED}
}, {
  //LED Index to Physical Positon
  {0,0},  {14,0},    {28,0},      {42,0},     {56,0},     {67,0},     {70,0},     {84,0},     {98,0},    {112,0},    {126,0},     {140,0},     {154,0},     {168,0},     {182,0},     {196,0},    {210,0},     {224,0},
  {224,13},          {196,13},                {182,13},               {154,13},               {112,13},                           {84,13},                  {56,13},     {28,13},                 {0,13},
  {0,25},                                                                                                                                                                                         {0,38},
  {0,51},                                                                                                                                                                                         {0,64},
  {28,64},                                                                                                                                                                                        {56,64},
  {84,64},           {112,64},                {154,64},                           {182,64},              {196,64},                {224,64},    {224,51},                 {224,38},                {224,25},
//{244,64},          {196,64},                {182,64},                           {154,64},              {112,64},                {84,64},     {56,64},                  {28,64},                 {0,64},
}, {
      1,       1,         1,           1,          1,          1,          1,          1,          1,          1,           1,          1,           1,           1,           1,           1,          1,           1,
      1,                  1,                       1,                      1,                      1,                                   1,                        1,           1,                       1,
      1,                                                                                                                                                                                                1,
      1,                                                                                                                                                                                                1,
      1,                                                                                                                                                                                                1,
      1,                  1,                       1,                                  1,                      1,                       1,           1,                        1,                       1,
} };
#endif

