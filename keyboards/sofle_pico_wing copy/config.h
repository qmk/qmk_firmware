// Copyright 2024 TheWerle (@TheWerle)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* I2C for OLED and touch*/
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

#ifdef OLED_ENABLE
#    define OLED_DISPLAY_128X64
#    define OLED_TIMEOUT 30000
#endif

/* Encoder settings */
#ifdef ENCODER_MAP_ENABLE
#    define ENCODER_MAP_KEY_DELAY 10
#endif

#ifdef RGB_MATRIX_ENABLE
#    define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 50
/* If you're setting colors per key, this is required */
#    define RGB_DISABLE_WHEN_USB_SUSPENDED
#endif

/* Allows for more than the default 4 layers in VIA. */
#ifndef DYNAMIC_KEYMAP_LAYER_COUNT
#    define DYNAMIC_KEYMAP_LAYER_COUNT 4
#endif


#define AUDIO_PWM_DRIVER PWMD1
#define AUDIO_PWM_CHANNEL RP2040_PWM_CHANNEL_A
#define AUDIO_PIN GP18
// #define AUDIO_PIN_ALT GP17
// #define AUDIO_PIN_ALT_AS_NEGATIVE
#define AUDIO_INIT_DELAY
// #define AUDIO_ENABLE_TONE_MULTIPLEXING
// #define AUDIO_TONE_MULTIPLEXING_RATE_DEFAULT 10
#define STARTUP_SONG SONG(MUSIC_SCALE_SOUND)
