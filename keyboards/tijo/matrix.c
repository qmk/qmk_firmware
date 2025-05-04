#include <stdbool.h>

#include "debounce.h"
#include "quantum.h"
#include "matrix.h"

#include "pio.h"
#include "spi.h"

void matrix_init_custom(void) {
    // TODO: initialize hardware here
    custom_spi_init();
    mux_init();
}

bool matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool matrix_has_changed = false;

    // TODO: add matrix scanning routine here

    return matrix_has_changed;
}