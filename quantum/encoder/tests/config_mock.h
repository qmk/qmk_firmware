// Copyright 2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODERS_PAD_A \
    { 0 }
#define ENCODERS_PAD_B \
    { 1 }

#ifdef __cplusplus
extern "C" {
#endif

#include "mock.h"

#ifdef __cplusplus
};
#endif
