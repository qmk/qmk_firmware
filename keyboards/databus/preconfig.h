// Created/amended by OleVoip 2025.
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "info_config.h"

/**
 * This is deeply confusing: columns and rows of the electic matrix cannot
 * be identified with the columns and rows in which the keys are arranged
 * on the keyboard, but QMK use of MATRIX_ROWS and MATRIX_COLS suggests
 * exactly that, especially since they introduced settings like COL2ROW
 * that add to the confusion. Hence, this project uses the terms
 * DRIVE_LINES and SENSE_LINES instead of MATRIX_COLS and MATRIX_ROWS.
 */
#define DRIVE_LINES MATRIX_ROWS
#define SENSE_LINES MATRIX_COLS
#if SENSE_LINES != 8
#   error With an 8bit data bus, the matrix should have 8 sense lines.
#endif

#define CONCAT_MACRONAME(a,b) a##b
#define XCONCAT_MACRONAME(a,b) CONCAT_MACRONAME(a,b)

// .