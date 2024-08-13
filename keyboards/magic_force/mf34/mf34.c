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

#include "quantum.h"

#ifdef RGB_MATRIX_ENABLE

// RGB Matrix 
led_config_t g_led_config = {
	{
    	// Key Matrix to LED Index
        {  0,  1,  2,  3 , 4,  5,  6},
        {  7,  8,  9,  10, 11, 12, 13 },
        {  14, 15, 16, 17, 18, 19, NO_LED },
        {  NO_LED, NO_LED, NO_LED, 20, 21, 22, 23 },
        {  NO_LED, 24, NO_LED, 25, 26, 27, NO_LED },
        {  28, 29, 30, NO_LED, 31, 32, 33 }
	}, {
		{0,  0}, {37,  0}, {74,  0}, {112,  0}, {149,  0}, {186,  0}, {224,  0},
        {0, 12}, {37, 12}, {74, 12}, {112, 12}, {149, 12}, {186, 12}, {224, 12},
        {0, 24}, {37, 24}, {74, 24}, {112, 17}, {149, 17}, {186, 17},
                                     {112, 38}, {149, 38}, {186, 38}, {224, 38},
                 {37, 51},           {112, 51}, {149, 51}, {186, 51},
        {0, 64}, {37, 64}, {74, 64},            {149, 64}, {186, 64}, {224, 64}
	}, {
        4,      4,      4,          4,      4,      4,      4,
        4,      4,      4,          4,      4,      4,      4,
        4,      4,      4,          4,      4,      4,
                                    4,      4,      4,      4,
                4,                  4,      4,      4,
        4,      4,      4,                  4,      4,      4
	}
};
#endif
