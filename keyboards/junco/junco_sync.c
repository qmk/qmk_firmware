// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

/* Only relevant if junco sync is enabled */
#ifdef JUNCO_SYNC_ENABLE
#    include "junco_sync.h"
#    include "print.h"
#    include "transactions.h"
#    include "split_util.h"
#    include "junco.h"

/* Sync common keyboard data */

// Pointer to the user's user_config.raw. If the user wants to sync their own user config,
// set this to the address of user_config.raw in the keyboard_post_init after reading the
// user_config from eeprom `user_config_raw_ptr = &user_config.raw`.
uint32_t* user_config_raw_ptr = NULL;

// Data type for sending data to slave
typedef struct {
    uint32_t kb_conf;     // Current keyboard config
    uint32_t default_lay; // Current default layer, SPLIT_LAYER_STATE_ENABLE is not persistent and may not sync in time
    uint32_t user_conf;   // If the user has a config...
    uint16_t keymap_conf; // Current keymap config
} kb_sync_data_t;
// Saves common data on master and sends it to slave
bool junco_sync(void) {
    // Count how many times retried
    static uint8_t retries = 0;
    // Allow max retries
    if (retries >= JUNCO_SYNC_RETRIES) {
        dprintf("Failure to sync: too many retries\n");
        retries = 0;
        return true;
    }

    // Ensure a split is actually connected
    if (!is_transport_connected()) {
        dprintf("Failure to sync: No split detected\n");
        retries++;
        return false;
    }

    uint8_t layer = get_highest_layer(default_layer_state);

    /*
        Save data to eeprom on master
        All the update functions will read before writing, so we
        don't need to ensure something changed before attempting to
        write.
    */
    // Save the kb data on master
    eeconfig_update_kb(kb_config.raw);

    // Save the default layer
    set_single_persistent_default_layer(layer);

    // Save user config on master
    uint32_t user_configuration = 0;
    if (user_config_raw_ptr) user_configuration = *user_config_raw_ptr;
    if (user_configuration != 0) eeconfig_update_user(user_configuration);

    // Save the Magic settings on master
    eeconfig_update_keymap(keymap_config.raw);

    // Data to be sent
    kb_sync_data_t m2s = {
        kb_config.raw,      // Send the keyboard config
        layer,              // Send the default layer
        user_configuration, // Send user config
        keymap_config.raw   // Send the keymap config (Magic)
    };

    // Execute RPC
    if (transaction_rpc_send(KB_SYNC, sizeof(m2s), &m2s)) {
        dprintf("Split synced!\n");
        retries = 0;
        return true;
    } else {
        dprintf("Failure to sync: RPC failed\n");
        retries++;
        return false;
    }
}
// Slave handler for KB_SYNC
void kb_sync_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const kb_sync_data_t* m2s = (kb_sync_data_t*)in_data;

    /* Save data to eeprom on slave side */
    // Save the keyboard data on slave
    eeconfig_update_kb(m2s->kb_conf);
    // Save the default layer
    set_single_persistent_default_layer(m2s->default_lay);
    // Save the keymap config
    if (m2s->keymap_conf != keymap_config.raw) eeconfig_update_keymap(m2s->keymap_conf);
    // Save the user config
    if (m2s->user_conf != 0) eeconfig_update_user(m2s->user_conf);
}

/* Reboot/Reset both halves, optionally clear eeprom */
typedef struct {
    bool reset;
    bool clear_eeproms;
} kb_sync_reset_flags_t;
// Flags for reset and clear. Will be the same on both the slave and master
kb_sync_reset_flags_t kb_sync_reset_flags = {false, false};

// Helper function that will clear EEPROM and reboot
void _junco_reset_helper(void) {
    // Clear EEPROM if needed
    if (kb_sync_reset_flags.clear_eeproms) {
        dprintf("Clearing EEPROM...\n");
#    ifdef EE_HANDS
        eeconfig_init_persist_handedness();
#    else
        ee_config_disable();
#    endif
    }

    // Flags back to false
    kb_sync_reset_flags.reset         = false;
    kb_sync_reset_flags.clear_eeproms = false;

    // Soft reset
    dprintf("Rebooting...\n");
    soft_reset_keyboard();
}
// Reboots the keyboard, optionally clearing EEPROMs
void junco_sync_reset(bool* needs_reset, bool* clear_eeprom, bool* failed) {
    // Count how many times retried
    static uint8_t retries = 0;
    // Allow max retries until just reseting the master
    if (retries >= JUNCO_SYNC_RETRIES) {
        // Give the user a chance to detect the failure before just resetting the master
        if ((failed) && (retries == JUNCO_SYNC_RETRIES)) {
            *failed = true;
            retries++;
            return;
        }

        dprintf("Failure to reset both halves: too many retries. Resetting master...\n");
        retries = 0;
        // Reset the external booleans
        if (needs_reset) *needs_reset = false;
        if (clear_eeprom) *clear_eeprom = false;
        if (failed) *failed = false;
        _junco_reset_helper();
    }

    // Check pointer
    if (!needs_reset) {
        dprintf("Failure to reset: needs_reset is NULL\n");
        retries = JUNCO_SYNC_RETRIES;
        return;
    }

    // Ensure reset actually needs to happen (only the master will know this)
    if (!*needs_reset && is_keyboard_master()) return;

    /*
        The slave will always reach this point, the master will only reach
        this point when a reset needs to happen. We can be assured that
        the flag struct will match on both halves. If reset is false on
        the slave it can return from the function, but the master knows
        a reset needs to happen so it sets its flags and tells the slave
        to do the same. We do it this way because rebooting directly
        within the slave handler will cause the slave to reset before
        the master knows what's happening, causing issues. Thus, this
        function is always called twice when a reset need to happen,
        first time sets the flags on both halves and the second time
        actually resets both halves.
    */

    // When the flag is set (will be same on slave & master)
    if (kb_sync_reset_flags.reset) {
        // Set the external booleans to false, reset is about to happen
        if (needs_reset) *needs_reset = false;
        if (clear_eeprom) *clear_eeprom = false;
        if (failed) *failed = false;

        // Let master finish first
        if (!is_keyboard_master()) wait_ms(100);

        retries = 0;
        // On both sides, reboot and clear eeproms as needed
        _junco_reset_helper();
    } else {
        // Only execute the following on master
        if (!is_keyboard_master()) return;

        // Ensure split is actually connected
        if (!is_transport_connected()) {
            dprintf("Failure to reset: no split detected\n");
            retries++;
            return;
        }

        /* Send reset request to slave */
        kb_sync_reset_flags_t m2s = {true, clear_eeprom ? (*clear_eeprom ? true : false) : false};
        // Execute RPC (sets flags on slave)
        if (transaction_rpc_send(KB_SYNC_RESET, sizeof(m2s), &m2s)) {
            // Set flags on master
            kb_sync_reset_flags = m2s;
        } else {
            dprintf("Failed to reset, retrying...\n");
            retries++;
        }
    }
}
// Slave handler for KB_SYNC_RESET
void kb_sync_reset_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    const kb_sync_reset_flags_t* m2s = (kb_sync_reset_flags_t*)in_data;
    // Set flags on slave
    kb_sync_reset_flags = *m2s;
}

#    ifdef RGB_MATRIX_ENABLE
/* Sync RGB settings between halves */
// Data to receive from slave
typedef struct {
    rgb_config_t config;
} kb_sync_rgb_data_t;
bool junco_sync_rgb(void) {
    // Count how many times retried
    static uint8_t retries = 0;
    // Allow max retries
    if (retries >= JUNCO_SYNC_RETRIES) {
        dprintf("Failure to sync RGB: too many retries\n");
        retries = 0;
        return true;
    }

    // Ensure split is actually connected
    if (!is_transport_connected()) {
        dprintf("Failure to sync RGB: no split detected\n");
        retries++;
        return false;
    }

    // Receive the slave's config
    kb_sync_rgb_data_t s2m = {0};
    // Execute RPC
    if (transaction_rpc_recv(KB_SYNC_RGB, sizeof(s2m), &s2m)) {
        /* Check if the configs match */
        if (memcmp(&s2m.config, &rgb_matrix_config, sizeof(rgb_matrix_config)) != 0) {
            retries++;
            dprintf("Failure to sync RGB: config mismatch, retrying...\n");
            return false;
        }

        // Success, both match
        dprintf("Successfully synced RGB\n");
        retries = 0;
        return true;
    } else {
        dprintf("Failure to sync RGB: RPC failed, retrying...\n");
        retries++;
        return false;
    }
}
// Slave handler for KB_SYNC_RGB
void kb_sync_rgb_slave_handler(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    kb_sync_rgb_data_t* s2m = (kb_sync_rgb_data_t*)out_data;
    // Update the slave's matrix config in EEPROM.
    // The slave and master configs sync on in the core,
    // however only the master side is saved to EEPROM.
    // Thus we can call update on the slave and both will be
    // be synced. The update implementation already ensures
    // a write only happens when a change is actually needed.
    eeconfig_update_rgb_matrix();
    // Send back to master
    s2m->config = rgb_matrix_config;
}

#    endif

/* Register RPC calls for syncing */
void junco_sync_init(void) {
    transaction_register_rpc(KB_SYNC, kb_sync_slave_handler);
    transaction_register_rpc(KB_SYNC_RESET, kb_sync_reset_slave_handler);
#    ifdef RGB_MATRIX_ENABLE
    transaction_register_rpc(KB_SYNC_RGB, kb_sync_rgb_slave_handler);
#    endif
}

#endif
