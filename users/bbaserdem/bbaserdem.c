/* Copyright 2021 Batuhan Başerdem
 * <baserdem.batuhan@gmail.com> @bbaserdem
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

#include "bbaserdem.h"
// Language imports
#include <sendstring_dvorak.h>
// Need memcpy and memcmp from string.h along with transfer stuff
#ifdef SPLIT_KEYBOARD
#include "transactions.h"
#include <string.h>
#endif // SPLIT_KEYBOARD

/*-------------------------*\
|*-----KEYBOARD CONFIG-----*|
\*-------------------------*/
userspace_config_t userspace_config;
userspace_runtime_t userspace_runtime;

/*---------------------------------*\
|*----SPLIT KEYBOARD TRANSPORT-----*|
\*---------------------------------*/
#ifdef SPLIT_KEYBOARD
userspace_config_t transport_userspace_config;
userspace_runtime_t transport_userspace_runtime;

// Translate the RPC data to the local variable
void userspace_config_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // Copy incoming data to local variable
    if (in_buflen == sizeof(transport_userspace_config)) {
        memcpy(&transport_userspace_config, in_data, in_buflen);
    }
    // There is no data to send back; so no output handling
}
void userspace_runtime_sync(uint8_t in_buflen, const void* in_data, uint8_t out_buflen, void* out_data) {
    // Copy incoming data to local variable
    if (in_buflen == sizeof(transport_userspace_runtime)) {
        memcpy(&transport_userspace_runtime, in_data, in_buflen);
    }
    // There is no data to send back; so no output handling
}

// Either send or receive the correct data
void userspace_transport_update(void) {
    if (is_keyboard_master()) {
        // If we are the main device; we want to send info.
        transport_userspace_config.raw = userspace_config.raw;
        transport_userspace_runtime.raw = userspace_runtime.raw;
    } else {
        // If we are the secondary device; we want to receive info, and save to eeprom.
        userspace_config.raw = transport_userspace_config.raw;
        userspace_runtime.raw = transport_userspace_runtime.raw;
    }
}

// Initiate the protocol on sync
void userspace_transport_sync(bool force_sync) {
    if (is_keyboard_master()) {
        // Keep track of the last state
        static userspace_config_t last_userspace_config;
        static userspace_runtime_t last_userspace_runtime;
        bool needs_sync = false;

        // Check if the config values are different
        if (memcmp(&transport_userspace_config, &last_userspace_config, sizeof(transport_userspace_config))) {
            needs_sync = true;
            memcpy(&last_userspace_config, &transport_userspace_config, sizeof(transport_userspace_config));
        }
        // Perform the sync if requested
        if (needs_sync || force_sync) {
            transaction_rpc_send(RPC_ID_CONFIG_SYNC, sizeof(transport_userspace_config), &transport_userspace_config);
            needs_sync = false;
        }

        // Check if the runtime values are different
        if (memcmp(&transport_userspace_runtime, &last_userspace_runtime, sizeof(transport_userspace_runtime))) {
            needs_sync = true;
            memcpy(&last_userspace_runtime, &transport_userspace_runtime, sizeof(transport_userspace_runtime));
        }

        // Perform the sync if requested
        if (needs_sync || force_sync) {
            transaction_rpc_send(RPC_ID_RUNTIME_SYNC, sizeof(transport_userspace_runtime), &transport_userspace_runtime);
            needs_sync = false;
        }
    }
}
#endif // SPLIT_KEYBOARD

/*---------------------------*\
|*-----KEYBOARD PRE INIT-----*|
\*---------------------------*/
/* This code runs before anything is started.
 * Good for early hardware setup
 */
__attribute__ ((weak)) void keyboard_pre_init_keymap(void) {}
__attribute__ ((weak)) void keyboard_pre_init_user(void) {
    // Keymap specific stuff
    keyboard_pre_init_keymap();
}

/*---------------------*\
|*-----MATRIX INIT-----*|
\*---------------------*/
/* This code runs once midway thru the firmware process.
 * So far, sets the base layer and fixes unicode mode
 */
__attribute__ ((weak)) void matrix_init_keymap(void) {}
void matrix_init_user (void) {
    // Keymap specific things
    matrix_init_keymap();
}

/*----------------------------*\
|*-----KEYBOARD POST INIT-----*|
\*----------------------------*/
/* This code runs after anything is started.
 * Good for late hardware setup, like setting up layer specifications
 */
__attribute__ ((weak)) void keyboard_post_init_keymap(void) {}
__attribute__ ((weak)) void keyboard_post_init_user(void) {
    // Fix beginning base layer, in case some other firmware was flashed
    //  set_single_persistent_default_layer(_BASE);

    // Unicode mode
#   ifdef UNICODEMAP_ENABLE
    set_unicode_input_mode(UC_LNX);
#   endif // UNICODEMAP_ENABLE

    // Split keyboard halves communication
#   ifdef SPLIT_KEYBOARD
    // Register the transactions
    transaction_register_rpc( RPC_ID_CONFIG_SYNC, userspace_config_sync );
    transaction_register_rpc(RPC_ID_RUNTIME_SYNC, userspace_runtime_sync);
    // Load default config values
    if (is_keyboard_master()) {
        // If we are main; load from eeconfig
        userspace_config.raw = eeconfig_read_user();
        // And update the transport variable
        userspace_transport_update();
        // Do one forced transfer to sync halves
        userspace_transport_sync(true);
    } else {
        // Just sync the data received
        userspace_transport_update();
    }
#   else // SPLIT_KEYBOARD
    // If we are not split; just load from eeprom
    userspace_config.raw = eeconfig_read_user();
#   endif // SPLIT_KEYBOARD

    // Backlight LED
#   ifdef BACKLIGHT_ENABLE
    keyboard_post_init_backlight();
#   endif // BACKLIGHT_ENABLE

    // RGB underglow
#   ifdef RGBLIGHT_ENABLE
    keyboard_post_init_underglow();
#   endif // RGBLIGHT_ENABLE

    // Keymap specific stuff
    keyboard_post_init_keymap();
}

/*---------------------------*\
|*-----HOUSEKEEPING TASK-----*|
\*---------------------------*/
/* I have no idea what this does
 */
__attribute__ ((weak)) void housekeeping_task_keymap(void) {}
void housekeeping_task_user(void) {
    // Check eeprom every now and then
    static userspace_config_t prev_userspace_config;
    static fast_timer_t throttle_timer = 0;
    static bool init_flag = true;

    // Read this if we never read it before
    if (init_flag) {
        init_flag = false;
        prev_userspace_config.raw = eeconfig_read_user();
    }

    // Throttled tasks here
    if (timer_elapsed_fast(throttle_timer) >= HOUSEKEEPING_THROTTLE_INTERVAL_MS) {
        // Refresh timer
        throttle_timer = timer_read_fast();
        // Check userspace config for eeprom updates
        if (memcmp(&prev_userspace_config, &userspace_config, sizeof(userspace_config))) {
            memcpy(&prev_userspace_config, &userspace_config, sizeof(userspace_config));
            eeconfig_update_user(userspace_config.raw);
        }
    }

    // Do transport stuff
#   ifdef SPLIT_KEYBOARD
    userspace_transport_update();
    userspace_transport_sync(false);
#   endif // SPLIT_KEYBOARD

    // Hook to keymap code
    housekeeping_task_keymap();
}

/*-----------------------*\
|*-----EECONFIG INIT-----*|
\*-----------------------*/
/* Default values to send to the eeprom
 */
void eeconfig_init_user(void) {
    // Set everything to default
    userspace_config.raw = 0;
    // Set encoder states to sane defaults if enabled
#   ifdef ENCODER_ENABLE
    reset_encoder_state();
#   endif // ENCODER_ENABLE
}

/*------------------------*\
|*-----PROCESS RECORD-----*|
\*------------------------*/
/* Process record: custom keycodes to process here
 * Allow also the following codes to hook here as well;
 *  Macro definitions
 *  Audio hooks
 */
__attribute__ ((weak))
bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Return after running through all individual hooks
    return
        process_record_keymap(keycode, record)  &&
#       ifdef AUDIO_ENABLE
        process_record_audio(keycode, record)   &&
#       endif // AUDIO_ENABLE
#       ifdef ENCODER_ENABLE
        process_record_encoder(keycode, record) &&
#       endif // ENCODER_ENABLE
        process_record_macro(keycode, record);
}

/*---------------------*\
|*-----MATRIX SCAN-----*|
\*---------------------*/
/* This code runs every frame
 * I used to check for layer switching here, but layer state is better used.
 * Try to not put anything here; as it runs hundreds time per second-ish
 */
__attribute__ ((weak)) void matrix_scan_keymap(void) { }
void matrix_scan_user (void) {
    // Keymap specific scan function
    matrix_scan_keymap();
}

/*---------------------*\
|*-----LAYER STATE-----*|
\*---------------------*/
/* This code runs after every layer change
 * State represents the new layer state.
 */
__attribute__ ((weak))
layer_state_t layer_state_set_keymap (layer_state_t state) {
    return state;
}
layer_state_t layer_state_set_user(layer_state_t state) {
    // Keymap layer state setting
    state = layer_state_set_keymap(state);
    // For underglow stuff
#   ifdef RGBLIGHT_ENABLE
    state = layer_state_set_underglow(state);
#   endif // RGBLIGHT_ENABLE
    // Audio playback
#   ifdef AUDIO_ENABLE
    state = layer_state_set_audio(state);
#   endif // AUDIO_ENABLE

    return state;
}

/*-----------------------------*\
|*-----DEFAULT LAYER STATE-----*|
\*-----------------------------*/
/* This code runs after every time default base layer is changed
 */
__attribute__ ((weak))
layer_state_t default_layer_state_set_keymap (layer_state_t state) {
    return state;
}
layer_state_t default_layer_state_set_user(layer_state_t state) {
    // Keymap level code
    state = default_layer_state_set_keymap(state);
    return state;
}

/*------------------------*\
|*-----LED SET KEYMAP-----*|
\*------------------------*/
/* Code for LED indicators
 * I'm not sure when exactly does this code run
 */
__attribute__ ((weak)) void led_set_keymap(uint8_t usb_led) {}
void led_set_user(uint8_t usb_led) {
    led_set_keymap(usb_led);
}

/*-----------------*\
|*-----SUSPEND-----*|
\*-----------------*/
/* Suspend stuff here, mostly for the rgb lighting.
 */
__attribute__ ((weak)) void suspend_power_down_keymap (void) { }
void suspend_power_down_user(void) {
    suspend_power_down_keymap();
    // RGB matrix sleep hook
#   ifdef RGB_MATRIX_ENABLE
    suspend_power_down_rgb();
#   endif // RGB_MATRIX_ENABLE
}
__attribute__ ((weak)) void suspend_wakeup_init_keymap (void) { }
void suspend_wakeup_init_user(void) {
    suspend_wakeup_init_keymap();
    // RGB matrix sleep hook
#   ifdef RGB_MATRIX_ENABLE
    suspend_wakeup_init_rgb();
#   endif // RGB_MATRIX_ENABLE
}

<<<<<<< HEAD
    state = layer_state_set_keymap (state);
#ifdef RGBLIGHT_ENABLE
    // Change RGB lighting depending on the last layer activated
    rgblight_change( get_highest_layer(state) );
#endif
    return state;
||||||| f439fe6055
    state = layer_state_set_keymap (state);
#ifdef RGBLIGHT_ENABLE
    // Change RGB lighting depending on the last layer activated
    rgblight_change( biton32(state) );
#endif
    return state;
=======
/*------------------*\
|*-----SHUTDOWN-----*|
\*------------------*/
/* Shutdown stuff here; for when entering bootmode.
 */
__attribute__ ((weak)) void shutdown_keymap (void) { }
void shutdown_user(void) {
    // Underglow LED hook on boot
#   ifdef RGBLIGHT_ENABLE
    shutdown_underglow();
#   endif // RGBLIGHT_ENABLE
    // Perkey led hook on boot
#   ifdef RGB_MATRIX_ENABLE
    shutdown_rgb();
#   endif // RGB_MATRIX_ENABLE
    // Keymap hooks
    shutdown_keymap();
>>>>>>> upstream/master
}
