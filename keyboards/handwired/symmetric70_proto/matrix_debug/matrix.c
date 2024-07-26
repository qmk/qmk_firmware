/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "atomic_util.h"
#include "util.h"
#include "wait.h"
#include "matrix.h"
#include "debounce.h"
#ifndef readPort
#    include "gpio_extr.h"
#endif

#ifndef MATRIX_DEBUG_PIN
#    define MATRIX_DEBUG_PIN_INIT()
#    define MATRIX_DEBUG_SCAN_START()
#    define MATRIX_DEBUG_SCAN_END()
#    define MATRIX_DEBUG_DELAY_START()
#    define MATRIX_DEBUG_DELAY_END()
#    define MATRIX_DEBUG_GAP()
#else
#    define MATRIX_DEBUG_GAP() asm volatile("nop \n nop" ::: "memory")
#endif

#ifndef MATRIX_IO_DELAY_ALWAYS
#    define MATRIX_IO_DELAY_ALWAYS 0
#endif

#ifdef DIRECT_PINS
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#    ifdef MATRIX_MUL_SELECT
static const pin_t col_sel[MATRIX_COLS]  = MATRIX_MUL_SEL;
#    endif
#endif

#ifdef MATRIX_IO_DELAY_PORTS
static const pin_t       delay_ports[] = {MATRIX_IO_DELAY_PORTS};
static const port_data_t delay_masks[] = {MATRIX_IO_DELAY_MASKS};
#    ifdef MATRIX_IO_DELAY_MULSEL
static const uint8_t delay_sel[] = {MATRIX_IO_DELAY_MULSEL};
#    endif
#endif

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        gpio_set_pin_output(pin);
        gpio_write_pin_low(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON { gpio_set_pin_input_high(pin); }
}

// matrix code

#ifdef DIRECT_PINS

static void init_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
        for (int col = 0; col < MATRIX_COLS; col++) {
            pin_t pin = direct_pins[row][col];
            if (pin != NO_PIN) {
                gpio_set_pin_input_high(pin);
            }
        }
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        pin_t pin = direct_pins[current_row][col_index];
        if (pin != NO_PIN) {
            current_row_value |= gpio_read_pin(pin) ? 0 : (MATRIX_ROW_SHIFTER << col_index);
        }
    }

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

#elif defined(DIODE_DIRECTION)
#    if (DIODE_DIRECTION == COL2ROW)

static void select_row(uint8_t row) { setPinOutput_writeLow(row_pins[row]); }

static void unselect_row(uint8_t row) { setPinInputHigh_atomic(row_pins[row]); }

static void unselect_rows(void) {
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static void init_pins(void) {
#        ifdef MATRIX_MUL_SELECT
    gpio_set_pin_output(MATRIX_MUL_SELECT);
    gpio_write_pin_low(MATRIX_MUL_SELECT);
#        endif
    unselect_rows();
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh_atomic(col_pins[x]);
    }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    // Select row
    select_row(current_row);
    matrix_output_select_delay();

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
        // Select the col pin to read (active low)
#        ifdef MATRIX_MUL_SELECT
        gpio_write_pin(MATRIX_MUL_SELECT, col_sel[col_index]);
        waitInputPinDelay();
#        endif
        uint8_t pin_state = gpio_read_pin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);
#        ifdef MATRIX_IO_DELAY_PORTS
    if (current_row_value) {  // wait for col signal to go HIGH
        bool is_pressed;
        do {
            MATRIX_DEBUG_DELAY_START();
            is_pressed = false;
            for (uint8_t i = 0; i < ARRAY_SIZE(delay_ports); i++) {
#            ifdef MATRIX_IO_DELAY_MULSEL
                gpio_write_pin(MATRIX_MUL_SELECT, delay_sel[i]);
                waitInputPinDelay();
#            endif
                is_pressed |= ((readPort(delay_ports[i]) & delay_masks[i]) != delay_masks[i]);
            }
            MATRIX_DEBUG_DELAY_END();
        } while (is_pressed);
    }
#        endif
#        ifdef MATRIX_IO_DELAY_ADAPTIVE
    if (current_row_value) {  // wait for col signal to go HIGH
        for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
            MATRIX_DEBUG_DELAY_START();
#            ifdef MATRIX_MUL_SELECT
            gpio_write_pin(MATRIX_MUL_SELECT, col_sel[col_index]);
            waitInputPinDelay();
#            endif
            while (gpio_read_pin(col_pins[col_index]) == 0) {
            }
            MATRIX_DEBUG_DELAY_END();
        }
    }
#        endif
#        ifdef MATRIX_IO_DELAY_ADAPTIVE2
    if (current_row_value) {  // wait for col signal to go HIGH
        pin_t state;
        do {
            MATRIX_DEBUG_DELAY_START();
            state = 0;
            for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
                MATRIX_DEBUG_DELAY_END();
                MATRIX_DEBUG_DELAY_START();
#            ifdef MATRIX_MUL_SELECT
                gpio_write_pin(MATRIX_MUL_SELECT, col_sel[col_index]);
                waitInputPinDelay();
#            endif
                state |= (gpio_read_pin(col_pins[col_index]) == 0);
            }
            MATRIX_DEBUG_DELAY_END();
        } while (state);
    }
#        endif
    if (MATRIX_IO_DELAY_ALWAYS || current_row + 1 < MATRIX_ROWS) {
        MATRIX_DEBUG_DELAY_START();
        matrix_output_unselect_delay(current_row, current_row_value != 0);  // wait for col signal to go HIGH
        MATRIX_DEBUG_DELAY_END();
    }

    // If the row has changed, store the row and return the changed flag.
    if (current_matrix[current_row] != current_row_value) {
        current_matrix[current_row] = current_row_value;
        return true;
    }
    return false;
}

#    elif (DIODE_DIRECTION == ROW2COL)

static void select_col(uint8_t col) { setPinOutput_writeLow(col_pins[col]); }

static void unselect_col(uint8_t col) { setPinInputHigh_atomic(col_pins[col]); }

static void unselect_cols(void) {
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh_atomic(col_pins[x]);
    }
}

static void init_pins(void) {
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInputHigh_atomic(row_pins[x]);
    }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col) {
    bool matrix_changed = false;
    bool key_pressed = false;

    // Select col
    select_col(current_col);
    matrix_output_select_delay();

    // For each row...
    for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
        // Store last value of row prior to reading
        matrix_row_t last_row_value    = current_matrix[row_index];
        matrix_row_t current_row_value = last_row_value;

        // Check row pin state
        if (gpio_read_pin(row_pins[row_index]) == 0) {
            // Pin LO, set col bit
            current_row_value |= (MATRIX_ROW_SHIFTER << current_col);
            key_pressed = true;
        } else {
            // Pin HI, clear col bit
            current_row_value &= ~(MATRIX_ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_row_value)) {
            matrix_changed |= true;
            current_matrix[row_index] = current_row_value;
        }
    }

    // Unselect col
    unselect_col(current_col);
    if (MATRIX_IO_DELAY_ALWAYS || current_col + 1 < MATRIX_COLS) {
        matrix_output_unselect_delay(current_col, key_pressed);  // wait for col signal to go HIGH
    }

    return matrix_changed;
}

#    else
#        error DIODE_DIRECTION must be one of COL2ROW or ROW2COL!
#    endif
#else
#    error DIODE_DIRECTION is not defined!
#endif

void matrix_init(void) {
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    bool changed = false;
    MATRIX_DEBUG_PIN_INIT();

    MATRIX_DEBUG_SCAN_START();
#if defined(DIRECT_PINS) || (DIODE_DIRECTION == COL2ROW)
    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        changed |= read_cols_on_row(raw_matrix, current_row);
    }
#elif (DIODE_DIRECTION == ROW2COL)
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        changed |= read_rows_on_col(raw_matrix, current_col);
    }
#endif
    MATRIX_DEBUG_SCAN_END();
    MATRIX_DEBUG_GAP();

    MATRIX_DEBUG_SCAN_START();
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    MATRIX_DEBUG_SCAN_END();
    MATRIX_DEBUG_GAP();

    MATRIX_DEBUG_SCAN_START();
    matrix_scan_kb();
    MATRIX_DEBUG_SCAN_END();
    return (uint8_t)changed;
}
