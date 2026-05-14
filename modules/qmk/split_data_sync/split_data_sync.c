// Copyright 2026 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#include "debug.h"
#include "timer.h"
#include "transactions.h"

typedef struct _master_to_slave_t {
    int m2s_data;
} master_to_slave_t;

typedef struct _slave_to_master_t {
    int s2m_data;
} slave_to_master_t;

static void module_sync_slave_handler(uint8_t in_buflen, const void *in_data, uint8_t out_buflen, void *out_data) {
    const master_to_slave_t *m2s = (const master_to_slave_t *)in_data;
    slave_to_master_t       *s2m = (slave_to_master_t *)out_data;
    s2m->s2m_data                = m2s->m2s_data + 5; // whatever comes in, add 5 so it can be sent back
}

void keyboard_post_init_split_data_sync(void) {
    transaction_register_rpc(EXAMPLE_MODULE_SYNC_A, module_sync_slave_handler);
}

void housekeeping_task_split_data_sync(void) {
    if (is_keyboard_master()) {
        // Interact with slave every 500ms
        static uint32_t last_sync = 0;
        if (timer_elapsed32(last_sync) > 500) {
            master_to_slave_t m2s = {6};
            slave_to_master_t s2m = {0};
            if (transaction_rpc_exec(EXAMPLE_MODULE_SYNC_A, sizeof(m2s), &m2s, sizeof(s2m), &s2m)) {
                last_sync = timer_read32();
                dprintf("Slave value: %d\n", s2m.s2m_data); // this will now be 11, as the slave adds 5
            } else {
                dprint("Slave sync failed!\n");
            }
        }
    }
}
