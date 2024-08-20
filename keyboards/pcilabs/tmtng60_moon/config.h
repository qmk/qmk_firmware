/*
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pcilabs_config_common.h"

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

#define MATRIX_ROWS 5
#define MATRIX_COLS 14

#define MUXES 4
#define MUX_PINS \
    { A4, A1, A2, A3 }
#define MUX_SELECTOR_BITS 4
#define MUX_SELECTOR_PINS \
    { B15, B14, B13, B12 }

#define MUX_CHANNELS (1 << MUX_SELECTOR_BITS)


#define DYNAMIC_KEYMAP_LAYER_COUNT 2
