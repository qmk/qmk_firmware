/*
Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <stdint.h>
#include "host.h"
#include "report.h"

#if defined(POINTING_DEVICE_DRIVER_adns5050)
#    include "drivers/sensors/adns5050.h"
#elif defined(POINTING_DEVICE_DRIVER_adns9800)
#    include "spi_master.h"
#    include "drivers/sensors/adns9800.h"
#elif defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
#    include "i2c_master.h"
#    include "drivers/sensors/pimoroni_trackball.h"
#elif defined(POINTING_DEVICE_DRIVER_pmw3360)
#    include "spi_master.h"
#    include "drivers/sensors/pmw3360.h"
#endif

void           pointing_device_init(void);
void           pointing_device_task(void);
void           pointing_device_send(void);
report_mouse_t pointing_device_get_report(void);
void           pointing_device_set_report(report_mouse_t newMouseReport);
bool           has_mouse_report_changed(report_mouse_t new, report_mouse_t old);

void           pointing_device_init_kb(void);
void           pointing_device_init_user(void);
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
