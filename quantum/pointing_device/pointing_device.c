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
#include "util.h"
#include "keyboard.h"
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif

extern const pointing_device_config_t pointing_device_configs[POINTING_DEVICE_COUNT];

report_mouse_t local_report = {0};
bool           report_ready = false;

#if defined(SPLIT_KEYBOARD)
report_mouse_t               shared_report                     = {0};
pointing_device_shared_cpi_t shared_cpi[POINTING_DEVICE_COUNT] = {0};

void pointing_device_set_shared_report(report_mouse_t report) {
    shared_report = report;
}

report_mouse_t pointing_device_get_shared_report(void) {
    return shared_report;
}

void pointing_device_set_shared_cpi(pointing_device_shared_cpi_t new_cpi[]) {
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        if (new_cpi[i].cpi && shared_cpi[i].cpi != new_cpi[i].cpi && new_cpi[i].update) { // cpi to set is not zero, is different to current and requires update
            pointing_device_set_cpi_by_index(new_cpi[i].cpi, i);
        }
    }
}

pointing_device_shared_cpi_t* pointing_device_get_shared_cpi(void) {
    return shared_cpi;
}

void pointing_device_reset_shared_cpi_update_flags(void) {
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        shared_cpi[i].update = false;
    }
}

#endif

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

__attribute__((weak)) void pointing_device_init_kb(void) {}

__attribute__((weak)) void pointing_device_init_user(void) {}

__attribute__((weak)) report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report, uint8_t index) {
    return pointing_device_task_user(mouse_report, index);
}

__attribute__((weak)) report_mouse_t pointing_device_task_user(report_mouse_t mouse_report, uint8_t index) {
    return mouse_report;
}

__attribute__((weak)) uint8_t pointing_device_handle_buttons(uint8_t buttons, bool pressed, pointing_device_buttons_t button) {
    if (pressed) {
        buttons |= 1 << (button);
    } else {
        buttons &= ~(1 << (button));
    }
    return buttons;
}

__attribute__((weak)) void pointing_device_init(void) {
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
#if defined(SPLIT_KEYBOARD)
        if (!POINTING_DEVICE_THIS_SIDE(i)) {
            continue; // Skip if not this side
        }
#endif
        if (pointing_device_configs[i].driver->init) {
            pointing_device_configs[i].driver->init(pointing_device_configs[i].config);
        }
        if (pointing_device_configs[i].motion.pin) {
            setPinInput(pointing_device_configs[i].motion.pin);
        }
    }
}

__attribute__((weak)) void pointing_device_send(void) {
    static report_mouse_t old_report   = {};
    report_mouse_t        empty_report = {0};

    // If you need to do other things, like debugging, this is the place to do it.
    if (has_mouse_report_changed(&local_report, &old_report) || (report_ready && (memcmp(&local_report, &empty_report, sizeof(report_mouse_t)) != 0))) { // report should be sent if it has movement when the device was ready.
        host_mouse_send(&local_report);
    }
    // send it and 0 it out except for buttons, so those stay until they are explicity over-ridden using update_pointing_device
    uint8_t buttons = local_report.buttons;
    memset(&local_report, 0, sizeof(local_report));
    local_report.buttons = buttons;
    memcpy(&old_report, &local_report, sizeof(local_report));
}

__attribute__((weak)) void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if IS_MOUSEKEY_BUTTON (keycode) {
        local_report.buttons = pointing_device_handle_buttons(local_report.buttons, pressed, keycode - KC_MS_BTN1);
        pointing_device_send();
    }
}

report_mouse_t pointing_device_adjust_report(report_mouse_t report, uint8_t index) {
    switch (pointing_device_configs[index].rotation) {
        case ROTATE_90:
            report.x = report.y;
            report.y = -report.x;
            break;
        case ROTATE_180:
            report.x = -report.x;
            report.y = -report.y;
            break;
        case ROTATE_270:
            report.x = -report.y;
            report.y = report.x;
            break;
        default:
            break;
    }
    if (pointing_device_configs[index].invert == INVERT_X || pointing_device_configs[index].invert == INVERT_XY) {
        report.x = -report.x;
    }
    if (pointing_device_configs[index].invert == INVERT_Y || pointing_device_configs[index].invert == INVERT_XY) {
        report.y = -report.y;
    }
    return report;
}

void pointing_device_add_and_clamp_report(report_mouse_t* report, report_mouse_t* additional_report) {
    report->x = pointing_device_xy_clamp((clamp_range_t)report->x + additional_report->x);
    report->y = pointing_device_xy_clamp((clamp_range_t)report->y + additional_report->y);
    report->h = pointing_device_hv_clamp((clamp_range_t)report->h + additional_report->h);
    report->v = pointing_device_hv_clamp((clamp_range_t)report->v + additional_report->v);
    report->buttons |= additional_report->buttons;
}

__attribute__((weak)) bool pointing_device_is_ready(pointing_device_config_t device_config, uint8_t index) {
    static fast_timer_t last_check[POINTING_DEVICE_COUNT] = {0};
    bool                ready                             = false;

    if (device_config.motion.pin) { // check pin assigned
        if (readPin(device_config.motion.pin) != device_config.motion.active_low) {
            ready = true;
        }
    } else if (timer_elapsed_fast(last_check[index]) >= device_config.throttle) {
        last_check[index] = timer_read_fast();
        ready             = true;
    }

    return ready;
}

report_mouse_t pointing_deivce_task_get_pointing_reports(bool* was_ready) {
    report_mouse_t temp_report = {0};
    *was_ready                 = false;
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        report_mouse_t loop_report = {0};
#if defined(SPLIT_KEYBOARD)
        if (!POINTING_DEVICE_THIS_SIDE(i)) {
            continue; // skip processing devices not on this side
        }
#endif
        bool device_ready = pointing_device_is_ready(pointing_device_configs[i], i);
        *was_ready |= device_ready;
        if (device_ready) {
            loop_report = pointing_device_configs[i].driver->get_report ? pointing_device_configs[i].driver->get_report(pointing_device_configs[i].config) : loop_report;
            loop_report = pointing_device_adjust_report(loop_report, i);
            loop_report = pointing_device_task_kb(loop_report, i);
            pointing_device_add_and_clamp_report(&temp_report, &loop_report);
        }
    }
    return temp_report;
}

__attribute__((weak)) void pointing_device_task(void) {
    local_report = pointing_deivce_task_get_pointing_reports(&report_ready);

    // automatic mouse layer function
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    pointing_device_task_auto_mouse(local_report);
#endif
    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    local_report.buttons           = local_report.buttons | mousekey_report.buttons;
#endif

#if defined(SPLIT_KEYBOARD)
    if (is_keyboard_master()) {
        static report_mouse_t last_shared_report = {0};
        if (memcmp(&last_shared_report, &shared_report, sizeof(report_mouse_t)) != 0) { // ensure shared report has changed, the target may have not updated this yet due to throttle or motion pin.
            pointing_device_add_and_clamp_report(&local_report, &shared_report);
            last_shared_report = shared_report;
            report_ready       = true;
        }
    } else {
        if (report_ready) { // even if the device produces the same or zero movement but was ready it should be sent, counter is used to ensure report is different. Note: implement debug prints for missed reports
            shared_report           = local_report;
            static uint8_t counter  = 0;
            shared_report.report_id = counter; // FIX ME - can't use the report id for this counter.
            if (counter == UINT8_MAX) {
                counter = 0;
            } else {
                counter++;
            }
        }
        return;
    }
#endif

    pointing_device_send();
}

/**
 * @brief Gets current mouse report used by pointing device task
 *
 * @return report_mouse_t
 */
report_mouse_t pointing_device_get_report(void) {
    return local_report;
}

/**
 * @brief Sets mouse report used be pointing device task
 *
 * @param[in] mouse_report
 */
void pointing_device_set_report(report_mouse_t mouse_report) {
    local_report = mouse_report;
}

uint16_t pointing_device_get_cpi_by_index(uint8_t index) {
#if defined(SPLIT_KEYBOARD)
    if (!POINTING_DEVICE_THIS_SIDE(index)) {
        return shared_cpi[index].cpi;
    }
#endif
    return pointing_device_configs[index].driver->get_cpi(pointing_device_configs[index].config);
}

/**
 * @brief Gets current pointing device CPI if supported
 *
 * Gets current cpi from pointing device driver if supported and returns it as uint16_t
 *
 * @return cpi value as uint16_t
 */
uint16_t pointing_device_get_cpi(void) {
    return pointing_device_get_cpi_by_index(0);
}

void pointing_device_set_cpi_by_index(uint16_t cpi, uint8_t index) {
#if defined(SPLIT_KEYBOARD)
    shared_cpi[index].cpi = cpi;
    if (!POINTING_DEVICE_THIS_SIDE(index)) {
        shared_cpi[index].update = true;
    }
#endif
    pointing_device_configs[index].driver->set_cpi(pointing_device_configs[index].config, cpi);
}

/**
 * @brief Set pointing device CPI if supported
 *
 * Takes a uint16_t value to set pointing device cpi if supported by driver.
 *
 * @param[in] cpi uint16_t value.
 */
void pointing_device_set_cpi(uint16_t cpi) {
    pointing_device_set_cpi_by_index(cpi, 0);
}
