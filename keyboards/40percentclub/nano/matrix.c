#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <string.h>
#include "matrix.h"
#include "nano.h"

void custom_matrix_init(void) {
    DDRF  &= ~(1<<4 | 1<<5 | 1<<6 | 1<<7);
    PORTF |=  (1<<4 | 1<<5 | 1<<6 | 1<<7);
    DDRC  &= ~(1<<6);
    PORTC |=  (1<<6);
    DDRD  &= ~(1<<0 | 1<<1 | 1<<4);
    PORTD |=  (1<<0 | 1<<1 | 1<<4);
}

bool custom_matrix_scan(matrix_row_t current_matrix[]) {
    matrix_row_t matrix_stage[MATRIX_ROWS];

    matrix_stage[0] =
        (PINF&(1<<4) ? 0 : (1<<0)) |
        (PINF&(1<<5) ? 0 : (1<<1)) |
        (PINF&(1<<6) ? 0 : (1<<2)) |
        (PINF&(1<<7) ? 0 : (1<<3));
    matrix_stage[1] =
        (PIND&(1<<1) ? 0 : (1<<0)) |
        (PIND&(1<<0) ? 0 : (1<<1)) |
        (PIND&(1<<4) ? 0 : (1<<2)) |
        (PINC&(1<<6) ? 0 : (1<<3));

    bool changed = memcmp(current_matrix, matrix_stage, sizeof(matrix_stage)) != 0;
    if(changed) {
        memcpy(matrix_stage, current_matrix, sizeof(matrix_stage));
    }

    return changed;
}