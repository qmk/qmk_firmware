/**
 * matrix.c
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "quantum.h"
#include "matrix.h"
#include "tca6424.h"
#include "m20add.h"

static const uint16_t row_pins[MATRIX_ROWS] = MATRIX_ROW_PINS;
static const uint16_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;

void matrix_init_custom(void)
{
    tca6424_init();
    // set port0
    tca6424_write_config(TCA6424_PORT0, 0);
    // set port1
    tca6424_write_config(TCA6424_PORT1, 0);
    // set port2
    tca6424_write_config(TCA6424_PORT2, 0xF5);

    // clear output
    tca6424_write_port(TCA6424_PORT0, 0);
    tca6424_write_port(TCA6424_PORT1, 0);
    tca6424_write_port(TCA6424_PORT2, 0);
}

bool matrix_scan_custom(matrix_row_t current_matrix[])
{
    bool changed = false;

    for (int col = 0; col < MATRIX_COLS; col++) {
        // Select col and wait for col selecton to stabilize
        set_pin(col_pins[col]);
        matrix_io_delay();

        // For each row...
        for(uint8_t row = 0; row< MATRIX_ROWS; row++) {
            uint8_t tmp = row;
            // Store last value of row prior to reading
            matrix_row_t last_row_value = current_matrix[tmp];

            // Check row pin state
            if (read_pin(row_pins[row])) {
                // Pin HI, set col bit
                current_matrix[tmp] |= (1 << col);
            } else {
                // Pin LOW, clear col bit
                current_matrix[tmp] &= ~(1 << col);
            }

            // Determine if the matrix changed state
            if ((last_row_value != current_matrix[tmp]) && !(changed)) {
                changed = true;
            }
        }
        // Unselect col
        clear_pin(col_pins[col]);
    }

    return changed;
}
