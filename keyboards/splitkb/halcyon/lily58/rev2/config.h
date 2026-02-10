// Copyright 2025 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// Make it easier to enter the bootloader
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

// UART1, communication between the two halves
#define SERIAL_USART_FULL_DUPLEX   // Enable full duplex operation mode.
#define SERIAL_USART_TX_PIN GP28   // USART TX pin
#define SERIAL_USART_RX_PIN GP29   // USART RX pin
#define SERIAL_PIO_USE_PIO1        // Use PIO1 as PIO0 is used for WS2812 driver

// VBUS detection
#define USB_VBUS_PIN GP1

//// VIK

// GPIO1 = GP27
// GPIO2 = GP26
// CS = GP13

#define I2C_DRIVER I2C0
#define I2C1_SDA_PIN GP16
#define I2C1_SCL_PIN GP17

#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP14
#define SPI_MOSI_PIN GP15
#define SPI_MISO_PIN GP12
