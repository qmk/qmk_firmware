// Copyright 2023 yuchi
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#define SERIAL_USART_FULL_DUPLEX
#define SERIAL_USART_TX_PIN GP0
#define SERIAL_USART_RX_PIN GP1

#define I2C_DRIVER I2CD1 // I2CD1 = I2C1
#define I2C1_SDA_PIN GP14
#define I2C1_SCL_PIN GP15

#define OLED_FONT_H "lib/glcdfont_lily.c"
