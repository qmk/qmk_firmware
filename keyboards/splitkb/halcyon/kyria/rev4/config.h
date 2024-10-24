// Copyright 2024 splitkb.com (support@splitkb.com)
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