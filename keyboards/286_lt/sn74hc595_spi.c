
#include "spi_master.h"
#include "gpio.h"
#include "matrix.h"


pin_t SS595 = A3;
bool lsbFirst = false;
uint8_t mode = 0;
uint16_t divisor = 16;
const uint8_t *data;
uint16_t length = 2;

/*
void matrix_scan_kb(void){
spi_transmit(*data, length);

}*/
/*
void matrix_init_kb(void) {
spi_start(SS595, lsbFirst, mode, divisor);

}*/
/*
void matrix_init_pins(void) {
    for (int row = 0; row < MATRIX_ROWS; row++) {
            pin_t pin = MATRIX_ROW_PINS[row];
            if (pin != NO_PIN) {
                setPinInputHigh(pin);
            }

    }
}*/
/*
void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    spi_start(SS595, lsbFirst, mode, divisor);
    u_int16_t  data = 1;
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }
    matrix_output_select_delay();

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        uint8_t pin_state = readMatrixPin(row_pins[row_shifter]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}*/
