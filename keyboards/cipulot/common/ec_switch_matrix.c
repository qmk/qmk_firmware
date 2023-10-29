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
#include "analog.h"
#include "atomic_util.h"
#include "math.h"
#include "print.h"
#include "wait.h"

eeprom_ec_config_t eeprom_ec_config;
ec_config_t        ec_config;

// Pin and port array
const uint32_t row_pins[]                                 = MATRIX_ROW_PINS;
const uint32_t amux_sel_pins[]                            = AMUX_SEL_PINS;
const uint32_t amux_en_pins[]                             = AMUX_EN_PINS;
const uint8_t  amux_n_col_sizes[]                         = AMUX_COL_CHANNELS_SIZES;
const uint8_t  amux_n_col_channels[][AMUX_MAX_COLS_COUNT] = {AMUX_COL_CHANNELS};
#define AMUX_SEL_PINS_COUNT (sizeof(amux_sel_pins) / sizeof(amux_sel_pins[0]))
#define EXPECTED_AMUX_SEL_PINS_COUNT ceil(log2(AMUX_MAX_COLS_COUNT)
// Checks for the correctness of the configuration
_Static_assert((sizeof(amux_en_pins) / sizeof(amux_en_pins[0])) == AMUX_COUNT, "AMUX_EN_PINS doesn't have the minimum number of bits required to enable all the multiplexers available");
// Check that number of select pins is enough to select all the channels
_Static_assert(AMUX_SEL_PINS_COUNT == EXPECTED_AMUX_SEL_PINS_COUNT), "AMUX_SEL_PINS doesn't have the minimum number of bits required address all the channels");
// Check that number of elements in AMUX_COL_CHANNELS_SIZES is enough to specify the number of channels for all the multiplexers available
_Static_assert((sizeof(amux_n_col_sizes) / sizeof(amux_n_col_sizes[0])) == AMUX_COUNT, "AMUX_COL_CHANNELS_SIZES doesn't have the minimum number of elements required to specify the number of channels for all the multiplexers available");

// static ec_config_t config;
static uint16_t sw_value[MATRIX_ROWS][MATRIX_COLS];

static adc_mux adcMux;

// Initialize the row pins
void init_row(void) {
    // Set all row pins as output and low
    for (uint8_t idx = 0; idx < MATRIX_ROWS; idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }
}

// Initialize the multiplexers
void init_amux(void) {
    for (uint8_t idx = 0; idx < AMUX_COUNT; idx++) {
        setPinOutput(amux_en_pins[idx]);
        writePinLow(amux_en_pins[idx]);
    }
    for (uint8_t idx = 0; idx < AMUX_SEL_PINS_COUNT; idx++) {
        setPinOutput(amux_sel_pins[idx]);
    }
}

// Select the multiplexer channel of the specified multiplexer
void select_amux_channel(uint8_t channel, uint8_t col) {
    // Get the channel for the specified multiplexer
    uint8_t ch = amux_n_col_channels[channel][col];
    // momentarily disable specified multiplexer
    writePinHigh(amux_en_pins[channel]);
    // Select the multiplexer channel
    for (uint8_t i = 0; i < AMUX_SEL_PINS_COUNT; i++) {
        writePin(amux_sel_pins[i], ch & (1 << i));
    }
    // re enable specified multiplexer
    writePinLow(amux_en_pins[channel]);
}

// Disable all the unused multiplexers
void disable_unused_amux(uint8_t channel) {
    // disable all the other multiplexers apart from the current selected one
    for (uint8_t idx = 0; idx < AMUX_COUNT; idx++) {
        if (idx != channel) {
            writePinHigh(amux_en_pins[idx]);
        }
    }
}
// Discharge the peak hold capacitor
void discharge_capacitor(void) {
    writePinLow(DISCHARGE_PIN);
}

// Charge the peak hold capacitor
void charge_capacitor(uint8_t row) {
    writePinHigh(DISCHARGE_PIN);
    writePinHigh(row_pins[row]);
}

// Initialize the peripherals pins
int ec_init(void) {
    // Initialize ADC
    palSetLineMode(ANALOG_PORT, PAL_MODE_INPUT_ANALOG);
    adcMux = pinToMux(ANALOG_PORT);

    // Dummy call to make sure that adcStart() has been called in the appropriate state
    adc_read(adcMux);

    // Initialize discharge pin as discharge mode
    writePinLow(DISCHARGE_PIN);
    setPinOutputOpenDrain(DISCHARGE_PIN);

    // Initialize drive lines
    init_row();

    // Initialize AMUXs
    init_amux();

    return 0;
}

// Get the noise floor
void ec_noise_floor(void) {
    // Initialize the noise floor to 0
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ec_config.noise_floor[row][col] = 0;
        }
    }

    // Get the noise floor
    for (uint8_t i = 0; i < DEFAULT_NOISE_FLOOR_SAMPLING_COUNT; i++) {
        for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
            disable_unused_amux(amux);
            for (int col = 0; col < amux_n_col_sizes[amux]; col++) {
                for (int row = 0; row < MATRIX_ROWS; row++) {
                    if (amux == 0) {
                        ec_config.noise_floor[row][col] += ec_readkey_raw(0, row, col);
                    } else {
                        ec_config.noise_floor[row][col + amux_n_col_sizes[amux - 1]] += ec_readkey_raw(amux, row, col);
                    }
                }
            }
        }
        wait_ms(5);
    }

    // Average the noise floor
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ec_config.noise_floor[row][col] /= DEFAULT_NOISE_FLOOR_SAMPLING_COUNT;
        }
    }
}

// Scan key values and update matrix state
bool ec_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    // Bottoming calibration mode: update bottoming out values and avoid keycode state change
    // IF statement is higher in the function to avoid the overhead of the execution of normal operation mode
    if (ec_config.bottoming_calibration) {
        for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
            disable_unused_amux(amux);
            for (int col = 0; col < amux_n_col_sizes[amux]; col++) {
                for (int row = 0; row < MATRIX_ROWS; row++) {
                    if (amux == 0) {
                        sw_value[row][col] = ec_readkey_raw(0, row, col);
                        if (ec_config.bottoming_calibration_starter[row][col]) {
                            ec_config.bottoming_reading[row][col]             = sw_value[row][col];
                            ec_config.bottoming_calibration_starter[row][col] = false;
                        } else if (sw_value[row][col] > ec_config.bottoming_reading[row][col]) {
                            ec_config.bottoming_reading[row][col] = sw_value[row][col];
                        }
                    } else {
                        sw_value[row][col] = ec_readkey_raw(amux, row, col);
                        if (ec_config.bottoming_calibration_starter[row][col + amux_n_col_sizes[amux - 1]]) {
                            ec_config.bottoming_reading[row][col + amux_n_col_sizes[amux - 1]]             = sw_value[row][col];
                            ec_config.bottoming_calibration_starter[row][col + amux_n_col_sizes[amux - 1]] = false;
                        } else if (sw_value[row][col] > ec_config.bottoming_reading[row][col + amux_n_col_sizes[amux - 1]]) {
                            ec_config.bottoming_reading[row][col + amux_n_col_sizes[amux - 1]] = sw_value[row][col];
                        }
                    }
                }
            }
        }
        // Return false to avoid keycode state change
        return false;
    }

    // Normal operation mode: update key state
    for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
        disable_unused_amux(amux);
        for (int col = 0; col < amux_n_col_sizes[amux]; col++) {
            for (int row = 0; row < MATRIX_ROWS; row++) {
                if (amux == 0) {
                    sw_value[row][col] = ec_readkey_raw(0, row, col);
                    updated |= ec_update_key(&current_matrix[row], row, col, sw_value[row][col]);
                } else {
                    sw_value[row][col + amux_n_col_sizes[amux - 1]] = ec_readkey_raw(amux, row, col);
                    updated |= ec_update_key(&current_matrix[row], row, col + amux_n_col_sizes[amux - 1], sw_value[row][col + amux_n_col_sizes[amux - 1]]);
                }
            }
        }
    }
    return updated;
}

// Read the capacitive sensor value
uint16_t ec_readkey_raw(uint8_t channel, uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    // Select the multiplexer
    select_amux_channel(channel, col);

    // Set the row pin to low state to avoid ghosting
    writePinLow(row_pins[row]);

    ATOMIC_BLOCK_FORCEON {
        // Set the row pin to high state and have capacitor charge
        charge_capacitor(row);
        // Read the ADC value
        sw_value = adc_read(adcMux);
    }
    // Discharge peak hold capacitor
    discharge_capacitor();
    // Waiting for the ghost capacitor to discharge fully
    wait_us(DISCHARGE_TIME);

    return sw_value;
}

// Update press/release state of key
bool ec_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // Normal board-wide APC
    if (ec_config.actuation_mode == 0) {
        if (current_state && sw_value < ec_config.rescaled_mode_0_release_threshold[row][col]) {
            *current_row &= ~(1 << col);
            uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
        if ((!current_state) && sw_value > ec_config.rescaled_mode_0_actuation_threshold[row][col]) {
            *current_row |= (1 << col);
            uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
            return true;
        }
    }
    // Rapid trigger starting from the initial deadzone
    else if (ec_config.actuation_mode == 1) {
        if (sw_value > ec_config.rescaled_mode_1_initial_deadzone_offset[row][col]) {
            // In DA zone?
            if (current_state) {
                // Key is pressed
                // Is key still moving down?
                if (sw_value > ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                } else if (sw_value < ec_config.extremum[row][col] - DEFAULT_MODE_1_RELEASE_SENSITIVITY) {
                    // Has key moved up enough to be released?
                    ec_config.extremum[row][col] = sw_value;
                    *current_row &= ~(1 << col);
                    uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            } else {
                // Key is not pressed
                // Is the key still moving up?
                if (sw_value < ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                } else if (sw_value > ec_config.extremum[row][col] + DEFAULT_MODE_1_ACTUATION_SENSITIVITY) {
                    // Has key moved down enough to be pressed?
                    ec_config.extremum[row][col] = sw_value;
                    *current_row |= (1 << col);
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
        } else {
            // Out of DA zone
            if (sw_value < ec_config.extremum[row][col]) {
                ec_config.extremum[row][col] = sw_value;
                *current_row &= ~(1 << col);
            }
        }
    }
    return false;
}

// Debug print key values
void ec_print_matrix(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d", sw_value[row][col]);
            if (col < (MATRIX_COLS - 1)) {
                print(",");
            }
        }
        print("\n");
    }
    print("\n");
}

// Rescale the value to a different range
uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
