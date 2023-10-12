// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* LCD config */
#define LCD_DC_PIN GP16   // data/command
#define LCD_CS_PIN GP17   // chip select
#define LCD_RST_PIN GP14  // reset
#define LCD_LED_PIN GP15  // backlight

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // milliseconds
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE