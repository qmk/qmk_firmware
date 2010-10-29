#ifndef MATRIX_SKEL_H
#define MATRIX_SKEL_H 1

#include <stdbool.h>

/* number of matrix rows */
int  matrix_rows(void);
/* number of matrix columns */
int  matrix_cols(void);
/* intialize matrix for scaning. should be called once. */
void matrix_init(void);
/* scan all key states on matrix */
int  matrix_scan(void);
/* whether modified from previous scan. used after matrix_scan. */
bool matrix_is_modified(void);
/* whether ghosting occur on matrix. */
bool matrix_has_ghost(void);
/* whether a swtich is on */
bool matrix_is_on(int row, int col);
/* matrix state on row */
uint16_t matrix_get_row(int row);
/* count keys pressed */
int matrix_key_count(void);
/* print matrix for debug */
void matrix_print(void);


#endif
