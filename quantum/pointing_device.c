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
#include "timer.h"
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif
#if (defined(POINTING_DEVICE_ROTATION_90) + defined(POINTING_DEVICE_ROTATION_180) + defined(POINTING_DEVICE_ROTATION_270)) > 1
#    error More than one rotation selected.  This is not supported.
#endif
#if defined(SPLIT_POINTING_ENABLE)
#    include "transactions.h"
#    include "keyboard.h"

report_mouse_t sharedReport = {};
uint16_t       sharedCpi    = 0;

void     pointing_device_set_shared_report(report_mouse_t report) { sharedReport = report; }
uint16_t pointing_device_get_shared_cpi(void) { return sharedCpi; }

#    if defined(POINTING_DEVICE_LEFT)
#        define POINTING_DEVICE_THIS_SIDE is_keyboard_left()
#    elif defined(POINTING_DEVICE_RIGHT)
#        define POINTING_DEVICE_THIS_SIDE !is_keyboard_left()
#    elif defined(POINTING_DEVICE_COMBINED)
#        define POINTING_DEVICE_THIS_SIDE true
#    endif

#endif  // defined(SPLIT_POINTING_ENABLE)

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

report_mouse_t pointing_device_adjust_by_defines(report_mouse_t mouse_report) {
        // Support rotation of the sensor data
#if defined(POINTING_DEVICE_ROTATION_90) || defined(POINTING_DEVICE_ROTATION_180) || defined(POINTING_DEVICE_ROTATION_270)
        int8_t x = mouse_report.x, y = mouse_report.y;
#    if defined(POINTING_DEVICE_ROTATION_90)
        mouse_report.x = y;
        mouse_report.y = -x;
#    elif defined(POINTING_DEVICE_ROTATION_180)
        mouse_report.x = -x;
        mouse_report.y = -y;
#    elif defined(POINTING_DEVICE_ROTATION_270)
        mouse_report.x = -y;
        mouse_report.y = x;
#    else
#        error "How the heck did you get here?!"
#    endif
#endif
        // Support Inverting the X and Y Axises
#if defined(POINTING_DEVICE_INVERT_X)
        mouse_report.x = -mouse_report.x;
#endif
#if defined(POINTING_DEVICE_INVERT_Y)
        mouse_report.y = -mouse_report.y;
#endif
    return mouse_report;
}

__attribute__((weak)) void pointing_device_task(void) {
#if defined(SPLIT_POINTING_ENABLE)
    // Don't poll the target side pointing device.
    if (!is_keyboard_master()) {
        return;
    };
#endif

#if defined(POINTING_DEVICE_TASK_THROTTLE_MS)
    static uint32_t last_exec = 0;
    if (timer_elapsed32(last_exec) < POINTING_DEVICE_TASK_THROTTLE_MS) {
        return;
    }
    last_exec = timer_read32();
#else
#    if defined(SPLIT_POINTING_ENABLE)
#        pragma message("It's recommended you enable a throttle when sharing pointing devices.")
#    endif
#endif

    // Gather report info
#ifdef POINTING_DEVICE_MOTION_PIN
#    if defined(SPLIT_POINTING_ENABLE)
#        error POINTING_DEVICE_MOTION_PIN not supported when sharing the pointing device report between sides.
#    endif
    if (!readPin(POINTING_DEVICE_MOTION_PIN))
#endif

#if defined(SPLIT_POINTING_ENABLE)
#    if defined(POINTING_DEVICE_COMBINED)
        static uint8_t oldButtons = 0;
    mouseReport.buttons = oldButtons;
    mouseReport         = pointing_device_driver.get_report(mouseReport);
    oldButtons          = mouseReport.buttons;
                                      #    elif defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
        mouseReport    = POINTING_DEVICE_THIS_SIDE ? pointing_device_driver.get_report(mouseReport) : sharedReport;
#    else
#        error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#    endif
#else
    mouseReport = pointing_device_driver.get_report(mouseReport);
#endif  // defined(SPLIT_POINTING_ENABLE)

    // allow kb to intercept and modify report
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
    if (is_keyboard_left()) {
        mouseReport  = pointing_device_adjust_by_defines(mouseReport);
        sharedReport = pointing_device_adjust_by_defines_right(sharedReport);
    } else {
        mouseReport  = pointing_device_adjust_by_defines_right(mouseReport);
        sharedReport = pointing_device_adjust_by_defines(sharedReport);
    }
    mouseReport  = is_keyboard_left() ? pointing_device_task_combined_kb(mouseReport, sharedReport) : pointing_device_task_combined_kb(sharedReport, mouseReport);
#else
    mouseReport  = pointing_device_adjust_by_defines(mouseReport);
    mouseReport = pointing_device_task_kb(mouseReport);
#endif
    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    mouseReport.buttons            = mouseReport.buttons | mousekey_report.buttons;
#endif
    pointing_device_send();
}

report_mouse_t pointing_device_get_report(void) { return mouseReport; }

void pointing_device_set_report(report_mouse_t newMouseReport) { mouseReport = newMouseReport; }

uint16_t pointing_device_get_cpi(void) {
#if defined(SPLIT_POINTING_ENABLE)
    return POINTING_DEVICE_THIS_SIDE ? pointing_device_driver.get_cpi() : sharedCpi;
#else
    return pointing_device_driver.get_cpi();
#endif
}

void pointing_device_set_cpi(uint16_t cpi) {
#if defined(SPLIT_POINTING_ENABLE)
    if (POINTING_DEVICE_THIS_SIDE) {
        pointing_device_driver.set_cpi(cpi);
    } else {
        sharedCpi = cpi;
    }
#else
    pointing_device_driver.set_cpi(cpi);
#endif
}

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
void pointing_device_set_cpi_on_side(bool left, uint16_t cpi) {
    bool local = (is_keyboard_left() & left) ? true : false;
    if (local) {
        pointing_device_driver.set_cpi(cpi);
    } else {
        sharedCpi = cpi;
    }
}

report_mouse_t pointing_device_combine_reports(report_mouse_t left_report, report_mouse_t right_report) {
    left_report.x |= right_report.x;
    left_report.y |= right_report.y;
    left_report.h |= right_report.h;
    left_report.v |= right_report.v;
    left_report.buttons |= right_report.buttons;
    return left_report;
}

report_mouse_t pointing_device_adjust_by_defines_right(report_mouse_t mouse_report) {
        // Support rotation of the sensor data
#if defined(POINTING_DEVICE_ROTATION_90_RIGHT) || defined(POINTING_DEVICE_ROTATION_RIGHT) || defined(POINTING_DEVICE_ROTATION_RIGHT)
        int8_t x = mouse_report.x, y = mouse_report.y;
#    if defined(POINTING_DEVICE_ROTATION_90_RIGHT)
        mouse_report.x = y;
        mouse_report.y = -x;
#    elif defined(POINTING_DEVICE_ROTATION_180_RIGHT)
        mouse_report.x = -x;
        mouse_report.y = -y;
#    elif defined(POINTING_DEVICE_ROTATION_270_RIGHT)
        mouse_report.x = -y;
        mouse_report.y = x;
#    else
#        error "How the heck did you get here?!"
#    endif
#endif
        // Support Inverting the X and Y Axises
#if defined(POINTING_DEVICE_INVERT_X_RIGHT)
        mouse_report.x = -mouse_report.x;
#endif
#if defined(POINTING_DEVICE_INVERT_Y_RIGHT)
        mouse_report.y = -mouse_report.y;
#endif
    return mouse_report;
}

__attribute__((weak)) report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) { return pointing_device_task_combined_user(left_report, right_report); }
__attribute__((weak)) report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) { return pointing_device_combine_reports(left_report, right_report); }
#endif
