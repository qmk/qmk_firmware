// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* Encoder */
#define ENCODER_DIRECTION_FLIP

/* LED */
#define LED_PIN_ON_STATE 0
#define LED_CAPS_LOCK_PIN C15
#define LED_SCROLL_LOCK_PIN C0

/* LED Driver */
#define DRIVER_1_CS B6
#define DRIVER_1_EN B7
#define DRIVER_COUNT 1
#define RGB_MATRIX_LED_COUNT 67

/* SPI Config */
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4

/* SPI Flash */
#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
#define WEAR_LEVELING_BACKING_SIZE (4 * 1024)

/* RGB Matrix*/
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_KEYRELEASES
