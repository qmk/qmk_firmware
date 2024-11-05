// Copyright 2024 splitkb.com (support@splitkb.com)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

//// VIK

#if HAL_USE_I2C == TRUE
#   undef RP_I2C_USE_I2C0
#   define RP_I2C_USE_I2C0 TRUE
#endif

#if HAL_USE_SPI == TRUE
#   undef RP_SPI_USE_SPI1
#   define RP_SPI_USE_SPI1 TRUE
#endif