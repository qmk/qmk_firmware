// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

// Bootloader
#define STM32_BOOTLOADER_DUAL_BANK TRUE
#define STM32_BOOTLOADER_DUAL_BANK_GPIO B7

// Peripheral power control pins
#define LCD_POWER_ENABLE_PIN A6

// Split configuration
#define SPLIT_TRANSACTION_IDS_KB RPC_ID_SYNC_STATE_KB
#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_WPM_ENABLE

// SPI Configuration
#define SPI_DRIVER SPID3
#define SPI_SCK_PIN C10
#define SPI_SCK_PAL_MODE 6
#define SPI_MOSI_PIN C12
#define SPI_MOSI_PAL_MODE 6
#define SPI_MISO_PIN C11
#define SPI_MISO_PAL_MODE 6

// LCD Configuration
#define LCD_RST_PIN B3
#define LCD_CS_PIN D2
#define LCD_DC_PIN A15
#ifndef LCD_ACTIVITY_TIMEOUT
#    define LCD_ACTIVITY_TIMEOUT 30000
#endif // LCD_ACTIVITY_TIMEOUT

// Backlight driver (to control LCD backlight)
#define BACKLIGHT_PWM_DRIVER PWMD17
#define BACKLIGHT_PWM_CHANNEL 1
#define BACKLIGHT_PAL_MODE 1

// RGB configuration
#define RGB_DI_PIN B2
#define WS2812_EXTERNAL_PULLUP
#define WS2812_PWM_DRIVER PWMD20
#define WS2812_PWM_CHANNEL 1
#define WS2812_PWM_PAL_MODE 3
#define WS2812_DMA_STREAM STM32_DMA1_STREAM1
#define WS2812_DMA_CHANNEL 1
#define WS2812_DMAMUX_ID STM32_DMAMUX1_TIM20_UP

// Audio configuration
#define AUDIO_PIN A5
#define AUDIO_PIN_ALT A4
#define AUDIO_PIN_ALT_AS_NEGATIVE
#ifndef STARTUP_SONG
#    define STARTUP_SONG SONG(STARTUP_SOUND)
#endif // STARTUP_SONG
