// Copyright 2024 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/**======================
 **    I2C Driver
 *========================**/

#if !defined(I2C_DRIVER)
#    define I2C_DRIVER I2CD1
#endif

#if !defined(I2C1_SDA_PIN)
#    define I2C1_SDA_PIN GP2
#endif

#if !defined(I2C1_SCL_PIN)
#    define I2C1_SCL_PIN GP3
#endif

/**======================
 **    SPI Driver
 *========================**/

#if !defined(SPI_DRIVER)
#    define SPI_DRIVER SPID0
#endif

#if !defined(SPI_SCK_PIN)
#    define SPI_SCK_PIN GP18
#endif

#if !defined(SPI_MISO_PIN)
#    define SPI_MISO_PIN GP20
#endif

#if !defined(SPI_MOSI_PIN)
#    define SPI_MOSI_PIN GP19
#endif

/**======================
 **      SERIAL Driver
 *========================**/

#if !defined(SERIAL_USART_DRIVER)
#    define SERIAL_USART_DRIVER SIOD0
#endif

#if !defined(SERIAL_USART_TX_PIN) && !defined(SOFT_SERIAL_PIN)
#    define SERIAL_USART_TX_PIN GP0
#endif

#if !defined(SERIAL_USART_RX_PIN)
#    define SERIAL_USART_RX_PIN GP1
#endif

/**======================
 **      UART Driver
 *========================**/

#if !defined(UART_DRIVER)
#    define UART_DRIVER SIOD0
#endif

#if !defined(UART_TX_PIN)
#    define UART_TX_PIN GP0
#endif

#if !defined(UART_RX_PIN)
#    define UART_RX_PIN GP1
#endif

#if !defined(UART_CTS_PIN)
#    define UART_CTS_PIN GP2
#endif

#if !defined(UART_RTS_PIN)
#    define UART_RTS_PIN GP3
#endif

/**======================
 **    Double-tap
 *========================**/

#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
