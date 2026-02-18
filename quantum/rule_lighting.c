/* Copyright 2026 Javier Domingo
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

#ifdef RGB_MATRIX_ENABLE

#include "rule_lighting.h"
#include "keymap_introspection.h"
#include <string.h>

#ifdef SPLIT_KEYBOARD
#    include "keyboard.h"
#    include "transactions.h"
#    include "timer.h"
#    include "split_util.h"
#endif

/**
 * Rules array defined by user in keymap.c
 * Weak default provides empty array if not defined
 */
__attribute__((weak)) const rule_lighting_entry_t rules[RULE_LIGHTING_ENTRIES] = {0};

#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
/* Slave-side RAM copy of rules synced from master
 * Sync is needed with DYNAMIC_KEYMAP because:
 * - EEPROM is per-chip (independent on each half)
 * - Keymaps can diverge between halves via VIA/HID writes
 * For static keymaps, both halves read rules directly from flash (no sync needed)
 */
static rule_lighting_entry_t slave_rules[RULE_LIGHTING_ENTRIES];

/* Master-side sync state */
static bool master_sync_complete = false;
#    endif

/**
 * Get rules array (master uses flash, slave uses RAM copy only for dynamic keymaps)
 */
const rule_lighting_entry_t *rule_lighting_get_rules(void) {
#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
    if (!is_keyboard_master()) {
        return slave_rules;
    }
#    endif
    return rules;
}

/**
 * Get keycode for a key position (supports split keyboard)
 * Uses keymap introspection on master, returns KC_NO on slave
 */
uint16_t get_synced_keycode(uint8_t layer, uint8_t row, uint8_t col) {
    /* Use keymap introspection to get keycode from EEPROM/flash */
    if (layer >= keymap_layer_count() || row >= MATRIX_ROWS || col >= MATRIX_COLS) {
        return KC_NO;
    }

    /* Both master and slave use keycode_at_keymap_location()
     * This reads from EEPROM if DYNAMIC_KEYMAP is enabled, flash otherwise */
    return keycode_at_keymap_location(layer, row, col);
}

#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)

/**
 * Slave handler for rule sync RPC
 * Receives rules from master and sends ACK back
 */
static void rule_lighting_slave_handler(uint8_t m2s_size, const void *m2s_buffer, uint8_t s2m_size, void *s2m_buffer) {
    uint8_t *ack = (uint8_t *)s2m_buffer;

    if (m2s_size == sizeof(slave_rules) && s2m_size >= 1) {
        memcpy(slave_rules, m2s_buffer, sizeof(slave_rules));
        *ack = 1; /* Send ACK */
    } else if (s2m_size >= 1) {
        *ack = 0; /* Invalid size */
    }
}

/**
 * Master sync - sync rules to slave on connection
 * Handles late slave connection by detecting disconnection and resetting sync state
 */
static void rule_lighting_master_sync(void) {
    /* If sync complete, check if slave disconnected to reset state */
    if (master_sync_complete) {
        if (!is_transport_connected()) {
            master_sync_complete = false;
        }
        return;
    }

    /* Try syncing if not complete and slave is connected */
    if (is_transport_connected()) {
        static uint32_t last_attempt = 0;
        if (timer_elapsed32(last_attempt) > 500) {
            last_attempt = timer_read32();

            /* Send rules and check ACK */
            uint8_t ack = 0;
            if (transaction_rpc_exec(SPLIT_RULE_LIGHTING_SYNC_ID, sizeof(rules), rules, sizeof(ack), &ack)) {
                if (ack == 1) {
                    master_sync_complete = true;
                }
            }
        }
    }
}

/**
 * Register split transactions - must be called AFTER split_post_init()
 */
void rule_lighting_post_init(void) {
    transaction_register_rpc(SPLIT_RULE_LIGHTING_SYNC_ID, rule_lighting_slave_handler);
}

#    endif /* SPLIT_KEYBOARD && DYNAMIC_KEYMAP_ENABLE */

/**
 * Housekeeping task for rule lighting
 * Handles split sync on master when dynamic keymaps are enabled
 */
void rule_lighting_task(void) {
#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
    if (is_keyboard_master()) {
        rule_lighting_master_sync();
    }
#    endif
}

/**
 * Initialize rule lighting (called from rgb_matrix_init)
 * No-op for flash-only implementation
 */
void rule_lighting_init(void) {
#    if defined(SPLIT_KEYBOARD) && defined(DYNAMIC_KEYMAP_ENABLE)
    /* Clear slave rules on init */
    if (!is_keyboard_master()) {
        memset(slave_rules, 0, sizeof(slave_rules));
    }
#    endif
}

#endif /* RGB_MATRIX_ENABLE */
