// Copyright 2023 Wilhelm Schuster
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Custom matrix pins and port select array */
#define MATRIX_KEY_ENABLE_PIN A4
#define MATRIX_KEY_STATE_PIN B15
#define MATRIX_KEY_HYS_PIN A8
#define MATRIX_MUX_ROW_PINS {A5, A6, A7}
#define MATRIX_MUX_COL_PINS {B0, B12, B13, B14}

/* While the original BOM uses an M24C64 EEPROM not directly supported by QMK,
 * said EEPROM uses the same parameters as the already supported 24LC64. */
#define EEPROM_I2C_24LC64

/* Bootmagic Lite key configuration */
// Esc key, i.e. the first key in the top row.
#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 13

//#define DEBUG_MATRIX_SCAN_RATE
