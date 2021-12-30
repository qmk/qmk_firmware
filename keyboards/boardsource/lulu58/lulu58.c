/*
Copyright 2020 Cole Smith <cole@boadsource.xyz>

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

#include "lulu58.h"
#ifdef RGB_MATRIX_ENABLE

led_config_t g_led_config = { {
    {12,11,10,9 ,8 ,7 },
    {18,17,16,15,14,13},
    {24,23,22,21,20,19},
    {30,29,28,27,26,25},
    {NO_LED,35,34,33,32,31},
    {42,43,44,45,46,47},
    {48,49,50,51,52,53},
    {54,55,56,57,58,59},
    {60,61,62,63,64,65},
    {NO_LED,66,67,68,69,70}
},{

  {86,55},{51,55},{17,40},{17,10},{51,10},{86,10},
  {0,0}, {17,0}, {34,0}, {51,0}, {68,0}, {86,0},
  {0,16},{17,16},{34,16},{51,16},{68,16},{86,16},
  {0,32},{17,32},{34,32},{51,32},{68,32},{86,32},
  {0,48},{17,48},{34,48},{51,48},{68,48},{86,48},{103,48},
                 {34,64},{51,64},{68,64},{86,64},


  {137,55},{172,55},{206,40},{206,10},{172,10},{137,10},
  {137,0}, {155,0}, {172,0}, {189,0}, {206,0}, {224,0},
  {137,16},{155,16},{172,16},{189,16},{206,16},{224,16},
  {137,32},{155,32},{172,32},{189,32},{206,32},{224,32},
  {137,48},{155,48},{172,48},{189,48},{155,48},{137,48},{120,48},
                    {172,64},{189,64},{155,64},{137,64}
},{2,2,2,2,2,2,
   4,4,4,4,4,1,
   1,4,4,4,4,4,
   4,4,4,4,4,1,
   1,4,4,4,4,4,
   1,4,1,1,1,
   2,2,2,2,2,2,
   4,4,4,4,4,1,
   1,4,4,4,4,4,
   4,4,4,4,4,1,
   1,4,4,4,4,4,
   1,4,1,1,1
}};

void suspend_power_down_kb(void) {
    rgb_matrix_set_suspend_state(true);
    suspend_power_down_user();
}

void suspend_wakeup_init_kb(void) {
    rgb_matrix_set_suspend_state(false);
    suspend_wakeup_init_user();
}
#endif


