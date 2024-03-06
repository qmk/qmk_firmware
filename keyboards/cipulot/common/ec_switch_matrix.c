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
#include "analog.h"
#include "atomic_util.h"
#include "math.h"
#include "print.h"
#include "wait.h"

#if defined(__AVR__)
#    error "AVR platforms not supported due to a variety of reasons. Among them there are limited memory, limited number of pins and ADC not being able to give satisfactory results."
#endif

#define OPEN_DRAIN_SUPPORT defined(PAL_MODE_OUTPUT_OPENDRAIN)

eeprom_ec_config_t eeprom_ec_config;
ec_config_t        ec_config;

// Pin and port array
const pin_t row_pins[]                                 = MATRIX_ROW_PINS;
const pin_t amux_sel_pins[]                            = AMUX_SEL_PINS;
const pin_t amux_en_pins[]                             = AMUX_EN_PINS;
const pin_t amux_n_col_sizes[]                         = AMUX_COL_CHANNELS_SIZES;
const pin_t amux_n_col_channels[][AMUX_MAX_COLS_COUNT] = {AMUX_COL_CHANNELS};

#define AMUX_SEL_PINS_COUNT ARRAY_SIZE(amux_sel_pins)
#define EXPECTED_AMUX_SEL_PINS_COUNT ceil(log2(AMUX_MAX_COLS_COUNT)
// Checks for the correctness of the configuration
_Static_assert(ARRAY_SIZE(amux_en_pins) == AMUX_COUNT, "AMUX_EN_PINS doesn't have the minimum number of bits required to enable all the multiplexers available");
// Check that number of select pins is enough to select all the channels
_Static_assert(AMUX_SEL_PINS_COUNT == EXPECTED_AMUX_SEL_PINS_COUNT), "AMUX_SEL_PINS doesn't have the minimum number of bits required address all the channels");
// Check that number of elements in AMUX_COL_CHANNELS_SIZES is enough to specify the number of channels for all the multiplexers available
_Static_assert(ARRAY_SIZE(amux_n_col_sizes) == AMUX_COUNT, "AMUX_COL_CHANNELS_SIZES doesn't have the minimum number of elements required to specify the number of channels for all the multiplexers available");

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
#ifdef OPEN_DRAIN_SUPPORT
    writePinLow(DISCHARGE_PIN);
#else
    writePinLow(DISCHARGE_PIN);
    setPinOutput(DISCHARGE_PIN);
#endif
}

// Charge the peak hold capacitor
void charge_capacitor(uint8_t row) {
#ifdef OPEN_DRAIN_SUPPORT
    writePinHigh(DISCHARGE_PIN);
#else
    setPinInput(DISCHARGE_PIN);
#endif
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
#ifdef OPEN_DRAIN_SUPPORT
    setPinOutputOpenDrain(DISCHARGE_PIN);
#else
    setPinOutput(DISCHARGE_PIN);
#endif

    // Initialize drive lines
    init_row();

    // Initialize AMUXs
    init_amux();

    return 0;
}

// Get the noise floor
void ec_noise_floor(void) {
    // Initialize the noise floor
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            ec_config.noise_floor[row][col] = 0;
        }
    }

    // Sample the noise floor
    for (uint8_t i = 0; i < DEFAULT_NOISE_FLOOR_SAMPLING_COUNT; i++) {
        for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
            disable_unused_amux(amux);
            for (uint8_t col = 0; col < amux_n_col_sizes[amux]; col++) {
                uint8_t sum = 0;
                for (uint8_t i = 0; i < (amux > 0 ? amux : 0); i++)
                    sum += amux_n_col_sizes[i];
                uint8_t adjusted_col = col + sum;
                for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                    ec_config.noise_floor[row][adjusted_col] += ec_readkey_raw(amux, row, col);
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

    for (uint8_t amux = 0; amux < AMUX_COUNT; amux++) {
        disable_unused_amux(amux);
        for (uint8_t col = 0; col < amux_n_col_sizes[amux]; col++) {
            for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
                uint8_t sum = 0;
                for (uint8_t i = 0; i < (amux > 0 ? amux : 0); i++)
                    sum += amux_n_col_sizes[i];
                uint8_t adjusted_col        = col + sum;
                sw_value[row][adjusted_col] = ec_readkey_raw(amux, row, col);

                if (ec_config.bottoming_calibration) {
                    if (ec_config.bottoming_calibration_starter[row][adjusted_col]) {
                        ec_config.bottoming_reading[row][adjusted_col]             = sw_value[row][adjusted_col];
                        ec_config.bottoming_calibration_starter[row][adjusted_col] = false;
                    } else if (sw_value[row][adjusted_col] > ec_config.bottoming_reading[row][adjusted_col]) {
                        ec_config.bottoming_reading[row][adjusted_col] = sw_value[row][adjusted_col];
                    }
                } else {
                    updated |= ec_update_key(&current_matrix[row], row, adjusted_col, sw_value[row][adjusted_col]);
                }
            }
        }
    }

    return ec_config.bottoming_calibration ? false : updated;
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

    // Real Time Noise Floor Calibration
    if (sw_value < (ec_config.noise_floor[row][col] - NOISE_FLOOR_THRESHOLD)) {
        uprintf("Noise Floor Change: %d, %d, %d\n", row, col, sw_value);
        ec_config.noise_floor[row][col]                             = sw_value;
        ec_config.rescaled_mode_0_actuation_threshold[row][col]     = rescale(ec_config.mode_0_actuation_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
        ec_config.rescaled_mode_0_release_threshold[row][col]       = rescale(ec_config.mode_0_release_threshold, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
        ec_config.rescaled_mode_1_initial_deadzone_offset[row][col] = rescale(ec_config.mode_1_initial_deadzone_offset, 0, 1023, ec_config.noise_floor[row][col], eeprom_ec_config.bottoming_reading[row][col]);
    }

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
    // Rapid Trigger
    else if (ec_config.actuation_mode == 1) {
        // Is key in active zone?
        if (sw_value > ec_config.rescaled_mode_1_initial_deadzone_offset[row][col]) {
            // Is key pressed while in active zone?
            if (current_state) {
                // Is the key still moving down?
                if (sw_value > ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                }
                // Has key moved up enough to be released?
                else if (sw_value < ec_config.extremum[row][col] - ec_config.mode_1_release_offset) {
                    ec_config.extremum[row][col] = sw_value;
                    *current_row &= ~(1 << col);
                    uprintf("Key released: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
            // Key is not pressed while in active zone
            else {
                // Is the key still moving up?
                if (sw_value < ec_config.extremum[row][col]) {
                    ec_config.extremum[row][col] = sw_value;
                }
                // Has key moved down enough to be pressed?
                else if (sw_value > ec_config.extremum[row][col] + ec_config.mode_1_actuation_offset) {
                    ec_config.extremum[row][col] = sw_value;
                    *current_row |= (1 << col);
                    uprintf("Key pressed: %d, %d, %d\n", row, col, sw_value);
                    return true;
                }
            }
        }
        // Key is not in active zone
        else {
            // Check to avoid key being stuck in pressed state near the active zone threshold
            if (sw_value < ec_config.extremum[row][col]) {
                ec_config.extremum[row][col] = sw_value;
                *current_row &= ~(1 << col);
                return true;
            }
        }
    }
    return false;
}

// Print the matrix values
void ec_print_matrix(void) {
    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS - 1; col++) {
            uprintf("%4d,", sw_value[row][col]);
        }
        uprintf("%4d\n", sw_value[row][MATRIX_COLS - 1]);
    }
    print("\n");
}

// Rescale the value to a different range
uint16_t rescale(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max) {
    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
