#include "matrix.h"

#include "quantum.h"

static matrix_row_t read_row(uint8_t row) {
    matrix_io_delay();  // without this wait read unstable value.

    // keypad and program buttons
    if (row == 12) {
        return ~(readPin(B4) | (readPin(B5) << 1) | 0b11111100);
    }

    return ~(readPin(B6) | readPin(B2) << 1 | readPin(B3) << 2 | readPin(B1) << 3 | readPin(F7) << 4 | readPin(F6) << 5 | readPin(F5) << 6 | readPin(F4) << 7);
}

static void unselect_rows(void) {
    // set A,B,C,G to 0
    PORTD &= 0xF0;
}

static void select_rows(uint8_t row) {
    // set A,B,C,G to row value
    PORTD |= (0x0F & row);
}

void matrix_init_custom(void) {
    // output low (multiplexers)
    setPinOutput(D0);
    setPinOutput(D1);
    setPinOutput(D2);
    setPinOutput(D3);

    // input with pullup (matrix)
    setPinInputHigh(B6);
    setPinInputHigh(B2);
    setPinInputHigh(B3);
    setPinInputHigh(B1);
    setPinInputHigh(F7);
    setPinInputHigh(F6);
    setPinInputHigh(F5);
    setPinInputHigh(F4);

    // input with pullup (program and keypad buttons)
    setPinInputHigh(B4);
    setPinInputHigh(B5);

    // initialize row and col
    unselect_rows();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        select_rows(i);
        matrix_row_t row = read_row(i);
        unselect_rows();
        bool row_has_changed = current_matrix[i] != row;
        matrix_has_changed |= row_has_changed;
        current_matrix[i] = row;
    }

    return matrix_has_changed;
}
