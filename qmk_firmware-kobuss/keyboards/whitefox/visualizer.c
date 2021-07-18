/* Copyright 2017 Fred Sundvik
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

#include "visualizer.h"
#include "visualizer_keyframes.h"
#include "default_animations.h"

static bool initial_update = true;

// Feel free to modify the animations below, or even add new ones if needed

void initialize_user_visualizer(visualizer_state_t *state) {
    // The brightness will be dynamically adjustable in the future
    // But for now, change it here.
    initial_update = true;
    start_keyframe_animation(&default_startup_animation);
}

void update_user_visualizer_state(visualizer_state_t *state, visualizer_keyboard_status_t *prev_status) {
    // Add more tests, change the colors and layer texts here
    // Usually you want to check the high bits (higher layers first)
    // because that's the order layers are processed for keypresses
    // You can for check for example:
    // state->status.layer
    // state->status.default_layer
    // state->status.leds (see led.h for available statuses)

    if (initial_update) {
        initial_update = false;
        start_keyframe_animation(&led_test_animation);
    }
}

void user_visualizer_suspend(visualizer_state_t *state) {
    start_keyframe_animation(&default_suspend_animation);
}

void user_visualizer_resume(visualizer_state_t *state) {
    initial_update = true;
    start_keyframe_animation(&default_startup_animation);
}
