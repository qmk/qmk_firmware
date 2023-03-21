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

#if defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT) || defined(POINTING_DEVICE_COMBINED)
#    ifndef SPLIT_POINTING_ENABLE
#        error "Using POINTING_DEVICE_LEFT or POINTING_DEVICE_RIGHT or POINTING_DEVICE_COMBINED, then SPLIT_POINTING_ENABLE is required but has not been defined"
#    endif
#endif

#if defined(SPLIT_POINTING_ENABLE)
#    include "transactions.h"
#    include "keyboard.h"

report_mouse_t shared_mouse_report = {};
uint16_t       shared_cpi          = 0;

/**
 * @brief Sets the shared mouse report used be pointing device task
 *
 * NOTE : Only available when using SPLIT_POINTING_ENABLE
 *
 * @param[in] new_mouse_report report_mouse_t
 */
void pointing_device_set_shared_report(report_mouse_t new_mouse_report) {
    shared_mouse_report = new_mouse_report;
}

/**
 * @brief Gets current pointing device CPI if supported
 *
 * Gets current cpi of the shared report and returns it as uint16_t
 *
 * NOTE : Only available when using SPLIT_POINTING_ENABLE
 *
 * @return cpi value as uint16_t
 */
uint16_t pointing_device_get_shared_cpi(void) {
    return shared_cpi;
}

#    if defined(POINTING_DEVICE_LEFT)
#        define POINTING_DEVICE_THIS_SIDE is_keyboard_left()
#    elif defined(POINTING_DEVICE_RIGHT)
#        define POINTING_DEVICE_THIS_SIDE !is_keyboard_left()
#    elif defined(POINTING_DEVICE_COMBINED)
#        define POINTING_DEVICE_THIS_SIDE true
#    endif

#endif // defined(SPLIT_POINTING_ENABLE)

static report_mouse_t local_mouse_report         = {};
static bool           pointing_device_force_send = false;

extern const pointing_device_driver_t pointing_device_driver;

/**
 * @brief Keyboard level code pointing device initialisation
 *
 */
__attribute__((weak)) void pointing_device_init_kb(void) {}

/**
 * @brief User level code pointing device initialisation
 *
 */
__attribute__((weak)) void pointing_device_init_user(void) {}

/**
 * @brief Weak function allowing for keyboard level mouse report modification
 *
 * Takes report_mouse_t struct allowing modification at keyboard level then returns report_mouse_t.
 *
 * @param[in] mouse_report report_mouse_t
 * @return report_mouse_t
 */
__attribute__((weak)) report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    return pointing_device_task_user(mouse_report);
}

/**
 * @brief Weak function allowing for user level mouse report modification
 *
 * Takes report_mouse_t struct allowing modification at user level then returns report_mouse_t.
 *
 * @param[in] mouse_report report_mouse_t
 * @return report_mouse_t
 */
__attribute__((weak)) report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return mouse_report;
}

/**
 * @brief Handles pointing device buttons
 *
 * Returns modified button bitmask using bool pressed and selected pointing_device_buttons_t button in uint8_t buttons bitmask.
 *
 * @param buttons[in] uint8_t bitmask
 * @param pressed[in] bool
 * @param button[in] pointing_device_buttons_t value
 * @return Modified uint8_t bitmask buttons
 */
__attribute__((weak)) uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
    if (pressed) {
        buttons |= 1 << (button);
    } else {
        buttons &= ~(1 << (button));
    }
    return buttons;
}

/**
 * @brief Initialises pointing device
 *
 * Initialises pointing device, perform driver init and optional keyboard/user level code.
 */
__attribute__((weak)) void pointing_device_init(void) {
#if defined(SPLIT_POINTING_ENABLE)
    if ((POINTING_DEVICE_THIS_SIDE))
#endif
    {
        pointing_device_driver.init();
#ifdef POINTING_DEVICE_MOTION_PIN
#    ifdef POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
        setPinInputHigh(POINTING_DEVICE_MOTION_PIN);
#    else
        setPinInput(POINTING_DEVICE_MOTION_PIN);
#    endif
#endif
    }

    pointing_device_init_kb();
    pointing_device_init_user();
}

/**
 * @brief Sends processed mouse report to host
 *
 * This sends the mouse report generated by pointing_device_task if changed since the last report. Once send zeros mouse report except buttons.
 *
 */
__attribute__((weak)) bool pointing_device_send(void) {
    static report_mouse_t old_report         = {};
    bool                  should_send_report = has_mouse_report_changed(&local_mouse_report, &old_report);

    if (should_send_report) {
        host_mouse_send(&local_mouse_report);
    }
    // send it and 0 it out except for buttons, so those stay until they are explicity over-ridden using update_pointing_device
    uint8_t buttons = local_mouse_report.buttons;
    memset(&local_mouse_report, 0, sizeof(local_mouse_report));
    local_mouse_report.buttons = buttons;
    memcpy(&old_report, &local_mouse_report, sizeof(local_mouse_report));

    return should_send_report || buttons;
}

/**
 * @brief Adjust mouse report by any optional common pointing configuration defines
 *
 * This applies rotation or inversion to the mouse report as selected by the pointing device common configuration defines.
 *
 * @param mouse_report[in] takes a report_mouse_t to be adjusted
 * @return report_mouse_t with adjusted values
 */
report_mouse_t pointing_device_adjust_by_defines(report_mouse_t mouse_report) {
    // Support rotation of the sensor data
#if defined(POINTING_DEVICE_ROTATION_90) || defined(POINTING_DEVICE_ROTATION_180) || defined(POINTING_DEVICE_ROTATION_270)
    mouse_xy_report_t x = mouse_report.x;
    mouse_xy_report_t y = mouse_report.y;
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

/**
 * @brief Retrieves and processes pointing device data.
 *
 * This function is part of the keyboard loop and retrieves the mouse report from the pointing device driver.
 * It applies any optional configuration e.g. rotation or axis inversion and then initiates a send.
 *
 */
__attribute__((weak)) bool pointing_device_task(void) {
#if defined(SPLIT_POINTING_ENABLE)
    // Don't poll the target side pointing device.
    if (!is_keyboard_master()) {
        return false;
    };
#endif

#if (POINTING_DEVICE_TASK_THROTTLE_MS > 0)
    static uint32_t last_exec = 0;
    if (timer_elapsed32(last_exec) < POINTING_DEVICE_TASK_THROTTLE_MS) {
        return false;
    }
    last_exec = timer_read32();
#endif

    // Gather report info
#ifdef POINTING_DEVICE_MOTION_PIN
#    if defined(SPLIT_POINTING_ENABLE)
#        error POINTING_DEVICE_MOTION_PIN not supported when sharing the pointing device report between sides.
#    endif
#    ifdef POINTING_DEVICE_MOTION_PIN_ACTIVE_LOW
    if (!readPin(POINTING_DEVICE_MOTION_PIN))
#    else
    if (readPin(POINTING_DEVICE_MOTION_PIN))
#    endif
#endif

#if defined(SPLIT_POINTING_ENABLE)
#    if defined(POINTING_DEVICE_COMBINED)
        static uint8_t old_buttons = 0;
    local_mouse_report.buttons = old_buttons;
    local_mouse_report         = pointing_device_driver.get_report(local_mouse_report);
    old_buttons                = local_mouse_report.buttons;
#    elif defined(POINTING_DEVICE_LEFT) || defined(POINTING_DEVICE_RIGHT)
        local_mouse_report = POINTING_DEVICE_THIS_SIDE ? pointing_device_driver.get_report(local_mouse_report) : shared_mouse_report;
#    else
#        error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#    endif
#else
    local_mouse_report = pointing_device_driver.get_report(local_mouse_report);
#endif // defined(SPLIT_POINTING_ENABLE)

    // allow kb to intercept and modify report
#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
    if (is_keyboard_left()) {
        local_mouse_report  = pointing_device_adjust_by_defines(local_mouse_report);
        shared_mouse_report = pointing_device_adjust_by_defines_right(shared_mouse_report);
    } else {
        local_mouse_report  = pointing_device_adjust_by_defines_right(local_mouse_report);
        shared_mouse_report = pointing_device_adjust_by_defines(shared_mouse_report);
    }
    local_mouse_report = is_keyboard_left() ? pointing_device_task_combined_kb(local_mouse_report, shared_mouse_report) : pointing_device_task_combined_kb(shared_mouse_report, local_mouse_report);
#else
    local_mouse_report = pointing_device_adjust_by_defines(local_mouse_report);
    local_mouse_report = pointing_device_task_kb(local_mouse_report);
#endif
    // automatic mouse layer function
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    pointing_device_task_auto_mouse(local_mouse_report);
#endif
    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    local_mouse_report.buttons     = local_mouse_report.buttons | mousekey_report.buttons;
#endif

    const bool send_report     = pointing_device_send() || pointing_device_force_send;
    pointing_device_force_send = false;

    return send_report;
}

/**
 * @brief Gets current mouse report used by pointing device task
 *
 * @return report_mouse_t
 */
report_mouse_t pointing_device_get_report(void) {
    return local_mouse_report;
}

/**
 * @brief Sets mouse report used be pointing device task
 *
 * @param[in] mouse_report
 */
void pointing_device_set_report(report_mouse_t mouse_report) {
    pointing_device_force_send = has_mouse_report_changed(&local_mouse_report, &mouse_report);
    memcpy(&local_mouse_report, &mouse_report, sizeof(local_mouse_report));
}

/**
 * @brief Gets current pointing device CPI if supported
 *
 * Gets current cpi from pointing device driver if supported and returns it as uint16_t
 *
 * @return cpi value as uint16_t
 */
uint16_t pointing_device_get_cpi(void) {
#if defined(SPLIT_POINTING_ENABLE)
    return POINTING_DEVICE_THIS_SIDE ? pointing_device_driver.get_cpi() : shared_cpi;
#else
    return pointing_device_driver.get_cpi();
#endif
}

/**
 * @brief Set pointing device CPI if supported
 *
 * Takes a uint16_t value to set pointing device cpi if supported by driver.
 *
 * @param[in] cpi uint16_t value.
 */
void pointing_device_set_cpi(uint16_t cpi) {
#if defined(SPLIT_POINTING_ENABLE)
    if (POINTING_DEVICE_THIS_SIDE) {
        pointing_device_driver.set_cpi(cpi);
    } else {
        shared_cpi = cpi;
    }
#else
    pointing_device_driver.set_cpi(cpi);
#endif
}

#if defined(SPLIT_POINTING_ENABLE) && defined(POINTING_DEVICE_COMBINED)
/**
 * @brief Set pointing device CPI if supported
 *
 * Takes a bool and uint16_t and allows setting cpi for a single side when using 2 pointing devices with a split keyboard.
 *
 * NOTE: Only available when using SPLIT_POINTING_ENABLE and POINTING_DEVICE_COMBINED
 *
 * @param[in] left true = left, false = right.
 * @param[in] cpi uint16_t value.
 */
void pointing_device_set_cpi_on_side(bool left, uint16_t cpi) {
    bool local = (is_keyboard_left() & left) ? true : false;
    if (local) {
        pointing_device_driver.set_cpi(cpi);
    } else {
        shared_cpi = cpi;
    }
}

/**
 * @brief clamps int16_t to int8_t
 *
 * @param[in] int16_t value
 * @return int8_t clamped value
 */
static inline int8_t pointing_device_hv_clamp(int16_t value) {
    if (value < INT8_MIN) {
        return INT8_MIN;
    } else if (value > INT8_MAX) {
        return INT8_MAX;
    } else {
        return value;
    }
}

/**
 * @brief clamps int16_t to int8_t
 *
 * @param[in] clamp_range_t value
 * @return mouse_xy_report_t clamped value
 */
static inline mouse_xy_report_t pointing_device_xy_clamp(clamp_range_t value) {
    if (value < XY_REPORT_MIN) {
        return XY_REPORT_MIN;
    } else if (value > XY_REPORT_MAX) {
        return XY_REPORT_MAX;
    } else {
        return value;
    }
}
/**
 * @brief combines 2 mouse reports and returns 2
 *
 * Combines 2 report_mouse_t structs, clamping movement values to int8_t and ignores report_id then returns the resulting report_mouse_t struct.
 *
 * NOTE: Only available when using SPLIT_POINTING_ENABLE and POINTING_DEVICE_COMBINED
 *
 * @param[in] left_report left report_mouse_t
 * @param[in] right_report right report_mouse_t
 * @return combined report_mouse_t of left_report and right_report
 */
report_mouse_t pointing_device_combine_reports(report_mouse_t left_report, report_mouse_t right_report) {
    left_report.x = pointing_device_xy_clamp((clamp_range_t)left_report.x + right_report.x);
    left_report.y = pointing_device_xy_clamp((clamp_range_t)left_report.y + right_report.y);
    left_report.h = pointing_device_hv_clamp((int16_t)left_report.h + right_report.h);
    left_report.v = pointing_device_hv_clamp((int16_t)left_report.v + right_report.v);
    left_report.buttons |= right_report.buttons;
    return left_report;
}

/**
 * @brief Adjust mouse report by any optional right pointing configuration defines
 *
 * This applies rotation or inversion to the mouse report as selected by the pointing device common configuration defines.
 *
 * NOTE: Only available when using SPLIT_POINTING_ENABLE and POINTING_DEVICE_COMBINED
 *
 * @param[in] mouse_report report_mouse_t to be adjusted
 * @return report_mouse_t with adjusted values
 */
report_mouse_t pointing_device_adjust_by_defines_right(report_mouse_t mouse_report) {
    // Support rotation of the sensor data
#    if defined(POINTING_DEVICE_ROTATION_90_RIGHT) || defined(POINTING_DEVICE_ROTATION_180_RIGHT) || defined(POINTING_DEVICE_ROTATION_270_RIGHT)
    mouse_xy_report_t x = mouse_report.x;
    mouse_xy_report_t y = mouse_report.y;
#        if defined(POINTING_DEVICE_ROTATION_90_RIGHT)
    mouse_report.x = y;
    mouse_report.y = -x;
#        elif defined(POINTING_DEVICE_ROTATION_180_RIGHT)
    mouse_report.x = -x;
    mouse_report.y = -y;
#        elif defined(POINTING_DEVICE_ROTATION_270_RIGHT)
    mouse_report.x = -y;
    mouse_report.y = x;
#        else
#            error "How the heck did you get here?!"
#        endif
#    endif
    // Support Inverting the X and Y Axises
#    if defined(POINTING_DEVICE_INVERT_X_RIGHT)
    mouse_report.x = -mouse_report.x;
#    endif
#    if defined(POINTING_DEVICE_INVERT_Y_RIGHT)
    mouse_report.y = -mouse_report.y;
#    endif
    return mouse_report;
}

/**
 * @brief Weak function allowing for keyboard level mouse report modification
 *
 * Takes 2 report_mouse_t structs allowing individual modification of sides at keyboard level then returns pointing_device_task_combined_user.
 *
 * NOTE: Only available when using SPLIT_POINTING_ENABLE and POINTING_DEVICE_COMBINED
 *
 * @param[in] left_report report_mouse_t
 * @param[in] right_report report_mouse_t
 * @return pointing_device_task_combined_user(left_report, right_report) by default
 */
__attribute__((weak)) report_mouse_t pointing_device_task_combined_kb(report_mouse_t left_report, report_mouse_t right_report) {
    return pointing_device_task_combined_user(left_report, right_report);
}

/**
 * @brief Weak function allowing for user level mouse report modification
 *
 * Takes 2 report_mouse_t structs allowing individual modification of sides at user level then returns pointing_device_combine_reports.
 *
 * NOTE: Only available when using SPLIT_POINTING_ENABLE and POINTING_DEVICE_COMBINED
 *
 * @param[in] left_report report_mouse_t
 * @param[in] right_report report_mouse_t
 * @return pointing_device_combine_reports(left_report, right_report) by default
 */
__attribute__((weak)) report_mouse_t pointing_device_task_combined_user(report_mouse_t left_report, report_mouse_t right_report) {
    return pointing_device_combine_reports(left_report, right_report);
}
#endif

__attribute__((weak)) void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if IS_MOUSEKEY_BUTTON (keycode) {
        local_mouse_report.buttons = pointing_device_handle_buttons(local_mouse_report.buttons, pressed, keycode - KC_MS_BTN1);
        pointing_device_send();
    }
}
