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

void           pointing_device_init(void);
void           pointing_device_task(void);
void           pointing_device_send(void);
report_mouse_t pointing_device_get_report(void);
void           pointing_device_set_report(report_mouse_t newMouseReport);
bool           has_mouse_report_changed(report_mouse_t new, report_mouse_t old);


typedef struct {
    uint8_t buttons;
    int8_t  x;
    int8_t  y;
} short_mouse_t;

typedef struct {
    void (*init)(void);
    short_mouse_t (*get_report)(void);
} pointing_device_driver_t;

void process_mouse_kb(report_mouse_t *report, int8_t x, int8_t y);
void process_wheel_kb(report_mouse_t *report, int8_t h, int8_t v);
void process_mouse_user(report_mouse_t *report, int8_t x, int8_t y);
void process_wheel_user(report_mouse_t *report, int8_t h, int8_t v);
