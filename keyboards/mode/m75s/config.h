/*
 Copyright 2020 Álvaro "Gondolindrim" Volpato <alvaro.volpato@usp.br>

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

/* USB Device descriptor parameter */
#define VENDOR_ID       0x00DE
#define PRODUCT_ID      0x7583 // For 75S
#define DEVICE_VER      0x0001
#define MANUFACTURER    Mode
#define PRODUCT         Mode 75S

/* key matrix size */
#define MATRIX_ROWS 7
#define MATRIX_COLS 16
                        //C0, C1, C2,  C3,  C4,  C5,  C6,  C7, C8,  C9, C10, C11, C12, C13, C14, C15
#define MATRIX_COL_PINS { C8, A8, A10, B13, B12, B10, B1, C10, C11, D2, C12, B3,  B4,  B5,  B8,  B9 }
                        //R0, R1, R2,  R3,  R4,  R5 , R6
#define MATRIX_ROW_PINS { C5, B0, B14, B15, C7 , C9 , A15} 
#define DIODE_DIRECTION COL2ROW

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define EEPROM_I2C_24LC128
//#define I2C1_CLOCK_SPEED 400000
//#define I2C1_DUTY_CYCLE FAST_DUTY_CYCLE_2

#define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT

#define TAP_CODE_DELAY 50

#define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR 16383 // Overriding to use more EEPROM
