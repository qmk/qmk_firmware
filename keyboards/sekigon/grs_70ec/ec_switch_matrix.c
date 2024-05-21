/* Copyright 2020 sekigon-gonnoc
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
#include <avr/interrupt.h>
#include "analog.h"
#include "print.h"

// pin connections
const uint8_t row_pins[]     = MATRIX_ROW_PINS;
const uint8_t col_channels[] = MATRIX_COL_CHANNELS;
const uint8_t mux_sel_pins[] = MUX_SEL_PINS;

_Static_assert(sizeof(mux_sel_pins) == 3, "invalid MUX_SEL_PINS");

static ecsm_config_t config;
static uint16_t      ecsm_sw_value[MATRIX_ROWS][MATRIX_COLS];

static inline void discharge_capacitor(void) { gpio_set_pin_output(DISCHARGE_PIN); }
static inline void charge_capacitor(uint8_t row) {
    gpio_set_pin_input(DISCHARGE_PIN);
    gpio_write_pin_high(row_pins[row]);
}

static inline void clear_all_row_pins(void) {
    for (int row = 0; row < sizeof(row_pins); row++) {
        gpio_write_pin_low(row_pins[row]);
    }
}

static inline void init_mux_sel(void) {
    for (int idx = 0; idx < sizeof(mux_sel_pins); idx++) {
        gpio_set_pin_output(mux_sel_pins[idx]);
    }
}

static inline void select_mux(uint8_t col) {
    uint8_t ch = col_channels[col];
    gpio_write_pin(mux_sel_pins[0], ch & 1);
    gpio_write_pin(mux_sel_pins[1], ch & 2);
    gpio_write_pin(mux_sel_pins[2], ch & 4);
}

static inline void init_row(void) {
    for (int idx = 0; idx < sizeof(row_pins); idx++) {
        gpio_set_pin_output(row_pins[idx]);
        gpio_write_pin_low(row_pins[idx]);
    }
}

// Initialize pins
int ecsm_init(ecsm_config_t const* const ecsm_config) {
    // save config
    config = *ecsm_config;

    // initialize discharge pin as discharge mode
    gpio_write_pin_low(DISCHARGE_PIN);
    gpio_set_pin_output(DISCHARGE_PIN);

    // set analog reference
    analogReference(ADC_REF_POWER);

    // initialize drive lines
    init_row();

    // initialize multiplexer select pin
    init_mux_sel();

    // set discharge pin to charge mode
    gpio_set_pin_input(DISCHARGE_PIN);

    return 0;
}

// Read key value of key (row, col)
uint16_t ecsm_readkey_raw(uint8_t row, uint8_t col) {
    uint16_t sw_value = 0;

    discharge_capacitor();

    select_mux(col);

    clear_all_row_pins();

    cli();

    charge_capacitor(row);

    sw_value = analogReadPin(ANALOG_PORT);

    sei();

    return sw_value;
}

// Update press/release state of key at (row, col)
bool ecsm_update_key(matrix_row_t* current_row, uint8_t col, uint16_t sw_value) {
    bool current_state = (*current_row >> col) & 1;

    // press to release
    if (current_state && sw_value < config.low_threshold) {
        *current_row &= ~(1 << col);
        return true;
    }

    // release to press
    if ((!current_state) && sw_value > config.high_threshold) {
        *current_row |= (1 << col);
        return true;
    }

    return false;
}

// Scan key values and update matrix state
bool ecsm_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    for (int col = 0; col < sizeof(col_channels); col++) {
        for (int row = 0; row < sizeof(row_pins); row++) {
            ecsm_sw_value[row][col] = ecsm_readkey_raw(row, col);
            updated |= ecsm_update_key(&current_matrix[row], col, ecsm_sw_value[row][col]);
        }
    }

    return updated;
}

// Print key values
void ecsm_print_matrix(void) {
    for (int row = 0; row < sizeof(row_pins); row++) {
        for (int col = 0; col < sizeof(col_channels); col++) {
            xprintf("%4d", ecsm_sw_value[row][col]);
        }
        xprintf("\n");
    }
}
