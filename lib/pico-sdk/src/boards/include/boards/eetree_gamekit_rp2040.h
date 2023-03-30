/*
 * Copyright (c) 2021 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// -----------------------------------------------------
// NOTE: THIS HEADER IS ALSO INCLUDED BY ASSEMBLER SO
//       SHOULD ONLY CONSIST OF PREPROCESSOR DIRECTIVES
// -----------------------------------------------------

#ifndef _BOARDS_EETREE_GAMEKIT_RP2040_H
#define _BOARDS_EETREE_GAMEKIT_RP2040_H

// For board detection
#define EETREE_GAMEKIT_RP2040

// --- UART ---
// no PICO_DEFAULT_UART
// no PICO_DEFAULT_UART_TX_PIN
// no PICO_DEFAULT_UART_RX_PIN

// --- LED ---
#ifndef PICO_DEFAULT_LED_PIN
    #define PICO_DEFAULT_LED_PIN 4
#endif
// no PICO_DEFAULT_WS2812_PIN

// --- I2C ---
#ifndef PICO_DEFAULT_I2C
    #define PICO_DEFAULT_I2C 1
#endif
#ifndef PICO_DEFAULT_I2C_SDA_PIN
    #define PICO_DEFAULT_I2C_SDA_PIN 10
#endif
#ifndef PICO_DEFAULT_I2C_SCL_PIN
    #define PICO_DEFAULT_I2C_SCL_PIN 11
#endif

// --- SPI ---
// no PICO_DEFAULT_SPI
// no PICO_DEFAULT_SPI_SCK_PIN
// no PICO_DEFAULT_SPI_TX_PIN
// no PICO_DEFAULT_SPI_RX_PIN
// no PICO_DEFAULT_SPI_CSN_PIN

// --- LCD ---
#ifndef EETREE_RP2040_LCD_SPI
    #define EETREE_RP2040_LCD_SPI 0
#endif
#ifndef EETREE_RP2040_LCD_DC_PIN
    #define EETREE_RP2040_LCD_DC_PIN 1
#endif
#ifndef EETREE_RP2040_LCD_SCLK_PIN
    #define EETREE_RP2040_LCD_SCLK_PIN 2
#endif
#ifndef EETREE_RP2040_LCD_TX_PIN
    #define EETREE_RP2040_LCD_TX_PIN 3
#endif
#ifndef EETREE_RP2040_LCD_RST_PIN
    #define EETREE_RP2040_LCD_RST_PIN 0
#endif
// no EETREE_RP2040_LCD_CS_PIN

// --- FLASH ---
#define PICO_BOOT_STAGE2_CHOOSE_W25Q080 1
#ifndef PICO_FLASH_SPI_CLKDIV
    #define PICO_FLASH_SPI_CLKDIV 2
#endif
#ifndef PICO_FLASH_SIZE_BYTES
    #define PICO_FLASH_SIZE_BYTES (2 * 1024 * 1024)
#endif

// All boards have B1 RP2040
#ifndef PICO_RP2040_B0_SUPPORTED
    #define PICO_RP2040_B0_SUPPORTED  0
#endif

#endif // _BOARDS_EETREE_GAMEKIT_RP2040_H
