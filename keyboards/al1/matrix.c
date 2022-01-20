#include "matrix.h"

#include "gpio.h"

static uint8_t read_rows(void) {
    return (readPin(C7) ? 0 : 1) |
           (readPin(B1) ? 0 : 2) |
           (readPin(B2) ? 0 : 4) |
           (readPin(C6) ? 0 : 8) |
           (readPin(B4) ? 0 : 16) |
           (readPin(B5) ? 0 : 32);
}

static void select_col(uint8_t col) {
    writePinLow(D3);

    writePin(D4, (col & 1));
    writePin(D5, (col & 2));
    writePin(D6, (col & 4));
    writePin(D7, (col & 8));
}

static void  unselect_cols(void) {
    writePinHigh(D3);
}

void matrix_init_custom(void) {
    /* 74HC154 col pin configuration
     * pin:     D3  D7  D6  D5  D4
     * row: off  0   x   x   x   x
     *      0    1   0   0   0   0
     *      1    1   0   0   0   1
     *      2    1   0   0   1   0
     *      3    1   0   0   1   1
     *      4    1   0   1   0   0
     *      5    1   0   1   0   1
     *      6    1   0   1   1   0
     *      7    1   0   1   1   1
     *      8    1   1   0   0   0
     *      9    1   1   0   0   1
     *      10   1   1   0   1   0
     *      11   1   1   0   1   1
     *      12   1   1   1   0   0
     *      13   1   1   1   0   1
     *      14   1   1   1   1   0
     *      15   1   1   1   1   1
     */
    setPinOutput(D3);
    writePinHigh(D3);

    setPinOutput(D4);
    setPinOutput(D5);
    setPinOutput(D6);
    setPinOutput(D7);


    /* Row pin configuration
     *
     * row:  0  1  2  3  4  5
     * pin: C7 B1 B2 C6 B4 B5
     *
     */
    setPinInputHigh(C7);
    setPinInputHigh(B1);
    setPinInputHigh(B2);
    setPinInputHigh(C6);
    setPinInputHigh(B4);
    setPinInputHigh(B5);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        select_col(col);
        matrix_io_delay();
        uint8_t rows = read_rows();

        for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
            bool prev_bit = current_matrix[row] & ((matrix_row_t)1 << col);
            bool curr_bit = rows & (1 << row);

            if (prev_bit != curr_bit) {
                current_matrix[row] ^= ((matrix_row_t)1 << col);
                changed = true;
            }
        }
        unselect_cols();
    }

    return changed;
}
