/* Copyright 2022
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

#include "joystick.h"
#include "wait.h"

#if defined(JOYSTICK_ANALOG)
#    include "analog.h"
#endif

joystick_t joystick_state = {
    .buttons = {0},
    .axes =
        {
#if JOYSTICK_AXIS_COUNT > 0
            0
#endif
        },
    .dirty = false,
};

// array defining the reading of analog values for each axis
__attribute__((weak)) joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
#if JOYSTICK_AXIS_COUNT > 0
    [0 ...(JOYSTICK_AXIS_COUNT - 1)] = JOYSTICK_AXIS_VIRTUAL
#endif
};

__attribute__((weak)) void joystick_axis_init(uint8_t axis) {
    if (axis >= JOYSTICK_AXIS_COUNT) return;

#if defined(JOYSTICK_ANALOG)
    gpio_set_pin_input(joystick_axes[axis].input_pin);
#endif
}

__attribute__((weak)) uint16_t joystick_axis_sample(uint8_t axis) {
    if (axis >= JOYSTICK_AXIS_COUNT) return 0;

#if defined(JOYSTICK_ANALOG)
    return analogReadPin(joystick_axes[axis].input_pin);
#else
    // default to resting position
    return joystick_axes[axis].mid_digit;
#endif
}

static inline bool is_virtual_axis(uint8_t axis) {
    return joystick_axes[axis].input_pin == NO_PIN;
}

void joystick_flush(void) {
    if (!joystick_state.dirty) return;

    // TODO: host.h?
    void host_joystick_send(joystick_t * joystick);
    host_joystick_send(&joystick_state);
    joystick_state.dirty = false;
}

void register_joystick_button(uint8_t button) {
    if (button >= JOYSTICK_BUTTON_COUNT) return;

    joystick_state.buttons[button / 8] |= 1 << (button % 8);
    joystick_state.dirty = true;
    joystick_flush();
}

void unregister_joystick_button(uint8_t button) {
    if (button >= JOYSTICK_BUTTON_COUNT) return;

    joystick_state.buttons[button / 8] &= ~(1 << (button % 8));
    joystick_state.dirty = true;
    joystick_flush();
}

int16_t joystick_read_axis(uint8_t axis) {
    if (axis >= JOYSTICK_AXIS_COUNT) return 0;

    int16_t axis_val = joystick_axis_sample(axis);

    // test the converted value against the lower range
    int32_t ref        = joystick_axes[axis].mid_digit;
    int32_t range      = joystick_axes[axis].min_digit;
    int32_t ranged_val = ((axis_val - ref) * -JOYSTICK_MAX_VALUE) / (range - ref);

    if (ranged_val > 0) {
        // the value is in the higher range
        range      = joystick_axes[axis].max_digit;
        ranged_val = ((axis_val - ref) * JOYSTICK_MAX_VALUE) / (range - ref);
    }

    // clamp the result in the valid range
    ranged_val = ranged_val < -JOYSTICK_MAX_VALUE ? -JOYSTICK_MAX_VALUE : ranged_val;
    ranged_val = ranged_val > JOYSTICK_MAX_VALUE ? JOYSTICK_MAX_VALUE : ranged_val;

    return ranged_val;
}

void joystick_init_axes(void) {
#if JOYSTICK_AXIS_COUNT > 0
    for (int i = 0; i < JOYSTICK_AXIS_COUNT; ++i) {
        if (is_virtual_axis(i)) {
            continue;
        }

        joystick_axis_init(i);
    }
#endif
}

void joystick_read_axes(void) {
#if JOYSTICK_AXIS_COUNT > 0
    for (int i = 0; i < JOYSTICK_AXIS_COUNT; ++i) {
        if (is_virtual_axis(i)) {
            continue;
        }

        joystick_set_axis(i, joystick_read_axis(i));
    }

    joystick_flush();
#endif
}

void joystick_set_axis(uint8_t axis, int16_t value) {
    if (axis >= JOYSTICK_AXIS_COUNT) return;

    if (value != joystick_state.axes[axis]) {
        joystick_state.axes[axis] = value;
        joystick_state.dirty      = true;
    }
}

void joystick_init(void) {
    joystick_init_axes();
}

void joystick_task(void) {
    joystick_read_axes();
}
