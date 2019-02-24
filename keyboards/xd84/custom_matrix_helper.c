#include <stdint.h>
#include <stdbool.h>
#include "wait.h"
#include "print.h"
#include "debug.h"
#include "util.h"
#include "matrix.h"
#include "debounce.h"
#include "quantum.h"

//_____COMMON__________________________________________________________________
// user-defined overridable functions
__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }
__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }
__attribute__((weak)) void matrix_init_user(void) {}
__attribute__((weak)) void matrix_scan_user(void) {}


//_____COULD BE COMMON_________________________________________________________
/* matrix state(1:on, 0:off) */
/*static*/ matrix_row_t raw_matrix[MATRIX_ROWS];
/*static*/ matrix_row_t matrix[MATRIX_ROWS];

#if (MATRIX_COLS <= 8)
#    define print_matrix_header()  print("\nr/c 01234567\n")
#    define print_matrix_row(row)  print_bin_reverse8(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop(matrix[i])
#    define ROW_SHIFTER ((uint8_t)1)
#elif (MATRIX_COLS <= 16)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse16(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop16(matrix[i])
#    define ROW_SHIFTER ((uint16_t)1)
#elif (MATRIX_COLS <= 32)
#    define print_matrix_header()  print("\nr/c 0123456789ABCDEF0123456789ABCDEF\n")
#    define print_matrix_row(row)  print_bin_reverse32(matrix_get_row(row))
#    define matrix_bitpop(i)       bitpop32(matrix[i])
#    define ROW_SHIFTER  ((uint32_t)1)
#endif

__attribute__ ((weak))
uint8_t matrix_rows(void) {
  return MATRIX_ROWS;
}

__attribute__ ((weak))
uint8_t matrix_cols(void) {
  return MATRIX_COLS;
}

__attribute__ ((weak))
matrix_row_t matrix_get_row(uint8_t row) {
  return matrix[row];
}

__attribute__ ((weak))
uint8_t matrix_key_count(void) {
  uint8_t count = 0;
  for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
    count += matrix_bitpop(i);
  }
  return count;
}

__attribute__ ((weak))
void matrix_print(void) {
  print_matrix_header();

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    phex(row); print(": ");
    print_matrix_row(row);
    print("\n");
  }
}


//_____CUSTOM MATRIX 'LITE'____________________________________________________
__attribute__ ((weak))
void custom_matrix_init(void) {
}

__attribute__ ((weak))
bool custom_matrix_scan(matrix_row_t current_matrix[]) {
    bool changed = true;
    return changed;
}

__attribute__ ((weak))
void matrix_init(void) {

  custom_matrix_init();

  // initialize matrix state: all keys off
  for (uint8_t i=0; i < MATRIX_ROWS; i++) {
    raw_matrix[i] = 0;
    matrix[i] = 0;
  }

  debounce_init(MATRIX_ROWS);

  matrix_init_quantum();
}

__attribute__ ((weak))
uint8_t matrix_scan(void) {
  bool changed = custom_matrix_scan(raw_matrix);

  debounce(raw_matrix, matrix, MATRIX_ROWS, changed);

  matrix_scan_quantum();
  return 1;
}
