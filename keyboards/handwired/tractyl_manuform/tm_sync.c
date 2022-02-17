/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 * Copyright 2021 Dasky (@daskygit)

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

#include QMK_KEYBOARD_H
#include "pointing_device.h"
#include "transactions.h"
#include <string.h>
#ifdef MOUSEKEY_ENABLE
#    include "mousekey.h"
#endif

// typedef struct {
//     uint16_t device_cpi;
// } kb_config_data_t;

kb_config_data_t                      kb_config;
static report_mouse_t                 shared_mouse_report;
extern const pointing_device_driver_t pointing_device_driver;

void kb_pointer_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    shared_mouse_report = pointing_device_driver.get_report(shared_mouse_report);
    memcpy(target2initiator_buffer, &shared_mouse_report, sizeof(report_mouse_t));
    shared_mouse_report.x = 0;
    shared_mouse_report.y = 0;
    shared_mouse_report.h = 0;
    shared_mouse_report.v = 0;
}

void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config)) {
        memcpy(&kb_config, initiator2target_buffer, sizeof(kb_config));
    }

    static uint16_t cpi = 0;
    // Check if the state values are different
    if (cpi != kb_config.device_cpi) {
        cpi = kb_config.device_cpi;
        if (!is_keyboard_left()) {
            pointing_device_set_cpi(cpi);
        }
    }
}

void keyboard_pre_init_sync(void) {
    memset(&kb_config, 0, sizeof(kb_config));
    memset(&shared_mouse_report, 0, sizeof(shared_mouse_report));
}

void keyboard_post_init_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, kb_config_sync_handler);
    transaction_register_rpc(RPC_ID_POINTER_STATE_SYNC, kb_pointer_sync_handler);
}

void housekeeping_task_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_config_data_t last_kb_config;
        static uint32_t         last_sync  = 0;
        bool                    needs_sync = false;

        // Check if the state values are different
        if (memcmp(&kb_config, &last_kb_config, sizeof(kb_config))) {
            needs_sync = true;
            memcpy(&last_kb_config, &kb_config, sizeof(kb_config));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_KB_CONFIG_SYNC, sizeof(kb_config), &kb_config)) {
                last_sync = timer_read32();
            }
        }
    }
}

void trackball_set_cpi(uint16_t cpi) {
    kb_config.device_cpi = cpi;
    if (!is_keyboard_left()) {
        pointing_device_set_cpi(cpi);
    }
}

void pointing_device_task(void) {
    if (!is_keyboard_master()) {
        return;
    }

#if defined(POINTING_DEVICE_TASK_THROTTLE)
    static uint32_t last_exec = 0;
    if (timer_elapsed32(last_exec) < 1) {
        return;
    }
    last_exec = timer_read32();
#endif

    report_mouse_t local_report = pointing_device_get_report();

    // Gather report info
#ifdef POINTING_DEVICE_MOTION_PIN
    if (!readPin(POINTING_DEVICE_MOTION_PIN))
#endif
#if defined(POINTING_DEVICE_COMBINED)
        local_report = pointing_device_driver.get_report(local_report);
    transaction_rpc_recv(RPC_ID_POINTER_STATE_SYNC, sizeof(report_mouse_t), &shared_mouse_report);
    local_report.x = local_report.x | shared_mouse_report.x;
    local_report.y = local_report.y | shared_mouse_report.y;
    local_report.h = local_report.h | shared_mouse_report.h;
    local_report.v = local_report.v | shared_mouse_report.v;
#elif defined(POINTING_DEVICE_LEFT)
    if (is_keyboard_left()) {
        local_report = pointing_device_driver.get_report(local_report);
    } else {
        transaction_rpc_recv(RPC_ID_POINTER_STATE_SYNC, sizeof(report_mouse_t), &local_report);
    }
#elif defined(POINTING_DEVICE_RIGHT)
    if (!is_keyboard_left()) {
        local_report = pointing_device_driver.get_report(local_report);
    } else {
        transaction_rpc_recv(RPC_ID_POINTER_STATE_SYNC, sizeof(report_mouse_t), &local_report);
    }
#else
#    error "You need to define the side(s) the pointing device is on. POINTING_DEVICE_COMBINED / POINTING_DEVICE_LEFT / POINTING_DEVICE_RIGHT"
#endif

    // Support rotation of the sensor data
#if defined(POINTING_DEVICE_ROTATION_90) || defined(POINTING_DEVICE_ROTATION_180) || defined(POINTING_DEVICE_ROTATION_270)
    int8_t x = local_report.x, y = local_report.y;
#    if defined(POINTING_DEVICE_ROTATION_90)
    local_report.x = y;
    local_report.y = -x;
#    elif defined(POINTING_DEVICE_ROTATION_180)
    local_report.x = -x;
    local_report.y = -y;
#    elif defined(POINTING_DEVICE_ROTATION_270)
    local_report.x = -y;
    local_report.y = x;
#    else
#        error "How the heck did you get here?!"
#    endif
#endif
    // Support Inverting the X and Y Axises
#if defined(POINTING_DEVICE_INVERT_X)
    local_report.x = -local_report.x;
#endif
#if defined(POINTING_DEVICE_INVERT_Y)
    local_report.y = -local_report.y;
#endif

    // allow kb to intercept and modify report
    local_report = pointing_device_task_kb(local_report);
    // combine with mouse report to ensure that the combined is sent correctly
#ifdef MOUSEKEY_ENABLE
    report_mouse_t mousekey_report = mousekey_get_report();
    local_report.buttons           = local_report.buttons | mousekey_report.buttons;
#endif
#if defined(POINTING_DEVICE_COMBINED)
    local_report.buttons = local_report.buttons | shared_mouse_report.buttons;
#endif
    pointing_device_set_report(local_report);
    pointing_device_send();
}
