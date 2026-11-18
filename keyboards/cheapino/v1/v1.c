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
//
// The rows are read one after another, so while a contact is changing it can
// show up in only some of the rows. That means it's mid-change: keep its last
// state, or a single click can count as two steps. Partly held columns are
// passed on as normal keys while the contact is open (e.g. two thumb keys
// held together). While a contact is closed its column can't be read, so
// those keys don't work until the encoder moves on.

#define ENC_PRESS_COL 7
#define ENC_A_COL 9
#define ENC_B_COL 11
#define FINGER_ROWS 3

static void read_contact(matrix_row_t matrix[], uint8_t col, bool *closed) {
    matrix_row_t bit  = (matrix_row_t)1 << col;
    uint8_t      rows = 0;
    for (uint8_t row = 0; row < FINGER_ROWS; row++) {
        if (matrix[row] & bit) rows++;
    }

    if (rows == FINGER_ROWS) {
        *closed = true;
    } else if (rows == 0) {
        *closed = false;
    }

    if (*closed) {
        for (uint8_t row = 0; row < FINGER_ROWS; row++) {
            matrix[row] &= ~bit;
        }
    }
}

void cheapino_read_encoder(matrix_row_t matrix[]) {
    static bool pressed = false, a = false, b = false;

    read_contact(matrix, ENC_PRESS_COL, &pressed);
    read_contact(matrix, ENC_A_COL, &a);
    read_contact(matrix, ENC_B_COL, &b);

    if (pressed) {
        matrix[3] |= 1;
    } else {
        matrix[3] &= ~(matrix_row_t)1;
    }
    cheapino_set_encoder_contacts(a, b);
}

void cheapino_fix_ghosting(matrix_row_t matrix[]) {
    cheapino_remove_ghosts(matrix, 0, FINGER_ROWS, 0, 12);
}
