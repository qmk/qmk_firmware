// Copyright 2022 @sadekbaroudi (Sadek Baroudi)
// Copyright 2023 @jasonhazel (Jason Hazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#include "matrix.h"
#include <string.h>
#include "spi_master.h"
#include "debug.h"
#include "wait.h"

#if (!defined(SHIFTREG_MATRIX_COL_CS))
#    error Missing shift register I/O pin definitions
#endif

int matrixArraySize = SHIFTREG_ROWS * sizeof(matrix_row_t);
matrix_row_t oldMatrix[SHIFTREG_ROWS];

#define SHIFTREG_OUTPUT_BITS 8
pin_t rowPinsSR[SHIFTREG_ROWS] = MATRIX_ROW_PINS_SR;

// semaphore to make sure SPI doesn't get called multiple times
static bool shiftRegisterSPILocked = false;

void semaphore_lock(bool value) {
    shiftRegisterSPILocked = value;
}

bool semaphore_is_locked(void) {
    return shiftRegisterSPILocked;
}

void sr_74hc595_spi_stop(void) {
    spi_stop();
    semaphore_lock(false);
}

bool sr_74hc595_spi_start(void) {
    if (!spi_start(SHIFTREG_MATRIX_COL_CS, false, 0, SHIFTREG_DIVISOR)) {
        dprintf("74hc595 matrix: failed to start spi\n");
        sr_74hc595_spi_stop();
        return false;
    }

    semaphore_lock(true);
    wait_us(1); // not sure if I need this
    return true;
}

bool sr_74hc595_spi_send_byte(uint8_t data) {
    sr_74hc595_spi_start();
    writePinLow(SHIFTREG_MATRIX_COL_CS);
    matrix_io_delay();
    spi_write(data);
    matrix_io_delay();
    writePinHigh(SHIFTREG_MATRIX_COL_CS);
    sr_74hc595_spi_stop();
    return true;
}

/**
 * Set the entire shift register to be full of inactive bits
 */
void clearColumns(void) {
    uint8_t value = 0b00000000;
    sr_74hc595_spi_send_byte(value);
}

void setColumn(int columnShift, bool test_run) {
    uint8_t columnShiftByte = ((uint8_t)1 << columnShift);
    if(test_run) {
        dprintf("byte sent: %d\n", columnShiftByte);
    }
    sr_74hc595_spi_send_byte(columnShiftByte);
}

/*
 * override of the qmk intialization function
 */
void matrix_init_custom(void) {
    wait_ms(300);
    spi_init();
    // Set up the initial states for all the row pins
    for (int r = 0; r < SHIFTREG_ROWS; r++) {
        // Note: This needs to use the internal pull down resistors, and atmegas do *not* support that
        setPinInputLow(rowPinsSR[r]);
    }

    // Set the CS to low by default, and specify as an output pin
    writePinHigh(SHIFTREG_MATRIX_COL_CS); // should be high when using SPI?
    setPinOutput(SHIFTREG_MATRIX_COL_CS);

    // Since it's the init, deactivate all the columns. We'll activate once we get to the matrix scan
    clearColumns();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    // respect the semaphore
    if (semaphore_is_locked()) {
        return false;
    }

    // Keep track of if something was modified
    bool matrix_has_changed = false;

    // reset the current matrix, as we'll be updating and comparing to the old matrix
    memset(current_matrix, 0, matrixArraySize);


    bool debug_output = false;
    // Loop through the columns, activating one at a time, and read the rows, and place in the new current_matrix
    for (int c = 0; c < SHIFTREG_COLS; c++) {
        if (debug_output) {
            dprintf("column iteration: %d\n", c);
        }
        setColumn(c, debug_output);
        matrix_io_delay();

        for (int r = 0; r < SHIFTREG_ROWS; r++) {
            current_matrix[r] |= ((readPin(rowPinsSR[r]) ? 1 : 0) << c);
        }
    }

    matrix_has_changed = memcmp(current_matrix, oldMatrix, matrixArraySize) != 0;
    memcpy(oldMatrix, current_matrix, matrixArraySize);

    if (matrix_has_changed) {
        matrix_print();
    }


    // Deactivate all the columns for the next run.
    clearColumns();
    matrix_io_delay();

    return matrix_has_changed;
}
