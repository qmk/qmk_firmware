// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include "config_common.h"

#define MATRIX_ROWS 10
#define MATRIX_COLS 7

/* COL2ROW or ROW2COL */
#define DIODE_DIRECTION COL2ROW

/* wiring of each half */
#define MATRIX_ROW_PINS { GP4, GP5, GP6, GP7, GP8 }
#define MATRIX_COL_PINS { GP9, GP10, GP11, GP12, GP13, GP14, GP15 }

/* Handness */
#define SPLIT_HAND_MATRIX_GRID GP5, GP15    /* row first because the board is col2row */

/* Disable diode intersection in matrix data */
#define MATRIX_MASKED

/* Bootloader settings */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Serial comunication for split keyboards */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* RGB pin */
#define RGB_DI_PIN GP23
/* Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral */
#define WS2812_PIO_USE_PIO1

/* Number of LEDs */
#define RGBLED_NUM 14

/* LCD Configuration */
#define SPI_DRIVER   SPID0
#define SPI_SCK_PIN	 GP18
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP19

#define LCD_RST_PIN GP16
#define LCD_CS_PIN GP17
#define LCD_DC_PIN GP21

/* Backlight LCD Configuration */
#define BACKLIGHT_LEVELS 10
#define BACKLIGHT_PIN GP28
/* #define BACKLIGHT_ON_STATE 1 */
#define BACKLIGHT_PWM_DRIVER PWMD6
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A


/* turn off effects when suspended */
#define RGB_DISABLE_WHEN_USB_SUSPENDED


/* Debounce time in ms for matrix scans */
#undef DEBOUNCE
#define DEBOUNCE 5

/* Set USB polling rate to 1000 Hz */
#define USB_POLLING_INTERVAL_MS 1

/* sets the number of milliseconds to pause after sending a wakeup packet.
*  Disabled by default, you might want to set this to 200 (or higher) if the
*  keyboard does not wake up properly after suspending.
*/
#define USB_SUSPEND_WAKEUP_DELAY 200

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* Tap dance setup */
#define TAPPING_TERM 200
#define TAPPING_TERM_PER_KEY


#ifdef RGBLIGHT_ENABLE
#    define RGBLIGHT_HUE_STEP  8
#    define RGBLIGHT_SAT_STEP  8
#    define RGBLIGHT_VAL_STEP  8
#    define RGBLIGHT_LIMIT_VAL 150
#    define RGBLIGHT_SLEEP
#    define RGBLIGHT_SPLIT
#    define RGBLIGHT_LAYERS
#endif

/* RGB matrix support */
#ifdef RGB_MATRIX_ENABLE
    #ifndef SPLIT_LAYER_STATE_ENABLE
        #define SPLIT_LAYER_STATE_ENABLE
    #endif
#endif

#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_WPM_ENABLE

#define SPLIT_WATCHDOG_ENABLE

/*
was necessary until LTO was disabled in rules.mk
#define SPLIT_WATCHDOG_TIMEOUT 15000
*/










