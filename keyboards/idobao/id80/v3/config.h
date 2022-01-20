/*
Copyright 2020 Sergey Vlasov <sigprof@gmail.com>
Copyright 2022 peepeetee

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0x6964 /* "id" */
#define PRODUCT_ID      0x0080
#define DEVICE_VER      0x0003
#define MANUFACTURER    IDOBAO
#define PRODUCT         ID80 v3


/* key matrix size */
#define MATRIX_ROWS 9
#define MATRIX_COLS 11

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
 * The matrix description in the vendor-supplied JSON file for kbfirmware.com
 * had 9 columns:
 *     { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
 * and 12 rows:
 *     { B7, B3, B2, B1, B0, E6, F0, F1, F4, F5, F6, F7 }
 * However, the row 6 was completely empty, and the pin F0 was not actually
 * routed anywhere on the PCB, therefore this row was removed to save some
 * resources (the EEPROM space for dynamic keymaps is especially scarce).
 *
 * After doing the above change, the matrix was transposed (rows and columns
 * were swapped), because a matrix with the COL2ROW layout can be scanned much
 * more efficiently than a matrix with the ROW2COL layout (depending on various
 * optimizations, the difference in scan rate can be over 2 times).  Because of
 * this, the "columns" in the matrix layout now mostly correspond to physical
 * rows, and the "rows" have mostly vertical physical orientation.
 */
#define MATRIX_ROW_PINS { D0, D1, D2, D3, D5, D4, D6, D7, B4 }
#define MATRIX_COL_PINS { B7, B3, B2, B1, B0, E6, F1, F4, F5, F6, F7 }

#define DIODE_DIRECTION COL2ROW


#define RGB_DI_PIN E2
#ifdef RGB_DI_PIN
#define RGBLIGHT_ANIMATIONS
#define RGBLED_NUM 103 /* 16 Bottom 87 top*/
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#endif

/* Bootmagic Lite key configuration: use the Esc key */
#define BOOTMAGIC_LITE_ROW      0
#define BOOTMAGIC_LITE_COLUMN   5

#define ENCODERS_PAD_A { C7 }
#define ENCODERS_PAD_B { C6 }




