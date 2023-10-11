// Copyright 2023 Pascal Jaeger <pascal.jaeger@leimstift.de>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define CRC8_USE_TABLE
#define CRC8_OPTIMIZE_SPEED

/* Reset to bootloader */
#define RESET_PIN                                  GP22
#define RESET_PIN_DOUBLE_TAP_RESET_TIMEOUT         1000U
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_LED     GP25
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 1000U

/* split settings */
#define SPLIT_POINTING_ENABLE
#define SPLIT_HAND_PIN GP28 // high = left, low = right

/* serial configuration for split keyboard */
#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN  GP0
#define SERIAL_USART_RX_PIN  GP1
#define SERIAL_USART_TIMEOUT 100
#define SERIAL_USART_SPEED   921600
#define SERIAL_USART_PIN_SWAP

/* i2c config for oleds */
#define I2C_DRIVER       I2CD1
#define I2C1_SDA_PIN     GP2
#define I2C1_SCL_PIN     GP3
#define I2C1_CLOCK_SPEED 400000

/* SPI config */
#define SPI_DIVER    SPID0
#define SPI_SCK_PIN  GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN GP16

/* pmw3360 config */
#define POINTING_DEVICE_CS_PIN GP17
