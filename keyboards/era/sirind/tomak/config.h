// Copyright 2023 Hyojin Bak (@eerraa)
// SPDX-License-Identifier: GPL-2.0-or-later
 
#pragma once

/* VBUS detection. */
#define USB_VBUS_PIN GP29

/* Serial Driver. */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1
#define SERIAL_USART_PIN_SWAP

/* Reset. */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

#define VIA_EEPROM_CUSTOM_CONFIG_SIZE 7