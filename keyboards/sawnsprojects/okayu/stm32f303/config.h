// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define WS2812_SPI SPID1 // default: SPID1
#define WS2812_SPI_MOSI_PAL_MODE 5 // MOSI pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5
#define WS2812_SPI_SCK_PIN B13 // Required for F072, may be for others -- SCK pin, see the respective datasheet for the appropriate values for your MCU. default: unspecified
#define WS2812_SPI_SCK_PAL_MODE 5 // SCK pin "alternate function", see the respective datasheet for the appropriate values for your MCU. default: 5