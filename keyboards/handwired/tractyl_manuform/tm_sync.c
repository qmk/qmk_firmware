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

#ifdef SPLIT_TRANSACTION_IDS_KB

#    include "tractyl_manuform.h"
#    include "transactions.h"
#    include <string.h>
#    include "drivers/sensors/pmw3360.h"

kb_runtime_config_t kb_state;
kb_slave_data_t     kb_slave;

void slave_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (target2initiator_buffer_size == sizeof(kb_slave)) {
        memcpy(target2initiator_buffer, &kb_slave, sizeof(kb_slave));
        if (kb_slave.mouse_x > 127) {
            kb_slave.mouse_x -= 127;
        } else if (kb_slave.mouse_x < -127) {
            kb_slave.mouse_x += 127;
        } else {
            kb_slave.mouse_x = 0;
        }

        if (kb_slave.mouse_y > 127) {
            kb_slave.mouse_y -= 127;
        } else if (kb_slave.mouse_y < -127) {
            kb_slave.mouse_y += 127;
        } else {
            kb_slave.mouse_y = 0;
        }
    }
}

void pointer_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(kb_state)) {
        memcpy(&kb_state, initiator2target_buffer, sizeof(kb_state));
    }
}

void keyboard_post_init_kb(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_STATE_SYNC, pointer_state_sync);
    transaction_register_rpc(RPC_ID_SLAVE_STATE, slave_state_sync);

    keyboard_post_init_user();
}

void kb_state_update(void) {
#    ifdef POINTING_DEVICE_ENABLE
    if (is_keyboard_master() && !is_keyboard_left()) {
        static uint16_t cpi = 0;
        if (cpi != kb_state.device_cpi) {
            cpi = kb_state.device_cpi;
            pmw_set_cpi(cpi);
        }
    }
#    endif
}

void kb_post_state_update(void) {
#    ifdef POINTING_DEVICE_ENABLE
    if (is_keyboard_master() && is_keyboard_left()) {
        report_mouse_t temp_report = pointing_device_get_report();
        temp_report.x              = kb_slave.mouse_x;
        temp_report.y              = kb_slave.mouse_y;
        pointing_device_set_report(temp_report);
    }
#    endif
}

void kb_state_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_runtime_config_t last_kb_state;
        static uint32_t            last_sync        = 0;
        static uint32_t            mouse_sync       = 0;
        bool                       needs_sync       = false;

        // Check if the state values are different
        if (memcmp(&kb_state, &last_kb_state, sizeof(kb_runtime_config_t))) {
            needs_sync = true;
            memcpy(&last_kb_state, &kb_state, sizeof(kb_runtime_config_t));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_STATE_SYNC, sizeof(kb_runtime_config_t), &kb_state)) {
                last_sync = timer_read32();
            }
        }

        if (is_keyboard_left()) {
            if (timer_elapsed32(mouse_sync) >= 5) {
                // always sync slave data, since it may contain device reports.
                if (transaction_rpc_recv(RPC_ID_SLAVE_STATE, sizeof(kb_slave_data_t), &kb_slave)) {
                    if (kb_slave.mouse_x >= -127 && kb_slave.mouse_x <= 127 && kb_slave.mouse_y >= -127 && kb_slave.mouse_y <= 127) {
                        mouse_sync = timer_read32();
                    }
                }
            }
        }
    }
}

void housekeeping_task_kb(void) {
    // Update kb_state so we can send to slave
    kb_state_update();

    // Data sync from master to slave
    kb_state_sync();

    kb_post_state_update();
}
#endif
