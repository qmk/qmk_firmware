/*
Copyright 2012-2018 Jun Wako, Jack Humbert, Yiancar
Port done by Andy Lee <alee@alittlepeacemusic.com>
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
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

#ifdef MATRIX_MASKED
    extern const matrix_row_t matrix_mask[];
#endif

#ifdef DIRECT_PINS
static pin_t direct_pins[MATRIX_ROWS][MATRIX_COLS] = DIRECT_PINS;
#elif (DIODE_DIRECTION == ROW2COL) || (DIODE_DIRECTION == COL2ROW)
// static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif

/* matrix state(1:on, 0:off) */
static matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
static matrix_row_t matrix[MATRIX_ROWS]; //debounced values

__attribute__ ((weak))
void matrix_init_kb(void) {
    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_kb(void) {
    matrix_scan_user();
}

__attribute__ ((weak))
void matrix_init_user(void) {
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

inline
uint8_t matrix_rows(void) {
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void) {
    return MATRIX_COLS;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & ((matrix_row_t)1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

void matrix_print(void)
{
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        print_hex8(row); print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

#ifdef DIRECT_PINS

static void init_pins(void) {
  for (int row = 0; row < MATRIX_ROWS; row++) {
    for (int col = 0; col < MATRIX_COLS; col++) {
      pin_t pin = direct_pins[row][col];
      if (pin != NO_PIN) {
        setPinInputHigh(pin);
      }
    }
  }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
  matrix_row_t last_row_value = current_matrix[current_row];
  current_matrix[current_row] = 0;

  for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {
    pin_t pin = direct_pins[current_row][col_index];
    if (pin != NO_PIN) {
      current_matrix[current_row] |= readPin(pin) ? 0 : (ROW_SHIFTER << col_index);
    }
  }

  return (last_row_value != current_matrix[current_row]);
}

#elif (DIODE_DIRECTION == COL2ROW)
/* Rows 0 - 5
 * These rows use a 74HC138 3-to-8 demultiplexer.
 *                C    B    A
 * row / pin:    PB0  PB1  PB2
 * 0:             0    0    0
 * 1:             0    0    1
 * 2:             0    1    0
 * 3:             0    1    1
 * 4:             1    0    0
 * 5:             1    0    1
 */
static void select_row(uint8_t col)
{
    switch (col) {
        case 0:
            writePinLow(B0);
            writePinLow(B1);
            writePinLow(B2);
            break;
        case 1:
            writePinLow(B0);
            writePinLow(B1);
            break;
        case 2:
            writePinLow(B0);
            writePinLow(B2);
            break;
        case 3:
            writePinLow(B0);
            break;
        case 4:
            writePinLow(B1);
            writePinLow(B2);
            break;
        case 5:
            writePinLow(B1);
            break;
    }
}

static void unselect_row(uint8_t col)
{
    switch (col) {
        case 0:
            writePinHigh(B0);
            writePinHigh(B1);
            writePinHigh(B2);
            break;
        case 1:
            writePinHigh(B0);
            writePinHigh(B1);
            break;
        case 2:
            writePinHigh(B0);
            writePinHigh(B2);
            break;
        case 3:
            writePinHigh(B0);
            break;
        case 4:
            writePinHigh(B1);
            writePinHigh(B2);
            break;
        case 5:
            writePinHigh(B1);
            break;
    }
}

static void unselect_rows(void)
{
    setPinOutput(B0);
    setPinOutput(B1);
    setPinOutput(B2);
	// make all pins high to select Y7, nothing is connected to that (otherwise the first row will act weird)
    writePinHigh(B0);
    writePinHigh(B1);
    writePinHigh(B2);
}

static void init_pins(void) {
  unselect_rows();
  for (uint8_t x = 0; x < MATRIX_COLS; x++) {
    setPinInputHigh(col_pins[x]);
  }
}

static bool read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row)
{
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for(uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++) {

        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |=  pin_state ? 0 : (ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return (last_row_value != current_matrix[current_row]);
}

#elif (DIODE_DIRECTION == ROW2COL)

static void select_col(uint8_t col)
{
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void unselect_col(uint8_t col)
{
    setPinInputHigh(col_pins[col]);
}

static void unselect_cols(void)
{
    for(uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh(col_pins[x]);
    }
}

static void init_pins(void) {
  unselect_cols();
  for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
    setPinInputHigh(row_pins[x]);
  }
}

static bool read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col)
{
    bool matrix_changed = false;

    // Select col and wait for col selecton to stabilize
    select_col(current_col);
    wait_us(30);

    // For each row...
    for(uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++)
    {

        // Store last value of row prior to reading
        matrix_row_t last_row_value = current_matrix[row_index];

        // Check row pin state
        if (readPin(row_pins[row_index]) == 0)
        {
            // Pin LO, set col bit
            current_matrix[row_index] |= (ROW_SHIFTER << current_col);
        }
        else
        {
            // Pin HI, clear col bit
            current_matrix[row_index] &= ~(ROW_SHIFTER << current_col);
        }

        // Determine if the matrix changed state
        if ((last_row_value != current_matrix[row_index]) && !(matrix_changed))
        {
            matrix_changed = true;
        }
    }

    // Unselect col
    unselect_col(current_col);

    return matrix_changed;
}

#endif

void matrix_init(void) {

    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i] = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_kb();
}

uint8_t matrix_scan(void)
{
  bool changed = false;

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

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_kb();
  return 1;
}
