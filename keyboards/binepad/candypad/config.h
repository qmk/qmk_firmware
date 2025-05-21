// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* ----- Encoder ----- */
#define ENCODER_DEFAULT_POS 0x3 // enable 1:1 resolution

/* ----- OLED ----- */
#ifdef OLED_ENABLE
/* I2C (for OLED) */
#    define I2C1_SCL_PIN GP23
#    define I2C1_SDA_PIN GP22
#    define I2C_DRIVER I2CD1

/* Configure oled driver for the 128x32 oled */
#    define OLED_TIMEOUT (15 * 60 * 1000) // 15 minutes
#    define OLED_UPDATE_INTERVAL 33       // ~30fps

/* Font */
#    define OLED_FONT_H "keyboards/binepad/candypad/glcdfont.c"
#    define OLED_FONT_END 127
#endif // OLED_ENABLE

/* ---- Direct pins, for use in (custom) `matrix.c` (please read that file) ----- */
// !! : DIRECT_PINS_CUSTOM must match the MATRIX_ROWS / MATRIX_COLS matrix structure
// clang-format off
#define DIRECT_PINS_CUSTOM                \
    {                                     \
        {NO_PIN, NO_PIN, NO_PIN, NO_PIN}, \
        {NO_PIN, NO_PIN, NO_PIN, NO_PIN}, \
        {NO_PIN, NO_PIN, NO_PIN, NO_PIN}, \
        {NO_PIN, NO_PIN, NO_PIN, NO_PIN}, \
        {NO_PIN, NO_PIN, NO_PIN, NO_PIN}, \
        {GP26,   GP3,    NO_PIN, NO_PIN}  \
    }
// clang-format on
