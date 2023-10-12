/* Copyright 2023 Cipulot
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

#include "ec_switch_matrix.h"
#include "action.h"
#include "via.h"

void apc_init_thresholds(void);
void apc_set_threshold(bool is_for_actuation);

// Declaring an _apc_config_t struct that will store our data
typedef struct _apc_config_t {
    uint16_t actuation_threshold;
    uint16_t release_threshold;
} apc_config;

// Check if the size of the reserved persistent memory is the same as the size of struct apc_config
_Static_assert(sizeof(apc_config) == EECONFIG_USER_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

// Declaring a new variable apc of type apc_config
apc_config apc;

// Declaring enums for VIA config menu
enum via_apc_enums {
    // clang-format off
    id_apc_actuation_threshold = 1,
    id_apc_release_threshold = 2
    // clang-format on
};

// Initializing persistent memory configuration: default values are declared and stored in PMEM
void eeconfig_init_user(void) {
    // Default values
    apc.actuation_threshold = DEFAULT_ACTUATION_LEVEL;
    apc.release_threshold   = DEFAULT_RELEASE_LEVEL;
    // Write default value to EEPROM now
    eeconfig_update_user_datablock(&apc);
}

// On Keyboard startup
void keyboard_post_init_user(void) {
    // Read custom menu variables from memory
    eeconfig_read_user_datablock(&apc);
    apc_init_thresholds();
}

// Handle the data received by the keyboard from the VIA menus
void apc_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_apc_actuation_threshold: {
            apc.actuation_threshold = value_data[1] | (value_data[0] << 8);
            apc_set_threshold(true);
            break;
        }
        case id_apc_release_threshold: {
            apc.release_threshold = value_data[1] | (value_data[0] << 8);
            apc_set_threshold(false);
            break;
        }
    }
}

// Handle the data sent by the keyboard to the VIA menus
void apc_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_apc_actuation_threshold: {
            value_data[0] = apc.actuation_threshold >> 8;
            value_data[1] = apc.actuation_threshold & 0xFF;
            break;
        }
        case id_apc_release_threshold: {
            value_data[0] = apc.release_threshold >> 8;
            value_data[1] = apc.release_threshold & 0xFF;
            break;
        }
    }
}

// Save the data to persistent memory after changes are made
void apc_config_save(void) {
    eeconfig_update_user_datablock(&apc);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                apc_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                apc_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                apc_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }

    *command_id = id_unhandled;
}

// Initialize the thresholds
void apc_init_thresholds(void) {
    ecsm_config.ecsm_actuation_threshold = apc.actuation_threshold;
    ecsm_config.ecsm_release_threshold   = apc.release_threshold;

    // Update the ecsm_config
    ecsm_update(&ecsm_config);
}

// Set the thresholds
void apc_set_threshold(bool is_for_actuation) {
    if (is_for_actuation) {
        ecsm_config.ecsm_actuation_threshold = apc.actuation_threshold;

    } else {
        ecsm_config.ecsm_release_threshold = apc.release_threshold;
    }
    // Update the ecsm_config
    ecsm_update(&ecsm_config);
}
