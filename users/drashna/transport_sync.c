#ifdef SPLIT_TRANSACTION_IDS_USER
#include "transport_sync.h"
#include "transactions.h"
#include <string.h>

typedef struct {
    bool            oled_on;
    uint16_t keymap_config;
} user_runtime_config_t;

user_runtime_config_t user_state;

void user_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_STATE_SYNC, user_sync);
}

void user_state_update(void) {
    if (is_keyboard_master()) {

#ifdef OLED_DRIVER_ENABLE
        user_state.oled_on = is_oled_on();
#endif

        user_state.keymap_config = keymap_config.raw;
    } else {
#ifdef OLED_DRIVER_ENABLE
        if (user_state.oled_on) {
            oled_on();
        } else {
            oled_off();
        }
#endif
        if (keymap_config.raw != user_state.keymap_config) {
            keymap_config.raw = user_state.keymap_config;
        }
    }
}

void user_state_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config_t last_user_state;
        static uint32_t              last_sync;
        bool                         needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_state));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_STATE_SYNC, sizeof(user_state), &user_state)) {
                last_sync = timer_read32();
            }
        }
    }
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    user_state_update();

    // Data sync from master to slave
    user_state_sync();
}
#endif
