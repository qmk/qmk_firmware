/* Copyright 2021 @ Keychron (https://www.keychron.com)
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

#include "matrix.h"
#include "quantum.h"

// Pin connected to DS of 74HC595
#define DATA_PIN A7
// Pin connected to SH_CP of 74HC595
#define CLOCK_PIN B1
// Pin connected to ST_CP of 74HC595
#define LATCH_PIN B0

#ifdef MATRIX_ROW_PINS
static const pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
#endif // MATRIX_ROW_PINS
#ifdef MATRIX_COL_PINS
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
#endif // MATRIX_COL_PINS

#define ROWS_PER_HAND (MATRIX_ROWS)

static inline void writePinLow_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinLow(pin);
    }
}

static inline void writePinHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        writePinHigh(pin);
    }
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}

// At 3.6V input, three nops (37.5ns) should be enough for all signals
#define small_delay() __asm__ __volatile__ ("nop;nop;nop;\n\t":::"memory")
#define compiler_barrier() __asm__ __volatile__ ("":::"memory")

static void shiftOut(uint8_t dataOut) {
    ATOMIC_BLOCK_FORCEON {
        for (uint8_t i = 0; i < 8; i++) {
            compiler_barrier();
            if (dataOut & 0x1) {
                writePinHigh(DATA_PIN);
            } else {
                writePinLow(DATA_PIN);
            }
            dataOut = dataOut >> 1;
            compiler_barrier();
            writePinHigh(CLOCK_PIN);
            small_delay();
            writePinLow(CLOCK_PIN);
        }
        compiler_barrier();
        writePinHigh(LATCH_PIN);
        small_delay();
        writePinLow(LATCH_PIN);
        compiler_barrier();
    }
}

static void shiftout_single(uint8_t data) {
    ATOMIC_BLOCK_FORCEON {
        compiler_barrier();
        if (data & 0x1) {
            writePinHigh(DATA_PIN);
        } else {
            writePinLow(DATA_PIN);
        }
        compiler_barrier();
        writePinHigh(CLOCK_PIN);
        small_delay();
        writePinLow(CLOCK_PIN);
        compiler_barrier();
        writePinHigh(LATCH_PIN);
        small_delay();
        writePinLow(LATCH_PIN);
        compiler_barrier();
    }
}

static bool select_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        writePinLow_atomic(pin);
#else
        setPinOutput_writeLow(pin);
#endif
        return true;
    } else {
        if (col == 8) {
            shiftout_single(0x00);
        }
        return true;
    }
    return false;
}

static void unselect_col(uint8_t col) {
    pin_t pin = col_pins[col];

    if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
        writePinHigh_atomic(pin);
#else
        setPinInputHigh_atomic(pin);
#endif
    } else {
        shiftout_single(0x01);
    }
}

static void unselect_cols(void) {
    // unselect column pins
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        pin_t pin = col_pins[x];

        if (pin != NO_PIN) {
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
            writePinHigh_atomic(pin);
#else
            setPinInputHigh_atomic(pin);
#endif
        }
        if (x == (MATRIX_COLS - 1))
            // unselect Shift Register
            shiftOut(0xFF);
    }
}

static void matrix_init_pins(void) {
    setPinOutput(DATA_PIN);
    setPinOutput(CLOCK_PIN);
    setPinOutput(LATCH_PIN);
#ifdef MATRIX_UNSELECT_DRIVE_HIGH
    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        if (col_pins[x] != NO_PIN) {
            setPinOutput(col_pins[x]);
        }
    }
#endif
    unselect_cols();
    for (uint8_t x = 0; x < MATRIX_ROWS; x++) {
        if (row_pins[x] != NO_PIN) {
            setPinInputHigh_atomic(row_pins[x]);
        }
    }
}

#if PAL_IOPORTS_WIDTH == 8
typedef uint8_t ioport_t;
#elif PAL_IOPORTS_WIDTH == 16
typedef uint16_t ioport_t;
#elif PAL_IOPORTS_WIDTH == 32
typedef uint32_t ioport_t;
#else
typedef ioportmask_t ioport_t;
#endif

#define read_pin_port_required(prev_index, pin) \
    ((uint8_t)(prev_index) == (uint8_t)-1 || row_pins[(prev_index)] == NO_PIN || PAL_PORT(pin) != PAL_PORT(row_pins[(prev_index)]))

#define read_pin_port(pin) ((ioport_t)palReadPort(PAL_PORT((pin))))

#define is_pin_set(val, pin) (((val) & (1U << PAL_PAD((pin)))) != 0)

static void matrix_read_rows_on_col(matrix_row_t current_matrix[], uint8_t current_col, matrix_row_t row_shifter) {
    bool key_pressed = false;
    ioport_t ports[ROWS_PER_HAND];

    // Select col
    if (!select_col(current_col)) { // select col
        return;                     // skip NO_PIN col
    }
    matrix_output_select_delay();

    // Read all required pins
#pragma GCC unroll 65534
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        const pin_t pin = row_pins[row_index];
        if (pin == NO_PIN)
            continue;
        // Only read port if we need to
        if (read_pin_port_required(row_index - 1, pin))
            ports[row_index] = read_pin_port(pin);
        else
            ports[row_index] = ports[row_index - 1];
    }

    // Unselect col
    unselect_col(current_col);

    // For each row...
#pragma GCC unroll 65534
    for (uint8_t row_index = 0; row_index < ROWS_PER_HAND; row_index++) {
        // Check row pin state
        const pin_t pin = row_pins[row_index];
        if (pin == NO_PIN)
            continue;
        if (!is_pin_set(ports[row_index], pin)) {
            // Pin LO, set col bit
            current_matrix[row_index] |= row_shifter;
            key_pressed = true;
        }
    }

    matrix_output_unselect_delay(current_col, key_pressed); // wait for all Row signals to go HIGH
}

void matrix_init_custom(void) {
    // initialize key pins
    matrix_init_pins();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set col, read rows
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
#pragma GCC unroll 65534
    for (uint8_t current_col = 0; current_col < MATRIX_COLS; current_col++, row_shifter <<= 1) {
        matrix_read_rows_on_col(curr_matrix, current_col, row_shifter);
    }

    matrix_row_t changed = 0;
#pragma GCC unroll 65534
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_row_t i = curr_matrix[current_row];
        i ^= current_matrix[current_row];
        changed |= i;
    }

    if (changed) {
#pragma GCC unroll 65534
        for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
            current_matrix[current_row] = curr_matrix[current_row];
        }
    }
    return changed;
}
