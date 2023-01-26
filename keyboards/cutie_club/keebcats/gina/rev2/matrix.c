#include <stdint.h>
#include <stdbool.h>
#include "quantum.h"
#include "i2c_master.h"

#include "pcal6416a/pcal6416a.h"
#include "indicator_leds.h"

static const pcal_gpio_pin row_pins[MATRIX_ROWS] = PCAL_ROW_PINS;
static const pcal_gpio_pin column_pins[MATRIX_COLS] = PCAL_COL_PINS;

static bool update_matrix_for_row(uint8_t row, matrix_row_t current_matrix[]) {
    matrix_row_t previous_row_state = current_matrix[row];
    current_matrix[row] = 0;

    pcal_write_pin(row_pins[row], LOW);

    for (uint8_t column = 0; column < MATRIX_COLS; column++) {
        pcal_gpio_pin current_column_pin = column_pins[column];

        if(pcal_read_pin(current_column_pin) == LOW) {
            current_matrix[row] |= (1 << column);
        }
    }

    pcal_write_pin(row_pins[row], HIGH);

    return previous_row_state != current_matrix[row];
}

void matrix_init_custom(void) {
    i2c_init();

    indicator_leds_init();
    set_pin_array_direction(column_pins, MATRIX_COLS, INPUT_PULLUP);
    set_pin_array_initial_state(row_pins, MATRIX_ROWS, HIGH);
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        if(update_matrix_for_row(row, current_matrix)) matrix_has_changed = true;
    }
    return matrix_has_changed;
}
