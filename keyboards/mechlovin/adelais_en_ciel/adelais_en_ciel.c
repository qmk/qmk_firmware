/* Copyright 2020 Team Mechlovin'
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

#include "adelais_en_ciel.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = { {
  //Key Matrix to LED Index
  {1,         2,         3,           4,          5,          6,          7,          8,          9,          10,         11,          12,          13,          14,          16},
  {18,        19,        20,          21,         22,         23,         24,         25,         26,         27,         28,          29,          30,          31,          0},
  {33,        34,        35,          36,         37,         38,         39,         40,         41,         42,         43,          44,          NO_LED,      45,          17},
  {46,        NO_LED,    47,          48,         49,         50,         51,         52,         53,         54,         55,          56,          58,          60,          32},
  {61,        NO_LED,    62,          NO_LED,     63,         NO_LED,     64,         NO_LED,     65,         NO_LED,     66,          NO_LED,      NO_LED,      57,          67}
}, {
  //LED Index to Physical Positon
  {0,0},      { 17,  0},  { 34, 0 },  { 51, 0 },  { 69, 0},   { 86, 0},   {100, 0},   {103, 0},   { 120, 0},  { 138, 0},  { 155, 0},  { 172, 0},  { 189, 0},    {207,  0},   {215,  0},   {223, 0},   {224, 0},
  {0,16},     { 17, 16},  { 34,16 },  { 51,16 },  { 69,16},   { 86,16},   {103,16},               { 120,16},  { 138,16},  { 155,16},  { 172,16},  { 189,16},    {207, 16},   {215, 16},   {224,16},
  {0,32},     { 17, 32},  { 34,32 },  { 51,32 },  { 69,32},   { 86,32},   {103,32},   { 120,32},  { 138,32},  { 155,32},  { 172,32},  { 189,32},  {207, 32},    {224,32},
              { 17, 48},  { 34,48 },  { 51,48 },  { 69,48},   { 86,48},   {103,48},   { 120,48},  { 138,48},  { 155,48},  { 172,48},  { 189,48},  {207, 48},    {215, 48},   {224,48},    {224,48},    
              { 17, 64},              { 51,64 },              { 86,64},   { 103,64},              { 138,64},              { 172,64},              {224, 64},
  {100,0},    { 69,0},    { 24, 0},   { 0,3},     { 0,16},    { 0,32},    { 0,51},    { 15,64 },  { 34,64},   { 69,64},   { 103,64},   {110,64},  { 120,64},    { 155,64},   { 189,64},  { 192,64},  { 224,58},  { 224,32},  { 224,16},  { 224,0},  { 207,0},  { 172,0},  { 138,0},
}, {
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,            1,           1,           1,  
  1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1,          1, 
} };
#endif

void matrix_init_kb(void) {
    // put your keyboard start-up code here
    // runs once when the firmware starts up

    matrix_init_user();
    led_init_ports();
}

void led_init_ports(void) {
    setPinOutput(B2);
    writePinLow(B2);
    setPinOutput(C15);
    writePinLow(C15);
    setPinOutput(B9);
    writePinLow(B9);
}

bool led_update_kb(led_t led_state) {
    if(led_update_user(led_state)) {
        writePin(B2, led_state.caps_lock);
        writePin(B9, led_state.scroll_lock);
        writePin(C12, led_state.num_lock);
    }

    return true;
}
