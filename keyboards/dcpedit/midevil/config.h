// Copyright 2023 Ming-Gih Lam (@dcpedit)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* LCD config */
#define LCD_DC_PIN GP16   // data/command
#define LCD_CS_PIN GP17   // chip select
#define LCD_RST_PIN GP14  // reset
#define BACKLIGHT_PIN GP15
#define BACKLIGHT_PWM_DRIVER PWMD7
#define BACKLIGHT_PWM_CHANNEL RP2040_PWM_CHANNEL_B
#define BACKLIGHT_LEVELS 5
#define BACKLIGHT_DEFAULT_LEVEL 4

/* SPI pins */
#define SPI_DRIVER SPID0
#define SPI_SCK_PIN GP18
#define SPI_MOSI_PIN GP19
#define SPI_MISO_PIN NO_PIN

#define QUANTUM_PAINTER_DISPLAY_TIMEOUT 0 // milliseconds
#define QUANTUM_PAINTER_SUPPORTS_256_PALETTE TRUE