/*
Copyright 2015 Jun Wako <wakojun@gmail.com>

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

#ifndef INFINITY_ERGODOX_CONFIG_H
#define INFINITY_ERGODOX_CONFIG_H


/* USB Device descriptor parameter */
#define VENDOR_ID       0x1c11
#define PRODUCT_ID      0xb04d
#define DEVICE_VER      0x0001
#define MANUFACTURER Input Club
#define PRODUCT Infinity_Ergodox/QMK

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

#define TAPPING_TOGGLE  1

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

#define TAPPING_TERM    200
#define IGNORE_MOD_TAP_INTERRUPT // this makes it possible to do rolling combos (zx) with keys that convert to other keys on hold (z becomes ctrl when you hold it, and when this option isn't enabled, z rapidly followed by x actually sends Ctrl-x. That's bad.)

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* key matrix size */
#define MATRIX_ROWS 18
#define MATRIX_COLS 5

// For some reason, the rows are colums in the schematic, and vice versa
#define MATRIX_ROW_PINS { B2, B3, B18, B19, C0, C9, C10, C11, D0 }
#define MATRIX_COL_PINS { D1, D4, D5, D6, D7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL */
#define DIODE_DIRECTION ROW2COL

/* Serial config (for communication between halves) */
#define SERIAL_USART_DRIVER SD1  // Only true for the master half
#define SERIAL_USART_CONFIG { (SERIAL_USART_SPEED), } // Only field is speed
#define SERIAL_USART_FULL_DUPLEX

/* number of backlight levels */
#define BACKLIGHT_LEVELS 3

#define LED_BRIGHTNESS_LO       100
#define LED_BRIGHTNESS_HI       255

/* LED matrix driver */
#define LED_DRIVER_ADDR_1 0x74
#define LED_DRIVER_COUNT 1
#define DRIVER_LED_TOTAL 76
#define LED_MATRIX_SPLIT { 38, 38 }
#define LED_DISABLE_WHEN_USB_SUSPENDED

/* i2c (for LED matrix) */
#define I2C1_CLOCK_SPEED 400000
#define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_BANK GPIOB
#define I2C1_SCL 0
#define I2C1_SDA 1

#ifdef ST7565_ENABLE
/* LCD driver */
#    define ST7565_A0_PIN C7
#    define ST7565_RST_PIN C8
#    define ST7565_SS_PIN C4
#    define ST7565_SPI_CLK_DIVISOR 2
#    define ST7565_CONTRAST 22
#    define ST7565_DISPLAY_WIDTH 128
#    define ST7565_DISPLAY_HEIGHT 32

/* SPI (for LCD) */
#    define SPI_DRIVER SPID1
#    define SPI_SCK_PIN C5
#    define SPI_SCK_PAL_MODE PAL_MODE_ALTERNATIVE_2
#    define SPI_MOSI_PIN C6
#    define SPI_MOSI_PAL_MODE PAL_MODE_ALTERNATIVE_2
#    define SPI_MISO_PIN A4  // Just an unused pin, the "normal" MISO pin (C7) is used for other things
#    define SPI_MISO_PAL_MODE PAL_MODE_ALTERNATIVE_7  // Default for A4
#endif

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    5

#define VISUALIZER_USER_DATA_SIZE 16

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
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
