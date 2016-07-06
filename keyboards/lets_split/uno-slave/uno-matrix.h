#ifndef UNO_MATRIX
#define UNO_MATRIX

#define MATRIX_ROWS 4
#define MATRIX_COLS 6

#include <stdbool.h>

typedef uint8_t matrix_row_t;

uint8_t matrix_rows(void);
uint8_t matrix_cols(void);
void matrix_init(void);
uint8_t matrix_scan(void);
bool matrix_is_modified(void);
bool matrix_is_on(uint8_t row, uint8_t col);
matrix_row_t matrix_get_row(uint8_t row);

#endif
