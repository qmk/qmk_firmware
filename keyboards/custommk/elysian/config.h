// Copyright 2024 customMK
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