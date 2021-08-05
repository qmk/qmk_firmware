#ifdef SPLIT_TRANSACTION_IDS_USER
#    include "transport_sync.h"
#    include "transactions.h"
#    include <string.h>

#    ifdef UNICODE_ENABLE
extern unicode_config_t unicode_config;
#    endif
#    ifdef AUDIO_ENABLE
#        include "audio.h"
#    endif
#    if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
extern bool tap_toggling;
#    endif
#    ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#    endif
extern userspace_config_t userspace_config;

typedef struct {
    bool     oled_on;
    bool     audio_enable;
    bool     audio_clicky_enable;
    bool     tap_toggling;
    bool     unicode_mode;
    uint16_t keymap_config;
    uint8_t  userspace_config;
    bool     swap_hands;
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
#    ifdef OLED_DRIVER_ENABLE
        user_state.oled_on = is_oled_on();
#    endif

        user_state.keymap_config = keymap_config.raw;
        user_state.userspace_config = userspace_config.raw & 0xF;
#    ifdef AUDIO_ENABLE
        user_state.audio_enable        = is_audio_on();
        user_state.audio_clicky_enable = is_clicky_on();
#    endif
#    if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
        user_state.tap_toggling = tap_toggling;
#    endif
#    ifdef SWAP_HANDS_ENABLE
        user_state.swap_hands = swap_hands;
#    endif

    } else {
#    ifdef OLED_DRIVER_ENABLE
        if (user_state.oled_on) {
            oled_on();
        } else {
            oled_off();
        }
#    endif
        keymap_config.raw    = user_state.keymap_config;
        userspace_config.raw = user_state.userspace_config;
#    ifdef UNICODE_ENABLE
        unicode_config.input_mode = user_state.unicode_mode;
#    endif
#    ifdef AUDIO_ENABLE
        if (user_state.audio_enable != is_audio_on()) {
            if (user_state.audio_enable) {
                audio_on();
            } else {
                audio_off();
            }
        }
        if (user_state.audio_clicky_enable != is_clicky_on()) {
            if (user_state.audio_clicky_enable) {
                clicky_on();
            } else {
                clicky_off();
            }
        }
#    endif
#    if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
        tap_toggling = user_state.tap_toggling;
#    endif
#    ifdef SWAP_HANDS_ENABLE
        swap_hands = user_state.swap_hands;
#    endif
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
