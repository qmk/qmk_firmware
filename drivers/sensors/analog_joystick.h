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

#pragma once

#include <stdbool.h>
#include <stdint.h>
#include "pointing_device.h"

#ifndef ANALOG_JOYSTICK_X_AXIS_PIN
#    error No pin specified for X Axis
#endif
#ifndef ANALOG_JOYSTICK_Y_AXIS_PIN
#    error No pin specified for Y Axis
#endif

#ifndef ANALOG_JOYSTICK_AXIS_MIN
#    define ANALOG_JOYSTICK_AXIS_MIN 0
#endif
#ifndef ANALOG_JOYSTICK_AXIS_MAX
#    define ANALOG_JOYSTICK_AXIS_MAX 1023
#endif
#ifndef ANALOG_JOYSTICK_SPEED_REGULATOR
#    define ANALOG_JOYSTICK_SPEED_REGULATOR 20
#endif
#ifndef ANALOG_JOYSTICK_READ_INTERVAL
#    define ANALOG_JOYSTICK_READ_INTERVAL 10
#endif
#ifndef ANALOG_JOYSTICK_SPEED_MAX
#    define ANALOG_JOYSTICK_SPEED_MAX 2
#endif

const pointing_device_driver_t analog_joystick_pointing_device_driver;

typedef struct {
    int8_t x;
    int8_t y;
    bool   button;
} report_analog_joystick_t;
report_analog_joystick_t analog_joystick_read(void);
void                     analog_joystick_init(void);
report_mouse_t           analog_joystick_get_report(report_mouse_t mouse_report);
