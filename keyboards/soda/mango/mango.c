/*
Copyright 2015 Álvaro "Gondolindrim" Volpato  <gondolindrim@acheronproject.com>

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

#include "mango.h"

#ifdef RGB_MATRIX_ENABLE

// RGB Matrix 
led_config_t g_led_config = {
	{
    	// Key Matrix to LED Index
                {  13, 14,  15,  16      },
                {  10, 11,  12,  NO_LED  },
                {  6,  7,   8,   9       },
                {  3,  4,   5,    NO_LED  },
                {  NO_LED,  0,  1,  2   },
	}, {
                    {32, 64},      {150, 64}, {224,  64},
                {0, 48}, {75, 48}, {150, 48},
                {0, 32}, {75, 32}, {150, 32}, {224, 24},
                {0, 16}, {75, 16}, {150, 16},
                {0, 0},  {75, 0},  {150, 0 }, {224, 0},
               
                
                
                    
	}, {
                4,      4,      4,      4,
                4,      4,      4,
                4,      4,      4,      4,
                4,      4,      4,
                        4,      4,      4
	}
};

#endif
