/* Copyright 2023 Cipulot, 2024 byungyoonc
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

// Copyright 2023 Dasky (@daskygit)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "quantum.h"
#include "graphics/display.h"
#include "he_switch_matrix.h"
#include "keyboard.h"
#include "rgb_matrix.h"
#include "he_switch_matrix.h"

void eeconfig_init_kb(void) {
    // Default values
    eeprom_he_config.actuation_mode                 = DEFAULT_ACTUATION_MODE;
    eeprom_he_config.mode_0_actuation_threshold     = DEFAULT_MODE_0_ACTUATION_LEVEL;
    eeprom_he_config.mode_0_release_threshold       = DEFAULT_MODE_0_RELEASE_LEVEL;
    eeprom_he_config.mode_1_initial_deadzone_offset = DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET;
    eeprom_he_config.mode_1_actuation_offset        = DEFAULT_MODE_1_ACTUATION_OFFSET;
    eeprom_he_config.mode_1_release_offset          = DEFAULT_MODE_1_RELEASE_OFFSET;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            eeprom_he_config.bottoming_reading[row][col] = DEFAULT_BOTTOMING_READING;
        }
    }
    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&eeprom_he_config, 0, EECONFIG_KB_DATA_SIZE);

    eeconfig_init_user();
}

// On Keyboard startup
void keyboard_post_init_kb(void) {
    display_init_kb();
    keyboard_post_init_user();

    // Read custom menu variables from memory
    eeconfig_read_kb_datablock(&eeprom_he_config, 0, EECONFIG_KB_DATA_SIZE);

    // Set runtime values to EEPROM values
    he_config.actuation_mode                 = eeprom_he_config.actuation_mode;
    he_config.mode_0_actuation_threshold     = eeprom_he_config.mode_0_actuation_threshold;
    he_config.mode_0_release_threshold       = eeprom_he_config.mode_0_release_threshold;
    he_config.mode_1_initial_deadzone_offset = eeprom_he_config.mode_1_initial_deadzone_offset;
    he_config.mode_1_actuation_offset        = eeprom_he_config.mode_1_actuation_offset;
    he_config.mode_1_release_offset          = eeprom_he_config.mode_1_release_offset;
    he_config.bottoming_calibration          = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            he_config.bottoming_calibration_starter[row][col]           = true;
            he_config.bottoming_reading[row][col]                       = eeprom_he_config.bottoming_reading[row][col];
            he_config.rescaled_mode_0_actuation_threshold[row][col]     = rescale(he_config.mode_0_actuation_threshold, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
            he_config.rescaled_mode_0_release_threshold[row][col]       = rescale(he_config.mode_0_release_threshold, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
            he_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(he_config.mode_1_initial_deadzone_offset, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
        }
    }

    rgb_matrix_set_flags(LED_FLAG_ALL);

    keyboard_post_init_user();
}

bool process_record_kb(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        display_key_counter();
    }
    return process_record_user(keycode, record);
}
