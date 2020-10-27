/* Copyright 2020 zvecr <git@zvecr.com>
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
 #ifndef ENCODER_ENABLE
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
                 {  10,  0  }, {  27,  0  }, {  45,   0 }, {  65,  0  }, {  65,  15 }, {  73,  46 }, {  93,  46 },
		 {  93,  60 }, {  65,  60 }, {  45,  40 }, {  27,  40 }, {  37,  10 }, {  28,  10 }, {  10,  10 },
		 // Left Key backlight
		 {  0 ,  2  }, {  13,  2  }, {  27,  1  }, {  41,  0  }, {  54,   1 }, {  68,   2 }, {  92,   2 }, 
                 {  92,  13 }, {  77,  12 }, {  62,  11 }, {  46,  10 }, {  31,  11 }, {  15,  12 }, {  0 ,  12 },
		 {  0 ,  20 }, {  15,  20 }, {  31,  21 }, {  46,  20 }, {  62,  21 }, {  77,  20 },
		 {  92,  27 }, {  77,  32 }, {  62,  31 }, {  46,  30 }, {  31,  31 }, {  15,  32 }, {  0 ,  32 },
		 {  0 ,  42 }, {  15,  42 }, {  31,  41 }, {  46,  39 }, {  62,  41 }, { 108,  37 }, { 123,  44 },
                               { 115,  54 }, { 108,  64 }, {  93,  59 }, {  78,  54 }, {  85,  49 }, { 100,  44 },
		 // Left Underglow
                 {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
		 {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 }, {  16,  20 },
		 // Left Key backlight
		 {  50,  48 }, {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 },
                 {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
		 {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 },
		 {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, 
		 {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, 
		               {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }

     },
      // LED Index to Flag
	 {
	     // Underglow
                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		 // Key backlight
                 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		   4,4,4,4,4,4,
		 // Underglow
                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		 // Key backlight
                 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		   4,4,4,4,4,4
     } 
};
 #endif


 #ifdef ENCODER_ENABLE
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
                 {  10,  0  }, {  27,  0  }, {  45,   0 }, {  65,  0  }, {  65,  15 }, {  73,  46 }, {  93,  46 },
		 {  93,  60 }, {  65,  60 }, {  45,  40 }, {  27,  40 }, {  37,  10 }, {  28,  10 }, {  10,  10 },
		 // Left Key backlight
		 {  0 ,  2  }, {  13,  2  }, {  27,  1  }, {  41,  0  }, {  54,   1 }, {  68,   2 }, {  92,   2 }, 
                 {  92,  13 }, {  77,  12 }, {  62,  11 }, {  46,  10 }, {  31,  11 }, {  15,  12 }, {  0 ,  12 },
		 {  0 ,  20 }, {  15,  20 }, {  31,  21 }, {  46,  20 }, {  62,  21 }, {  77,  20 },
		 {  92,  27 }, {  77,  32 }, {  62,  31 }, {  46,  30 }, {  31,  31 }, {  15,  32 }, {  0 ,  32 },
		 {  0 ,  42 }, {  15,  42 }, {  31,  41 }, {  46,  39 }, {  62,  41 }, { 108,  37 }, { 123,  44 },
                               { 115,  54 }, { 108,  64 }, {  93,  59 }, {  78,  54 }, {  85,  49 }, { 100,  44 },
		 // Left Underglow
                 {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
		 {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 }, {  16,  20 },
		 // Left Key backlight
		 {  50,  48 }, {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 },
                 {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 },
		 {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 },
		 {  16,  20 }, {  16,  38 }, {  50,  48 }, {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, 
		 {  68,   2 }, {  68,  19 }, {  85,  16 }, {  50,  13 }, {  16,  20 }, {  16,  38 }, {  50,  48 }, 
		               {  85,  52 }, {  95,  63 }, {  85,  21 }, {  85,   4 }, {  68,   2 }, {  68,  19 }

     },
      // LED Index to Flag
	 {
	     // Underglow
                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 
		 // Key backlight
                 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		   4,4,4,4,4,4,
		 // Underglow
                 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		 // Key backlight
                 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		 4,4,4,4,4,4,4,
		   4,4,4,4,4,4
     } 
};
#endif

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

#endif

void matrix_init_kb(void) {
    #ifdef RGB_MATRIX_ENABLE
    if (!is_keyboard_master())
    {
      swap_matrix_hands(&g_led_config);
    }
    #endif
}
