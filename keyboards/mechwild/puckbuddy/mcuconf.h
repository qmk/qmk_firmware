// Copyright 2022 Kyle McCreery (@kylemccreery)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE

#undef STM32_SPI_USE_SPI1
#define STM32_SPI_USE_SPI1 TRUE

/* spi config */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5    
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5
#define CIRQUE_PINNACLE_SPI_DIVISOR 8
#define CIRQUE_PINNACLE_SPI_CS_PIN A4