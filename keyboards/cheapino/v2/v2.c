// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "cheapino.h"

// v2: each half has its own rows. Rows 0-2 are the right half (columns 0-5),
// rows 4-6 the left half (columns 6-11). Row 3 holds the encoder.

#define ENC_ROW 3
#define ENC_A_BIT ((matrix_row_t)1 << 2)
#define ENC_B_BIT ((matrix_row_t)1 << 4)

void cheapino_read_encoder(matrix_row_t matrix[]) {
    cheapino_set_encoder_contacts(matrix[ENC_ROW] & ENC_A_BIT, matrix[ENC_ROW] & ENC_B_BIT);
    matrix[ENC_ROW] &= ~(ENC_A_BIT | ENC_B_BIT);
}

void cheapino_fix_ghosting(matrix_row_t matrix[]) {
    cheapino_remove_ghosts(matrix, 0, 3, 0, 6); // right half
    cheapino_remove_ghosts(matrix, 4, 3, 6, 6); // left half
}
