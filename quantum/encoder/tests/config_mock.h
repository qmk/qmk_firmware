// Copyright 2022-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "config_encoder_common.h"

#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODER_A_PINS \
    { 0 }
#define ENCODER_B_PINS \
    { 1 }

#ifdef __cplusplus
extern "C" {
#endif

#include "mock.h"

#ifdef __cplusplus
};
#endif
