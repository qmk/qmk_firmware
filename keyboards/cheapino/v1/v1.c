// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#include "cheapino.h"

// v1: both halves share rows 0-2. The left half uses columns 0-5 and the
// right half columns 6-11, so all 6 column pins can ghost together.
//
// Because of a routing quirk on the v1 PCB, the encoder contacts show up as
// a whole column held in rows 0-2: column 7 for the press, 9 and 11 for the
// A and B contacts. Holding all three keys of one of those columns at once
// is assumed never to happen. Row 3 isn't scanned; the press is put there
// as key [3, 0], same position as on v2.

#define ENC_PRESS_COL 7
#define ENC_A_COL 9
#define ENC_B_COL 11
#define FINGER_ROWS 3

static bool take_column(matrix_row_t matrix[], uint8_t col) {
    matrix_row_t bit = (matrix_row_t)1 << col;
    for (uint8_t row = 0; row < FINGER_ROWS; row++) {
        if (!(matrix[row] & bit)) return false;
    }
    for (uint8_t row = 0; row < FINGER_ROWS; row++) {
        matrix[row] &= ~bit;
    }
    return true;
}

void cheapino_read_encoder(matrix_row_t matrix[]) {
    if (take_column(matrix, ENC_PRESS_COL)) {
        matrix[3] |= 1;
    } else {
        matrix[3] &= ~(matrix_row_t)1;
    }

    bool a = take_column(matrix, ENC_A_COL);
    bool b = take_column(matrix, ENC_B_COL);
    cheapino_set_encoder_contacts(a, b);
}

void cheapino_fix_ghosting(matrix_row_t matrix[]) {
    cheapino_remove_ghosts(matrix, 0, FINGER_ROWS, 0, 12);
}
