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
#include "gpio.h"

#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
#    include "pointing_device_auto_mouse.h"
#endif

#ifndef POINTING_DEVICE_COUNT
#    define POINTING_DEVICE_COUNT 1
#endif

typedef enum {
    ROTATE_0,
    ROTATE_90,
    ROTATE_180,
    ROTATE_270,
} pointing_device_rotations_t;
typedef enum {
    UNKNOWN,
    LEFT,
    RIGHT,
} pointing_device_side_t;
typedef enum {
    NONE,
    INVERT_X,
    INVERT_Y,
    INVERT_XY,
} pointing_device_invert_t;

typedef struct {
    pin_t   cs;
    uint8_t mode;
    uint8_t divisor;
} pointing_device_spi_config_t;

typedef struct {
    uint16_t address;
    uint16_t timeout;
} pointing_device_i2c_config_t;

typedef struct {
    pin_t pin;
    bool  active_low;
} pointing_device_motion_t;

typedef struct {
    void (*init)(const void *);
    report_mouse_t (*get_report)(const void *);
    void (*set_cpi)(const void *, uint16_t);
    uint16_t (*get_cpi)(const void *);
} pointing_device_driver_t;

typedef struct {
    const pointing_device_driver_t   *driver;
    const pointing_device_rotations_t rotation;
    const pointing_device_invert_t    invert;
    const uint8_t                     throttle;
    const void                       *config;
    const pointing_device_motion_t    motion;
#if defined(SPLIT_KEYBOARD)
    const pointing_device_side_t side;
#endif
} pointing_device_config_t;

typedef struct {
    uint16_t cpi;
    bool     update;
} pointing_device_shared_cpi_t;

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

#if defined(POINTING_DEVICE_DRIVER_ADNS9800)
#include "adns9800.h"
#endif
#if defined(POINTING_DEVICE_DRIVER_AZOTEQ_IQS5XX)
#include "azoteq_iqs5xx.h"
#endif
#if defined(POINTING_DEVICE_DRIVER_CIRQUE_PINNACLE_I2C) || defined(POINTING_DEVICE_DRIVER_CIRQUE_PINNACLE_SPI)
#include "cirque_pinnacle.h"
#endif
#if defined(POINTING_DEVICE_DRIVER_PIMORONI_TRACKBALL)
#include "pimoroni_trackball.h"
#endif 
#if defined(POINTING_DEVICE_DRIVER_PMW3360)
#include "pmw3360.h"
#endif 
#if defined(POINTING_DEVICE_DRIVER_PMW3389)
#include "pmw3389.h"
#endif 

#ifdef MOUSE_EXTENDED_REPORT
#    define XY_REPORT_MIN INT16_MIN
#    define XY_REPORT_MAX INT16_MAX
typedef int32_t clamp_range_t;
#else
#    define XY_REPORT_MIN INT8_MIN
#    define XY_REPORT_MAX INT8_MAX
typedef int16_t clamp_range_t;
#endif

#define POINTING_DEVICE_NO_MOTION_PIN \
    { 0 }
#define POINTING_DEVICE_THIS_SIDE(index) (pointing_device_configs[index].side == (is_keyboard_left() ? LEFT : RIGHT))


#define CONSTRAIN_HID(amt) ((amt) < INT8_MIN ? INT8_MIN : ((amt) > INT8_MAX ? INT8_MAX : (amt)))
#define CONSTRAIN_HID_XY(amt) ((amt) < XY_REPORT_MIN ? XY_REPORT_MIN : ((amt) > XY_REPORT_MAX ? XY_REPORT_MAX : (amt)))

void           pointing_device_init(void);
bool           pointing_device_task(void);
bool           pointing_device_send(void);
report_mouse_t pointing_device_get_report(void);
void           pointing_device_set_report(report_mouse_t mouse_report);
uint16_t       pointing_device_get_cpi(void);
void           pointing_device_set_cpi(uint16_t cpi);

uint16_t pointing_device_get_cpi_by_index(uint8_t index);
void     pointing_device_set_cpi_by_index(uint16_t cpi, uint8_t index);

void           pointing_device_init_kb(void);
void           pointing_device_init_user(void);
report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report, uint8_t index);
report_mouse_t pointing_device_task_user(report_mouse_t mouse_report, uint8_t index);
uint8_t        pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button);
report_mouse_t pointing_device_adjust_by_defines(report_mouse_t mouse_report);
void           pointing_device_keycode_handler(uint16_t keycode, bool pressed);
report_mouse_t pointing_deivce_task_get_pointing_reports(bool *was_ready);

void                          pointing_device_set_shared_report(report_mouse_t report);
report_mouse_t                pointing_device_get_shared_report(void);
void                          pointing_device_set_shared_cpi(pointing_device_shared_cpi_t cpi[]);
pointing_device_shared_cpi_t *pointing_device_get_shared_cpi(void);
void                          pointing_device_reset_shared_cpi_update_flags(void);
