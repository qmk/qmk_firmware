/* Copyright 2020 Stephen J. Bush
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

# Description

Use encoders to control mouse movement. Movement speed is determined by
how quickly and how many times you've "clicked" the encoder. Turning both
encoders together will yield diagonal movement.

Several of the macros defined in quantum/mousekey.h are reused here.
However, the mouse movement is actually performed using the pointing_device
features instead.

# Usage

- Add the following to your rules.mk

        ENCODER_ENABLE = yes       # Enables the use of one or more encoders
        POINTING_DEVICE_ENABLE = yes

- Add the following block to your keymap.c

        #ifdef ENCODER_ENABLE
        void encoder_update_user(uint8_t index, bool clockwise) {
        #    ifdef POINTING_DEVICE_ENABLE
            encoder_update_mouse(index, clockwise);
        #    endif
            return;
        #endif

# Description

- The faster you turn, the faster the mouse moves.
- The more turns for a given axis, the greater the movement on that axis.

*/

#include QMK_KEYBOARD_H
#include "etchamouse.h"
#include "pointing_device.h"

#ifdef POINTING_DEVICE_ENABLE
#    ifdef ENCODER_ENABLE

/** Track movement separately in both directions. This will allow us to
 *  smooth out the movement along diagonals
 */
typedef struct {
    bool     clockwise;
    uint8_t  count;
    uint16_t timer;
    uint16_t elapsed;
} key_tracker_t;

static key_tracker_t tracker_x = {false, 0, 0, 0};
static key_tracker_t tracker_y = {false, 0, 0, 0};

/**
 * @brief Calculate the mouse move units for the given tracker.
 *
 * By using a key tracker rederence, we can minimize the amount of space
 * required on the stack. As we will have the tracker object, we will also
 * take the clockwise direction into account, which completely internalizes
 * the movement unit logic within this single function.
 *
 * @param tracker: Pointer to a key tracker object.
 * @return A integer from -127 to 127
 */
static int8_t move_unit(key_tracker_t *tracker) {
    if (0 == tracker->count) return 0;

    const uint16_t modifier = TAPPING_TERM_MOUSE_ENCODER < tracker->elapsed ? 1 : (TAPPING_TERM_MOUSE_ENCODER - tracker->elapsed) >> 1;
    uint16_t       speed    = MOUSEKEY_INITIAL_SPEED + MOUSEKEY_MOVE_DELTA * modifier * (tracker->count >> 1);

    /* convert speed to USB mouse speed 1 to 127 */
    speed = (uint8_t)(speed / (1000.0f / MOUSEKEY_INTERVAL));
    speed = speed < 1 ? 1 : speed;

    return (tracker->clockwise ? 1 : -1) * (speed > MOUSEKEY_MOVE_MAX ? MOUSEKEY_MOVE_MAX : speed);
}

/**
 * @brief Update key press tracker
 *
 * Update the time elapsed since the last keypress.
 * If the key has not been pressed since the tapping term, then reset the count to zero.
 * If the key was pressed, update the timer and increment the count.
 * Number of keypresses will degrade based on tapping term and zero out based
 * on the persistenc term.
 *
 * @param tracker: The object to update
 * @param pressed: A boolean indicating whether or not the key was pressed
 * @return None.
 */
static void update_tracker(key_tracker_t *tracker, bool pressed, bool clockwise) {
    tracker->elapsed = timer_elapsed(tracker->timer);
    if (pressed) {
        tracker->timer = timer_read();
        tracker->count += 1;
        tracker->clockwise = clockwise;
    } else if (TAPPING_TERM_PERSISTENCE < tracker->elapsed) {
        tracker->count = 0;
    } else if (TAPPING_TERM_MOUSE_ENCODER < tracker->elapsed) {
        tracker->count >>= 1;
    }
}

bool encoder_update_mouse(uint8_t index, bool clockwise) {
    report_mouse_t curr_report = pointing_device_get_report();

    update_tracker(&tracker_x, 0 == index, clockwise);
    update_tracker(&tracker_y, 1 == index, clockwise);

    curr_report.x += move_unit(&tracker_x);
    curr_report.y += move_unit(&tracker_y);

    pointing_device_set_report(curr_report);
    pointing_device_send();

    return true;
}

#    endif
#endif
