/*
Copyright 2024 Mkass420 (@Mkass420)
SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "pcilabs_common/pcilabs_config_common.h"

#define RAW_USAGE_PAGE 0xFF60
#define RAW_USAGE_ID 0x61

#define MATRIX_ROWS 1
#define MATRIX_COLS 2
#define MUXES 0
#define HALL_PINS \
    { A2, A1 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 1
