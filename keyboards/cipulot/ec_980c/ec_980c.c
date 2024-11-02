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

#include "ec_switch_matrix.h"
#include "quantum.h"

void eeconfig_init_kb(void) {
    // Default values
    eeprom_ec_config.num.h                          = 0;
    eeprom_ec_config.num.s                          = 0;
    eeprom_ec_config.num.v                          = 60;
    eeprom_ec_config.num.enabled                    = true;
    eeprom_ec_config.caps.h                         = 0;
    eeprom_ec_config.caps.s                         = 0;
    eeprom_ec_config.caps.v                         = 60;
    eeprom_ec_config.caps.enabled                   = true;
    eeprom_ec_config.scroll.h                       = 0;
    eeprom_ec_config.scroll.s                       = 0;
    eeprom_ec_config.scroll.v                       = 60;
    eeprom_ec_config.scroll.enabled                 = true;
    eeprom_ec_config.actuation_mode                 = DEFAULT_ACTUATION_MODE;
    eeprom_ec_config.mode_0_actuation_threshold     = DEFAULT_MODE_0_ACTUATION_LEVEL;
    eeprom_ec_config.mode_0_release_threshold       = DEFAULT_MODE_0_RELEASE_LEVEL;
    eeprom_ec_config.mode_1_initial_deadzone_offset = DEFAULT_MODE_1_INITIAL_DEADZONE_OFFSET;
    eeprom_ec_config.mode_1_actuation_offset        = DEFAULT_MODE_1_ACTUATION_OFFSET;
    eeprom_ec_config.mode_1_release_offset          = DEFAULT_MODE_1_RELEASE_OFFSET;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            eeprom_ec_config.bottoming_reading[row][col] = DEFAULT_BOTTOMING_READING;
        }
    }
    // Write default value to EEPROM now
    eeconfig_update_kb_datablock(&eeprom_ec_config, 0, EECONFIG_KB_DATA_SIZE);

    eeconfig_init_user();
}

// On Keyboard startup
void keyboard_post_init_kb(void) {
    // Read custom menu variables from memory
    eeconfig_read_kb_datablock(&eeprom_ec_config, 0, EECONFIG_KB_DATA_SIZE);

    // Set runtime values to EEPROM values
    ec_config.actuation_mode                 = eeprom_ec_config.actuation_mode;
    ec_config.mode_0_actuation_threshold     = eeprom_ec_config.mode_0_actuation_threshold;
    ec_config.mode_0_release_threshold       = eeprom_ec_config.mode_0_release_threshold;
    ec_config.mode_1_initial_deadzone_offset = eeprom_ec_config.mode_1_initial_deadzone_offset;
    ec_config.mode_1_actuation_offset        = eeprom_ec_config.mode_1_actuation_offset;
    ec_config.mode_1_release_offset          = eeprom_ec_config.mode_1_release_offset;
    ec_config.bottoming_calibration          = false;
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ec_config.bottoming_calibration_starter[row][col]           = true;
            ec_config.bottoming_reading[row][col]                       = eeprom_ec_config.bottoming_reading[row][col];
            ec_config.rescaled_mode_0_actuation_threshold[row][col]     = rescale(ec_config.mode_0_actuation_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_0_release_threshold[row][col]       = rescale(ec_config.mode_0_release_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(ec_config.mode_1_initial_deadzone_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_1_actuation_offset[row][col]        = rescale(ec_config.mode_1_actuation_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
            ec_config.rescaled_mode_1_release_offset[row][col]          = rescale(ec_config.mode_1_release_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
        }
    }

    // Call the indicator callback to set the indicator color
    rgb_matrix_indicators_kb();

    keyboard_post_init_user();
}

// INDICATOR CALLBACK ------------------------------------------------------------------------------
/* LED index to physical position
 *
 * LED0 | LED1 |  LED2
 * -----+------+--------
 * Num  | Caps | Scroll |
 */
bool rgb_matrix_indicators_kb(void) {
    if (!rgb_matrix_indicators_user()) {
        return false;
    }

    if (eeprom_ec_config.num.enabled) {
        // The rgb_matrix_set_color function needs an RGB code to work, so first the indicator color is cast to an HSV value and then translated to RGB
        hsv_t hsv_num_indicator_color = {eeprom_ec_config.num.h, eeprom_ec_config.num.s, eeprom_ec_config.num.v};
        rgb_t rgb_num_indicator_color = hsv_to_rgb(hsv_num_indicator_color);
        if (host_keyboard_led_state().num_lock)
            rgb_matrix_set_color(NUM_INDICATOR_INDEX, rgb_num_indicator_color.r, rgb_num_indicator_color.g, rgb_num_indicator_color.b);
        else
            rgb_matrix_set_color(NUM_INDICATOR_INDEX, 0, 0, 0);
    }
    if (eeprom_ec_config.caps.enabled) {
        hsv_t hsv_caps_indicator_color = {eeprom_ec_config.caps.h, eeprom_ec_config.caps.s, eeprom_ec_config.caps.v};
        rgb_t rgb_caps_indicator_color = hsv_to_rgb(hsv_caps_indicator_color);
        if (host_keyboard_led_state().caps_lock)
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, rgb_caps_indicator_color.r, rgb_caps_indicator_color.g, rgb_caps_indicator_color.b);
        else
            rgb_matrix_set_color(CAPS_INDICATOR_INDEX, 0, 0, 0);
    }
    if (eeprom_ec_config.scroll.enabled) {
        hsv_t hsv_scroll_indicator_color = {eeprom_ec_config.scroll.h, eeprom_ec_config.scroll.s, eeprom_ec_config.scroll.v};
        rgb_t rgb_scroll_indicator_color = hsv_to_rgb(hsv_scroll_indicator_color);
        if (host_keyboard_led_state().scroll_lock)
            rgb_matrix_set_color(SCROLL_INDICATOR_INDEX, rgb_scroll_indicator_color.r, rgb_scroll_indicator_color.g, rgb_scroll_indicator_color.b);
        else
            rgb_matrix_set_color(SCROLL_INDICATOR_INDEX, 0, 0, 0);
    }

    return true;
}
