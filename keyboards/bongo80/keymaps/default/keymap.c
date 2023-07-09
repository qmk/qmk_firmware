// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "images.h"
#include <stdio.h>

enum keycodes {
	KC_OLED_STATE = SAFE_RANGE,
};

enum layers {
	_QWERTY, _MEDIA
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * ┌───┐ ┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┬───┬───┬───┐┌───┐ ┌───┬───┬───┐
     * │Esc│ │F1 │F2 │F3 │F4 ││F5 │F6 │F7 │F8 ││F9 │F10│F11│F12││Ole│ │Del│Psc│Hom│
     * └───┘ └───┴───┴───┴───┘└───┴───┴───┴───┘└───┴───┴───┴───┘└───┘ └───┴───┴───┘
     * ┌───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬───┬────────┐ ┌───┐
     * │ ` │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │ 7 │ 8 │ 9 │ 0 │ - │ = │ Backsp │ │VUp│ ┌──────┐
     * ├───┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬──────┤ ├───┤ │screen│
     * │ Tab │ Q │ W │ E │ R │ T │ Y │ U │ I │ O │ P │ [ │ ] │  \   │ │VDn│ └──────┘
     * ├─────┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴┬──┴──────┤ └───┘
     * │ Caps │ A │ S │ D │ F │ G │ H │ J │ K │ L │ ; │ ' │  Enter  │
     * ├──────┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─┬─┴─────────┤     ┌───┐
     * │ Shift  │ Z │ X │ C │ V │ B │ N │ M │ , │ . │ / │    Shift  │     │ ↑ │
     * ├────┬───┴┬──┴─┬─┴───┴───┴───┴───┴───┴──┬┴───┼───┴┬────┬─────┤ ┌───┼───┼───┐
     * │Ctrl│Meta│Alt │                        │ Alt│Meta│Menu│Ctrl │ │ ← │ ↓ │ → │
     * └────┴────┴────┴────────────────────────┴────┴────┴────┴─────┘ └───┴───┴───┘
     */
    [_QWERTY] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_OLED_STATE, KC_DEL, KC_PSCR, KC_HOME,

        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,       KC_AUDIO_VOL_UP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,       KC_AUDIO_VOL_DOWN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT,             KC_UP,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_RGUI, MO(_MEDIA),  KC_RCTL,    KC_LEFT, KC_DOWN, KC_RGHT
    ),

	[_MEDIA] = LAYOUT(
		QK_BOOT,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,   _______,  _______,  _______,

        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,   _______,
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,   _______,   _______,   _______,
        _______,   _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,              _______,
        _______,               _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,   _______,              _______,              _______,
        _______,   _______,    _______,                            _______,                            _______,    _______,    _______,   _______,     KC_MEDIA_PREV_TRACK,  KC_MEDIA_PLAY_PAUSE,  KC_MEDIA_NEXT_TRACK)
};

#ifdef OLED_ENABLE

// Time per frame in millis
#define FRAME_LENGTH_SLOW 400
#define FRAME_LENGTH_MED 300
#define FRAME_LENGTH_FAST 200

// Represents an animation, including the frames and length (time) per frame
struct frame_set {
	const int len;
	int frame_len;
	const char** frames;
};

enum state {
	IDLE = 0, SLOW = 1, MED = 2, FAST = 3
};

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

bool oled_task_user() {

	curr_wpm = get_current_wpm();
	led_usb_state = host_keyboard_led_state();
	if (run_oled) {
    	render_animate();
	}
    return false;
}

#endif
