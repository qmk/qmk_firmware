// Copyright 2023 VertorWang (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* SPI */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

/* Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12

/* RGB Driver */
#define WS2812_SPI_DRIVER SPIDM2
#define WS2812_SPI_MOSI_PAL_MODE 0
#define WS2812_SPI_SCK_PAL_MODE 0
