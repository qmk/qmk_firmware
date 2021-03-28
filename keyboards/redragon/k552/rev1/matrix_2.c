#include <argz.h>
/*
 * Copyright 2011 Jun Wako <wakojun@gmail.com>
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
 *
 * Ported to QMK by Stephen Peery <https://github.com/smp4488/>
 */

#include <stdint.h>
#include <stdbool.h>
#include <SN32F240.h>
#include "ch.h"
#include "hal.h"

#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"
#include "color.h"

static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const pin_t led_row_pins[LED_MATRIX_ROWS_HW] = LED_MATRIX_ROW_PINS;
static uint16_t row_ofsts[LED_MATRIX_ROWS];

matrix_row_t raw_matrix[MATRIX_ROWS]; //raw values
matrix_row_t last_matrix[MATRIX_ROWS] = {0};  // raw values
matrix_row_t matrix[MATRIX_ROWS]; //debounced values

static bool matrix_changed = false;
static uint8_t current_row = 0;

extern volatile LED_TYPE led_state[DRIVER_LED_TOTAL];

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

__WEAK inline matrix_row_t matrix_get_row(uint8_t row) { return matrix[row]; }

__WEAK void matrix_print(void) {}


_Noreturn void color_loop(void);

static void select_col (uint8_t col)
{
    setPinInput(col_pins[col]);
    writePinHigh(col_pins[col]);
}

static void unselect_col (uint8_t col)
{
    setPinOutput(col_pins[col]);
    writePinLow(col_pins[col]);
}

static void select_row (uint8_t row)
{
    setPinOutput(row_pins[row]);
    writePinLow(row_pins[row]);
}

static void unselect_row (uint8_t row)
{
    setPinInputHigh(row_pins[row]);
}

static void unselect_rows (void)
{
    for (uint8_t x = 0; x < MATRIX_ROWS; x++)
    {
        unselect_row(x);
    }
}

static void init_pins(void) {

    //  Unselect ROWs
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        setPinInput(row_pins[x]);
        writePinHigh(row_pins[x]);
    }

    // Unselect COLs
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinOutput(col_pins[x]);
        writePinHigh(col_pins[x]);
    }

    for (uint8_t x = 0; x < LED_MATRIX_ROWS_HW; x++) {
        setPinOutput(led_row_pins[x]);
        writePinHigh(led_row_pins[x]);
    }
}

static bool read_cols_on_row (matrix_row_t current_matrix[], uint8_t current_row)
{
    // Store last value of row prior to reading
    matrix_row_t last_row_value = current_matrix[current_row];

    // Clear data in matrix row
    current_matrix[current_row] = 0;

    // Select row and wait for row selecton to stabilize
    select_row(current_row);
    wait_us(30);

    // For each col...
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++)
    {
        // Set pin to input
        select_col(col_index);

        // Select the col pin to read (active low)
        uint8_t pin_state = readPin(col_pins[col_index]);

        // Set pin to output
        unselect_col(col_index);

        // Populate the matrix row with the state of the col pin
        current_matrix[current_row] |= pin_state ? 0 : (MATRIX_ROW_SHIFTER << col_index);
    }

    // Unselect row
    unselect_row(current_row);

    return last_row_value != current_matrix[current_row];
}

void matrix_init (void)
{
    // initialize key pins
    init_pins();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++)
    {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

     color_loop();

    matrix_init_quantum();
}

#if 1
uint8_t matrix_scan(void) {
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++) {
        for (uint8_t row_index = 0; row_index < MATRIX_ROWS; row_index++) {
            // Determine if the matrix changed state
            if ((last_matrix[row_index] != raw_matrix[row_index])) {
                matrix_changed         = true;
                last_matrix[row_index] = raw_matrix[row_index];
            }
        }
    }

    debounce(raw_matrix, matrix, MATRIX_ROWS, matrix_changed);

    matrix_scan_quantum();

    return matrix_changed;
}

#else
uint8_t matrix_scan (void)
{
    bool changed = false;

    volatile uint32_t col_index = 1;

    for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
    {
        setPinOutput(led_row_pins[y]);
        writePinHigh(led_row_pins[y]);
    }

    while (1)
    {
        for (uint32_t x = 0; x < sizeof(col_pins) / sizeof(col_pins[0]); x++)
        {
            setPinOutput(col_pins[x]);
            writePinLow(col_pins[x]);

            // writePinHigh(col_pins[x]);

            for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
            {
                setPinOutput(led_row_pins[y]);
                writePinHigh(led_row_pins[y]);
            }

            // for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
            // {
            //// On
            //// setPinInput(led_row_pins[y]);
            // setPinOutput(led_row_pins[y]);
            // writePinHigh(led_row_pins[y]);
            // }

            chThdSleepMilliseconds(1);
            setPinInput(col_pins[x]);

            // setPinInput(col_pins[col_index]);
        }
    }

    chThdSleepMilliseconds(5000);
    for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
    {
        // Off
        // setPinOutput(led_row_pins[y]);
        writePinLow(led_row_pins[y]);
    }

    // for (uint8_t x = 0; x < MATRIX_COLS; x++)
    while (1)
    {
        for (uint32_t x = 0; x < sizeof(col_pins) / col_pins[0]; x++)
        {
            setPinOutput(col_pins[x]);
            writePinLow(col_pins[x]);

            // setPinInput(col_pins[col_index]);
        }

        // Turn COL On
// writePinHigh(col_pins[col_index]);
// chThdSleepMilliseconds(10);

        for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
        {
            // On
            // setPinInput(led_row_pins[y]);
            setPinOutput(led_row_pins[y]);
            writePinHigh(led_row_pins[y]);
            chThdSleepMilliseconds(100);

            // Off
            // setPinOutput(led_row_pins[y]);
            writePinLow(led_row_pins[y]);
        }

        for (uint8_t y = 0; y < LED_MATRIX_ROWS; y++)
        {
        }

        // Turn COL Off
        // setPinInput(col_pins[col_index]);

        // writePinHigh(col_pins[col_index]);
        chThdSleepMilliseconds(10);
    }

    //// Set row, read cols
    // for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++)
    // {
    // changed |= read_cols_on_row(raw_matrix, current_row);
    // }

    // debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    // matrix_scan_quantum();

    return (uint8_t) changed;
}

#endif

_Noreturn void color_loop (void)
{
//    volatile uint32_t col_index = 1;
//    uint32_t pins[] = { C0, C1, C3, C4, C14, C15, C5, C6, C7, C8, C9, C10, D0, D1, D2, D3, D4, D5 };
//    setPinInputHigh(C2);
//
//    uint8_t y = 0;
//
//        for (uint32_t i = 0; i < sizeof(pins); i++)
//    {
//        // On
//        // setPinInput(pins[y]);
//        setPinOutput(pins[i]);
//        writePinLow(pins[i]);
//        chThdSleepMilliseconds(200);
//    }
//
//    while (y < sizeof(pins))
//    {
//        setPinOutput(pins[y]);
//        do
//        {
//            writePinHigh(pins[y]);
//            chThdSleepMilliseconds(1000);
//            writePinLow(pins[y]);
//            chThdSleepMilliseconds(1000);
//        } while(readPin(C2));
//        y++;
//    }

    for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y++)
    {
        // On
        // setPinInput(led_row_pins[y]);
        setPinOutput(led_row_pins[y]);
        writePinLow(led_row_pins[y]);
        chThdSleepMilliseconds(200);
    }
//
//    for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y++)
//    {
//        // On
//        // setPinInput(led_row_pins[y]);
////        setPinOutput(led_row_pins[y]);
//        writePinHigh(led_row_pins[y]);
//        chThdSleepMilliseconds(1000);
//        writePinLow(led_row_pins[y]);
//        chThdSleepMilliseconds(1000);
//    }

//    while (1);

    while (1)
     for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++)
    {
        // Turn COL On
        setPinOutput(col_pins[col_index]);
        writePinLow(col_pins[col_index]);
        chThdSleepMilliseconds(10);

        for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y++)
        {
            // On
            // setPinInput(led_row_pins[y]);
            setPinOutput(led_row_pins[y]);
            writePinHigh(led_row_pins[y]);
            chThdSleepMilliseconds(500);
//        }
//
//        ;
//
//        chThdSleepMilliseconds(100);
//
//        for (uint8_t y = 0; y < LED_MATRIX_ROWS_HW; y+=3)
//        {
            // Off
            // setPinOutput(led_row_pins[y]);
            writePinLow(led_row_pins[y]);
//            chThdSleepMilliseconds(1000);
        }

        // Turn COL Off
        setPinInput(col_pins[col_index]);
        writePinHigh(col_pins[col_index]);
        chThdSleepMilliseconds(10);
    }
}