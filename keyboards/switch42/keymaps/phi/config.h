#pragma once

/* split keyboard setup */
#define USE_SERIAL              /* SERIAL or MATRIX_I2C */
#define USE_SERIAL_PD2
#define MASTER_LEFT             /* LEFT or RIGHT (or EE_HANDS) */

#define MATRIX_ROWS_SINGLE (MATRIX_ROWS >> 1) /* # of rows per hand */
#define BACKLIGHT_NUM (MATRIX_ROWS_SINGLE * MATRIX_COLS - (MATRIX_COLS >> 1))
#define UNDERGLOW_NUM 4

#undef RGBLED_NUM
#define RGBLED_NUM (BACKLIGHT_NUM + UNDERGLOW_NUM)
