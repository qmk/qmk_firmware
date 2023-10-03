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

#pragma once

#define MOUSEKEY_INTERVAL       20
#define MOUSEKEY_DELAY          0
#define MOUSEKEY_TIME_TO_MAX    60
#define MOUSEKEY_MAX_SPEED      7
#define MOUSEKEY_WHEEL_DELAY 0

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    get_mods() == (MOD_BIT(KC_LCTL) | MOD_BIT(KC_RCTL)) || \
    get_mods() == (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)) \
)

/* Serial config (for communication between halves) */
#define SERIAL_USART_DRIVER SD1  // Only true for the master half
#define SERIAL_USART_CONFIG { (SERIAL_USART_SPEED), } // Only field is speed
#define SERIAL_USART_FULL_DUPLEX

#define LED_BRIGHTNESS_LO       100
#define LED_BRIGHTNESS_HI       255

/* LED matrix driver */
#define LED_DRIVER_ADDR_1 0x74
#define LED_DRIVER_COUNT 1
#define LED_MATRIX_LED_COUNT 76
#define LED_MATRIX_SPLIT { 38, 38 }
#define LED_DISABLE_WHEN_USB_SUSPENDED

// LED Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_led_matrix?id=led-matrix-effects
#define ENABLE_LED_MATRIX_ALPHAS_MODS
#define ENABLE_LED_MATRIX_BREATHING
#define ENABLE_LED_MATRIX_BAND
#define ENABLE_LED_MATRIX_BAND_PINWHEEL
#define ENABLE_LED_MATRIX_BAND_SPIRAL
#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
#define ENABLE_LED_MATRIX_CYCLE_OUT_IN
#define ENABLE_LED_MATRIX_DUAL_BEACON
#if defined(LED_MATRIX_KEYREACTIVE_ENABLED)
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
#    define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
#    define ENABLE_LED_MATRIX_SPLASH
#    define ENABLE_LED_MATRIX_MULTISPLASH
#endif
#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_WAVE_UP_DOWN

/* i2c (for LED matrix) */
#define I2C1_CLOCK_SPEED 400000
#define I2C1_SCL_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_SDA_PAL_MODE PAL_MODE_ALTERNATIVE_2
#define I2C1_SCL_PIN B0
#define I2C1_SDA_PIN B1

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
