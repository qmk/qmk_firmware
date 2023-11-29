// Copyright 2023 JoyLee (@itarze)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* RGB Matrix */
#define RGB_MATRIX_LED_COUNT 88
#define RGB_DISABLE_WHEN_USB_SUSPENDED
#define RGB_MATRIX_DEFAULT_VAL 80

/* SPI Config for spi flash*/
#define SPI_DRIVER SPIDQ
#define SPI_SCK_PIN B3
#define SPI_MOSI_PIN B5
#define SPI_MISO_PIN B4
#define SPI_MOSI_PAL_MODE 5

#define EXTERNAL_FLASH_SPI_SLAVE_SELECT_PIN C12
