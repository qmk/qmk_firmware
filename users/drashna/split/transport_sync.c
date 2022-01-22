// Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#include "transport_sync.h"
#include "transactions.h"
#include <string.h>
#ifdef __AVR__
#    include <avr/wdt.h>
#endif

#ifdef CUSTOM_UNICODE_ENABLE
#    include "process_unicode_common.h"
extern unicode_config_t unicode_config;
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
extern audio_config_t audio_config;
extern bool           delayed_tasks_run;
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
extern bool tap_toggling;
#endif
#ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#endif

#if defined(SPLIT_WATCHDOG_TIMEOUT)
static bool     watchdog_ping_done = false;
static uint32_t watchdog_timer     = 0;
#endif

extern userspace_config_t userspace_config;
extern bool               host_driver_disabled;

uint16_t transport_keymap_config    = 0;
uint32_t transport_userspace_config = 0, transport_user_state = 0;

user_runtime_config_t user_state;

void user_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_user_state)) {
        memcpy(&transport_user_state, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_keymap_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_keymap_config)) {
        memcpy(&transport_keymap_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}
void user_config_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(transport_userspace_config)) {
        memcpy(&transport_userspace_config, initiator2target_buffer, initiator2target_buffer_size);
    }
}

#if defined(SPLIT_WATCHDOG_TIMEOUT)
void watchdog_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) { watchdog_ping_done = true; }
#endif

#ifdef OLED_ENABLE
#include "oled/oled_stuff.h"
void keylogger_string_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == OLED_KEYLOGGER_LENGTH) {
        memcpy(&keylog_str, initiator2target_buffer, initiator2target_buffer_size);
    }
}
#endif

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_STATE_SYNC, user_state_sync);
    transaction_register_rpc(RPC_ID_USER_KEYMAP_SYNC, user_keymap_sync);
    transaction_register_rpc(RPC_ID_USER_CONFIG_SYNC, user_config_sync);
#ifdef OLED_ENABLE
    transaction_register_rpc(RPC_ID_USER_KEYLOG_STR, keylogger_string_sync);
#endif

#if defined(SPLIT_WATCHDOG_TIMEOUT)
#    if defined(PROTOCOL_LUFA)
    wdt_disable();
#    endif
    transaction_register_rpc(RPC_ID_USER_WATCHDOG_SYNC, watchdog_handler);
    watchdog_timer = timer_read32();
#endif
}

void user_transport_update(void) {
    if (is_keyboard_master()) {
        transport_keymap_config    = keymap_config.raw;
        transport_userspace_config = userspace_config.raw;
#ifdef AUDIO_ENABLE
        user_state.audio_enable        = is_audio_on();
        user_state.audio_clicky_enable = is_clicky_on();
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
        user_state.tap_toggling = tap_toggling;
#endif
#ifdef UNICODE_ENABLE
        user_state.unicode_mode = unicode_config.input_mode;
#endif
#ifdef SWAP_HANDS_ENABLE
        user_state.swap_hands = swap_hands;
#endif
        user_state.host_driver_disabled = host_driver_disabled;

        transport_user_state = user_state.raw;
    } else {
        keymap_config.raw    = transport_keymap_config;
        userspace_config.raw = transport_userspace_config;
        user_state.raw       = transport_user_state;
#ifdef UNICODE_ENABLE
        unicode_config.input_mode = user_state.unicode_mode;
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
        tap_toggling = user_state.tap_toggling;
#endif
#ifdef SWAP_HANDS_ENABLE
        swap_hands = user_state.swap_hands;
#endif
        host_driver_disabled = user_state.host_driver_disabled;
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static uint16_t last_keymap = 0;
        static uint32_t last_config = 0, last_sync[4], last_user_state = 0;
        bool            needs_sync = false;
#ifdef OLED_ENABLE
        static char     keylog_temp[OLED_KEYLOGGER_LENGTH] = { 0 };
#endif

        // Check if the state values are different
        if (memcmp(&transport_user_state, &last_user_state, sizeof(transport_user_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &transport_user_state, sizeof(transport_user_state));
        }
        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[0]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_STATE_SYNC, sizeof(user_state), &user_state)) {
                last_sync[0] = timer_read32();
            }
            needs_sync = false;
        }

        // Check if the state values are different
        if (memcmp(&transport_keymap_config, &last_keymap, sizeof(transport_keymap_config))) {
            needs_sync = true;
            memcpy(&last_keymap, &transport_keymap_config, sizeof(transport_keymap_config));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[1]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_KEYMAP_SYNC, sizeof(transport_keymap_config), &transport_keymap_config)) {
                last_sync[1] = timer_read32();
            }
            needs_sync = false;
        }

        // Check if the state values are different
        if (memcmp(&user_state, &last_config, sizeof(transport_userspace_config))) {
            needs_sync = true;
            memcpy(&last_config, &user_state, sizeof(transport_userspace_config));
        }

        // Send to slave every 500ms regardless of state change
        if (timer_elapsed32(last_sync[2]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_CONFIG_SYNC, sizeof(transport_userspace_config), &transport_userspace_config)) {
                last_sync[2] = timer_read32();
            }
            needs_sync = false;
        }

#ifdef OLED_ENABLE
        // Check if the state values are different
        if (memcmp(&keylog_str, &keylog_temp, OLED_KEYLOGGER_LENGTH)) {
            needs_sync = true;
            memcpy(&keylog_temp, &keylog_str, OLED_KEYLOGGER_LENGTH);
        }
        if (timer_elapsed32(last_sync[3]) > 250) {
            needs_sync = true;
        }

        // Perform the sync if requested
        if (needs_sync) {
            if (transaction_rpc_send(RPC_ID_USER_KEYLOG_STR, OLED_KEYLOGGER_LENGTH, &keylog_str)) {
                last_sync[3] = timer_read32();
            }
            needs_sync = false;
        }
#endif
    }

#if defined(SPLIT_WATCHDOG_TIMEOUT)
    if (!watchdog_ping_done) {
        if (is_keyboard_master()) {
            if (timer_elapsed32(watchdog_timer) > 100) {
                uint8_t any_data = 1;
                if (transaction_rpc_send(RPC_ID_USER_WATCHDOG_SYNC, sizeof(any_data), &any_data)) {
                    watchdog_ping_done = true;  // successful ping
                } else {
                    dprint("Watchdog ping failed!\n");
                }
                watchdog_timer = timer_read32();
            }
        } else {
            if (timer_elapsed32(watchdog_timer) > 3500) {
                software_reset();
                while (1) {
                }
            }
        }
    }
#endif

}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    user_transport_update();

    // Data sync from master to slave
    user_transport_sync();
}
