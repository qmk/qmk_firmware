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

#include "analog.h"
#include "wait.h"

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
__attribute__((weak)) joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {};

__attribute__((weak)) void joystick_task(void) {
    joystick_read_axes();
}

void joystick_flush(void) {
    if (joystick_state.dirty) {
        host_joystick_send(&joystick_state);
        joystick_state.dirty = false;
    }
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

    // disable pull-up resistor
    writePinLow(joystick_axes[axis].input_pin);

    // if pin was a pull-up input, we need to uncharge it by turning it low
    // before making it a low input
    setPinOutput(joystick_axes[axis].input_pin);

    wait_us(10);

    if (joystick_axes[axis].output_pin != JS_VIRTUAL_AXIS) {
        setPinOutput(joystick_axes[axis].output_pin);
        writePinHigh(joystick_axes[axis].output_pin);
    }

    if (joystick_axes[axis].ground_pin != JS_VIRTUAL_AXIS) {
        setPinOutput(joystick_axes[axis].ground_pin);
        writePinLow(joystick_axes[axis].ground_pin);
    }

    wait_us(10);

    setPinInput(joystick_axes[axis].input_pin);

    wait_us(10);

#if defined(ANALOG_JOYSTICK_ENABLE) && (defined(__AVR__) || defined(PROTOCOL_CHIBIOS))
    int16_t axis_val = analogReadPin(joystick_axes[axis].input_pin);
#else
    // default to resting position
    int16_t axis_val = joystick_axes[axis].mid_digit;
#endif

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

void joystick_read_axes(void) {
#if JOYSTICK_AXIS_COUNT > 0
    for (int i = 0; i < JOYSTICK_AXIS_COUNT; ++i) {
        if (joystick_axes[i].input_pin == JS_VIRTUAL_AXIS) {
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
