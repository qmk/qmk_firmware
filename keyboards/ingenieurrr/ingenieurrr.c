/* Copyright 2020 Yncognito
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
led_config_t g_led_config ={
    	{
        {0  ,1  ,2  ,3, 4  ,5  ,6  ,16,17,18,19,20,21,7  },
        {22,23,24,	NO_LED,8,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED},
	{NO_LED,NO_LED,NO_LED,	NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,12,NO_LED,NO_LED,NO_LED,14,NO_LED},
	{NO_LED,NO_LED,9,	NO_LED,NO_LED,NO_LED,10,NO_LED,NO_LED,NO_LED,NO_LED,13,NO_LED,NO_LED},
	{NO_LED,NO_LED,NO_LED,11,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED,NO_LED}
	},

	{	
	{1,1},{10,1},{200,1},{30,1},{40,1},{50,1},{60,1},{70,1},{80,1},{90,1},{100,1},{110,1},{120,1},{130,1},{150,50}, {1,1},{10,1},{200,1},{30,1},{40,1},{50,1},{60,1},{70,1},{80,1},{90,1}
	},

    	{
        4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4
   	}
};

#endif
