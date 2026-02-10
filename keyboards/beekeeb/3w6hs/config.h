// Copyright 2023 beekeeb
// Copyright 2021 weteor
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 10

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)

#define MATRIX_ROW_PINS_L { GP7, GP8, GP9, GP10}
#define MATRIX_COL_PINS_L { GP11, GP12, GP13, GP14, GP15 }

#define MATRIX_ROW_PINS_R { P10, P11, P12, P05 }
#define MATRIX_COL_PINS_R { P06, P13, P14, P01, P00 }

#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP0
#define I2C1_SCL_PIN GP1
