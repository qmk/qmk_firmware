// Copyright 2023 Cole Smith (@boardsource)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
// #define NO_DEBUG

/* disable print */
// #define NO_PRINT

/* disable action features */
// #define NO_ACTION_LAYER
// #define NO_ACTION_TAPPING
// #define NO_ACTION_ONESHOT

#pragma once
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 200U

#define RGB_MATRIX_LED_COUNT 70
#define RGB_DI_PIN GP21

#define AUDIO_PIN GP29
#define AUDIO_PWM_DRIVER PWMD6
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define AUDIO_CLICKY
#define AUDIO_INIT_DELAY 1000
#define STARTUP_SONG SONG(STARTUP_SOUND)

// SPI Configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP26
#define SPI_MOSI_PIN GP27

// Display Configuration
#define OLED_CS_PIN GP25
#define OLED_DC_PIN GP20
#define OLED_RST_PIN GP28
