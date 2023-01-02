// Copyright 2022 Dane Skalski (@Daneski13)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "junco.h"

// Keyboard level data
kb_config_t kb_config;

#ifdef JUNCO_SYNC_ENABLE

/* Whether to sync flags */
// Whether a reset needs to happen (applies to both sides)
kb_needs_reset_t kb_needs_reset = {.reset = false, .eeprom = false};
// Whether the sides need to sync
bool kb_needs_sync = false;
// Whether the sides need to sync the RGB
bool kb_needs_rgb_sync = false;

/*
    Enable/Disable Junco Sync status
    (will be synced between sides)
*/
void junco_sync_enable(void) {
    if (kb_config.junco_sync_enabled) return;
    kb_config.junco_sync_enabled = true;
    dprintf("Junco Sync: Enabled\n");
    kb_needs_sync = true;
}
void junco_sync_disable(void) {
    if (!kb_config.junco_sync_enabled) return;
    kb_config.junco_sync_enabled = false;
    dprintf("Junco Sync: Disabled\n");
    kb_needs_sync = true;
}
bool is_junco_sync_enabled(void) {
    return kb_config.junco_sync_enabled;
}

#endif

// With EE_HANDS, if the user didn't explicitly set the handedness at compile time,
// the handedness is cleared with a normal eeconfig_init. This function gets around
// that.
#ifdef EE_HANDS
void eeconfig_init_persist_handedness(void) {
    // Clear EEPROM but persist handedness
    bool handedness = eeconfig_read_handedness();
    eeconfig_init();
    eeconfig_update_handedness(handedness);
}
#endif

// Keyboard level EEPROM init
void eeconfig_init_kb(void) {
    /* Reset kb eeprom */
    kb_config.raw                = 0;
    kb_config.junco_sync_enabled = true; // Enabled by default
    eeconfig_update_kb(kb_config.raw);

    // Call the user EEPROM init
    eeconfig_init_user();
}

// Keyboard level post init
void keyboard_post_init_kb(void) {
    // Read the kb config from EEPROM
    kb_config.raw = eeconfig_read_kb();

#ifdef JUNCO_SYNC_ENABLE
    printf("Junco Sync available, status: %s\n", kb_config.junco_sync_enabled ? "enabled" : "disabled");

    // Register the RPC calls for syncing. Init regardless
    // of junco_sync_enabled because if re-enabled, we
    // want to be able to sync that state to the slave
    // and bring it up-to-date with the master.
    junco_sync_init();
#endif

    // Call the user post init
    keyboard_post_init_user();
}

// Keyboard level intercept of key processing
bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    // Call the user key processing first
    bool user_process = process_record_user(keycode, record);
    // If the user processing returns false, return false
    if (!user_process) return false;

#ifdef JUNCO_SYNC_ENABLE
    // If Junco sync is disabled, skip
    if (!kb_config.junco_sync_enabled) return true;

    /*
        Intercept EEPROM related keycodes and reboot, setting
        flags that will cause syncing
    */
    switch (keycode) {
        // Intercept eeprom clear/reboot
        case QK_CLEAR_EEPROM:
            if (record->event.pressed) {
                kb_needs_reset.reset  = true;
                kb_needs_reset.eeprom = true;
            }
            return false;
        case QK_REBOOT:
            if (record->event.pressed) {
                kb_needs_reset.reset  = true;
                kb_needs_reset.eeprom = false;
            }
            return false;

        // Intercept all Magic keycodes for extension
        case CL_SWAP ... EC_TOGG:
            // Set kb_needs_sync on key release because the
            // keypress down will be processed normally.
            // It will update the master's EEPROM for us
            // so we can be absolutely sure the master
            // is up to date
            if (!record->event.pressed) {
                kb_needs_sync = true;
            }
            break;
        // Intercept all RGB keycodes for extension
        case RGB_TOG ... RGB_MODE_TWINKLE:
            // Process RGB sync on key release because
            // we want both events to be processed normally.
            // Depending on the user's settings, RGB changes
            // may only actually happen on key release.
            if (!record->event.pressed) {
                kb_needs_rgb_sync = true;
            }
            break;
        // Intercept default layer changes
        case QK_DEF_LAYER ... QK_DEF_LAYER_MAX:
            // Processes sync on key release because the
            // keypress should be processed normally
            if (!record->event.pressed) {
                kb_needs_sync = true;
            }
            break;
        // Default case
        default:
            break;
    }
#endif

    return true;
}

/*
    - Keyboard level housekeeping -
    Actually where the syncs get called. Housekeeping is called periodically,
    so if a sync fails it will be retried in a timely manner, also acts as
    a loop that allows junco_sync_reset to work.
 */
void housekeeping_task_kb(void) {
#ifdef JUNCO_SYNC_ENABLE
    // If Junco sync is disabled, skip (assuming we don't need to sync it being disabled)
    if (!kb_config.junco_sync_enabled && !kb_needs_sync) return;

    // Will only actually reset when the kb_needs_reset.reset is true
    // Top level because needs to be called on both the slave and master
    junco_sync_reset(&kb_needs_reset.reset, &kb_needs_reset.eeprom, NULL);

    /* The rest is only for master side */
    if (!is_keyboard_master()) return;

    // Ensure something actually needs to be synced.
    if (!kb_needs_sync && !kb_needs_rgb_sync) return;

    // Throttles syncing to the specified speed.
    // (Default is sync no faster than once per second)
    static uint32_t last_sync = 0;
    if (timer_elapsed32(last_sync) < JUNCO_SYNC_THROTTLE) return;

    // Update timer
    last_sync = timer_read32();

    // Check if sync is needed
    if (kb_needs_sync) {
        // If attempt failed, flag still needs to be true
        kb_needs_sync = !junco_sync();
        return;
    }

    if (kb_needs_rgb_sync) {
#    ifdef RGB_MATRIX_ENABLE
        // If attempt failed, flag still needs to be true
        kb_needs_rgb_sync = !junco_sync_rgb();
#    else
        kb_needs_rgb_sync = false;
#    endif
        return;
    }

#endif
}
