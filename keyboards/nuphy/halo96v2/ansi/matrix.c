#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

// Define row and column masks
#define rowA_bits (PAL_PORT_BIT(PAL_PAD(A0)) | PAL_PORT_BIT(PAL_PAD(A1)) | PAL_PORT_BIT(PAL_PAD(A2)) | PAL_PORT_BIT(PAL_PAD(A3)))
#define rowC_bits (PAL_PORT_BIT(PAL_PAD(C14)) | PAL_PORT_BIT(PAL_PAD(C15)))

#define colA_bits (PAL_PORT_BIT(PAL_PAD(A4)) | PAL_PORT_BIT(PAL_PAD(A5)) | PAL_PORT_BIT(PAL_PAD(A6)) | PAL_PORT_BIT(PAL_PAD(A7)) | \
                   PAL_PORT_BIT(PAL_PAD(A8)) | PAL_PORT_BIT(PAL_PAD(A9)) | PAL_PORT_BIT(PAL_PAD(A10)) | PAL_PORT_BIT(PAL_PAD(A15)))

#define colB_bits (PAL_PORT_BIT(PAL_PAD(B0)) | PAL_PORT_BIT(PAL_PAD(B1)) | PAL_PORT_BIT(PAL_PAD(B3)) | \
                   PAL_PORT_BIT(PAL_PAD(B10)) | PAL_PORT_BIT(PAL_PAD(B11)) | PAL_PORT_BIT(PAL_PAD(B12)) | \
                   PAL_PORT_BIT(PAL_PAD(B13)) | PAL_PORT_BIT(PAL_PAD(B14)) | PAL_PORT_BIT(PAL_PAD(B15)))

#define colC_bits (PAL_PORT_BIT(PAL_PAD(C10)) | PAL_PORT_BIT(PAL_PAD(C11)) | PAL_PORT_BIT(PAL_PAD(C12)))
#define colD_bits (PAL_PORT_BIT(PAL_PAD(D2)))

#ifndef MATRIX_DEBOUNCE
#    define MATRIX_DEBOUNCE 10
#endif

// matrix state
extern matrix_row_t raw_matrix[MATRIX_ROWS];
extern matrix_row_t matrix[MATRIX_ROWS];

// Read all columns as one 32-bit value
static inline matrix_row_t read_cols(void) {
    uint16_t portA = palReadPort(GPIOA);
    uint16_t portB = palReadPort(GPIOB);
    uint16_t portC = palReadPort(GPIOC);
    uint16_t portD = palReadPort(GPIOD);

    matrix_row_t result = 0;

    // Each bit is 1 if key is pressed (active-low input)
    result |= ((portA & (PAL_PORT_BIT(PAL_PAD(A4)) | PAL_PORT_BIT(PAL_PAD(A5)) | PAL_PORT_BIT(PAL_PAD(A6)) | PAL_PORT_BIT(PAL_PAD(A7)))) ^ 0x00F0) >> 4;
    result |= ((portB & (PAL_PORT_BIT(PAL_PAD(B0)) | PAL_PORT_BIT(PAL_PAD(B1)))) ^ 0x0003) << 4;
    result |= ((portB & (PAL_PORT_BIT(PAL_PAD(B10)) | PAL_PORT_BIT(PAL_PAD(B11)) | PAL_PORT_BIT(PAL_PAD(B12)) | PAL_PORT_BIT(PAL_PAD(B13)) | PAL_PORT_BIT(PAL_PAD(B14)) | PAL_PORT_BIT(PAL_PAD(B15)))) ^ 0xFC00) >> 4;
    result |= ((portA & (PAL_PORT_BIT(PAL_PAD(A8)) | PAL_PORT_BIT(PAL_PAD(A9)) | PAL_PORT_BIT(PAL_PAD(A10)))) ^ 0x0700) << 3;
    result |= ((portA & PAL_PORT_BIT(PAL_PAD(A15))) ^ PAL_PORT_BIT(PAL_PAD(A15))) ? (1 << 14) : 0;
    result |= ((portC & (PAL_PORT_BIT(PAL_PAD(C10)) | PAL_PORT_BIT(PAL_PAD(C11)) | PAL_PORT_BIT(PAL_PAD(C12)))) ^ 0x1C00) >> 1;
    result |= ((portD & PAL_PORT_BIT(PAL_PAD(D2))) ^ PAL_PORT_BIT(PAL_PAD(D2))) ? (1 << 18) : 0;
    result |= ((portB & PAL_PORT_BIT(PAL_PAD(B3))) ^ PAL_PORT_BIT(PAL_PAD(B3))) ? (1 << 20) : 0;

    return result;
}

static inline void unselect_rows(void) {
    palSetPort(GPIOA, rowA_bits);
    palSetPort(GPIOC, rowC_bits);
}

static inline void select_row(uint8_t row) {
    if (row < 2) {
        palClearPort(GPIOC, PAL_PORT_BIT(PAL_PAD(C14 + row)));
    } else {
        palClearPort(GPIOA, PAL_PORT_BIT(PAL_PAD(A0 + (row - 2))));
    }
}

void matrix_init_custom(void) {
    palSetGroupMode(GPIOA, rowA_bits, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetGroupMode(GPIOC, rowC_bits, 0, PAL_MODE_OUTPUT_PUSHPULL);
    palSetPort(GPIOA, rowA_bits);
    palSetPort(GPIOC, rowC_bits);

    palSetGroupMode(GPIOA, colA_bits, 0, PAL_MODE_INPUT_PULLUP);
    palSetGroupMode(GPIOB, colB_bits, 0, PAL_MODE_INPUT_PULLUP);
    palSetGroupMode(GPIOC, colC_bits, 0, PAL_MODE_INPUT_PULLUP);
    palSetGroupMode(GPIOD, colD_bits, 0, PAL_MODE_INPUT_PULLUP);
}

uint8_t matrix_scan_custom(matrix_row_t current_matrix[]) {
    bool changed = false;

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        uint8_t debounce_guard = MATRIX_DEBOUNCE;
        while (debounce_guard > 0)
            debounce_guard = ((((palReadPort(GPIOA) & colA_bits) ^ colA_bits) |
                               ((palReadPort(GPIOB) & colB_bits) ^ colB_bits) |
                               ((palReadPort(GPIOC) & colC_bits) ^ colC_bits) |
                               ((palReadPort(GPIOD) & colD_bits) ^ colD_bits)) == 0)
                                  ? debounce_guard - 1
                                  : MATRIX_DEBOUNCE;

        select_row(row);
        matrix_output_select_delay();
        matrix_row_t cols = read_cols();
        unselect_rows();

        changed |= (current_matrix[row] != cols);
        current_matrix[row] = cols;
    }

    return changed;
}
