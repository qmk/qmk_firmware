/* Copyright 2022 Johannes Schneider (@JohSchneider) */
/* SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#include "quantum.h"


#include <gpio.h>
// defined in the used mainboard/MCU
extern const pin_t row_pins_MCU[MATRIX_ROWS / 2];
extern const pin_t col_pins_MCU[MATRIX_COLS];
