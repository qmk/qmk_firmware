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

#ifndef ANALOG_JOYSTICK_AXIS_MIN
#    define ANALOG_JOYSTICK_AXIS_MIN 0
#endif
#ifndef ANALOG_JOYSTICK_AXIS_MAX
#    define ANALOG_JOYSTICK_AXIS_MAX 1023
#endif
#ifndef ANALOG_JOYSTICK_SPEED_REGULATOR
#    define ANALOG_JOYSTICK_SPEED_REGULATOR 20
#endif
#ifndef ANALOG_JOYSTICK_SPEED_MAX
#    define ANALOG_JOYSTICK_SPEED_MAX 2
#endif
#ifndef ANALOG_JOYSTICK_CLICK_PIN
#    define ANALOG_JOYSTICK_CLICK_PIN NO_PIN
#endif
typedef struct {
    pin_t    x;
    pin_t    y;
    pin_t    button;
    uint16_t axis_min;
    uint16_t axis_max;
    uint8_t  speed_regulator;
    uint8_t  speed_max;
} analog_joystick_config_t;

typedef struct {
    int8_t x;
    int8_t y;
    bool   button;
} report_analog_joystick_t;

const pointing_device_driver_t analog_joystick_driver_default;

#if defined(ANALOG_JOYSTICK_X_AXIS_PIN) & defined(ANALOG_JOYSTICK_Y_AXIS_PIN)
const analog_joystick_config_t analog_joystick_config_default;
#endif

report_analog_joystick_t analog_joystick_read(analog_joystick_config_t* analog_config);
void                     analog_joystick_init(const void* config);
report_mouse_t           analog_joystick_get_report(const void* config);
