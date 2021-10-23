/* Copyright 2021 Harrison Chan (Xelus)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

/* USB Device descriptor parameter */
#define VENDOR_ID       0x5845 // "XE"
#define PRODUCT_ID      0x5052 // "PR"
#define DEVICE_VER      0x0001
#define MANUFACTURER    Xelus
#define PRODUCT         Xelus Pachi RGB

/* key matrix size */
#define MATRIX_ROWS 6
#define MATRIX_COLS 17

/* key matrix pins */
#define MATRIX_ROW_PINS { B14, B13, B12, B2, A8, B15 }
#define MATRIX_COL_PINS { C13, C14, C15, H0, A0, A1, A2, A3, A4, A5, A6, A7, B0, B1, H1, B10, B11 }
#define UNUSED_PINS

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE 5

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

// I2C setup
#define I2C1_SCL            8
#define I2C1_SDA            9
#define I2C1_SCL_PAL_MODE   4
#define I2C1_SDA_PAL_MODE   4
#define I2C1_TIMINGR_PRESC  0U
#define I2C1_TIMINGR_SCLDEL 11U
#define I2C1_TIMINGR_SDADEL 0U
#define I2C1_TIMINGR_SCLH   14U
#define I2C1_TIMINGR_SCLL   42U

// I2C EEPROM
#define EEPROM_I2C_24LC64

// RGB Matrix defines
#define DRIVER_ADDR_1 0b0110000
#define DRIVER_ADDR_2 0b0110001

#define DRIVER_COUNT 1
#define DRIVER_1_LED_TOTAL 117
#define DRIVER_LED_TOTAL DRIVER_1_LED_TOTAL
#define ISSI_DRIVER_TOTAL DRIVER_LED_TOTAL

#define RGB_MATRIX_STARTUP_VAL 80
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_DISABLE_WHEN_USB_SUSPENDED  // turn off effects when suspended
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_CYCLE_ALL

#define FORCE_NKRO
