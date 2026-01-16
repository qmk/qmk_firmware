// Copyright 2022-2023 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once
#include "config_encoder_common.h"

#define MATRIX_ROWS 1
#define MATRIX_COLS 1

/* Here, "pins" from 0 to 31 are allowed. */
#define ENCODER_A_PINS \
    {                  \
    }
#define ENCODER_B_PINS \
    {                  \
    }
#define ENCODER_A_PINS_RIGHT {0, 2}
#define ENCODER_B_PINS_RIGHT {1, 3}

#ifdef __cplusplus
extern "C" {
#endif

#include "mock_split.h"

#ifdef __cplusplus
};
#endif
