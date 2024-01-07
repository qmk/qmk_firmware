// Copyright 2023 binepad (@binepad)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// Don't need SPI
#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 FALSE

// Don't need I2C
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE

// Don't need ADC
#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 FALSE
