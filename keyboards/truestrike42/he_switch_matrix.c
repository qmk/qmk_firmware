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

#include "he_switch_matrix.h"
#include "analog.h"
#include "print.h"
#include "wait.h"

#if defined(__AVR__)
#    error "AVR platforms not supported due to a variety of reasons. Among them there are limited memory, limited number of pins and ADC not being able to give satisfactory results."
#endif

eeprom_he_config_t eeprom_he_config;
he_config_t        he_config;

// Pin and port array
const pin_t row_pins[]                               = MATRIX_ROW_PINS;
const pin_t amux_sel_pins[]                          = AMUX_SEL_PINS;
const pin_t amux_n_col_channels[AMUX_MAX_COLS_COUNT] = AMUX_COL_CHANNELS;
const uint8_t rows_per_col[]                         = ROWS_PER_COL;

#define AMUX_SEL_PINS_COUNT ARRAY_SIZE(amux_sel_pins)

static uint16_t sw_value[MATRIX_ROWS][MATRIX_COLS];
static adc_mux adcMux[MATRIX_ROWS];

void init_row(void) {
    // Set all row pins to analog input
    for (uint8_t idx = 0; idx < MATRIX_ROWS; ++idx) {
        palSetLineMode(row_pins[idx], PAL_MODE_INPUT_ANALOG);
        adcMux[idx] = pinToMux(row_pins[idx]);
    }
}

void init_amux(void) {
    // Set all AMUX SEL pins to GPIO output
    for (uint8_t idx = 0; idx < AMUX_SEL_PINS_COUNT; ++idx) {
        gpio_set_pin_output(amux_sel_pins[idx]);
    }
}

void select_amux(uint8_t col) {
    uint8_t ch = amux_n_col_channels[col];
    // Select the multiplexer channel
    for (uint8_t idx = 0; idx < AMUX_SEL_PINS_COUNT; ++idx) {
        gpio_write_pin(amux_sel_pins[idx], ch & (1 << idx));
    }
}

int he_init(void) {
    init_row();

    init_amux();

    return 0;
}

// Get the noise ceiling
void he_noise_ceiling(void) {
    // Initialize the noise ceiling
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            he_config.noise_ceiling[row][col] = 0;
        }
    }

    // Sample the noise ceiling
    for (uint8_t i = 0; i < DEFAULT_NOISE_CEILING_SAMPLING_COUNT; i++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            select_amux(col);
            for (uint8_t row = 0; row < rows_per_col[col]; row++) {
                he_config.noise_ceiling[row][col] += he_readkey_raw(row);
            }
        }
        wait_ms(5);
    }

    // Average the noise ceiling
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            he_config.noise_ceiling[row][col] /= DEFAULT_NOISE_CEILING_SAMPLING_COUNT;
        }
    }
}

// Scan key values and update matrix state
bool he_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_amux(col);
        for (uint8_t row = 0; row < rows_per_col[col]; row++) {
            sw_value[row][col] = he_readkey_raw(row);
            if (he_config.bottoming_calibration) {
                if (he_config.bottoming_calibration_starter[row][col]) {
                    he_config.bottoming_reading[row][col] = sw_value[row][col];
                    he_config.bottoming_calibration_starter[row][col] = false;
                } else if (sw_value[row][col] < he_config.bottoming_reading[row][col]) {
                    he_config.bottoming_reading[row][col] = sw_value[row][col];
                }
            } else {
                updated |= he_update_key(&current_matrix[row], row, col, sw_value[row][col]);
            }
        }
    }

    return he_config.bottoming_calibration ? false : updated;
}

// Read the Hall effect sensor value
uint16_t he_readkey_raw(uint8_t row) {
    uint16_t sw_value = 0;

    // Read the ADC value
    sw_value = adc_read(adcMux[row]);

    return sw_value;
}

// Update press/release state of key
bool he_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // Real Time Noise Floor Calibration
    if ((he_config.noise_ceiling[row][col] + NOISE_CEILING_THRESHOLD) < sw_value) {
        uprintf("Noise Floor Change: %d, %d, %d\n", row, col, sw_value);
        he_config.noise_ceiling[row][col]                           = sw_value;
        he_config.rescaled_mode_0_actuation_threshold[row][col]     = rescale(he_config.mode_0_actuation_threshold, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
        he_config.rescaled_mode_0_release_threshold[row][col]       = rescale(he_config.mode_0_release_threshold, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
        he_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(he_config.mode_1_initial_deadzone_offset, 0, 1023, he_config.noise_ceiling[row][col], eeprom_he_config.bottoming_reading[row][col]);
    }

    // Normal board-wide APC
    if (he_config.actuation_mode == 0) {
        if (current_state && he_config.rescaled_mode_0_release_threshold[row][col] < sw_value) {
            *current_row &= ~(1 << col);
            uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
        if ((!current_state) && sw_value < he_config.rescaled_mode_0_actuation_threshold[row][col]) {
            *current_row |= (1 << col);
            uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
    }

    // Rapid Trigger
    else if (he_config.actuation_mode == 1) {
        // Is key in active zone?
        if (sw_value < he_config.rescaled_mode_1_initial_deadzone_offset[row][col]) {
            // Is key pressed while in active zone?
            if (current_state) {
                // Is the key still moving down?
                if (sw_value < he_config.extremum[row][col]) {
                    he_config.extremum[row][col] = sw_value;
                    //uprintf("Key going down: %d, %d, %d\n", row, col, sw_value);
                }
                // Has key moved up enough to be released?
                else if (he_config.extremum[row][col] + he_config.mode_1_release_offset < sw_value) {
                    he_config.extremum[row][col] = sw_value;
                    *current_row &= ~(1 << col);
                    uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
            // Key is not pressed while in active zone
            else {
                // Is the key still moving up?
                if (he_config.extremum[row][col] < sw_value) {
                    he_config.extremum[row][col] = sw_value;
                }
                // Has key moved down enough to be pressed?
                else if (sw_value < he_config.extremum[row][col] - he_config.mode_1_actuation_offset) {
                    he_config.extremum[row][col] = sw_value;
                    *current_row |= (1 << col);
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
        }
        // Key is not in active zone
        else {
            // Check to avoid key being stuck in pressed state near the active zone threshold
            if (he_config.extremum[row][col] < sw_value) {
                he_config.extremum[row][col] = sw_value;
                *current_row &= ~(1 << col);
                return true;
            }
        }
    }
    return false;
}

// Print the matrix values
void he_print_matrix(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            if (row < rows_per_col[col])
            {
                uprintf("%4d,", sw_value[row][col]);
            }
        }
        uprintf("%4d\n", sw_value[row][MATRIX_COLS - 1]);
    }
    print("\n");
}

// Rescale the value to a different range
uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
