/* Copyright 2024 burkfers (@burkfers)
 * Copyright 2024 Wimads (@wimads)
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

#include "action.h"
#include "report.h"

report_mouse_t pointing_device_task_maccel(report_mouse_t mouse_report);
bool           process_record_maccel(uint16_t keycode, keyrecord_t *record, uint16_t takeoff, uint16_t growth_rate, uint16_t offset, uint16_t limit);

typedef struct _maccel_config_t {
    float growth_rate;
    float offset;
    float limit;
    float takeoff;
    bool  enabled;
} maccel_config_t;

extern maccel_config_t g_maccel_config;

void maccel_enabled(bool enable);
bool maccel_get_enabled(void);
void maccel_toggle_enabled(void);

float maccel_get_takeoff(void);
float maccel_get_growth_rate(void);
float maccel_get_offset(void);
float maccel_get_limit(void);
void  maccel_set_growth_rate(float val);
void  maccel_set_growth_rate(float val);
void  maccel_set_offset(float val);
void  maccel_set_limit(float val);

void keyboard_post_init_maccel(void);
