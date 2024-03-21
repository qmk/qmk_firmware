/* Copyright 2023 Cipulot
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
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

#include "keyboards/cipulot/common/eeprom_tools.h"
#include "ec_switch_matrix.h"
#include "action.h"
#include "print.h"
#include "via.h"

#ifdef VIA_ENABLE

void ec_rescale_values(uint8_t item);
void ec_save_threshold_data(uint8_t option);
void ec_save_bottoming_reading(void);
void ec_show_calibration_data(void);
void ec_clear_bottoming_calibration_data(void);

// Declaring enums for VIA config menu
enum via_enums {
    // clang-format off
    id_num_indicator_enabled    = 1,
    id_num_indicator_brightness = 2,
    id_num_indicator_color      = 3,
    id_caps_indicator_enabled    = 4,
    id_caps_indicator_brightness = 5,
    id_caps_indicator_color      = 6,
    id_scroll_indicator_enabled    = 7,
    id_scroll_indicator_brightness = 8,
    id_scroll_indicator_color      = 9,
    id_actuation_mode = 10,
    id_mode_0_actuation_threshold = 11,
    id_mode_0_release_threshold = 12,
    id_save_threshold_data = 13,
    id_mode_1_initial_deadzone_offset = 14,
    id_mode_1_actuation_offset = 15,
    id_mode_1_release_offset = 16,
    id_bottoming_calibration = 17,
    id_noise_floor_calibration = 18,
    id_show_calibration_data = 19,
    id_clear_bottoming_calibration_data = 20
    // clang-format on
};

// Handle the data received by the keyboard from the VIA menus
void via_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_num_indicator_enabled: {
            if (value_data[0] == 1) {
                eeprom_ec_config.num.enabled = true;
                uprintf("#########################\n");
                uprintf("# Num indicator enabled #\n");
                uprintf("#########################\n");
            } else {
                eeprom_ec_config.num.enabled = false;
                uprintf("##########################\n");
                uprintf("# Num indicator disabled #\n");
                uprintf("##########################\n");
            }
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, num.enabled);
            break;
        }
        case id_num_indicator_brightness: {
            eeprom_ec_config.num.v = value_data[0];
            uprintf("Num indicator brightness: %d\n", eeprom_ec_config.num.v);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, num.v);
            break;
        }
        case id_num_indicator_color: {
            eeprom_ec_config.num.h = value_data[0];
            eeprom_ec_config.num.s = value_data[1];
            uprintf("Num indicator color: %d, %d\n", eeprom_ec_config.num.h, eeprom_ec_config.num.s);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, num.h);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, num.s);
            break;
        }
        case id_caps_indicator_enabled: {
            if (value_data[0] == 1) {
                eeprom_ec_config.caps.enabled = true;
                uprintf("##########################\n");
                uprintf("# Caps indicator enabled #\n");
                uprintf("##########################\n");
            } else {
                eeprom_ec_config.caps.enabled = false;
                uprintf("###########################\n");
                uprintf("# Caps indicator disabled #\n");
                uprintf("###########################\n");
            }
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, caps.enabled);
            break;
        }
        case id_caps_indicator_brightness: {
            eeprom_ec_config.caps.v = value_data[0];
            uprintf("Caps indicator brightness: %d\n", eeprom_ec_config.caps.v);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, caps.v);
            break;
        }
        case id_caps_indicator_color: {
            eeprom_ec_config.caps.h = value_data[0];
            eeprom_ec_config.caps.s = value_data[1];
            uprintf("Caps indicator color: %d, %d\n", eeprom_ec_config.caps.h, eeprom_ec_config.caps.s);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, caps.h);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, caps.s);
            break;
        }
        case id_scroll_indicator_enabled: {
            if (value_data[0] == 1) {
                eeprom_ec_config.scroll.enabled = true;
                uprintf("############################\n");
                uprintf("# Scroll indicator enabled #\n");
                uprintf("############################\n");
            } else {
                eeprom_ec_config.scroll.enabled = false;
                uprintf("#############################\n");
                uprintf("# Scroll indicator disabled #\n");
                uprintf("#############################\n");
            }
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, scroll.enabled);
            break;
        }
        case id_scroll_indicator_brightness: {
            eeprom_ec_config.scroll.v = value_data[0];
            uprintf("Scroll indicator brightness: %d\n", eeprom_ec_config.scroll.v);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, scroll.v);
            break;
        }
        case id_scroll_indicator_color: {
            eeprom_ec_config.scroll.h = value_data[0];
            eeprom_ec_config.scroll.s = value_data[1];
            uprintf("Scroll indicator color: %d, %d\n", eeprom_ec_config.scroll.h, eeprom_ec_config.scroll.s);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, scroll.h);
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, scroll.s);
            break;
        }
        case id_actuation_mode: {
            eeprom_ec_config.actuation_mode = value_data[0];
            ec_config.actuation_mode        = eeprom_ec_config.actuation_mode;
            if (ec_config.actuation_mode == 0) {
                uprintf("#########################\n");
                uprintf("#  Actuation Mode: APC  #\n");
                uprintf("#########################\n");
            } else if (ec_config.actuation_mode == 1) {
                uprintf("#################################\n");
                uprintf("# Actuation Mode: Rapid Trigger #\n");
                uprintf("#################################\n");
            }
            EEPROM_KB_PARTIAL_UPDATE(eeprom_ec_config, actuation_mode);
            break;
        }
        case id_mode_0_actuation_threshold: {
            ec_config.mode_0_actuation_threshold = value_data[1] | (value_data[0] << 8);
            uprintf("APC Mode Actuation Threshold: %d\n", ec_config.mode_0_actuation_threshold);
            break;
        }
        case id_mode_0_release_threshold: {
            eeprom_ec_config.mode_0_release_threshold = value_data[1] | (value_data[0] << 8);
            ec_config.mode_0_release_threshold        = eeprom_ec_config.mode_0_release_threshold;
            uprintf("APC Mode Release Threshold: %d\n", ec_config.mode_0_release_threshold);
            break;
        }
        case id_mode_1_initial_deadzone_offset: {
            ec_config.mode_1_initial_deadzone_offset = value_data[1] | (value_data[0] << 8);
            uprintf("Rapid Trigger Mode Initial Deadzone Offset: %d\n", ec_config.mode_1_initial_deadzone_offset);
            break;
        }
        case id_mode_1_actuation_offset: {
            ec_config.mode_1_actuation_offset = value_data[0];
            uprintf("Rapid Trigger Mode Actuation Sensitivity: %d\n", ec_config.mode_1_actuation_offset);
            break;
        }
        case id_mode_1_release_offset: {
            ec_config.mode_1_release_offset = value_data[0];
            uprintf("Rapid Trigger Mode Release Sensitivity: %d\n", ec_config.mode_1_release_offset);
            break;
        }
        case id_bottoming_calibration: {
            if (value_data[0] == 1) {
                ec_config.bottoming_calibration = true;
                uprintf("##############################\n");
                uprintf("# Bottoming calibration mode #\n");
                uprintf("##############################\n");
            } else {
                ec_config.bottoming_calibration = false;
                ec_save_bottoming_reading();
                uprintf("## Bottoming calibration done ##\n");
                ec_show_calibration_data();
            }
            break;
        }
        case id_save_threshold_data: {
            ec_save_threshold_data(value_data[0]);
            break;
        }
        case id_noise_floor_calibration: {
            if (value_data[0] == 0) {
                ec_noise_floor();
                ec_rescale_values(0);
                ec_rescale_values(1);
                ec_rescale_values(2);
                uprintf("#############################\n");
                uprintf("# Noise floor data acquired #\n");
                uprintf("#############################\n");
                break;
            }
        }
        case id_show_calibration_data: {
            // Show calibration data once if the user toggle the switch
            if (value_data[0] == 0) {
                ec_show_calibration_data();
                break;
            }
        }
        case id_clear_bottoming_calibration_data: {
            if (value_data[0] == 0) {
                ec_clear_bottoming_calibration_data();
            }
        }
        default: {
            // Unhandled value.
            break;
        }
    }

    // Call the indicator callback to set the indicator color
    indicators_callback();
}

// Handle the data sent by the keyboard to the VIA menus
void via_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_num_indicator_enabled: {
            value_data[0] = eeprom_ec_config.num.enabled;
            break;
        }
        case id_num_indicator_brightness: {
            value_data[0] = eeprom_ec_config.num.v;
            break;
        }
        case id_num_indicator_color: {
            value_data[0] = eeprom_ec_config.num.h;
            value_data[1] = eeprom_ec_config.num.s;
            break;
        }
        case id_caps_indicator_enabled: {
            value_data[0] = eeprom_ec_config.caps.enabled;
            break;
        }
        case id_caps_indicator_brightness: {
            value_data[0] = eeprom_ec_config.caps.v;
            break;
        }
        case id_caps_indicator_color: {
            value_data[0] = eeprom_ec_config.caps.h;
            value_data[1] = eeprom_ec_config.caps.s;
            break;
        }
        case id_scroll_indicator_enabled: {
            value_data[0] = eeprom_ec_config.scroll.enabled;
            break;
        }
        case id_scroll_indicator_brightness: {
            value_data[0] = eeprom_ec_config.scroll.v;
            break;
        }
        case id_scroll_indicator_color: {
            value_data[0] = eeprom_ec_config.scroll.h;
            value_data[1] = eeprom_ec_config.scroll.s;
            break;
        }
        case id_actuation_mode: {
            value_data[0] = eeprom_ec_config.actuation_mode;
            break;
        }
        case id_mode_0_actuation_threshold: {
            value_data[0] = eeprom_ec_config.mode_0_actuation_threshold >> 8;
            value_data[1] = eeprom_ec_config.mode_0_actuation_threshold & 0xFF;
            break;
        }
        case id_mode_0_release_threshold: {
            value_data[0] = eeprom_ec_config.mode_0_release_threshold >> 8;
            value_data[1] = eeprom_ec_config.mode_0_release_threshold & 0xFF;
            break;
        }
        case id_mode_1_initial_deadzone_offset: {
            value_data[0] = eeprom_ec_config.mode_1_initial_deadzone_offset >> 8;
            value_data[1] = eeprom_ec_config.mode_1_initial_deadzone_offset & 0xFF;
            break;
        }
        case id_mode_1_actuation_offset: {
            value_data[0] = eeprom_ec_config.mode_1_actuation_offset;
            break;
        }
        case id_mode_1_release_offset: {
            value_data[0] = eeprom_ec_config.mode_1_release_offset;
            break;
        }
        default: {
            // Unhandled value.
            break;
        }
    }
}

// Handle the commands sent and received by the keyboard with VIA
void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    // data = [ command_id, channel_id, value_id, value_data ]
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                via_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                via_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                // Bypass the save function in favor of pinpointed saves
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

// Rescale the values received by VIA to fit the new range
void ec_rescale_values(uint8_t item) {
    switch (item) {
        // Rescale the APC mode actuation thresholds
        case 0:
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    ec_config.rescaled_mode_0_actuation_threshold[row][col] = rescale(ec_config.mode_0_actuation_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
                }
            }
            break;
        // Rescale the APC mode release thresholds
        case 1:
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    ec_config.rescaled_mode_0_release_threshold[row][col] = rescale(ec_config.mode_0_release_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
                }
            }
            break;
        // Rescale the Rapid Trigger mode initial deadzone offsets
        case 2:
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                for (uint8_t col = 0; col < MATRIX_COLS; col++) {
                    ec_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(ec_config.mode_1_initial_deadzone_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
                }
            }
            break;

        default:
            // Unhandled item.
            break;
    }
}

void ec_save_threshold_data(uint8_t option) {
    // Save APC mode thresholds and rescale them for runtime usage
    if (option == 0) {
        eeprom_ec_config.mode_0_actuation_threshold = ec_config.mode_0_actuation_threshold;
        eeprom_ec_config.mode_0_release_threshold   = ec_config.mode_0_release_threshold;
        ec_rescale_values(0);
        ec_rescale_values(1);
    }
    // Save Rapid Trigger mode thresholds and rescale them for runtime usage
    else if (option == 1) {
        eeprom_ec_config.mode_1_initial_deadzone_offset = ec_config.mode_1_initial_deadzone_offset;
        ec_rescale_values(2);
    }
    eeconfig_update_kb_datablock(&eeprom_ec_config);
    uprintf("####################################\n");
    uprintf("# New thresholds applied and saved #\n");
    uprintf("####################################\n");
}

// Save the bottoming reading
void ec_save_bottoming_reading(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            // If the bottom reading doesn't go over the noise floor by 100, it is likely that:
            // 1. The key is not actually in the matrix
            // 2. The key is on an alternative layout, therefore not being pressed
            // 3. The key in in the current layout but not being pressed
            if (ec_config.bottoming_reading[row][col] < (ec_config.noise_floor[row][col] + 100)) {
                eeprom_ec_config.bottoming_reading[row][col] = 1023;
            } else {
                eeprom_ec_config.bottoming_reading[row][col] = ec_config.bottoming_reading[row][col];
            }
        }
    }
    // Rescale the values to fit the new range for runtime usage
    ec_rescale_values(0);
    ec_rescale_values(1);
    ec_rescale_values(2);
    eeconfig_update_kb_datablock(&eeprom_ec_config);
}

// Show the calibration data
void ec_show_calibration_data(void) {
    uprintf("\n###############\n");
    uprintf("# Noise Floor #\n");
    uprintf("###############\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", ec_config.noise_floor[row][col]);
        }
        uprintf("%4d\n", ec_config.noise_floor[row][MATRIX_COLS - 1]);
    }

    uprintf("\n######################\n");
    uprintf("# Bottoming Readings #\n");
    uprintf("######################\n");
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", eeprom_ec_config.bottoming_reading[row][col]);
        }
        uprintf("%4d\n", eeprom_ec_config.bottoming_reading[row][MATRIX_COLS - 1]);
    }

    uprintf("\n######################################\n");
    uprintf("# Rescaled APC Mode Actuation Points #\n");
    uprintf("######################################\n");
    uprintf("Original APC Mode Actuation Point: %4d\n", ec_config.mode_0_actuation_threshold);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", ec_config.rescaled_mode_0_actuation_threshold[row][col]);
        }
        uprintf("%4d\n", ec_config.rescaled_mode_0_actuation_threshold[row][MATRIX_COLS - 1]);
    }

    uprintf("\n######################################\n");
    uprintf("# Rescaled APC Mode Release Points   #\n");
    uprintf("######################################\n");
    uprintf("Original APC Mode Release Point: %4d\n", ec_config.mode_0_release_threshold);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", ec_config.rescaled_mode_0_release_threshold[row][col]);
        }
        uprintf("%4d\n", ec_config.rescaled_mode_0_release_threshold[row][MATRIX_COLS - 1]);
    }

    uprintf("\n#######################################################\n");
    uprintf("# Rescaled Rapid Trigger Mode Initial Deadzone Offset #\n");
    uprintf("#######################################################\n");
    uprintf("Original Rapid Trigger Mode Initial Deadzone Offset: %4d\n", ec_config.mode_1_initial_deadzone_offset);
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", ec_config.rescaled_mode_1_initial_deadzone_offset[row][col]);
        }
        uprintf("%4d\n", ec_config.rescaled_mode_1_initial_deadzone_offset[row][MATRIX_COLS - 1]);
    }
    print("\n");
}

// Clear the calibration data
void ec_clear_bottoming_calibration_data(void) {
    // Clear the EEPROM data
    eeconfig_init_kb();

    // Reset the runtime values to the EEPROM values
    keyboard_post_init_kb();

    uprintf("######################################\n");
    uprintf("# Bottoming calibration data cleared #\n");
    uprintf("######################################\n");
}

#endif // VIA_ENABLE
