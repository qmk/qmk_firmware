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

#include "transport_sync.h"
#include "transactions.h"
#include <string.h>

#ifdef UNICODE_ENABLE
extern unicode_config_t unicode_config;
#endif
#ifdef AUDIO_ENABLE
#    include "audio.h"
extern bool delayed_tasks_run;
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
extern bool tap_toggling;
#endif
#ifdef SWAP_HANDS_ENABLE
extern bool swap_hands;
#endif
extern userspace_config_t userspace_config;

__attribute__((aligned(8))) typedef struct {
    bool audio_enable;
    bool audio_clicky_enable;
    bool tap_toggling;
    bool unicode_mode;
    bool swap_hands;
} user_runtime_config_t;

uint16_t transport_keymap_config    = 0;
uint32_t transport_userspace_config = 0;

user_runtime_config_t user_state;

void user_state_sync(uint8_t initiator2target_buffer_size, const void* initiator2target_buffer, uint8_t target2initiator_buffer_size, void* target2initiator_buffer) {
    if (initiator2target_buffer_size == sizeof(user_state)) {
        memcpy(&user_state, initiator2target_buffer, initiator2target_buffer_size);
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

void keyboard_post_init_transport_sync(void) {
    // Register keyboard state sync split transaction
    transaction_register_rpc(RPC_ID_USER_STATE_SYNC, user_state_sync);
    transaction_register_rpc(RPC_ID_USER_KEYMAP_SYNC, user_keymap_sync);
    transaction_register_rpc(RPC_ID_USER_CONFIG_SYNC, user_config_sync);
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
#ifdef SWAP_HANDS_ENABLE
        user_state.swap_hands = swap_hands;
#endif

    } else {
        keymap_config.raw    = transport_keymap_config;
        userspace_config.raw = transport_userspace_config;
#ifdef UNICODE_ENABLE
        unicode_config.input_mode = user_state.unicode_mode;
#endif
#ifdef AUDIO_ENABLE
        if (delayed_tasks_run) {
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
        }
#endif
#if defined(POINTING_DEVICE_ENABLE) && defined(KEYBOARD_handwired_tractyl_manuform)
        tap_toggling = user_state.tap_toggling;
#endif
#ifdef SWAP_HANDS_ENABLE
        swap_hands = user_state.swap_hands;
#endif
    }
}

void user_transport_sync(void) {
    if (is_keyboard_master()) {
        // Keep track of the last state, so that we can tell if we need to propagate to slave
        static user_runtime_config_t last_user_state;
        static uint16_t              last_keymap = 0;
        static uint32_t              last_config = 0;
        static uint32_t              last_sync[3];
        bool                         needs_sync = false;

        // Check if the state values are different
        if (memcmp(&user_state, &last_user_state, sizeof(user_state))) {
            needs_sync = true;
            memcpy(&last_user_state, &user_state, sizeof(user_state));
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
        }
    }
}

void housekeeping_task_user(void) {
    // Update kb_state so we can send to slave
    user_transport_update();

    // Data sync from master to slave
    user_transport_sync();
}
