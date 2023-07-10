/* Copyright 2023 Sam Kelly (@samkellu)
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
#include <stdio.h>
#include "bongo80.h"
#include "oled.h"

#ifdef OLED_ENABLE

// Time per frame in millis
#define FRAME_LENGTH_SLOW 400
#define FRAME_LENGTH_MED 300
#define FRAME_LENGTH_FAST 200

// Framesets for each typing state
struct frame_set no_caps[] = {
	{.frames = idle_no_caps, .len = idle_len, .frame_len = FRAME_LENGTH_SLOW},
	{.frames = slow_no_caps, .len = slow_len, .frame_len = FRAME_LENGTH_SLOW},
	{.frames = med_no_caps, .len = med_len, .frame_len = FRAME_LENGTH_MED},
	{.frames = fast_no_caps, .len = fast_len, .frame_len = FRAME_LENGTH_FAST}
};

struct frame_set caps[] = {
	{.frames = idle_caps, .len = idle_len, .frame_len = FRAME_LENGTH_SLOW},
	{.frames = slow_caps, .len = slow_len, .frame_len = FRAME_LENGTH_SLOW},
	{.frames = med_caps, .len = med_len, .frame_len = FRAME_LENGTH_MED},
	{.frames = fast_caps, .len = fast_len, .frame_len = FRAME_LENGTH_FAST}
};

struct frame_set* frame_sets[] = {no_caps, caps};
struct frame_set* curr_frame_set = &no_caps[0];
int curr_frame_index = 0;

int curr_wpm = 0;
led_t led_usb_state;
bool run_oled = 1;
uint32_t time = 0;

static void render_animate(void) {

	// Writes the WPM to the screen
	char to_write[32];
	if (led_usb_state.caps_lock) {
		sprintf(to_write, "WPM:%d CAPS  ", curr_wpm);
	} else {
		sprintf(to_write, "WPM:%d       ", curr_wpm);
	}

	oled_set_cursor(0, 7);
	oled_write(to_write, false);
	oled_set_cursor(0, 0);

	// Updates frame being displayed based on set interval
    if (timer_elapsed(time) > curr_frame_set->frame_len) {

        time = timer_read();

		// Ensures a smoothly animated transition between the different states of the animation
		if (curr_frame_index == curr_frame_set->len - 1) {

			// Assigns frameset based on typing speed
			int frame_set_index = 0;
			if (curr_wpm <= 3) {
				frame_set_index = IDLE;

			} else if (curr_wpm <= 20) {
				frame_set_index = SLOW;

			} else if (curr_wpm <= 35) {
				frame_set_index = MED;

			} else {
				frame_set_index = FAST;
			}

			curr_frame_set = &frame_sets[led_usb_state.caps_lock][frame_set_index];
			curr_frame_index = 0;

		} else {
        	curr_frame_index++;
		}

		oled_write_raw_P(curr_frame_set->frames[curr_frame_index], frame_size);
    }
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
		// Handles the keycode for turning on and off the oled screen
		case KC_OLED_STATE:
			if (record->event.pressed) {
				run_oled = !run_oled;
				oled_clear();
			}
			return false;
	}
	return true;
}

bool oled_task_kb() {

	curr_wpm = get_current_wpm();
	led_usb_state = host_keyboard_led_state();
	if (run_oled) {
    	render_animate();
	}
    return false;
}

#endif

