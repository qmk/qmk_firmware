/* Copyright 2024 Morgan Newell Sun
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

#include "report.h"

#ifndef POINTING_DEVICE_DRAGSCROLL_ENABLE
#    error "POINTING_DEVICE_DRAGSCROLL_ENABLE not defined! check config settings"
#endif

#ifndef DRAGSCROLL_THROTTLE_MS
#    define DRAGSCROLL_THROTTLE_MS 16
#endif

#ifndef DRAGSCROLL_TIMEOUT_MS
#    define DRAGSCROLL_TIMEOUT_MS 500
#endif

#ifndef DRAGSCROLL_MULTIPLIER_H
#    define DRAGSCROLL_MULTIPLIER_H 0.1
#endif
#ifndef DRAGSCROLL_MULTIPLIER_V
#    define DRAGSCROLL_MULTIPLIER_V 0.1
#endif

#ifndef DRAGSCROLL_SMOOTHING
#    define DRAGSCROLL_SMOOTHING 5
#else
#    if DRAGSCROLL_SMOOTHING < 1
#        error "DRAGSCROLL_SMOOTHING must be a positive integer!"
#    endif
#endif

#ifndef DRAGSCROLL_AXIS_SNAPPING_THRESHOLD
#    define DRAGSCROLL_AXIS_SNAPPING_THRESHOLD 0.25
#endif
#ifndef DRAGSCROLL_AXIS_SNAPPING_RATIO
#    define DRAGSCROLL_AXIS_SNAPPING_RATIO 2.0
#endif

#ifdef DRAGSCROLL_ACCELERATION
#    ifndef DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON
#        define DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON
#    endif
#    ifndef DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF
#        define DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF
#    endif
#endif
#if !defined(DRAGSCROLL_ACCELERATION) && (defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_ON) || defined(DRAGSCROLL_ACCELERATION_WHEN_HIRES_SCROLLING_IS_OFF))
#    define DRAGSCROLL_ACCELERATION
#endif

#ifdef DRAGSCROLL_ACCELERATION
#    ifndef DRAGSCROLL_ACCELERATION_SCALE
#        define DRAGSCROLL_ACCELERATION_SCALE 500.0
#    endif
#    ifndef DRAGSCROLL_ACCELERATION_BLEND
#        define DRAGSCROLL_ACCELERATION_BLEND 0.872116 // matches windows enhanced pointer precision behavior
#    endif
#endif

#if defined(DRAGSCROLL_ACCELERATION) && defined(SEND_STRING_ENABLE)
void start_dragscroll_acceleration_scale_calibration(void);
void finish_dragscroll_acceleration_scale_calibration(void);
#endif

void           dragscroll_init(void);
void           pointing_device_dragscroll(report_mouse_t* mouse_report);
void           dragscroll_on(void);
void           dragscroll_off(void);
void           dragscroll_toggle(void);
bool           is_dragscroll_on(void);
void           dragscroll_axis_snapping_on(void);
void           dragscroll_axis_snapping_off(void);
void           dragscroll_axis_snapping_toggle(void);
bool           is_dragscroll_axis_snapping_on(void);
report_mouse_t get_pre_dragscroll_mouse_report(void);

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED) && !defined(DRAGSCROLL_APPLIED_AFTER_POINTING_DEVICE_TASK_KB)
void           pointing_device_dragscroll_combined(report_mouse_t* mouse_report_left, report_mouse_t* mouse_report_right);
void           dragscroll_on_right(void);
void           dragscroll_off_right(void);
void           dragscroll_toggle_right(void);
bool           is_dragscroll_on_right(void);
void           dragscroll_axis_snapping_on_right(void);
void           dragscroll_axis_snapping_off_right(void);
void           dragscroll_axis_snapping_toggle_right(void);
bool           is_dragscroll_axis_snapping_on_right(void);
report_mouse_t get_pre_dragscroll_mouse_report_right(void);
#endif
