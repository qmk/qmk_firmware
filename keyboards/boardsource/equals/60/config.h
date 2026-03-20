// Copyright 2023 Cole Smith (@boardsource)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#define AUDIO_PIN GP29
#define AUDIO_PWM_DRIVER PWMD6
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_B

#define AUDIO_INIT_DELAY

// SPI Configuration
#define SPI_DRIVER SPID1
#define SPI_SCK_PIN GP26
#define SPI_MOSI_PIN GP27

// Display Configuration
#define OLED_CS_PIN GP25
#define OLED_DC_PIN GP20
#define OLED_RST_PIN GP28
