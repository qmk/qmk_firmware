// Copyright 2023 jonylee@hfd (@jonylee1986)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef WB32_SPI_USE_QSPI
#define WB32_SPI_USE_QSPI TRUE

#undef WB32_I2C_USE_I2C1
#define WB32_I2C_USE_I2C1 TRUE
