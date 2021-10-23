/* Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
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

#include "tractyl_manuform.h"
#include "transactions.h"
#include <string.h>
#include "drivers/sensors/pmw3360.h"

kb_config_data_t  kb_config;
kb_mouse_report_t sync_mouse_report;

void kb_pointer_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (target2initiator_buffer_size == sizeof(sync_mouse_report)) {
        memcpy(target2initiator_buffer, &sync_mouse_report, sizeof(sync_mouse_report));
    }
    sync_mouse_report.x = 0;
    sync_mouse_report.y = 0;
}

void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config)) {
        memcpy(&kb_config, initiator2target_buffer, sizeof(kb_config));
    }

    static uint16_t cpi = 0;
    // Check if the state values are different
    if (cpi != kb_config.device_cpi) {
        cpi = kb_config.device_cpi;
    }
}

void keyboard_pre_init_sync(void) {
    memset(&kb_config, 0, sizeof(kb_config));
    memset(&sync_mouse_report, 0, sizeof(sync_mouse_report));
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
        pmw_set_cpi(cpi);
    }
}
