#ifndef DEBOUNCE_H
#define DEBOUNCE_H
#include <stdbool.h>
#include <stdint.h>
#include "matrix.h"
#ifdef __cplusplus
extern "C" {
#endif
  /* called to initialize any data stores your implementation has*/
  void matrix_debounce_init(void);
  /* call this every keyboard_task to debounce the matrix*/
  void matrix_debounce(void);
  /* matrix state on row */
  matrix_row_t matrix_debounce_get_row(uint8_t row);
  /* whether a switch is on */
  bool matrix_debounce_is_on(uint8_t row, uint8_t col);

#ifdef __cplusplus
}
#endif
#endif
