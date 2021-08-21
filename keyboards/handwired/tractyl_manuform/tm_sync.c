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
kb_pointer_data_t kb_pointer;

void kb_config_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_config)) {
        memcpy(&kb_config, initiator2target_buffer, sizeof(kb_config));
    }
}
void kb_pointer_sync_handler(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (target2initiator_buffer_size == sizeof(kb_pointer)) {
        memcpy(target2initiator_buffer, &kb_pointer, sizeof(kb_pointer));
    }
}

void keyboard_pre_init_sync(void) {
    memset(&kb_config, 0, sizeof(kb_config));
    memset(&kb_pointer, 0, sizeof(kb_pointer));
}

void keyboard_post_init_kb(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_KB_CONFIG_SYNC, kb_config_sync_handler);
    transaction_register_rpc(RPC_ID_POINTER_STATE_SYNC, kb_pointer_sync_handler);

    keyboard_post_init_user();
}

void kb_config_update(void) {
    if (is_keyboard_master()) {
        static uint16_t cpi = 0;
        if (cpi != kb_config.device_cpi) {
            cpi = kb_config.device_cpi;
            pmw_set_cpi(cpi);
        }
    }
}

void kb_config_sync(void) {
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

void kb_pointer_sync(void) {
    if (is_keyboard_master() && is_keyboard_left()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static uint32_t last_sync = 0;

        // Perform the sync if requested
        if (timer_elapsed32(last_sync) >= 5) {
            if (transaction_rpc_recv(RPC_ID_POINTER_STATE_SYNC, sizeof(kb_pointer), &kb_pointer)) {
                last_sync = timer_read32();
            }
        }
    }
}

void housekeeping_task_kb(void) {
    // Update kb_config so we can send to slave
    kb_config_update();
    // Data sync from master to slave
    kb_config_sync();
    kb_pointer_sync();
}

void kb_pointer_sync_send(int8_t x, int8_t y) {
    kb_pointer.mouse_x = x;
    kb_pointer.mouse_y = y;
}

kb_pointer_data_t kb_pointer_sync_get(void) { return (kb_pointer_data_t){.mouse_x = kb_pointer.mouse_x, .mouse_y = kb_pointer.mouse_y}; }

void trackball_set_cpi(uint16_t cpi) {
    kb_config.device_cpi = cpi;
    if (!is_keyboard_left()) {
        pmw_set_cpi(cpi);
    }
}
