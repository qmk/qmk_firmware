#include "matrix.h"
#include "quantum.h"

/* 
    It is included in quamtum/matrix.c, but I copied it
    because it is necessary to implement matrix_scan. Not
    included when using CUSTOM_MATRIX=lite!
*/

extern matrix_row_t raw_matrix[MATRIX_ROWS]; // raw values
extern matrix_row_t matrix[MATRIX_ROWS];     // debounced values
pin_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
pin_t col_pins[MATRIX_COLS]   = MATRIX_COL_PINS;

static inline void setPinInputHigh_atomic(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinInputHigh(pin);
    }
}

static inline void setPinOutput_writeLow(pin_t pin) {
    ATOMIC_BLOCK_FORCEON {
        setPinOutput(pin);
        writePinLow(pin);
    }
}

static bool select_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
        setPinOutput_writeLow(pin);
        return true;
    }
    return false;
}

static void unselect_row(uint8_t row) {
    pin_t pin = row_pins[row];
    if (pin != NO_PIN) {
#            ifdef MATRIX_UNSELECT_DRIVE_HIGH
        setPinOutput_writeHigh(pin);
#            else
        setPinInputHigh_atomic(pin);
#            endif
    }
}

static inline uint8_t readMatrixPin(pin_t pin) {
    if (pin != NO_PIN) {
        return readPin(pin);
    } else {
        return 1;
    }
}

/* end of copy */

void matrix_init(void) {
    // We don't need to initialize the pin.
    // matrix_init_pins();

    // initialize matrix state: all keys off
    memset(matrix, 0, sizeof(matrix));
    memset(raw_matrix, 0, sizeof(raw_matrix));

    matrix_init_quantum();
}

void matrix_read_cols_on_row(matrix_row_t current_matrix[], uint8_t current_row) {
    // Start with a clear matrix row
    matrix_row_t current_row_value = 0;

    for (uint8_t x = 0; x < MATRIX_COLS; x++) {
        setPinInputHigh_atomic(col_pins[x]);
    }

    if (!select_row(current_row)) { // Select row
        return;                     // skip NO_PIN row
    }
    matrix_output_select_delay();

    // For each col...
    matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
    for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
        if (current_row == col_index)
            continue;

        uint8_t pin_state = readMatrixPin(col_pins[col_index]);

        // Populate the matrix row with the state of the col pin
        current_row_value |= pin_state ? 0 : row_shifter;
    }

    // Unselect row
    unselect_row(current_row);
    matrix_output_unselect_delay(current_row, current_row_value != 0); // wait for all Col signals to go HIGH

    // Update the matrix
    current_matrix[current_row] = current_row_value;
}

static const char pin_name[MATRIX_ALL][4] = MATRIX_ALL_PINS_STRING;
uint8_t matrix_scan(void) {
    /*
        We're going to try to find the culprit.
        Let's look at an example matrix.

           A1 A2 A3 B1 B2 B3
        A1 X  ?  ?  ?  ?  ?
        A2 ?  X  ?  ?  ?  ?
        A3 ?  ?  X  ?  ?  ?
        B1 ?  ?  ?  X  ?  ?
        B2 ?  ?  ?  ?  X  ?
        B3 ?  ?  ?  ?  ?  X

        We find a switch that goes into "?".
        Any pin can be an input or an output.

        For example, let's say a real keyboard has the following matrix:
           A1 A3
        B1 a  b
        B2 c  d

        Here's what the matrix looks like when you press each key

           A1 A2 A3 B1 B2 B3
        A1 X  ?  ?  ?  ?  ?
        A2 ?  X  ?  ?  ?  ?
        A3 ?  ?  X  ?  ?  ?
        B1 a  ?  b  X  ?  ?
        B2 c  ?  d  ?  X  ?
        B3 ?  ?  ?  ?  ?  X

        Haha we can infer the shape of the matrix from this.
    */
    matrix_row_t curr_matrix[MATRIX_ROWS] = {0};

    // Set row, read cols
    for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
        matrix_read_cols_on_row(curr_matrix, current_row);
    }

    bool changed = memcmp(raw_matrix, curr_matrix, sizeof(curr_matrix)) != 0;
    if (changed) {
        for (uint8_t current_row = 0; current_row < MATRIX_ROWS; current_row++) {
            matrix_row_t curr_row_value = curr_matrix[current_row];    
            matrix_row_t prev_row_value = raw_matrix[current_row];
            matrix_row_t row_shifter = MATRIX_ROW_SHIFTER;
            for (uint8_t col_index = 0; col_index < MATRIX_COLS; col_index++, row_shifter <<= 1) {
                if ( (prev_row_value & row_shifter) && !(curr_row_value & row_shifter) ){
                    // Turn off
                    uprintf("%s to %s: Turn off\n", pin_name[current_row], pin_name[col_index]);
                }
                else if ( !(prev_row_value & row_shifter) && (curr_row_value & row_shifter) ){
                    // Turn on
                    uprintf("%s to %s: Turn on\n", pin_name[current_row], pin_name[col_index]);
                }
            }
        }
        
        memcpy(raw_matrix, curr_matrix, sizeof(curr_matrix)); // haha is needed?
    }

    matrix_scan_quantum();

    return (uint8_t)0; // haha im not changed
}