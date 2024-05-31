/* Protokeeb Copyright 2024 A-Tech Officials (@atechofficials)
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. 
 * If not, see <https://www.gnu.org/licenses/gpl-3.0.html>.
 */

#pragma once

/*
#define VENDOR_ID 0x419A
#define PRODUCT_ID 0x1717
#define DEVICE_VERSION 0x0100 // v1.0.0
#define MANUFACTURER "A-Tech Officials"
#define PRODUCT "Protokeeb"
*/

#define MATRIX_ROWS 4
#define MATRIX_COLS 4

/*
#define MATRIX_ROW_PINS \
		{ GP2, GP3, GP4, GP5 }

#define MATRIX_COL_PINS \
		{ GP6, GP7, GP8, GP9 }

#define DIODE_DIRECTION COL2ROW
*/

//#define DEBOUNCE 20

#ifdef RGBLIGHT_ENABLE
/* ARGB LED Data-In Pin */
//#define WS2812_DI_PIN GP10

/* ARGB LED Byte order */
// #define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_GRB // for WS2812
#define WS2812_BYTE_ORDER WS2812_BYTE_ORDER_RGB // for WS2812B-2020

/* Total number of ARGB LEDs connected */
//#define RGBLIGHT_LED_COUNT 4

/* Total number of ARGB LEDs in Matrix */
//#define RGB_MATRIX_LED_COUNT 16

/* Peripheral used */
#define WS2812_PIO_USE_PIO1

//#define RGBLIGHT_HUE_STEP 15
//#define RGBLIGHT_SAT_STEP 15
//#define RGBLIGHT_VAL_STEP 15

/* ARGB LED T-reset period between frames */
// #define WS2812_TRST_US 280

/* The maximum ARGB LED brightness level */
//#define RGBLIGHT_LIMIT_VAL 127

/* RGB LEDs Default/Fallback Values */
//#define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_STATIC_LIGHT
//#define RGBLIGHT_DEFAULT_HUE 0
//#define RGBLIGHT_DEFAULT_SAT 255
//#define RGBLIGHT_DEFAULT_VAL 50
//#define RGBLIGHT_DEFAULT_SPD 0

// Enable RGB lighting upon clearing the EEPROM
//#define RGBLIGHT_DEFAULT_ON true

/* If defined, the RGB lighting will be switched off when the host goes to sleep */
//#define RGBLIGHT_SLEEP

/* RGB lighting effects and animations Enable */
//#define RGBLIGHT_EFFECT_BREATHING
//#define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#define RGBLIGHT_EFFECT_SNAKE
//#define RGBLIGHT_EFFECT_KNIGHT
//#define RGBLIGHT_EFFECT_CHRISTMAS
//#define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#define RGBLIGHT_EFFECT_RGB_TEST
//#define RGBLIGHT_EFFECT_ALTERNATING
//#define RGBLIGHT_EFFECT_TWINKLE

/* RGB lighting effects and animations settings */
#define RGBLIGHT_EFFECT_BREATHE_MAX RGBLIGHT_LIMIT_VAL
#define RGBLIGHT_EFFECT_CHRISTMAS_INTERVAL 40
#define RGBLIGHT_EFFECT_CHRISTMAS_STEP 2
#define RGBLIGHT_EFFECT_KNIGHT_LED_NUM RGBLIGHT_LED_COUNT
#define RGBLIGHT_EFFECT_KNIGHT_LENGTH 3
#define RGBLIGHT_EFFECT_KNIGHT_OFFSET 0
#define RGBLIGHT_EFFECT_SWIRL_RANGE 255
#define RGBLIGHT_EFFECT_SNAKE_LENGTH 4
#define RGBLIGHT_EFFECT_TWINKLE_LIFE 200
#define RGBLIGHT_EFFECT_TWINKLE_PROBABILITY 1/127

#endif

/* Tap Dance timing */
#define TAPPING_TERM 200

/* I2C Interface configuration */
#define I2C_DRIVER I2CD0

//#define I2C_SCL_PIN NO_PIN
#define I2C_SCL_PIN GP21
//#define I2C_SCL_PAL_MODE 4

//#define I2C_SDA_PIN NO_PIN
#define I2C_SDA_PIN GP20
//#define I2C_SDA_PAL_MODE 4

/* SPI Interface configuration */
#define SPI_DRIVER SPID0

#define SPI_SCK_PIN NO_PIN
//#define SPI_SCK_PIN GP18
//#define SPI_SCK_PAL_MODE 5

#define SPI_MOSI_PIN NO_PIN
//#define SPI_MOSI_PIN GP19
//#define SPI_MOSI_PAL_MODE 5

#define SPI_MISO_PIN NO_PIN
//#define SPI_MISO_PIN GP20
//#define SPI_MISO_PAL_MODE 5

/* Bootloader Enter Button
 * Press and hold when pluging the keyboard
 * to enter the bootloader for flashing
 */
//#define BOOTMAGIC_ROW 0
//#define BOOTMAGIC_COLUMN 0

/* Double tap reset bootloader entry */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET

/* Bootloader timeout window in milli-seconds */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

/* LED to blink when entering bootloader mode */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25

/* RP2040 External SPI Flash Type */
//#define RP2040_FLASH_W25Q080 // Default
//#define RP2040_FLASH_GENERIC_03H

/* Mechanical lcoking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE

/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE

#if defined (ENCODER_ENABLE)
//#define ENCODER_PAD_A { GP12 }
//#define ENCODER_PAD_B { GP13 }

// For Multiple Encoders Setup
// #define ENCODERS_PAD_A { encoder1a, encoder2a }
// #define ENCODERS_PAD_B { encoder1b, encoder2b }

// #define ENCODER_DIRECTION_FLIP

//#define ENCODER_RESOLUTION 2

// For setting individual resolution for each encoder
// #define ENCODER_RESOLUTIONS { 4, 2 }

// #define ENCODER_DEFAULT_POS 0x3
#define ENCODER_MAP_KEY_DELAY 10
#endif

/*
#if defined(DIP_SWITCH_ENABLE)
#define DIP_SWITCH_PINS { GP14 }
#endif
*/