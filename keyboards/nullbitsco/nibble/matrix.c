/* Copyright 2018 Jack Humbert
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

/* Set 0 if debouncing isn't needed */
#ifndef DEBOUNCE
#define DEBOUNCE 5
#endif

#define COL_SHIFTER ((uint32_t)1)

static uint16_t debouncing_time;
static bool debouncing = false;

static const uint8_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint8_t col_pins[MATRIX_MUX_COLS] = MATRIX_COL_MUX_PINS;

static matrix_row_t matrix[MATRIX_ROWS];
static matrix_row_t matrix_debouncing[MATRIX_ROWS];

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col);
static void unselect_cols(void);
static void select_col(uint8_t col);
static void init_io(void);

inline uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

void matrix_init(void) {
    init_io();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        matrix[i] = 0;
        matrix_debouncing[i] = 0;
    }

    matrix_init_quantum();
}

uint8_t matrix_scan(void)
{
    // Set col, read rows
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        bool matrix_changed = read_rows_on_col(matrix_debouncing, current_col);
        if (matrix_changed) {
            debouncing = true;
            debouncing_time = timer_read();
        }
    }

    if (debouncing && (timer_elapsed(debouncing_time) > DEBOUNCE)) {
        for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
            matrix[i] = matrix_debouncing[i];
        }
        debouncing = false;
    }

    matrix_scan_quantum();
    return 1;
}

static void select_col(uint8_t col)
{
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        uint8_t state = (col & (0b1 << bit)) >> bit;
        writePin(col_pins[bit], state);
    }
}

static void unselect_cols(void) {
    for (uint8_t bit = 0; bit < MATRIX_MUX_COLS; bit++) {
        writePinLow(col_pins[bit]);
    }
}

static void init_io(void) {
    // Set cols to outputs, low
    for (uint8_t pin = 0; pin < MATRIX_MUX_COLS; pin++) {
        setPinOutput(col_pins[pin]);
    }
    unselect_cols();

    #ifdef MATRIX_ACTIVE_HIGH
    // Set rows to input, no pullup
    for (uint8_t pin = 0; pin < MATRIX_ROWS; pin++) {
        setPinInput(row_pins[pin]);
    }
    #else //MATRIX_ACTIVE_LOW
    // Set rows to input pullup
    for (uint8_t pin = 0; pin < MATRIX_ROWS; pin++) {
        setPinInputHigh(row_pins[pin]);
    }
    #endif
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    select_col(current_col);
    wait_us(5);

    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {
        matrix_row_t last_row_value = current_matrix[row_index];

        #ifdef MATRIX_ACTIVE_HIGH
        if (readPin(row_pins[row_index]))
        #else
        if (!readPin(row_pins[row_index]))
        #endif
        {
            current_matrix[row_index] |= (COL_SHIFTER << current_col);
        }
        else
        {
            current_matrix[row_index] &= ~(COL_SHIFTER << current_col);
        }

        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    return matrix_changed;
}

inline bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 0123456789ABCDEFGHIJKLMNOPQRSTUV  \n");

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row); print(": ");
        print_bin_reverse32(matrix_get_row(row));
        print("\n");
    }
}