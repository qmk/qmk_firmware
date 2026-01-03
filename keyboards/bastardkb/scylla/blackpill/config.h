// Copyright 2020 Christopher Courtney <drashna@live.com> (@drashna)
// Copyright 2021 Stefan Kerkmann (@KarlK90)
// Copyright 2022 Charly Delay <charly@codesink.dev> (@0xcharly)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

/* RGB settings. */
#define WS2812_PWM_DRIVER PWMD2
#define WS2812_PWM_CHANNEL 2
#define WS2812_PWM_PAL_MODE 1
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_PWM_DMA_CHANNEL 3

/* SPI config for EEPROM. */
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN A5
#define SPI_SCK_PAL_MODE 5
#define SPI_MOSI_PIN A7
#define SPI_MOSI_PAL_MODE 5
#define SPI_MISO_PIN A6
#define SPI_MISO_PAL_MODE 5

/* EEPROM config. */
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN A4
