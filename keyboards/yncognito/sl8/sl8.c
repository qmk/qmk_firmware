/* Copyright 2021 Yncognito
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

#include "sl8.h"

#ifdef RGB_MATRIX_ENABLE
led_config_t g_led_config ={
    {
        {0  ,2  ,4  ,6  },
        {1  ,3  ,5  ,7  }
	},
	{
        {0,0},{32,0},{64,0},{96,0},
        {128,0},{160,0},{192,0},{224,0}
    },
    {
        0x04,0x04,0x04,0x04,
        0x04,0x04,0x04,0x04
    }
};

#endif
