
#pragma once

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 10

#define MATRIX_ROWS_PER_SIDE (MATRIX_ROWS / 2)
#define MATRIX_COLS_PER_SIDE (MATRIX_COLS / 2)

// wiring
#define MATRIX_ROW_PINS_MCU \
    { B7, B6, B5, A2 }
#define MATRIX_COL_PINS_MCU \
    { B8, B4, B3, A15, A14 }
#define MATRIX_ROW_PINS_MCP \
    { B0, B1, B2, B3 }
#define MATRIX_COL_PINS_MCP \
    { A0, A1, A2, A3, A4 }

#define MATRIX_ROW_PINS \
    { B7, B6, B5, A2, A0, A0, A0, A0 }
#define MATRIX_COL_PINS \
    { B8, B4, B3, A15, A14, A1, A1, A1, A1, A1 }

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 5

/* i2c settings */

#define I2C_DRIVER I2CD2
#define I2C1_SCL_PIN B10
#define I2C1_SDA_PIN B11
#define I2C1_TIMINGR_PRESC 2U
#define I2C1_TIMINGR_SCLDEL 1U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH 9U
#define I2C1_TIMINGR_SCLL 26U
#define I2C1_SCL_PAL_MODE 1
#define I2C1_SDA_PAL_MODE 1
