// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/**======================
 **    I2C Driver
 *========================**/

#ifndef I2C_DRIVER
#    define I2C_DRIVER I2CD1
#endif
#ifndef I2C1_SDA_PIN
#    define I2C1_SDA_PIN D1
#endif
#ifndef I2C1_SCL_PIN
#    define I2C1_SCL_PIN D0
#endif

/**======================
 **    SPI Driver
 *========================**/
#ifndef SPI_DRIVER
#    define SPI_DRIVER SPID0
#endif
#ifndef SPI_SCK_PIN
#    define SPI_SCK_PIN B1
#endif
#ifndef SPI_MISO_PIN
#    define SPI_MISO_PIN B3
#endif
#ifndef SPI_MOSI_PIN
#    define SPI_MOSI_PIN B2
#endif

/**======================
 **      UART Driver
 *========================**/

#ifndef UART_DRIVER
#    define UART_DRIVER SIOD0
#endif

#ifndef UART_TX_PIN
#    define UART_TX_PIN D3
#endif

#ifndef UART_RX_PIN
#    define UART_RX_PIN D2
#endif

/**======================
 **    Double-tap
 *========================**/

#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#endif
#ifndef RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT
#    define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U
#endif
