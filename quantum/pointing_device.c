/* Copyright 2017 Joshua Broekhuijsen <snipeye+qmk@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)
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

#include "pointing_device.h"
#include <string.h>
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif
#if (defined(POINTING_DEVICE_ROTATION_90) + defined(POINTING_DEVICE_ROTATION_180) + defined(POINTING_DEVICE_ROTATION_270)) > 1
#    error More than one rotation selected.  This is not supported.
#endif

static report_mouse_t mouseReport = {};

extern const pointing_device_driver_t pointing_device_driver;

__attribute__((weak)) bool has_mouse_report_changed(report_mouse_t new, report_mouse_t old) { return memcmp(&new, &old, sizeof(new)); }

__attribute__((weak)) void           pointing_device_init_kb(void) {}
__attribute__((weak)) void           pointing_device_init_user(void) {}
__attribute__((weak)) report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) { return pointing_device_task_user(mouse_report); }
__attribute__((weak)) report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) { return mouse_report; }

__attribute__((weak)) uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
    if (pressed) {
        buttons |= 1 << (button);
    } else {
        buttons &= ~(1 << (button));
    }
    return buttons;
}

__attribute__((weak)) void pointing_device_init(void) {
    pointing_device_driver.init();
#ifdef POINTING_DEVICE_MOTION_PIN
    setPinInputHigh(POINTING_DEVICE_MOTION_PIN);
#endif
    pointing_device_init_kb();
    pointing_device_init_user();
}

__attribute__((weak)) void pointing_device_send(void) {
    static report_mouse_t old_report = {};

    // If you need to do other things, like debugging, this is the place to do it.
    if (has_mouse_report_changed(mouseReport, old_report)) {
        host_mouse_send(&mouseReport);
    }
    // send it and 0 it out except for buttons, so those stay until they are explicity over-ridden using update_pointing_device
    mouseReport.x = 0;
    mouseReport.y = 0;
    mouseReport.v = 0;
    mouseReport.h = 0;

    memcpy(&old_report, &mouseReport, sizeof(mouseReport));
}

__attribute__((weak)) void pointing_device_task(void) {
    // Gather report info
#ifdef POINTING_DEVICE_MOTION_PIN
    if (!readPin(POINTING_DEVICE_MOTION_PIN))
#endif
        mouseReport = pointing_device_driver.get_report(mouseReport);

        // Support rotation of the sensor data
#if defined(POINTING_DEVICE_ROTATION_90) || defined(POINTING_DEVICE_ROTATION_180) || defined(POINTING_DEVICE_ROTATION_270)
    int8_t x = mouseReport.x, y = mouseReport.y;
#    if defined(POINTING_DEVICE_ROTATION_90)
    mouseReport.x = y;
    mouseReport.y = -x;
#    elif defined(POINTING_DEVICE_ROTATION_180)
    mouseReport.x = -x;
    mouseReport.y = -y;
#    elif defined(POINTING_DEVICE_ROTATION_270)
    mouseReport.x = -y;
    mouseReport.y = x;
#    else
#        error "How the heck did you get here?!"
#    endif
#endif
    // Support Inverting the X and Y Axises
#if defined(POINTING_DEVICE_INVERT_X)
    mouseReport.x = -mouseReport.x;
#endif
#if defined(POINTING_DEVICE_INVERT_Y)
    mouseReport.y = -mouseReport.y;
#endif

    // allow kb to intercept and modify report
    mouseReport = pointing_device_task_kb(mouseReport);
    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    mouseReport.buttons            = mouseReport.buttons | mousekey_report.buttons;
#endif
    pointing_device_send();
}

report_mouse_t pointing_device_get_report(void) { return mouseReport; }

void pointing_device_set_report(report_mouse_t newMouseReport) { mouseReport = newMouseReport; }

uint16_t pointing_device_get_cpi(void) { return pointing_device_driver.get_cpi(); }

void pointing_device_set_cpi(uint16_t cpi) { pointing_device_driver.set_cpi(cpi); }
