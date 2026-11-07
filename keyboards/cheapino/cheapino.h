// Copyright 2023 Thomas Haukland (@tompi)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// Implemented by each revision, called from the matrix scan.
void cheapino_read_encoder(matrix_row_t matrix[]);
void cheapino_fix_ghosting(matrix_row_t matrix[]);

// Shared helpers for the revisions.
void cheapino_remove_ghosts(matrix_row_t matrix[], uint8_t first_row, uint8_t num_rows, uint8_t first_col, uint8_t num_cols);
void cheapino_set_encoder_contacts(bool a_closed, bool b_closed);
