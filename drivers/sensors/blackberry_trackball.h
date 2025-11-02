/*
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



/*
USAGE

In your rules.mk add:

POINTING_DEVICE_ENABLE = yes
POINTING_DEVICE_DRIVER = blackberry_trackball

Then define the following:

#define BLACKBERRY_TRACKBALL_DEBUG               (optional, if you want to read the recognized direction)
#define BLACKBERRY_TRACKBALL_STEP 30             (optional. Cursor moves faster or slower, if you don't define it, defualt step is 5)
#define BLACKBERRY_TRACKBALL_UP_PIN      pin_1   (required, where the "up" hall effect sensor is connected)
#define BLACKBERRY_TRACKBALL_DOWN_PIN    pin_2   (required, where the "down" hall effect sensor is connected)
#define BLACKBERRY_TRACKBALL_LEFT_PIN    pin_3   (required, where the "left" hall effect sensor is connected)
#define BLACKBERRY_TRACKBALL_RIGHT_PIN   pin_4   (required, where the "right" hall effect sensor is connected)
*/





#pragma once

#include "pointing_device.h"

#ifndef BLACKBERRY_TRACKBALL_STEP
#    define BLACKBERRY_TRACKBALL_STEP 5
#endif

#define M_UP 0
#define M_DOWN 1
#define M_LEFT 2
#define M_RIGHT 3


const pointing_device_driver_t blackberry_trackball_pointing_device_driver;
void blackberry_trackball_init(void);
report_mouse_t blackberry_trackball_get_report(report_mouse_t mouse_report);
