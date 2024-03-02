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
#include "print.h"
#include "wait.h"

/* Pin and port array */
const uint32_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t  col_channels[] = MATRIX_COL_CHANNELS;
const uint32_t mux_sel_pins[] = MUX_SEL_PINS;

static ecsm_config_t config;
static uint16_t      ecsm_sw_value[MATRIX_ROWS][MATRIX_COLS];

static adc_mux adcMux;

static inline void discharge_capacitor(void) {
    writePinLow(DISCHARGE_PIN);
}
static inline void charge_capacitor(uint8_t row) {
    writePinHigh(DISCHARGE_PIN);
    writePinHigh(row_pins[row]);
}

static inline void init_mux_sel(void) {
    for (int idx = 0; idx < 3; idx++) {
        setPinOutput(mux_sel_pins[idx]);
    }
}

static inline void select_mux(uint8_t col) {
    uint8_t ch = col_channels[col];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
}

static inline void init_row(void) {
    for (int idx = 0; idx < MATRIX_ROWS; idx++) {
        setPinOutput(row_pins[idx]);
        writePinLow(row_pins[idx]);
    }
}

/* Initialize the peripherals pins */
int ecsm_init(ecsm_config_t const* const ecsm_config) {
    // Initialize config
    config = *ecsm_config;

    palSetLineMode(ANALOG_PORT, PAL_MODE_INPUT_ANALOG);
    adcMux = pinToMux(ANALOG_PORT);

    //Dummy call to make sure that adcStart() has been called in the appropriate state
    adc_read(adcMux);

    // Initialize discharge pin as discharge mode
    writePinLow(DISCHARGE_PIN);
    setPinOutputOpenDrain(DISCHARGE_PIN);

    // Initialize drive lines
    init_row();

    // Initialize multiplexer select pin
    init_mux_sel();

    // Enable AMUX
    setPinOutput(APLEX_EN_PIN_0);
    writePinLow(APLEX_EN_PIN_0);
    setPinOutput(APLEX_EN_PIN_1);
    writePinLow(APLEX_EN_PIN_1);

    return 0;
}

int ecsm_update(ecsm_config_t const* const ecsm_config) {
    // Save config
    config = *ecsm_config;
    return 0;
}

// Read the capacitive sensor value
uint16_t ecsm_readkey_raw(uint8_t channel, uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    // Select the multiplexer
    if (channel == 0) {
        writePinHigh(APLEX_EN_PIN_0);
        select_mux(col);
        writePinLow(APLEX_EN_PIN_0);
    } else {
        writePinHigh(APLEX_EN_PIN_1);
        select_mux(col);
        writePinLow(APLEX_EN_PIN_1);
    }

    // Set strobe pins to low state
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
bool ecsm_update_key(matrix_row_t* current_row, uint8_t row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // Press to release
    if (current_state && sw_value < config.ecsm_actuation_threshold) {
        *current_row &= ~(1 << col);
        return true;
    }

    // Release to press
    if ((!current_state) && sw_value > config.ecsm_release_threshold) {
        *current_row |= (1 << col);
        return true;
    }

    return false;
}

// Scan key values and update matrix state
bool ecsm_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    // Disable AMUX of channel 1
    writePinHigh(APLEX_EN_PIN_1);
    for (int col = 0; col < sizeof(col_channels); col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_value[row][col] = ecsm_readkey_raw(0, row, col);
            updated |= ecsm_update_key(&current_matrix[row], row, col, ecsm_sw_value[row][col]);
        }
    }

    // Disable AMUX of channel 1
    writePinHigh(APLEX_EN_PIN_0);
    for (int col = 0; col < (sizeof(col_channels) - 1); col++) {
        for (int row = 0; row < MATRIX_ROWS; row++) {
            ecsm_sw_value[row][col + 8] = ecsm_readkey_raw(1, row, col);
            updated |= ecsm_update_key(&current_matrix[row], row, col + 8, ecsm_sw_value[row][col + 8]);
        }
    }
    return updated;
}

// Debug print key values
void ecsm_print_matrix(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            uprintf("%4d", ecsm_sw_value[row][col]);
            if (col < (MATRIX_COLS - 1)) {
                print(",");
            }
        }
        print("\n");
    }
    print("\n");
}
