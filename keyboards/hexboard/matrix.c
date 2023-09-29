#include "platforms/chibios/vendors/RP/_pin_defs.h"
#include "gpio.h"
#include "matrix.h"
// #include <util/delay.h>

static const uint8_t columns[MATRIX_COLS] = MATRIX_COL_PINS;

static const pin_t mux_pins[4] = MATRIX_ROW_PINS;

void matrix_init_custom(void) {
    // TODO: initialize hardware here
    // Set pinModes for the digital button matrix.
    for (int pinNumber = 0; pinNumber < MATRIX_COLS; pinNumber++) { // For each column pin...
        setPinInputHigh(columns[pinNumber]); // set the pinMode to INPUT_PULLUP (+3.3V / HIGH).
    }
    setPinOutput(mux_pins[0]);
    setPinOutput(mux_pins[1]);
    setPinOutput(mux_pins[2]);
    setPinOutput(mux_pins[3]);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here
    // Button Deck
    for (int rowIndex = 0; rowIndex < 14; rowIndex++) { // Iterate through each of the row pins on the multiplexing chip.
        writePin(mux_pins[0], rowIndex & 1);
        writePin(mux_pins[1], (rowIndex & 2) >> 1);
        writePin(mux_pins[2], (rowIndex & 4) >> 2);
        writePin(mux_pins[3], (rowIndex & 8) >> 3);
        for (int columnIndex = 0; columnIndex < MATRIX_COLS; columnIndex++) { // Now iterate through each of the column pins that are connected to the current row pin.
            pin_t columnPin = columns[columnIndex]; // Hold the currently selected column pin in a variable.
            setPinInputHigh(columnPin); // Set that row pin to INPUT_PULLUP mode (+3.3V / HIGH).
            //_delay_us(10); // Delay to give the pin modes time to change state (false readings are caused otherwise).
            matrix_io_delay();
            bool previousValue = (current_matrix[rowIndex] >> columnIndex ) & 1;
            bool buttonState = ! readPin(columnPin); // inverted...
            matrix_has_changed |= previousValue != buttonState;
            if (buttonState) {
                current_matrix[rowIndex] |= (1 << columnIndex);
            } else {
                current_matrix[rowIndex] &= ~(1 << columnIndex);
            }

            // Set the selected column pin back to INPUT mode (0V / LOW).
            setPinInput(columnPin);
        }
    }

    return matrix_has_changed;
}
