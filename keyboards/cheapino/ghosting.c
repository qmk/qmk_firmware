//
// Created by Thomas Haukland on 2024-05-05.
//

#include "matrix.h"
#include "quantum.h"
#include "print.h"

// This is just to be able to declare constants as they appear in the qmk console
#define rev(b) \
            ((b & 1) << 15) | \
            ((b & (1 << 1)) << 13) | \
            ((b & (1 << 2)) << 11) | \
            ((b & (1 << 3)) << 9) | \
            ((b & (1 << 4)) << 7) | \
            ((b & (1 << 5)) << 5) | \
            ((b & (1 << 6)) << 3) | \
            ((b & (1 << 7)) << 1) | \
            ((b & (1 << 8)) >> 1) | \
            ((b & (1 << 9)) >> 3) | \
            ((b & (1 << 10)) >> 5) | \
            ((b & (1 << 11)) >> 7) | \
            ((b & (1 << 12)) >> 9) | \
            ((b & (1 << 13)) >> 11) | \
            ((b & (1 << 14)) >> 13) | \
            b >> 15

/* This is for debugging the matrix rows
void printBits(uint16_t n)
{
    long i;
    for (i = 15; i >= 0; i--) {
        if ((n & (1 << i)) != 0) {
            printf("1");
        }
        else {
            printf("0");
        }
    }
    printf("\n");
}
*/

bool bit_pattern_set(uint16_t number, uint16_t bitPattern) {
    return !(~number & bitPattern);
}

void fix_ghosting_instance(
        matrix_row_t current_matrix[],
        unsigned short row_num_with_possible_error_cause,
        uint16_t possible_error_cause,
        unsigned short row_num_with_possible_error,
        uint16_t possible_error,
        uint16_t error_fix) {
    if (bit_pattern_set(current_matrix[row_num_with_possible_error_cause], possible_error_cause)) {
        if (bit_pattern_set(current_matrix[row_num_with_possible_error], possible_error)) {
            current_matrix[row_num_with_possible_error] = current_matrix[row_num_with_possible_error] ^ error_fix;
        }
    }
}

void fix_ghosting_column(
        matrix_row_t matrix[],
        uint16_t possible_error_cause,
        uint16_t possible_error,
        uint16_t error_fix) {
    // First the right side
    for (short i = 0; i<3; i++) {
        fix_ghosting_instance(matrix, i, possible_error_cause, (i+1)%3, possible_error, error_fix);
        fix_ghosting_instance(matrix, i, possible_error_cause, (i+2)%3, possible_error, error_fix);
    }

    // Then exactly same procedure on the left side
    for (short i = 0; i<3; i++) {
        fix_ghosting_instance(matrix, i+4, possible_error_cause<<6, 4+((i+1)%3), possible_error<<6, error_fix<<6);
        fix_ghosting_instance(matrix, i+4, possible_error_cause<<6, 4+((i+2)%3), possible_error<<6, error_fix<<6);
    }
}

// For QWERTY layout, key combo a+s+e also outputs q. This suppresses the q, and other similar ghosts
// These are observed ghosts(following a pattern). TODO: need to fix this for v3
// Might need to add 2 diodes(one in each direction) for every row, to increase voltage drop.
void fix_ghosting(matrix_row_t matrix[]) {
    fix_ghosting_column(matrix,
                        rev(0B0110000000000000),
                        rev(0B1010000000000000),
                        rev(0B0010000000000000));
    fix_ghosting_column(matrix,
                        rev(0B0110000000000000),
                        rev(0B0101000000000000),
                        rev(0B0100000000000000));

    fix_ghosting_column(matrix,
                        rev(0B0001100000000000),
                        rev(0B0010100000000000),
                        rev(0B0000100000000000));
    fix_ghosting_column(matrix,
                        rev(0B0001100000000000),
                        rev(0B0001010000000000),
                        rev(0B0001000000000000));

    fix_ghosting_column(matrix,
                        rev(0B1000010000000000),
                        rev(0B1000100000000000),
                        rev(0B1000000000000000));
    fix_ghosting_column(matrix,
                        rev(0B1000010000000000),
                        rev(0B0100010000000000),
                        rev(0B0000010000000000));

    fix_ghosting_column(matrix,
                        rev(0B1001000000000000),
                        rev(0B0101000000000000),
                        rev(0B0001000000000000));
    fix_ghosting_column(matrix,
                        rev(0B1001000000000000),
                        rev(0B1010000000000000),
                        rev(0B1000000000000000));

    fix_ghosting_column(matrix,
                        rev(0B0100100000000000),
                        rev(0B0100010000000000),
                        rev(0B0100000000000000));
    fix_ghosting_column(matrix,
                        rev(0B0100100000000000),
                        rev(0B1000100000000000),
                        rev(0B0000100000000000));
}
