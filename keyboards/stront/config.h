// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_PIN_SWAP
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

/* any side can be master by default, enable split sync to support it */
#define EE_HANDS
#define SPLIT_POINTING_ENABLE

/* SPI config for display/touchpad */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP10
#define SPI_MOSI_PIN GP11
#define SPI_MISO_PIN GP12

/* touchpad config */
#define POINTING_DEVICE_RIGHT
#define POINTING_DEVICE_CS_PIN GP9
#define POINTING_DEVICE_ROTATION_180
#define CIRQUE_PINNACLE_DIAMETER_MM 40

/* LCD config */
#define LCD_DC_PIN GP12
#define LCD_CS_PIN GP9
#define LCD_RST_PIN GP13
#define BACKLIGHT_PWM_DRIVER PWMD7
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define QUANTUM_PAINTER_LVGL_USE_CUSTOM_CONF
