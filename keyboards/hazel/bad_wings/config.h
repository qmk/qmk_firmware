// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#define SPI_SCK_PIN     GP2
#define SPI_MOSI_PIN    GP3
#define SPI_MISO_PIN    GP4

#define SHIFTREG_MATRIX_COL_CS  GP0
#define SHIFTREG_DIVISOR        8
#define SHIFTREG_ROWS           5
#define SHIFTREG_COLS           8

#define MATRIX_ROW_PINS_SR { GP26, GP27, GP28, GP29, GP6 }

#define POINTING_DEVICE_CS_PIN      GP1
#define CIRQUE_PINNACLE_DIAMETER_MM 35
#define POINTING_DEVICE_ROTATION_90