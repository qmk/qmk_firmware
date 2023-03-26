/*
Copyright 2021 mtei

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
// clang-format off
#include <stdint.h>
#include <stdbool.h>
#include <gpio.h>
#ifndef readPort
#    include "gpio_extr.h"
#endif
#include "util.h"
#include "matrix.h"
#include "matrix_extr.h"
#include "debounce.h"
#include "quantum.h"

#define ALWAYS_INLINE inline __attribute__((always_inline))
#define NO_INLINE     __attribute__((noinline))
#define LOCAL_FUNC static
#define LOCAL_DATA static

#ifndef _BV
#    define _BV(bit) (1 << (bit))
#endif

#ifndef MATRIX_DEBUG_PIN
#    define MATRIX_DEBUG_PIN_INIT()
#    define MATRIX_DEBUG_SCAN_START()
#    define MATRIX_DEBUG_SCAN_END()
#    define MATRIX_DEBUG_DELAY_START()
#    define MATRIX_DEBUG_DELAY_END()
#    define MATRIX_DEBUG_GAP()
#else
#    define MATRIX_DEBUG_GAP()  asm volatile("nop \n nop":::"memory")
#endif

typedef uint16_t     port_width_t;
#if MATRIX_TYPE == DIRECT_SWITCH || MATRIX_TYPE == DIODE_COL2ROW
#    define MATRIX_LINES MATRIX_ROWS
typedef matrix_row_t matrix_line_t;
#endif
#if MATRIX_TYPE == DIODE_ROW2COL
#    define MATRIX_LINES MATRIX_COLS
typedef matrix_col_t matrix_line_t;
#endif
typedef struct _port_descriptor {
    int device;
    pin_t port;
} port_descriptor;

/* matrix state(1:on, 0:off) */
extern matrix_row_t raw_matrix[MATRIX_ROWS];  // raw values
extern matrix_row_t matrix[MATRIX_ROWS];      // debounced values

#define setPortBitOutput_writeLow(port, bit) \
    do { setPortBitOutput(port, bit); writePortBitLow(port, bit); } while(0)
#define setPortBitOutput_writeLow_atomic(port, bit) \
    do { ATOMIC_BLOCK_FORCEON { setPortBitOutput_writeLow(port, bit); } } while(0)
#define setPortBitInputHigh_atomic(port, bit) \
    do { ATOMIC_BLOCK_FORCEON { setPortBitInputHigh(port, bit); } } while(0)

#if defined(MATRIX_IN_PORTS) && defined(MATRIX_IN_PINS)
#   include "matrix_config_expand.c"
#else
#   error matrix.c need defined MATRIX_IN_PORTS and MATRIX_IN_PINS
#endif

LOCAL_FUNC
void unselect_output(uint8_t out_index) {
    unselect_output_inline(out_index);
}

LOCAL_FUNC
void init_output_ports(void) {
    for (int i = 0; i < END_outpin_index; i++) {
        unselect_output(i);
    }
}

LOCAL_FUNC
void init_all_ports(void) {
    init_input_ports();
    init_output_ports();
    init_inport_mask();
    init_extension();
}

LOCAL_FUNC ALWAYS_INLINE void select_line_and_read_input_ports(uint8_t current_line, port_width_t port_buffer[NUM_OF_INPUT_PORTS]);
LOCAL_FUNC void select_line_and_read_input_ports(uint8_t current_line, port_width_t port_buffer[NUM_OF_INPUT_PORTS]) {
    // Select row (or col)
    select_output(current_line);
    matrix_output_select_delay();

    // Read ports
    read_all_input_ports(port_buffer, false);

    // Unselect row (or col)
    unselect_output_inline(current_line);
}

LOCAL_FUNC ALWAYS_INLINE void read_matrix_line(matrix_line_t phy_matrix[], uint8_t current_line);

#if MATRIX_TYPE == DIODE_ROW2COL || MATRIX_TYPE == DIODE_COL2ROW
LOCAL_FUNC void read_matrix_line(matrix_line_t phy_matrix[], uint8_t current_line) {
    // Start with a clear matrix row
    matrix_line_t current_line_value = 0;
    port_width_t port_buffer[NUM_OF_INPUT_PORTS];

#ifdef MATRIX_GPIO_NEED_SEPARATE_ATOMIC
    select_line_and_read_input_ports(current_line, port_buffer);
#else
    ATOMIC_BLOCK_FORCEON {
        select_line_and_read_input_ports(current_line, port_buffer);
    }
#endif

    // Build row (or col)
    current_line_value = build_matrix_line(port_buffer);

    // Wait signal raise up
    if (current_line_value) {
        MATRIX_DEBUG_DELAY_START();
        wait_unselect_done();
        MATRIX_DEBUG_DELAY_END();
    }
    phy_matrix[current_line] = current_line_value;
}
#endif // MATRIX_TYPE == DIODE_ROW2COL || MATRIX_TYPE == DIODE_COL2ROW

#if MATRIX_TYPE == DIRECT_SWITCH
LOCAL_FUNC void read_matrix_line(matrix_line_t phy_matrix[], uint8_t current_line) {
    port_width_t port_buffer[NUM_OF_INPUT_PORTS];

    if (current_line != 0) {
        return;
    }

    for (uint8_t i = 0; i < MATRIX_LINES; i++) {
        phy_matrix[i] = 0;
    }

    read_all_input_ports(port_buffer, false);

    // Build matrix
    build_matrix_direct(port_buffer, phy_matrix);
}
#endif // MATRIX_TYPE == DIRECT_SWITCH

void matrix_init(void) {
    // initialize key pins
    init_all_ports();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_kb();
}

uint8_t matrix_scan(void) {
    matrix_line_t phy_matrix[MATRIX_LINES];

    MATRIX_DEBUG_PIN_INIT();

    MATRIX_DEBUG_SCAN_START();

    // read I/O port to phy_matrix[] (physical matrix)
    //select line, read inputs
    for (uint8_t current_line = 0; current_line < MATRIX_LINES; current_line++) {
        read_matrix_line(phy_matrix, current_line);
    }
    MATRIX_DEBUG_SCAN_END(); MATRIX_DEBUG_GAP(); MATRIX_DEBUG_SCAN_START();

    bool changed = false;
#if MATRIX_TYPE == DIRECT_SWITCH || MATRIX_TYPE == DIODE_COL2ROW
    // copy phy_matrix[] to raw_matrix[]
    for (uint8_t current_line = 0; current_line < MATRIX_ROWS; current_line++) {
        if (raw_matrix[current_line] != phy_matrix[current_line]) {
            changed = true;
            raw_matrix[current_line] = phy_matrix[current_line];
        }
    }
#endif
#if MATRIX_TYPE == DIODE_ROW2COL
    // transpose phy_matrix[] to raw_matrix[]
    matrix_row_t trans_matrix[MATRIX_ROWS];
    for (uint8_t i = 0; i < MATRIX_ROWS; i++ ) {
        trans_matrix[i] = 0;
    }
    for (uint8_t src_line = 0; src_line < MATRIX_LINES; src_line++) {
        matrix_line_t src_line_data = phy_matrix[src_line];
        matrix_row_t dist_bit = MATRIX_ROW_SHIFTER << src_line;
        for (uint8_t dist_rows = 0; dist_rows < MATRIX_ROWS; dist_rows++) {
            if ((src_line_data & 1) == 1) {
                trans_matrix[dist_rows] |= dist_bit;
            }
            src_line_data >>= 1;
        }
    }
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        if (raw_matrix[current_row] != trans_matrix[current_row]) {
            changed = true;
            raw_matrix[current_row] = trans_matrix[current_row];
        }
    }
#endif
    MATRIX_DEBUG_SCAN_END(); MATRIX_DEBUG_GAP(); MATRIX_DEBUG_SCAN_START();

    // debounce raw_matrix[] to matrix[]
    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);
    MATRIX_DEBUG_SCAN_END(); MATRIX_DEBUG_GAP();

    MATRIX_DEBUG_SCAN_START();
    matrix_scan_kb();
    MATRIX_DEBUG_SCAN_END();
    return (uint8_t)changed;
}
