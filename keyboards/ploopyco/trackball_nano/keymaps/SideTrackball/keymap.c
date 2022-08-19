/* Copyright 2021 Colin Lam (Ploopy Corporation)
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2019 Sunjun Kim
 * Copyright 2019 Hiroyuki Okada
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
#include "math.h"
#include QMK_KEYBOARD_H

#define ACCEL_FACTOR 8
#define SCROLL_X_THRESHOLD 60
#define SCROLL_Y_THRESHOLD 30
#define TRANSLATE_ANGLE 0
#define PRECISIONMODE_FACTOR 0.6
// safe range starts at `PLOOPY_SAFE_RANGE` instead.
uint8_t scroll_enabled = 0;
uint8_t lock_state = 0;
int16_t delta_x = 0;
int16_t delta_y = 0;
bool PloopyAcceleration;

void process_mouse_user(report_mouse_t *mouse_report, float x, float y) {

	//# If num lock and caps lock is registered, call the keyboard reset
	if (host_keyboard_led_state().num_lock && host_keyboard_led_state().caps_lock)
	{
		reset_keyboard();
	}
	//# If num lock is registered alone, start the scrolling action
	// https://www.reddit.com/r/ploopy/comments/nlvgkq/how_to_scroll_with_the_trackball_nano/
	else if (host_keyboard_led_state().num_lock) {

		delta_x += x;
		delta_y += y;
		
		if (delta_x > SCROLL_X_THRESHOLD) {
			mouse_report->h = 1;
			mouse_report->v = 0;
			delta_x = 0;
		} else if (delta_x < -SCROLL_X_THRESHOLD) {
			mouse_report->h = -1;
			mouse_report->v = 0;
			delta_x = 0;
		}
		else if (delta_y > SCROLL_Y_THRESHOLD) {
			mouse_report->v = -1;
			mouse_report->h = 0;
			delta_y = 0;
		} else if (delta_y < -SCROLL_Y_THRESHOLD) {
			mouse_report->v = 1;
			mouse_report->h = 0;
			delta_y = 0;
		}
	} 
	//# otherwise the ploopy performs as a mouse
	else {
		
		//# Working on a precision mode when scroll lock is pressed down
		// This is why this func gets float input instead of int now
		if(host_keyboard_led_state().scroll_lock)
		{
			x *= PRECISIONMODE_FACTOR;
			y *= PRECISIONMODE_FACTOR;
			if(x > 0 && x < 1) x = 1; 
			if(x < 0 && x  > -1) x = -1; 
			if(y > 0 && y < 1) y = 1; 
			if(y < 0 && y  > -1) y = -1; 
		}
		
		// https://www.reddit.com/r/ploopy/comments/nlvgkq/how_to_scroll_with_the_trackball_nano/
		if (PloopyAcceleration) {

			// Testing revealed the max reasonable x/y values were ~16.
			// `x*x/16 + x` results in ~2x speed at the max value, while maintaining 1x speed at the minimum.
			// But the x*x cancels the sign, so we need to negate it if the input value is negative.
			x = (x > 0 ? x*x/ACCEL_FACTOR+x : -x*x/ACCEL_FACTOR+x);
			y = (y > 0 ? y*y/ACCEL_FACTOR+y : -y*y/ACCEL_FACTOR+y);
		}

		//# working on offset rotation support, as I use my ploopy at a 45 deg angle
		// I'm actually used to the default angle now and this feels weird :s I wouldn't say this is neccessary
		if(TRANSLATE_ANGLE != 0)
		{
			double dx = cos(TRANSLATE_ANGLE) * x - sin(TRANSLATE_ANGLE) * y;
			double dy = sin(TRANSLATE_ANGLE) * x + cos(TRANSLATE_ANGLE) * y;
			x = dx;
			y = dy;
		}

		mouse_report->x = (int16_t) x;
		mouse_report->y = (int16_t) y;
	}
}


void keyboard_pre_init_user() {
	PloopyAcceleration = true;
}

double clamp(double d, double min, double max) {
  const double t = d < min ? min : d;
  return t > max ? max : t;
}