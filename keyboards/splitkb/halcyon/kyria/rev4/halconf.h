// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

//// VIK

// GPIO1 = GP27
// GPIO2 = GP26
// CS = GP13

#if HAL_USE_I2C == TRUE
#   define I2C_DRIVER I2C0
#   define I2C1_SDA_PIN GP16
#   define I2C1_SCL_PIN GP17
#endif

#if HAL_USE_SPI == TRUE
#   define SPI_DRIVER SPID1
#   define SPI_SCK_PIN GP14
#   define SPI_MOSI_PIN GP15
#   define SPI_MISO_PIN GP12
#   define SPI_USE_WAIT TRUE
#   define SPI_SELECT_MODE SPI_SELECT_MODE_PAD
#endif

#include_next <halconf.h>