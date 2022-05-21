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

// safe range starts at `PLOOPY_SAFE_RANGE` instead.
uint8_t scroll_enabled = 0;
uint8_t lock_state = 0;
int8_t  delta_x        = 0;
int8_t  delta_y        = 0;

// Dummy
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {{{ KC_NO }}};

void process_mouse_user(report_mouse_t *mouse_report, int8_t x, int8_t y) {
    if (scroll_enabled) {
        delta_x += x;
		delta_y += y;

		if (delta_x > 60) {
			mouse_report->h = 1;
			delta_x = 0;
		} else if (delta_x < -60) {
			mouse_report->h = -1;
			delta_x = 0;
		}

		if (delta_y > 15) {
			mouse_report->v = -1;
			delta_y = 0;
		} else if (delta_y < -15) {
			mouse_report->v = 1;
			delta_y = 0;
		}
    } else {
        mouse_report->x = x;
		mouse_report->y = y;
    }
}

void keyboard_post_init_user(void) {
	lock_state = host_keyboard_led_state().num_lock;
}

bool led_update_user(led_t led_state) {
	static uint8_t lock_count = 0;
	static uint16_t scroll_timer = 0;

	if (timer_elapsed(scroll_timer) > 25) {
		scroll_timer = timer_read();
		lock_count = 0;
	}

	if (led_state.num_lock != lock_state) {
		lock_count++;

		if (lock_count == 2) {
			scroll_enabled = !scroll_enabled;
			lock_count = 0;
			delta_x = 0;
			delta_y = 0;
		}
	}

	lock_state = led_state.num_lock;
	return true;
}
