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

#include <stdbool.h>
#include <stdint.h>
#include "host.h"
#include "report.h"

typedef struct {
    bool (*init)(void);
    report_mouse_t (*get_report)(report_mouse_t mouse_report);
    void (*set_cpi)(uint16_t);
    uint16_t (*get_cpi)(void);
} pointing_device_driver_t;

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    include "pointing_device_auto_mouse.h"
#endif

#if defined(POINTING_DEVICE_DRIVER_adns5050)
#    include "drivers/sensors/adns5050.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_pmw3320)
#    include "drivers/sensors/pmw3320.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_paw3222)
#    include "spi_master.h"
#    include "drivers/sensors/paw3222.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_adns9800)
#    include "spi_master.h"
#    include "drivers/sensors/adns9800.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_analog_joystick)
#    include "analog.h"
#    include "drivers/sensors/analog_joystick.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_azoteq_iqs5xx)
#    include "i2c_master.h"
#    include "drivers/sensors/azoteq_iqs5xx.h"
#elif defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_i2c) || defined(POINTING_DEVICE_DRIVER_cirque_pinnacle_spi)
#    include "drivers/sensors/cirque_pinnacle.h"
#    include "pointing_device_gestures.h"
#elif defined(POINTING_DEVICE_DRIVER_paw3204)
#    include "drivers/sensors/paw3204.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_pimoroni_trackball)
#    include "i2c_master.h"
#    include "drivers/sensors/pimoroni_trackball.h"
// support for legacy pimoroni defines
#    ifdef PIMORONI_TRACKBALL_INVERT_X
#        define POINTING_DEVICE_INVERT_X
#    endif
#    ifdef PIMORONI_TRACKBALL_INVERT_Y
#        define POINTING_DEVICE_INVERT_Y
#    endif
#    ifdef PIMORONI_TRACKBALL_ROTATE
#        define POINTING_DEVICE_ROTATION_90
#    endif
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#elif defined(POINTING_DEVICE_DRIVER_pmw3360) || defined(POINTING_DEVICE_DRIVER_pmw3389)
#    include "spi_master.h"
#    include "drivers/sensors/pmw33xx_common.h"
#    define POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
#else
bool           pointing_device_driver_init(void);
report_mouse_t pointing_device_driver_get_report(report_mouse_t mouse_report);
uint16_t       pointing_device_driver_get_cpi(void);
void           pointing_device_driver_set_cpi(uint16_t cpi);
#endif

typedef enum {
    POINTING_DEVICE_BUTTON1,
    POINTING_DEVICE_BUTTON2,
    POINTING_DEVICE_BUTTON3,
    POINTING_DEVICE_BUTTON4,
    POINTING_DEVICE_BUTTON5,
    POINTING_DEVICE_BUTTON6,
    POINTING_DEVICE_BUTTON7,
    POINTING_DEVICE_BUTTON8,
} pointing_device_buttons_t;

typedef enum {
    POINTING_DEVICE_STATUS_UNKNOWN,
    POINTING_DEVICE_STATUS_INIT_FAILED,
    POINTING_DEVICE_STATUS_FAILED,
    POINTING_DEVICE_STATUS_SUCCESS,
} pointing_device_status_t;

#ifdef MOUSE_EXTENDED_REPORT
typedef int32_t xy_clamp_range_t;
#else
typedef int16_t xy_clamp_range_t;
#endif

#ifdef WHEEL_EXTENDED_REPORT
typedef int32_t hv_clamp_range_t;
#else
typedef int16_t hv_clamp_range_t;
#endif

#define CONSTRAIN_HID(amt) ((amt) < INT8_MIN ? INT8_MIN : ((amt) > INT8_MAX ? INT8_MAX : (amt)))
#define CONSTRAIN_HID_XY(amt) ((amt) < MOUSE_REPORT_XY_MIN ? MOUSE_REPORT_XY_MIN : ((amt) > MOUSE_REPORT_XY_MAX ? MOUSE_REPORT_XY_MAX : (amt)))

void                     pointing_device_init(void);
bool                     pointing_device_task(void);
bool                     pointing_device_send(void);
report_mouse_t           pointing_device_get_report(void);
void                     pointing_device_set_report(report_mouse_t mouse_report);
uint16_t                 pointing_device_get_cpi(void);
void                     pointing_device_set_cpi(uint16_t cpi);
pointing_device_status_t pointing_device_get_status(void);
void                     pointing_device_set_status(pointing_device_status_t status);

void           pointing_device_init_kb(void);
void           pointing_device_init_user(void);
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report);
uint8_t        pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button);
report_mouse_t pointing_device_adjust_by_defines(report_mouse_t mouse_report);
void           pointing_device_keycode_handler(uint16_t keycode, bool pressed);

#ifdef POINTING_DEVICE_HIRES_SCROLL_ENABLE
uint16_t pointing_device_get_hires_scroll_resolution(void);
#endif

#if defined(SPLIT_POINTING_ENABLE)
void     pointing_device_set_shared_report(report_mouse_t report);
uint16_t pointing_device_get_shared_cpi(void);
#    if !defined(POINTING_DEVICE_TASK_THROTTLE_MS)
#        define POINTING_DEVICE_TASK_THROTTLE_MS 1
#    endif
#    if defined(POINTING_DEVICE_COMBINED)
void           pointing_device_set_cpi_on_side(bool left, uint16_t cpi);
report_mouse_t pointing_device_combine_reports(report_mouse_t left_report, report_mouse_t right_report);
report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report);
report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report);
report_mouse_t pointing_device_adjust_by_defines_right(report_mouse_t mouse_report);
#    endif // defined(POINTING_DEVICE_COMBINED)
#endif     // defined(SPLIT_POINTING_ENABLE)
