/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "analog_joystick.h"
#include "analog.h"
#include "gpio.h"
#include "wait.h"
#include "timer.h"
#include <stdlib.h>
#include "pointing_device_internal.h"

const pointing_device_driver_t analog_joystick_pointing_device_driver = {
    .init       = analog_joystick_init,
    .get_report = analog_joystick_get_report,
    .set_cpi    = NULL,
    .get_cpi    = NULL,
};

// Set Parameters
#ifndef ANALOG_JOYSTICK_AUTO_AXIS
uint16_t minAxisValue = ANALOG_JOYSTICK_AXIS_MIN;
uint16_t maxAxisValue = ANALOG_JOYSTICK_AXIS_MAX;
#else
int16_t minAxisValues[2];
int16_t maxAxisValues[2];
#endif

uint8_t maxCursorSpeed = ANALOG_JOYSTICK_SPEED_MAX;
uint8_t speedRegulator = ANALOG_JOYSTICK_SPEED_REGULATOR; // Lower Values Create Faster Movement

#ifdef ANALOG_JOYSTICK_WEIGHTS
int8_t weights[101] = ANALOG_JOYSTICK_WEIGHTS;
#endif

int16_t xOrigin, yOrigin;

uint16_t lastCursor = 0;

uint8_t prevValues[2] = {0, 0};

int16_t axisCoordinate(pin_t pin, uint16_t origin, uint8_t axis) {
    int8_t  direction;
    int16_t distanceFromOrigin;
    int16_t range;

    int16_t position = analogReadPin(pin);

    if (origin == position) {
        return 0;
    } else if (origin > position) {
        distanceFromOrigin = origin - position;
#ifdef ANALOG_JOYSTICK_AUTO_AXIS
        if (position < minAxisValues[axis]) {
            minAxisValues[axis] = position;
        }
        range = origin - minAxisValues[axis];
#else
        range = origin - minAxisValue;
#endif
        direction = -1;
    } else {
        distanceFromOrigin = position - origin;

#ifdef ANALOG_JOYSTICK_AUTO_AXIS
        if (position > maxAxisValues[axis]) {
            maxAxisValues[axis] = position;
        }
        range = maxAxisValues[axis] - origin;
#else
        range = maxAxisValue - origin;
#endif
        direction = 1;
    }

    float   percent    = (float)distanceFromOrigin / range;
    int16_t coordinate = (int16_t)(percent * 100);
    if (coordinate < 0) {
        return 0;
    } else if (coordinate > 100) {
        return 100 * direction;
    } else {
        return coordinate * direction;
    }
}

int8_t axisToMouseComponent(pin_t pin, int16_t origin, uint8_t maxSpeed, uint8_t axis) {
    int16_t coordinate = axisCoordinate(pin, origin, axis);
    int8_t  result;
#ifndef ANALOG_JOYSTICK_WEIGHTS
    if (coordinate != 0) {
        float percent = (float)coordinate / 100;
        result        = percent * maxCursorSpeed * (abs(coordinate) / speedRegulator);
    } else {
        return 0;
    }
#else
    result = weights[abs(coordinate)] * (coordinate < 0 ? -1 : 1) * maxCursorSpeed / speedRegulator;
#endif

#ifdef ANALOG_JOYSTICK_CUTOFF
    uint8_t pv       = prevValues[axis];
    prevValues[axis] = abs(result);
    if (pv > abs(result)) {
        return 0;
    }
#endif

    return result;
}

report_analog_joystick_t analog_joystick_read(void) {
    report_analog_joystick_t report = {0};

    if (timer_elapsed(lastCursor) > ANALOG_JOYSTICK_READ_INTERVAL) {
        lastCursor = timer_read();
        report.x   = axisToMouseComponent(ANALOG_JOYSTICK_X_AXIS_PIN, xOrigin, maxCursorSpeed, 0);
        report.y   = axisToMouseComponent(ANALOG_JOYSTICK_Y_AXIS_PIN, yOrigin, maxCursorSpeed, 1);
    }
#ifdef ANALOG_JOYSTICK_CLICK_PIN
    report.button = !gpio_read_pin(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    return report;
}

bool analog_joystick_init(void) {
    gpio_set_pin_input_high(ANALOG_JOYSTICK_X_AXIS_PIN);
    gpio_set_pin_input_high(ANALOG_JOYSTICK_Y_AXIS_PIN);

#ifdef ANALOG_JOYSTICK_CLICK_PIN
    gpio_set_pin_input_high(ANALOG_JOYSTICK_CLICK_PIN);
#endif
    // Account for drift
    xOrigin = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
    yOrigin = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);

#ifdef ANALOG_JOYSTICK_AUTO_AXIS
    minAxisValues[0] = xOrigin - 100;
    minAxisValues[1] = yOrigin - 100;
    maxAxisValues[0] = xOrigin + 100;
    maxAxisValues[1] = yOrigin + 100;
#endif

    return true;
}

report_mouse_t analog_joystick_get_report(report_mouse_t mouse_report) {
    report_analog_joystick_t data = analog_joystick_read();

    pd_dprintf("Raw ] X: %d, Y: %d\n", data.x, data.y);

    mouse_report.x = data.x;
    mouse_report.y = data.y;

    mouse_report.buttons = pointing_device_handle_buttons(mouse_report.buttons, data.button, POINTING_DEVICE_BUTTON1);

    return mouse_report;
}
