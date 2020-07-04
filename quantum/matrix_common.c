#include "matrix.h"
#include "debounce.h"
#include "wait.h"
#include "print.h"
#include "debug.h"

#ifndef MATRIX_IO_DELAY
#    define MATRIX_IO_DELAY 30
#endif

/* matrix state(1:on, 0:off) */
matrix_row_t raw_matrix[MATRIX_ROWS];
matrix_row_t matrix[MATRIX_ROWS];

#ifdef MATRIX_MASKED
extern const matrix_row_t matrix_mask[];
#endif

// user-defined overridable functions

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

__attribute__((weak)) void matrix_scan_user(void) {}

// helper functions

inline uint8_t matrix_rows(void) { return MATRIX_ROWS; }

inline uint8_t matrix_cols(void) { return MATRIX_COLS; }

inline bool matrix_is_on(uint8_t row, uint8_t col) { return (matrix[row] & ((matrix_row_t)1 << col)); }

inline matrix_row_t matrix_get_row(uint8_t row) {
    // Matrix mask lets you disable switches in the returned matrix data. For example, if you have a
    // switch blocker installed and the switch is always pressed.
#ifdef MATRIX_MASKED
    return matrix[row] & matrix_mask[row];
#else
    return matrix[row];
#endif
}

// Deprecated.
bool matrix_is_modified(void) {
    if (debounce_active()) return false;
    return true;
}

#if (MATRIX_COLS <= 8)
#    define print_matrix_header() print("\nr/c 01234567\n")
#    define print_matrix_row(row) print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop(matrix_get_row(row))
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop16(matrix_get_row(row))
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header() print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row) print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(row) bitpop32(matrix_get_row(row))
#endif

void matrix_print(void) {
    print_matrix_header();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        phex(row);
        print(": ");
        print_matrix_row(row);
        print("\n");
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        count += matrix_bitpop(i);
    }
    return count;
}

__attribute__((weak)) void matrix_io_delay(void) { wait_us(MATRIX_IO_DELAY); }

// CUSTOM MATRIX 'LITE'
__attribute__((weak)) void matrix_init_custom(void) {}

__attribute__((weak)) bool matrix_scan_custom(matrix_row_t current_matrix[]) { return true; }

__attribute__((weak)) void matrix_init(void) {
    matrix_init_custom();

    // initialize matrix state: all keys off
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        raw_matrix[i] = 0;
        matrix[i]     = 0;
    }

    debounce_init(MATRIX_ROWS);

    matrix_init_quantum();
}

__attribute__((weak)) uint8_t matrix_scan(void) {
    bool changed = matrix_scan_custom(raw_matrix);

    debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

    matrix_scan_quantum();
    return changed;
}

__attribute__((weak)) bool peek_matrix(uint8_t row_index, uint8_t col_index, bool raw) {
    return 0 != ( (raw? raw_matrix[row_index]:matrix[row_index])
                  & (MATRIX_ROW_SHIFTER << col_index));
}
