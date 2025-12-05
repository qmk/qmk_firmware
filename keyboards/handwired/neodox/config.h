// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


/* Bootloader settings */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* Serial comunication for split keyboards */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

/* Force the usage of PIO1 peripheral, by default the WS2812 implementation uses the PIO0 peripheral */
#define WS2812_PIO_USE_PIO1

/* LCD Configuration */
#define SPI_DRIVER   SPID0
#define SPI_SCK_PIN	 GP18
#define SPI_MISO_PIN GP20
#define SPI_MOSI_PIN GP19

#define LCD_RST_PIN GP16
#define LCD_CS_PIN GP17
#define LCD_DC_PIN GP21


/* #define BACKLIGHT_ON_STATE 1 */
#define BACKLIGHT_PWM_DRIVER PWMD6
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE
