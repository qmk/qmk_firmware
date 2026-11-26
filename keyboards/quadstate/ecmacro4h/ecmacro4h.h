// Copyright 2026 QuadState (@QuadState)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "quantum.h"

// One row of EC keys. A reading is an rc_pio tick count (16 ns units) that
// rises as the key is pressed; config.h sets the pins and the thresholds.
#define EC_KEY_COUNT MATRIX_COLS

// Baselines and thresholds (ecmacro4h.c)
void     ec_baseline_sample(uint8_t key, uint16_t ticks);
uint16_t ec_press_threshold(uint8_t key);
uint16_t ec_release_threshold(uint8_t key);
