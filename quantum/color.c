/* Copyright 2017 Jason Williams
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


#include "color.h"
#include "led_tables.h"
#include "progmem.h"

RGB hsv_to_rgb( HSV hsv )
{
	RGB rgb;
	uint8_t region, p, q, t;
	uint16_t h, s, v, remainder;

	if ( hsv.s == 0 )
	{
		rgb.r = hsv.v;
		rgb.g = hsv.v;
		rgb.b = hsv.v;
		return rgb;
	}

	h = hsv.h;
	s = hsv.s;
	v = hsv.v;

	region = h / 43;
	remainder = (h - (region * 43)) * 6;

	p = (v * (255 - s)) >> 8;
	q = (v * (255 - ((s * remainder) >> 8))) >> 8;
	t = (v * (255 - ((s * (255 - remainder)) >> 8))) >> 8;

	switch ( region )
	{
		case 0:
			rgb.r = v;
			rgb.g = t;
			rgb.b = p;
			break;
		case 1:
			rgb.r = q;
			rgb.g = v;
			rgb.b = p;
			break;
		case 2:
			rgb.r = p;
			rgb.g = v;
			rgb.b = t;
			break;
		case 3:
			rgb.r = p;
			rgb.g = q;
			rgb.b = v;
			break;
		case 4:
			rgb.r = t;
			rgb.g = p;
			rgb.b = v;
			break;
		default:
			rgb.r = v;
			rgb.g = p;
			rgb.b = q;
			break;
	}

	rgb.r = pgm_read_byte( &CIE1931_CURVE[rgb.r] );
	rgb.g = pgm_read_byte( &CIE1931_CURVE[rgb.g] );
	rgb.b = pgm_read_byte( &CIE1931_CURVE[rgb.b] );

	return rgb;
}

