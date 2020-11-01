/* Copyright 2020 fruitkt
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
#include "rev2.h"
#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config = {
         // Key Matrix to LED Index
	 {
         // Left
         {   15,16,17,18,19,20,21    }, 
         {   28,27,26,25,24,23,22    }, 
         {   29,30,31,32,33,34,NO_LED}, 
         {   41,40,39,38,37,36,35    }, 
         {   42,43,44,45,46,53,54    }, 
         {   NO_LED,52,51,50,49,48,47}, 
	 // Right
         {   70,71,72,73,74,75,76    }, 
         {   83,82,81,80,79,78,77    }, 
         {   84,85,86,87,88,89,NO_LED}, 
         {   96,95,94,93,92,91,90    }, 
         {  97,98,99,100,101,108,109 }, 
         {NO_LED,107,106,105,104,103,102} 
     },
    // LED Index to Physical Position 
   	 {
		 // Left Underglow
                 {  28,  11 }, {  45,  7  }, {  67,  11 }, {  73,  18 }, {  73,  28 }, {  73,  36 }, {  95,  41 },
		 {  90,  50 }, {  78,  46 }, /*{  64,  41 },*/ {  50,  36 }, {  28,  38 }, {  17,  32 }, {  17,  23 },
                 {  17,  16 },
		 // Left Key backlight
		 {  11,  14 }, {  22,  14 }, {  34,  12 }, {  45,  11 }, {  56,  12 }, {  67,  13 }, {  78,  13 }, 
                 {  78,  23 }, {  68,  20 }, {  56,  19 }, {  45,  18 }, {  34,  19 }, {  22,  21 }, {  11,  21 },  
		 {  11,  28 }, {  22,  28 }, {  34,  26 }, {  45,  25 }, {  56,  26 }, {  67,  27 },
		 {  67,  34 }, {  56,  33 }, {  45,  32 }, {  46,  30 }, {  34,  33 }, {  22,  36 }, {  11,  36 },
		 {  15,  43 }, {  22,  43 }, {  34,  38 }, {  45,  39 }, {  56,  41 }, {  90,  39 }, { 107,  41 },
                               {  95,  48 }, {  95,  37 }, {  84,  48 }, {  71,  46 }, {  87,  43 }, {  78,  41 },
		 // Right Underglow
                 { 196,  11 }, { 179,  7  }, { 157,  11 }, { 151,  18 }, { 151,  28 }, { 146,  36 }, { 123,  41 },
		 { 134,  50 }, { 146,  46 },/* { 160,  41 },*/ { 174,  36 }, { 196,  38 }, { 218,  32 }, { 218,  23 },
                 { 218,  16 },
		 // Right Key backlight
		 { 213,  14 }, { 202,  14 }, { 190,  12 }, { 179,  11 }, { 162,  12 }, { 157,  13 }, { 148,  13 },
                 { 146,  23 }, { 157,  20 }, { 162,  19 }, { 179,  18 }, { 190,  19 }, { 202,  21 }, { 213,  21 },
		 { 213,  28 }, { 202,  28 }, { 190,  26 }, { 179,  25 }, { 162,  26 }, { 157,  27 },
		 { 146,  32 }, { 157,  34 }, { 162,  33 }, { 179,  32 }, { 190,  33 }, { 202,  36 }, { 213,  36 }, 
		 { 209,  43 }, { 202,  43 }, { 190,  41 }, { 179,  39 }, { 160,  41 }, { 134,  39 }, { 123,  41 }, 
		 { 129,  48 }, { 131,  57 }, { 140,  50 }, { 153,  46 }, { 140,  43 }, { 149,  41 }


     },
      // LED Index to Flag
	 {
	     // Underglow
                 2,2,2,2,2,2,2,
                 2,2,2,2,2,2,2,
		 // Key backlight
                 4,4,4,4,4,4,1,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,1,1,
		 // Underglow
                 2,2,2,2,2,2,2,
                 2,2,2,2,2,2,2,
		 // Key backlight
                 4,4,4,4,4,4,1,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,1,1
     } 
};
/*
void swap_matrix_hands(led_config_t* led_config)
{
    uint8_t uint8;
    point_t point;
    int i, j;

    int half_matrix_rows = MATRIX_ROWS / 2;
    int half_driver_led_total = DRIVER_LED_TOTAL / 2;

    for (i = 0; i < half_matrix_rows; i++)
    {
        for (j = 0; j < MATRIX_COLS; j++)
        {
            uint8 = led_config->matrix_co[i][j];
            led_config->matrix_co[i][j] = led_config->matrix_co[i + half_matrix_rows][j];
            led_config->matrix_co[i + half_matrix_rows][j] = uint8;
        }
    }

    for (i = 0; i < half_driver_led_total; i++)
    {
        point = led_config->point[i];
        led_config->point[i] = led_config->point[i + half_driver_led_total];
        led_config->point[i + half_driver_led_total] = point;
    }
}
*/
#endif
/*
void matrix_init_kb(void) {
    #ifdef RGB_MATRIX_ENABLE
    if (!is_keyboard_master())
    {
      swap_matrix_hands(&g_led_config);
    }
    #endif
}
*/

