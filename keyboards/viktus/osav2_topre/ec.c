/* Copyright 2023 Viktus Design LLC
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

#include "quantum.h"
#include "ec.h"
#include "analog.h"
//#include "debug.h"  // needed for debugging

// sensing channel definitions
#define A0 0
#define A1 1
#define A2 2
#define A3 3
#define A4 4
#define A5 5
#define A6 6
#define A7 7

// analog connection settings
#define DISCHARGE_PIN D3
#define ANALOG_PORT D4

#ifndef MUX_SEL_PIN
#   define MUX_SEL_PINS \
        { D0, D1, D2 }
#endif

// pin connections
const uint8_t row_channels[] = MATRIX_ROW_PINS;
const uint8_t col_pins[]     = MATRIX_COL_PINS;
const uint8_t mux_sel_pins[] = MUX_SEL_PINS;

_Static_assert(sizeof(mux_sel_pins) == 3, "invalid MUX_SEL_PINS");

static ec_config_t config;
static uint16_t    ec_sw_value[MATRIX_COLS][MATRIX_ROWS];

static inline void discharge_capacitor(void) { setPinOutput(DISCHARGE_PIN); }
static inline void charge_capacitor(uint8_t col) {
    setPinInput(DISCHARGE_PIN);
    writePinHigh(col_pins[col]);
}

static inline void clear_all_col_pins(void) {
    for (int col = 0; col < sizeof(col_pins); col++) {
        writePinLow(col_pins[col]);
    }
}

void init_mux_sel(void) {
    for (int idx = 0; idx < sizeof(mux_sel_pins); idx++) {
        setPinOutput(mux_sel_pins[idx]);
    }
}

void select_mux(uint8_t row) {
    uint8_t ch = row_channels[row];
    writePin(mux_sel_pins[0], ch & 1);
    writePin(mux_sel_pins[1], ch & 2);
    writePin(mux_sel_pins[2], ch & 4);
}

void init_col(void) {
    for (int idx = 0; idx < sizeof(col_pins); idx++) {
        setPinOutput(col_pins[idx]);
        writePinLow(col_pins[idx]);
    }
}

void ec_init(ec_config_t const* const ec_config) {
    // save config
    config = *ec_config;

    // initialize discharge pin as discharge mode
    writePinLow(DISCHARGE_PIN);
    setPinOutput(DISCHARGE_PIN);

    // set analog reference
    analogReference(ADC_REF_POWER);

    // initialize drive lines
    init_col();

    // initialize multiplexer select pin
    init_mux_sel();

    // set discharge pin to charge mode
    setPinInput(DISCHARGE_PIN);
}

uint16_t ec_readkey_raw(uint8_t col, uint8_t row) {
    uint16_t sw_value = 0;

    discharge_capacitor();

    select_mux(row);

    clear_all_col_pins();

    cli();

    charge_capacitor(col);

    sw_value = analogReadPin(ANALOG_PORT);

    sei();

    return sw_value;
}

bool ec_update_key(matrix_row_t* current_row, matrix_row_t col, uint16_t sw_value, uint16_t reset_pt, uint16_t actuation_pt) {
    bool current_state = (*current_row >> col) & 1;

    // press to release
    if (current_state && sw_value < reset_pt) {
        *current_row &= ~(MATRIX_ROW_SHIFTER << col);
        return true;
    }

    // release to press
    if ((!current_state) && sw_value > actuation_pt) {
        *current_row |= (MATRIX_ROW_SHIFTER << col);
        return true;
    }

    return false;
}

// Define a struct to hold row and column values
typedef struct {
    uint8_t row;
    uint8_t col;
} KeyPosition;

// Define specific key positions
const KeyPosition SPLIT_BACKSPACE_LEFT_1U = {0, 14};
const KeyPosition BACKSPACE_2U            = {0, 15};
const KeyPosition RIGHT_SHIFT_1_75U       = {3, 14};
const KeyPosition LEFT_SPACE_COL3         = {4, 3};
const KeyPosition LEFT_SPACE_COL4         = {4, 4};
const KeyPosition LEFT_SPACE_COL5         = {4, 5};
const KeyPosition LEFT_SPACE_COL6         = {4, 6};
const KeyPosition RIGHT_SHIFT_2_75U       = {4, 14};

// Custom actuation point adjustments
void adjust_actuation_points(uint16_t* reset_pt, uint16_t* actuation_pt, KeyPosition key_pos) {
    // Check if the key is one of the specific keys that need adjustment
    if ((key_pos.row == SPLIT_BACKSPACE_LEFT_1U.row && key_pos.col == SPLIT_BACKSPACE_LEFT_1U.col) || (key_pos.row == BACKSPACE_2U.row && key_pos.col == BACKSPACE_2U.col) || (key_pos.row == RIGHT_SHIFT_1_75U.row && key_pos.col == RIGHT_SHIFT_1_75U.col) || (key_pos.row == RIGHT_SHIFT_2_75U.row && key_pos.col == RIGHT_SHIFT_2_75U.col)) {
        *reset_pt     = 48;
        *actuation_pt = 53;
    } else if ((key_pos.row == LEFT_SPACE_COL3.row && key_pos.col == LEFT_SPACE_COL3.col) || (key_pos.row == LEFT_SPACE_COL4.row && key_pos.col == LEFT_SPACE_COL4.col)) {
        *reset_pt     = 50;
        *actuation_pt = 60;
    } else if ((key_pos.row == LEFT_SPACE_COL5.row && key_pos.col == LEFT_SPACE_COL5.col) || (key_pos.row == LEFT_SPACE_COL6.row && key_pos.col == LEFT_SPACE_COL6.col)) {
        *reset_pt     = 48;
        *actuation_pt = 58;
    }

    // Fail-safe mechanism: Check if reset_pt and actuation_pt are within 5 points of each other for the current key
    if (*actuation_pt - *reset_pt < 5) {
        // Handle the error: print an error message and halt the firmware
        fprintf(stderr, "Error: reset_pt and actuation_pt must have a difference of at least 5 points for each key\n");
        exit(EXIT_FAILURE);
    }
}

bool ec_matrix_scan(matrix_row_t current_matrix[]) {
    bool updated = false;

    for (int row = 0; row < sizeof(row_channels); row++) {
        for (int col = 0; col < sizeof(col_pins); col++) {
            uint16_t reset_pt     = DEFAULT_RESET_PT;
            uint16_t actuation_pt = DEFAULT_ACTUATION_PT;

            // Create a KeyPosition struct for the current key
            KeyPosition key_pos = {row, col};

            // Apply custom actuation point adjustments
            adjust_actuation_points(&reset_pt, &actuation_pt, key_pos);

            ec_sw_value[col][row] = ec_readkey_raw(col, row);
            updated |= ec_update_key(&current_matrix[row], col, ec_sw_value[col][row], reset_pt, actuation_pt);
        }
    }

    return updated;
}

// console debugging for pad values
/*void ec_dprint_matrix(void) {
    for (int row = 0; row < sizeof(row_channels); row++) {
        for (int col = 0; col < sizeof(col_pins); col++) {
            dprintf("%5d", ec_sw_value[col][row]);
        }
        dprintf("\n");
    }
}*/
