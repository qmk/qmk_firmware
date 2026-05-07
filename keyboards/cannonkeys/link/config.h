/* Copyright 2024 CannonKeys */
/* SPDX-License-Identifier: GPL-2.0-or-later */

#pragma once

/* VBUS-routed pin for upstream detection */
#define USB_VBUS_PIN GP27

#define	SPLIT_HAND_PIN_LOW_IS_LEFT

// Configure full duplex split comms over PIO
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP28
#define SERIAL_USART_RX_PIN GP29
#define SERIAL_USART_PIN_SWAP

/* RP2040- and hardware-specific config */
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#define PICO_XOSC_STARTUP_DELAY_MULTIPLIER 64

/* I2C for OLEDs */
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

#define OLED_DISPLAY_64X128
