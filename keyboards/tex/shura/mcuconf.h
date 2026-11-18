// Copyright 2026 Mauro DiBenedetto
// Copyright 2026 Antonio SJ Musumeci (@trapexit)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "nvic.h"

#define HT32F52352_MCUCONF

// No crystal: 8 MHz HSI x6 = 48 MHz, trimmed against USB SOF in board_init().
#define HT32_CKCU_SW CKCU_GCCR_SW_PLL
#define HT32_PLL_USE_HSE FALSE
#define HT32_PLL_FBDIV 6
#define HT32_PLL_OTDIV 0
#define HT32_AHB_PRESCALER 1
#define HT32_USART_PRESCALER 1
#define HT32_USB_PRESCALER 1
#define HT32_ST_USE_HCLK TRUE

#define HT32_USB_USE_USB0 TRUE
#define HT32_USB_USB0_IRQ_PRIORITY 5
// wait_us() timer
#define HT32_GPT_USE_BFTM0 TRUE
// Bluetooth module UART
#define HT32_SERIAL_USE_USART0 TRUE
#define HT32_USART0_IRQ_PRIORITY 6
// U3 SPI NOR flash (wear-leveled EEPROM)
#define HT32_SPI_USE_SPI1 TRUE
#define HT32_SPI1_IRQ_PRIORITY 7
