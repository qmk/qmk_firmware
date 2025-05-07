// Copyright 2025 customMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

// FRAM configuration
#define EXTERNAL_EEPROM_SPI_SLAVE_SELECT_PIN B7
#define EXTERNAL_EEPROM_SPI_CLOCK_DIVISOR 4

// SPI configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

// Audio configuration
#define AUDIO_PIN B8
#define AUDIO_PWM_DRIVER PWMD4
#define AUDIO_PWM_CHANNEL 3 
#define AUDIO_PWM_PAL_MODE 2
#define AUDIO_STATE_TIMER GPTD5
#define AUDIO_INIT_DELAY

// RGB Matrix configuration
#define WS2812_PWM_DRIVER PWMD1
#define WS2812_PWM_CHANNEL 3
#define WS2812_PWM_PAL_MODE 1
#define WS2812_DMA_STREAM STM32_DMA2_STREAM5
#define WS2812_DMA_CHANNEL 6

// Switch matrix configuration
#define COL_SHIFT_IN_PIN A2
#define COL_SHIFT_CLK_PIN A3

#define MATRIX_ROWS 7
#define MATRIX_COLS 32
#define MATRIX_ROW_PINS { C13, C14, C15, B1, A7, A5, A6 }

#define LED_CAPS_LOCK_PIN B10
#define LED_NUM_LOCK_PIN B0
#define LED_SCROLL_LOCK_PIN A1
#define LED_MIC_MUTE_PIN B13

#define MIC_MUTE_STATE_PIN B9
#define MIC_MUTE_CONTROL_PIN A0
#define USB_AUDIO_ENABLE_PIN B6

#define LED_PIN_ON_STATE 0
