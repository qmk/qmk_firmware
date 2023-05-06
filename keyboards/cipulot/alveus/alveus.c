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

#include "alveus.h"
#include "ec_switch_matrix.h"
#include "eeprom.h"
#include "eeconfig.h"

_Static_assert(sizeof(apc_config) == EECONFIG_KB_DATA_SIZE, "Mismatch in keyboard EECONFIG stored data");

void keyboard_post_init_kb(void) {
    eeconfig_read_kb_datablock(&apc);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ecsm_config.low_threshold_matrix[row][col]  = apc.apc_actuation_level * 4;
            ecsm_config.high_threshold_matrix[row][col] = apc.apc_deactuation_level * 4;
        }
    }
    ecsm_update(&ecsm_config);
}

void eeconfig_init_kb(void) {
    // Default values
    apc.apc_enabled           = false;
    apc.apc_actuation_level   = 175;
    apc.apc_deactuation_level = 162;
    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&apc);
}

enum via_apc { id_apc_enable = 1, id_actuation_threshold = 2, id_deactuation_threshold = 3 };

void apc_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_apc_enable: {
            apc.apc_enabled = value_data[0];
            if (apc.apc_enabled) {
                printf(" <------------------- APC ENABLED -------------------> \n");
            } else {
                printf(" <------------------- APC DISABLED -------------------> \n");
                for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                        ecsm_config.low_threshold_matrix[row][col]  = apc.apc_actuation_level * 4;
                        ecsm_config.high_threshold_matrix[row][col] = apc.apc_deactuation_level * 4;
                    }
                }
                ecsm_update(&ecsm_config);
            }
            break;
        }
        case id_actuation_threshold: {
            apc.apc_actuation_level = value_data[0];
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    ecsm_config.low_threshold_matrix[row][col] = apc.apc_actuation_level * 4;
                }
            }
            ecsm_update(&ecsm_config);
            uprintf("APC ACTUATION LEVEL: %4d\n", apc.apc_actuation_level * 4);
            break;
        }
        case id_deactuation_threshold: {
            apc.apc_deactuation_level = value_data[0];
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    ecsm_config.high_threshold_matrix[row][col] = apc.apc_deactuation_level * 4;
                }
            }
            ecsm_update(&ecsm_config);
            uprintf("APC DEACTUATION LEVEL: %4d\n", apc.apc_deactuation_level * 4);
            break;
        }
    }
}

void apc_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_apc_enable: {
            value_data[0] = apc.apc_enabled;
            break;
        }
        case id_actuation_threshold: {
            value_data[0] = apc.apc_actuation_level;
            break;
        }
        case id_deactuation_threshold: {
            value_data[0] = apc.apc_deactuation_level;
            break;
        }
    }
}

void apc_config_save(void) {
    eeconfig_update_kb_datablock(&apc);
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
