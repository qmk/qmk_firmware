#ifndef MATRIX_H
#define MATRIX_H

#include <stdbool.h>

/* number of matrix rows */
uint8_t matrix_rows(void);
/* number of matrix columns */
uint8_t matrix_cols(void);
/* intialize matrix for scaning. should be called once. */
void matrix_init(void);
/* scan all key states on matrix */
uint8_t matrix_scan(void);
/* whether modified from previous scan. used after matrix_scan. */
bool matrix_is_modified(void);
/* whether ghosting occur on matrix. */
bool matrix_has_ghost(void);
/* whether a swtich is on */
bool matrix_is_on(uint8_t row, uint8_t col);
/* matrix state on row */
#if (MATRIX_COLS <= 8)
uint8_t matrix_get_row(uint8_t row);
#else
uint16_t matrix_get_row(uint8_t row);
#endif
/* count keys pressed */
uint8_t matrix_key_count(void);
/* print matrix for debug */
void matrix_print(void);


#endif
