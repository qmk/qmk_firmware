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
#include QMK_KEYBOARD_H

int16_t  delta_x = 0;
int16_t  delta_y = 0;

#define SCROLL_THRESHOLD_X 100
#define SCROLL_THRESHOLD_Y 100

#define SCROLL_TIMEOUT 500
#define CURSOR_TIMEOUT 700

report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
	static uint16_t scroll_timer;
	static bool scrolling = false;

	static uint16_t cursor_timer;
	static bool cursor = false;

	led_t leds = host_keyboard_led_state();

	if (mouse_report.x || mouse_report.y) {
		scroll_timer = timer_read();
		if (!scrolling) {
			scrolling = true;
			if (!leds.scroll_lock) {
				tap_code(KC_SCROLL_LOCK);
			}
		}
	} else if (scrolling && timer_elapsed(scroll_timer) > SCROLL_TIMEOUT) {
		scrolling = false;
		if (leds.scroll_lock) {
			tap_code(KC_SCROLL_LOCK);
		}
	}


	if (leds.caps_lock && leds.num_lock && leds.scroll_lock) {
		reset_keyboard();
	} else if (leds.num_lock) {
        delta_x += mouse_report.x;
		delta_y += mouse_report.y;
		mouse_report.x = mouse_report.y = 0;

		if (delta_x > SCROLL_THRESHOLD_X) {
			mouse_report.h = 1;
			delta_x = 0;
		} else if (delta_x < -SCROLL_THRESHOLD_X) {
			mouse_report.h = -1;
			delta_x = 0;
		}

		if (delta_y > SCROLL_THRESHOLD_Y) {
			mouse_report.v = -1;
			delta_y = 0;
		} else if (delta_y < -SCROLL_THRESHOLD_Y) {
			mouse_report.v = 1;
			delta_y = 0;
		}

		if (mouse_report.h || mouse_report.v) {
		cursor_timer = timer_read();
			if (!cursor) {
				cursor = true;
			}
		} else if (cursor && timer_elapsed(cursor_timer) > CURSOR_TIMEOUT) {
			cursor = false;
			if (leds.num_lock) {
				tap_code(KC_NUM_LOCK);
			}
		}
    }

	return mouse_report;
}
