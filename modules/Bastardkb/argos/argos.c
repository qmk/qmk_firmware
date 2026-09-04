
// Copyright 2026 Quentin LEBASTARD <bstkbd@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#include QMK_KEYBOARD_H

#include "argos.h"
#include "argos_combo.h"
#include "argos_tapdance.h"
#include "argos_rgb.h"

#include "eeconfig.h"
#include "eeprom.h"
#include "keymap_introspection.h"
#include "nvm_eeprom_eeconfig_internal.h"
#include "nvm_eeprom_via_internal.h"
#include "print.h"
#include "quantum.h"
#include "raw_hid.h"
#include "transactions.h"
#include "version.h"
#include "via.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

#if BK_HAS_POINTING_DEVICE
#include "bk_pointing_device.h"
#endif

ASSERT_COMMUNITY_MODULES_MIN_API_VERSION(1, 0, 0);

// Magic position for keycode execution
#define ARGOS_MATRIX_MAGIC 240

// Whether we are capturing keycodes (testing keymap)
bool capturing_all_keycodes = false;

// Magic keycode override
uint16_t g_argos_magic_keycode_override = 0;

argos_config_t argos_config;

// Internal EEPROM access functions - uses eeconfig_kb_datablock
// TODO does this mess with the dilemma screen configuration? It should not
__attribute__((weak)) void argos_read_eeprom(uint16_t offset, void *buf,
                                             uint16_t size) {
    void *ee_start =
        (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + offset);
    void *ee_end =
        (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR +
                            MIN(ARGOS_EEPROM_SIZE_CALC, offset + size));
    eeprom_read_block(buf, ee_start, ee_end - ee_start);
}

__attribute__((weak)) void argos_write_eeprom(uint16_t offset, const void *buf,
                                              uint16_t size) {
    void *ee_start =
        (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR + offset);
    void *ee_end =
        (void *)(uintptr_t)(DYNAMIC_KEYMAP_EEPROM_MAX_ADDR +
                            MIN(ARGOS_EEPROM_SIZE_CALC, offset + size));
    eeprom_update_block(buf, ee_start, ee_end - ee_start);
}

/*
    To make migrating from QMK as easy as possible, on first load we copy
    over the combos. QMK does not store combos in eeprom, so we have to load them using
    combo_get_raw and then manually copy each one into eeprom through our custom
    data structure
*/
void keyboard_post_init_argos(void) {
    // Read configuration from eeprom
    argos_read_eeprom(ARGOS_OFFSET_CONFIG, &argos_config, sizeof(argos_config));
    if (!argos_config.has_copied_qmk_config) {
        // this is our first load ever
        argos_combos_copy_from_QMK();
        argos_config.has_copied_qmk_config = true;
        argos_config.themeId = 16; // default to dark theme
        argos_config.has_displayed_welcome_message = false;
        argos_config.global_tapping_term = TAPPING_TERM;
        argos_config.global_combo_term = COMBO_TERM;
        argos_write_eeprom(ARGOS_OFFSET_CONFIG, &argos_config,
                           sizeof(argos_config));  
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        argos_rgb_init();
#endif
    }
    argos_combos_load_from_eeprom();
    argos_tap_dances_load_from_eeprom();
    argos_reload_tap_dances();
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
    argos_rgb_load_from_eeprom();
    // for rgb sync, needed for propagating changes
    transaction_register_rpc(RPC_ID_RGB_SYNC, rgb_sync_handler);
#endif
}

bool argos_handle_command(uint8_t *data, uint8_t length) {
    uint8_t protocol = data[0];

    
    if (protocol != ARGOS_CMD_PREFIX)
        return false; // not an Argos command

    uint8_t *command_id = &(data[1]);
    uint8_t *command_data = &(data[2]);

    // whether we should send a response back after handling the command
    // for example, when listening for a combo key, we want to wait until the
    // key is pressed to send the data
    bool send_data = false;

    switch (*command_id) {
    case argos_id_get_kb_info: {
        command_data[0] = ARGOS_PROTOCOL_VERSION >> 8;
        command_data[1] = ARGOS_PROTOCOL_VERSION & 0xFF;
        command_data[2] = ARGOS_TAP_DANCE_ENTRIES;
        command_data[3] = ARGOS_COMBO_ENTRIES;
        command_data[4] = ARGOS_KEYS_PER_COMBO;
        command_data[5] = argos_config.themeId;
        command_data[6] = QMK_KEYCODES_VERSION_COMPATIBLE_0;
        command_data[7] = QMK_KEYCODES_VERSION_COMPATIBLE_1;
        command_data[8] = QMK_KEYCODES_VERSION_COMPATIBLE_2;
        command_data[9] = argos_config.has_displayed_welcome_message;
        command_data[10] = (argos_config.global_tapping_term >> 8) & 0xFF;
        command_data[11] = argos_config.global_tapping_term & 0xFF;
        command_data[12] = (argos_config.global_combo_term >> 8) & 0xFF;
        command_data[13] = argos_config.global_combo_term & 0xFF;
#ifdef POINTING_DEVICE_LEFT
        command_data[14] = 1; // pointing device on left
#else
        command_data[14] = 0; // pointing device on right
#endif
        send_data = true;
        break;
    }

    case argos_id_set_welcome_message_displayed: {
        argos_config.has_displayed_welcome_message = command_data[0];
        argos_write_eeprom(ARGOS_OFFSET_CONFIG, &argos_config,
                           sizeof(argos_config));
        send_data = true;
        break;
    }

    case argos_id_set_combo: {
        uint8_t combo_index = command_data[0];
        uint16_t keycode = command_data[1] << 8 | (command_data[2]);
        argos_combo_set_keycode(combo_index, keycode, 0);
        for (int i = 0; i < ARGOS_KEYS_PER_COMBO; i++) {
            uint16_t key =
                command_data[3 + i * 2] << 8 | (command_data[4 + i * 2]);
            argos_combo_set_keycode(combo_index, key, i+1); // first key is the result keycode
        }
        // reload combo from eeprom
        argos_combo_load_from_eeprom(combo_index);
        send_data = true; // ack
        break;
    }

    case argos_id_set_global_tapping_term: {
        argos_config.global_tapping_term = command_data[0] << 8| command_data[1];
        argos_write_eeprom(ARGOS_OFFSET_CONFIG, &argos_config,
                           sizeof(argos_config));
        send_data = true;
        break;
    }
    
    case argos_id_set_global_combo_term: {
        argos_config.global_combo_term = command_data[0] << 8| command_data[1];
        argos_write_eeprom(ARGOS_OFFSET_CONFIG, &argos_config,
                           sizeof(argos_config));
        send_data = true;
        break;
    }

    case argos_id_set_theme_id: {
        argos_config.themeId = command_data[0];
        argos_write_eeprom(ARGOS_OFFSET_CONFIG, &argos_config,
                           sizeof(argos_config));
        send_data = true;
        break;
    }

    case argos_id_get_tap_dance: {
        uint8_t index = command_data[0];
        argos_td_entry_t entry = {0};
        // TODO: is it really necessary to read from the eeprom here?
        // can't we just read from the tap dance array directly?
        argos_tap_dance_read_eeprom(index, &entry);
        command_data[1] = entry.on_tap & 0xFF;
        command_data[2] = (entry.on_tap >> 8) & 0xFF;
        command_data[3] = entry.on_hold & 0xFF;
        command_data[4] = (entry.on_hold >> 8) & 0xFF;
        command_data[5] = entry.on_double_tap & 0xFF;
        command_data[6] = (entry.on_double_tap >> 8) & 0xFF;
        command_data[7] = entry.on_tap_hold & 0xFF;
        command_data[8] = (entry.on_tap_hold >> 8) & 0xFF;
        command_data[9] = entry.custom_tapping_term & 0xFF;
        command_data[10] = (entry.custom_tapping_term >> 8) & 0xFF;
        send_data = true;
        break;
    }

    case argos_id_capture_all_keycodes: {
        // This command is used to capture all keycodes pressed.
        // It is meant to be used to test the keymap, in the "test keycodes"
        // tab.
        uint8_t new_state = command_data[0];
        if (new_state) {
            capturing_all_keycodes = true;
        } else {
            capturing_all_keycodes = false;
        }
        // we do not ACK, the ACK will be in process_records_argos_capture_all_keycodes
        break;
    }

    case argos_id_set_tap_dance: {
        uint8_t index = command_data[0];
        for (int i = 0; i < 4; i++) { // 4 keys per tap dance
            uint16_t keycode =
                (command_data[i * 2 + 1] << 8) | (command_data[i * 2 + 2]);
            argos_tap_dance_set_keycode(index, keycode, i);
        }
        send_data = true; // ack
        break;
    }

    case argos_id_get_combo: {
        uint8_t combo_index = command_data[0];
        if (combo_index >= ARGOS_COMBO_ENTRIES)
            break; // invalid index
        combo_t combo = argos_combo_get(combo_index);
        command_data[1] = !combo.disabled;
        command_data[2] = combo.keycode & 0xFF;
        command_data[3] = (combo.keycode >> 8) & 0xFF;
        // data 4 and 5 reserved for custom tapping term
        for (int i = 0; i < ARGOS_KEYS_PER_COMBO; i++) {
            uint16_t key = combo.keys[i];
            command_data[6 + i * 2] = key & 0xFF;
            command_data[7 + i * 2] = (key >> 8) & 0xFF;
        }
        send_data = true;
        break;
    }

    // legacy
    case argos_id_capture_combo_key: {
        break;
    }

    // set a specific key in a tap dance.
    // we don't return any data to specify if we succeeded or not, because the webapp will reload the tap dance directly.
    case argos_id_set_tap_dance_keycode: {
        const uint8_t layer  = command_data[0];
        const uint8_t row   = command_data[1];
        const uint8_t col   = command_data[2];
        const uint16_t keycode = (command_data[3] << 8) | command_data[4];
        const uint8_t tap_dance_action_index = command_data[5];

        // TODO: move all this to argos_tapdance.c
        // read the key at the position, is it already a tap dance?
        const uint16_t current_keycode = dynamic_keymap_get_keycode(layer, row, col);
        // range for tap dances is 0x5700 to 0x57FF
        bool is_tap_dance = current_keycode >= QK_TAP_DANCE && current_keycode < QK_TAP_DANCE + ARGOS_TAP_DANCE_ENTRIES;
        uint8_t td_index = 0;
        uint16_t new_keycode_td = 0;
        if (is_tap_dance) {
            // find the tap dance number: based on the keycode number.
            td_index = current_keycode - QK_TAP_DANCE;
            // reassign the appropriate keycode directly
            argos_tap_dance_set_keycode(td_index, keycode, tap_dance_action_index);
            new_keycode_td = current_keycode; // no need to change the keycode, it's already a tap dance
        }
        else{
            // if it's not a tap dance yet....
            // first we need to find an available tap dance entry. We have up to 256 available.
            argos_td_entry_t *entry;
            for(uint8_t i = 0; i < ARGOS_TAP_DANCE_ENTRIES; i++){
                // argos_tap_dance_read_eeprom(i, &entry);
                entry = argos_tap_dance_get(i);

                if(entry->on_tap == 0 && entry->on_hold == 0 && entry->on_double_tap == 0 && entry->on_tap_hold == 0){
                    // this tap dance is empty, we can use it
                    td_index = i;
                    // assign tap dance keycode to the position on the keymap
                    break;
                }
            }

            // modify the key in the keymap to be a tap dance with the right index
            new_keycode_td = QK_TAP_DANCE + td_index;
            dynamic_keymap_set_keycode(layer, row, col, new_keycode_td);

            // now we're sure that we have a tap dance and that it's assigned properly. time to modify it        
            // if we are assigning a single tap, we can directly modify it
            if(tap_dance_action_index == 0){
                argos_tap_dance_set_keycode(td_index, keycode, tap_dance_action_index);
            }
            // if we are assigning something else than single tap, then store the previous keycode as the single tap action
            else{
                // assign keycode and save in eeprom
                argos_tap_dance_set_keycode(td_index, current_keycode, 0);
                argos_tap_dance_set_keycode(td_index, keycode, tap_dance_action_index);
            }
        }

        // now, we need to test for a specific case: we might have had a deletion.
        argos_td_entry_t* updated_entry = argos_tap_dance_get(td_index);
        if(keycode == 0){
            // that's fine, we set everything up already for the tap dance.
            // however, if we deleted everything except the singe tap then we need to turn it back to a normal keycode.
            if(updated_entry->on_hold == 0 && updated_entry->on_double_tap == 0 && updated_entry->on_tap_hold == 0){
                dynamic_keymap_set_keycode(layer, row, col, updated_entry->on_tap);
                // return the keycode to the webapp
                new_keycode_td = updated_entry->on_tap;
                // clear the tap dance single tap entry as it's no longer used
                argos_tap_dance_set_keycode(td_index, 0, 0);
            }
        }

        // return the tap dance index that was modified/created, so the webapp can keep track of it
        // otherwise, the webapp might not know the number of the new tap dance created.
        command_data[0] = td_index; 
        command_data[1] = (new_keycode_td >> 8) & 0xFF;
        command_data[2] = new_keycode_td & 0xFF;
        command_data[3] = (updated_entry->on_tap >> 8) & 0xFF;
        command_data[4] = updated_entry->on_tap & 0xFF;
        command_data[5] = (updated_entry->on_hold >> 8) & 0xFF;
        command_data[6] = updated_entry->on_hold & 0xFF;
        command_data[7] = (updated_entry->on_double_tap >> 8) & 0xFF;
        command_data[8] = updated_entry->on_double_tap & 0xFF;
        command_data[9] = (updated_entry->on_tap_hold >> 8) & 0xFF;
        command_data[10] = updated_entry->on_tap_hold & 0xFF;
        send_data = true; 
        break;
    }

    // legacy
    case argos_id_delete_combo_key: {
        break;
    }

    case argos_id_get_rgb_matrix_led_at_position: {
        send_data = true;
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        uint8_t layer = command_data[0];
        uint8_t index = command_data[1];
        uint8_t offset = command_data[2];
        argos_rgb_t entry = {0};
        argos_rgb_get_led_at_position(&entry, layer, index, offset);
        command_data[0] = entry.r;
        command_data[1] = entry.g;
        command_data[2] = entry.b;
        command_data[3] = entry.passthrough;
        command_data[4] = entry.on;
        command_data[5] = entry.custom;
        break;
#endif
    }

    case argos_id_set_rgb_matrix_led_at_position: {
        send_data = true;
#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
        uint8_t led_layer = command_data[0];
        uint8_t led_row = command_data[1]; // legacy
        uint8_t led_col = command_data[2]; // legacy
        uint8_t r = command_data[3]; 
        uint8_t g = command_data[4];
        uint8_t b = command_data[5];
        bool passthrough = command_data[6];
        bool on = command_data[7];
        bool custom = command_data[8];
        uint8_t offset = command_data[9];
        uint8_t index = command_data[10];
        argos_rgb_set_led_at_position(led_layer, led_row, led_col, r, g, b, passthrough, on, custom, offset, index);
        break;
#endif
    }

#ifdef BK_HAS_POINTING_DEVICE
    case argos_id_set_sniping_dpi:
    case argos_id_set_dpi:
    case argos_id_set_auto_mouse_layer_enabled:
    case argos_id_set_auto_precision_on_mouse_layer_enabled:
    case argos_id_set_axis_invert:
    case argos_id_get_pointing_device_info: {
        send_data = bkpd_dispatch_command(*command_id, &command_data);
        break;
    }

#endif // BK_HAS_POINTING_DEVICE

    default:
        return false;
    }

    if (send_data) {
        raw_hid_send(data, length);
    }

    return true;
}

// Override via_command_kb to intercept Via protocol commands
bool via_command_kb(uint8_t *data, uint8_t length) {
    // try to handle it with argos
    bool result = argos_handle_command(data, length);
    if (result) {
        return true;
    } else {
        return false;
    }
    return false;
}

bool process_record_argos(uint16_t keycode, keyrecord_t *record) {
    // are we capturing all keycodes? (testing keymap)
    bool captured = process_records_argos_capture_all_keycodes(keycode, record);
    if (captured) {
        return false; // we captured a keycode, no need to process further
    }
    return true;
}

/*
    The webapp has a function where we can capture keycodes.
    We don't want to set "capture keycodes" forever, otherwise switching away from the app
    Will keep capturing keycodes. Instead, the webapp sends a capture command first and we then setup
    a back and forth exchange between webapp and keyboard, until the webapp disconnects.
*/
bool process_records_argos_capture_all_keycodes(uint16_t keycode, keyrecord_t *record) {
    // are we capturing all keycodes? (testing keymap)
    if (capturing_all_keycodes) {
        // send the keycode to the webapp
        uint8_t data[32] = {0};
        data[0] = ARGOS_CMD_PREFIX;
        data[1] = argos_id_capture_all_keycodes;
        if (record->event.pressed) {
            data[2] = 1;
        } else { // released
            data[2] = 0;
        }
        data[3] = keycode & 0xFF;
        data[4] = (keycode >> 8) & 0xFF;
        raw_hid_send(data, sizeof(data));
        capturing_all_keycodes = false; // Stop capturing keycodes
        return true; // we captured a keycode, no need to process further
    }
    return false;
}

// Override keymap_key_to_keycode to handle magic position for tap dance/combo
// execution
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key) {
    if (key.row == ARGOS_MATRIX_MAGIC && key.col == ARGOS_MATRIX_MAGIC) {
        return g_argos_magic_keycode_override;
    } else if (key.row < MATRIX_ROWS && key.col < MATRIX_COLS) {
        return keycode_at_keymap_location(layer, key.row, key.col);
    }
#ifdef ENCODER_MAP_ENABLE
    else if (key.row == KEYLOC_ENCODER_CW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, true);
    } else if (key.row == KEYLOC_ENCODER_CCW && key.col < NUM_ENCODERS) {
        return keycode_at_encodermap_location(layer, key.col, false);
    }
#endif // ENCODER_MAP_ENABLE
#ifdef DIP_SWITCH_MAP_ENABLE
    else if (key.row == KEYLOC_DIP_SWITCH_ON && key.col < NUM_DIP_SWITCHES) {
        return keycode_at_dip_switch_map_location(key.col, true);
    } else if (key.row == KEYLOC_DIP_SWITCH_OFF && key.col < NUM_DIP_SWITCHES) {
        return keycode_at_dip_switch_map_location(key.col, false);
    }
#endif // DIP_SWITCH_MAP_ENABLE

    // Use dynamic keymap for normal keys
    return KC_NO;
}

// Keycode execution helpers
// We need it for tap dance
void argos_keycode_down(uint16_t keycode) {
    g_argos_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        register_code16(keycode);
    } else {
        action_exec((keyevent_t){.type = KEY_EVENT,
                                 .key = (keypos_t){.row = ARGOS_MATRIX_MAGIC,
                                                   .col = ARGOS_MATRIX_MAGIC},
                                 .pressed = 1,
                                 .time = (timer_read() | 1)});
    }
}

// Keycode execution helpers
// We need it for tap dance
void argos_keycode_up(uint16_t keycode) {
    g_argos_magic_keycode_override = keycode;

    if (keycode <= QK_MODS_MAX) {
        unregister_code16(keycode);
    } else {
        action_exec((keyevent_t){.type = KEY_EVENT,
                                 .key = (keypos_t){.row = ARGOS_MATRIX_MAGIC,
                                                   .col = ARGOS_MATRIX_MAGIC},
                                 .pressed = 0,
                                 .time = (timer_read() | 1)});
    }
}

void argos_keycode_tap(uint16_t keycode) {
    argos_keycode_down(keycode);
    wait_ms(ARGOS_TAP_CODE_DELAY);
    argos_keycode_up(keycode);
}

// override tapping term
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    return argos_config.global_tapping_term;
}

// override combo term
uint16_t get_combo_term(uint16_t combo_index, combo_t *combo) {
    return argos_config.global_combo_term;
}