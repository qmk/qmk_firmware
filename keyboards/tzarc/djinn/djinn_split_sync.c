// Copyright 2018-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#include "transactions.h"
#include "split_util.h"
#include "djinn.h"

kb_runtime_config kb_state;
uint32_t          last_slave_sync_time = 0;

void kb_state_update(void) {
    if (is_keyboard_master()) {
        // Modify allowed current limits
        usbpd_update();
    }
}

void kb_state_sync(void) {
    if (!is_transport_connected()) return;

    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static kb_runtime_config last_kb_state;
        static uint32_t          last_sync;
        bool                     needs_sync = false;

        // Check if the state values are different
        if (memcmp(&kb_state, &last_kb_state, sizeof(kb_runtime_config))) {
            needs_sync = true;
            memcpy(&last_kb_state, &kb_state, sizeof(kb_runtime_config));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 500) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_SYNC_STATE_KB, sizeof(kb_runtime_config), &kb_state)) {
                last_sync = timer_read32();
            } else {
                dprint("Failed to perform data transaction\n");
            }
        }
    }
}

void kb_state_sync_slave(uint8_t m2s_size, const void* m2s_buffer, uint8_t s2m_size, void* s2m_buffer) {
    if (m2s_size == sizeof(kb_runtime_config)) {
        memcpy(&kb_state, m2s_buffer, sizeof(kb_runtime_config));
        last_slave_sync_time = timer_read32();
    }
}
