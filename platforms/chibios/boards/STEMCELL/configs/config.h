// Copyright 2022 Mega Mind(@megamind4089)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#ifndef EARLY_INIT_PERFORM_BOOTLOADER_JUMP
#    define EARLY_INIT_PERFORM_BOOTLOADER_JUMP TRUE
#endif

/**======================
 **    I2C Driver
 *========================**/

#if !defined(I2C1_SDA_PIN)
#    define I2C1_SDA_PIN D0
#endif

#if !defined(I2C1_SCL_PIN)
#    define I2C1_SCL_PIN D1
#endif

/**======================
 **      SERIAL Driver
 *========================**/

#if !defined(SERIAL_USART_DRIVER)
#    define SERIAL_USART_DRIVER SD2
#endif

/**======================
 **    SPI Driver
 *========================**/
#ifndef SPI_DRIVER
#    define SPI_DRIVER SPID1
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
