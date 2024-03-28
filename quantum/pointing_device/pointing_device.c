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
#include "pointing_device_internal.h"
#include <string.h>
#include "timer.h"
#include "util.h"
#include "keyboard.h"
#include "split_util.h"
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif

extern const pointing_device_config_t pointing_device_configs[POINTING_DEVICE_COUNT];

const report_mouse_t     empty_report                                       = {0};
report_mouse_t           local_report                                       = {0};
uint8_t                  buttons[POINTING_DEVICE_COUNT]                     = {0};
pointing_device_status_t pointing_device_init_status[POINTING_DEVICE_COUNT] = {0};

#if defined(SPLIT_KEYBOARD)
pointing_device_shared_report_t shared_report                     = {0};
pointing_device_shared_cpi_t    shared_cpi[POINTING_DEVICE_COUNT] = {0};

void pointing_device_set_shared_report(pointing_device_shared_report_t report) {
    shared_report = report;
}

pointing_device_shared_report_t pointing_device_get_shared_report(void) {
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

bool pointing_device_check_shared_cpi_update_flags(void) {
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        if (shared_cpi[i].update) {
            return true;
        }
    }
    return false;
}

bool pointing_device_task_handle_shared_report(report_mouse_t* local_report, bool* device_was_ready) {
    static uint8_t counter = 0;
    if (is_keyboard_master()) {
        static uint shared_buttons = 0;
        if (counter != shared_report.counter) {
            shared_buttons = 0;
#    if defined(POINTING_DEVICE_DEBUG)
            if (shared_report.counter != (((uint16_t)counter + 1) & UINT8_MAX)) {
                pd_dprintf("POINTING DEVICE: Missed shared report - last report: %d, new report: %d\n", counter, shared_report.counter);
            }
#    endif
            pointing_device_add_and_clamp_report(local_report, &shared_report.report);
            counter           = shared_report.counter;
            *device_was_ready = true;
            shared_buttons    = shared_report.report.buttons;
            return true;
        } else {
            if (shared_buttons && is_transport_connected()) {
                local_report->buttons |= shared_buttons;
            } else {
                shared_buttons = 0; // Don't want stuck buttons
            }
        }
    } else {
        if (*device_was_ready) {
            if (pointing_device_report_ready(&shared_report.report, local_report, device_was_ready)) {
                memcpy(&shared_report, local_report, sizeof(report_mouse_t));
                shared_report.counter = counter;
                counter               = (((uint16_t)counter + 1) & UINT8_MAX);
                return true;
            }
        }
    }
    return false;
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

__attribute__((weak)) void pointing_device_init_kb(void) {
    pointing_device_init_user();
}

__attribute__((weak)) void pointing_device_init_user(void) {}

__attribute__((weak)) void pointing_device_init_kb_by_index(uint8_t index) {
    pointing_device_init_user_by_index(index);
}

__attribute__((weak)) void pointing_device_init_user_by_index(uint8_t index) {}

__attribute__((weak)) report_mouse_t pointing_device_task_kb(report_mouse_t mouse_report) {
    return pointing_device_task_user(mouse_report);
}

__attribute__((weak)) report_mouse_t pointing_device_task_user(report_mouse_t mouse_report) {
    return mouse_report;
}

__attribute__((weak)) report_mouse_t pointing_device_task_kb_by_index(report_mouse_t mouse_report, uint8_t index) {
    return pointing_device_task_user_by_index(mouse_report, index);
}

__attribute__((weak)) report_mouse_t pointing_device_task_user_by_index(report_mouse_t mouse_report, uint8_t index) {
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

bool pointing_device_report_ready(report_mouse_t* last_report, report_mouse_t* new_report, bool* device_was_ready) {
    bool ready = has_mouse_report_changed(last_report, new_report);
    if (!ready && *device_was_ready) {
        ready = memcmp(new_report, &empty_report, sizeof(report_mouse_t)) != 0;
    }
    return ready;
}

__attribute__((weak)) void pointing_device_init(void) {
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        pointing_device_init_status[i] = PD_STATUS_NOT_READY;
#if defined(SPLIT_KEYBOARD)
        if (!POINTING_DEVICE_THIS_SIDE(i)) {
            continue; // Skip if not this side
        }
#endif
        if (pointing_device_configs[i].driver->init) {
            pointing_device_init_status[i] = pointing_device_configs[i].driver->init(pointing_device_configs[i].comms_config, pointing_device_configs[i].device_config);
            if (pointing_device_init_status[i] == PD_STATUS_OK && pointing_device_configs[i].driver->adjust) {
                pointing_device_configs[i].driver->adjust(pointing_device_configs[i].comms_config, pointing_device_configs[i].device_config, pointing_device_configs[i].rotation, pointing_device_configs[i].invert, true);
            }
        }
        if (pointing_device_configs[i].motion.pin) {
            gpio_set_pin_input(pointing_device_configs[i].motion.pin);
        }
        pointing_device_init_kb_by_index(i);
    }
    pointing_device_init_kb();
}

__attribute__((weak)) void pointing_device_send(report_mouse_t* sending_report) {
    if (is_keyboard_master()) {
        host_mouse_send(sending_report);
    }
    memset(sending_report, 0, sizeof(report_mouse_t));
}

__attribute__((weak)) void pointing_device_keycode_handler(uint16_t keycode, bool pressed) {
    if IS_MOUSEKEY_BUTTON (keycode) {
        local_report.buttons = pointing_device_handle_buttons(local_report.buttons, pressed, keycode - KC_MS_BTN1);
        pointing_device_send(&local_report);
    }
}

void pointing_device_adjust_report(report_mouse_t* report, uint8_t index, pointing_device_adjustments_supported_t adj_handled) {
    mouse_xy_report_t x = report->x;
    mouse_xy_report_t y = report->y;
    if (adj_handled != PD_ADJ_SUPPORT_ROTATE) {
        switch (pointing_device_configs[index].rotation) {
            case PD_ROTATE_90:
                report->x = y;
                report->y = -x;
                break;
            case PD_ROTATE_180:
                report->x = -x;
                report->y = -y;
                break;
            case PD_ROTATE_270:
                report->x = -y;
                report->y = x;
                break;
            default:
                break;
        }
    }
    if (adj_handled != PD_ADJ_SUPPORT_INVERT) {
        if (pointing_device_configs[index].invert == PD_INVERT_X || pointing_device_configs[index].invert == PD_INVERT_XY) {
            report->x = -report->x;
        }
        if (pointing_device_configs[index].invert == PD_INVERT_Y || pointing_device_configs[index].invert == PD_INVERT_XY) {
            report->y = -report->y;
        }
    }
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

    if (pointing_device_init_status[index] == PD_STATUS_OK && timer_elapsed_fast(last_check[index]) >= device_config.throttle) {
        last_check[index] = timer_read_fast();
        if (device_config.motion.pin) { // FIX ME
            if (gpio_read_pin(device_config.motion.pin) != device_config.motion.active_low) {
                ready = true;
            }
        } else {
            ready = true;
        }
    }
    // pd_dprintf("Pointing Device %d Ready: %d Init: %d\n", index, ready, pointing_device_init_status[index]);
    return ready;
}

bool pointing_deivce_task_get_pointing_reports(report_mouse_t* report) {
    bool device_was_ready = false;
    for (uint8_t i = 0; i < POINTING_DEVICE_COUNT; i++) {
        report_mouse_t loop_report = {0};
#if defined(SPLIT_KEYBOARD)
        if (!POINTING_DEVICE_THIS_SIDE(i)) {
            continue; // skip processing devices not on this side
        }
#endif
        if (pointing_device_configs[i].driver->get_report && pointing_device_is_ready(pointing_device_configs[i], i) && pointing_device_configs[i].driver->get_report(&loop_report, pointing_device_configs[i].comms_config, pointing_device_configs[i].device_config) == PD_STATUS_OK) { // get_report is not NULL, device is ready, report is valid
            device_was_ready                                    = true;
            pointing_device_adjustments_supported_t adj_handled = PD_ADJ_SUPPORT_NONE;
            if (pointing_device_configs[i].driver->adjust == NULL || (adj_handled = pointing_device_configs[i].driver->adjust(pointing_device_configs[i].comms_config, pointing_device_configs[i].device_config, pointing_device_configs[i].rotation, pointing_device_configs[i].invert, false)) != PD_ADJ_SUPPORT_BOTH) {
                pointing_device_adjust_report(&loop_report, i, adj_handled);
            }
            loop_report = pointing_device_task_kb_by_index(loop_report, i); // Maybe simpler to not pass pointer to user?
            buttons[i]  = loop_report.buttons;
            pointing_device_add_and_clamp_report(report, &loop_report);
        } else {
            if (buttons[i]) {
                report->buttons |= buttons[i];
            }
        }
    }
    return device_was_ready;
}

__attribute__((weak)) bool pointing_device_task(void) {
    bool device_was_ready    = pointing_deivce_task_get_pointing_reports(&local_report);
    bool report_is_different = false;
#if defined(SPLIT_KEYBOARD)
    report_is_different = pointing_device_task_handle_shared_report(&local_report, &device_was_ready);
#endif

    local_report = pointing_device_task_kb(local_report);

    // automatic mouse layer function
#ifdef POINTING_DEVICE_AUTO_MOUSE_ENABLE
    pointing_device_task_auto_mouse(local_report);
#endif

    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    local_report.buttons           = local_report.buttons | mousekey_report.buttons;
#endif

    static report_mouse_t last_sent_report = {0};
    if (!report_is_different) {
        report_is_different = pointing_device_report_ready(&last_sent_report, &local_report, &device_was_ready);
    }
    if (report_is_different) {
        memcpy(&last_sent_report, &local_report, sizeof(report_mouse_t));
        pointing_device_send(&local_report);
    }

    return report_is_different;
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
    return pointing_device_configs[index].driver->get_cpi(pointing_device_configs[index].comms_config, pointing_device_configs[index].device_config);
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
        return;
    }
#endif
    pointing_device_configs[index].driver->set_cpi(cpi, pointing_device_configs[index].comms_config, pointing_device_configs[index].device_config);
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
