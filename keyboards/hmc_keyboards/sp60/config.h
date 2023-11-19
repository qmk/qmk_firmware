/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once
/* Includes -----------------------------------------------------------------*/

/* #include "config_common.h" */

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS { B5, B4, B3, A15, A1, A2 }
#define MATRIX_COL_PINS { A10, A9, A8, B15, B14, B13, B12, B11, B10, B2, B0, A7, A6, B1, A5, A4, A3 }


        /**<   二极管方向  */
#define DIODE_DIRECTION COL2ROW
