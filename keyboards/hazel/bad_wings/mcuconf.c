// Copyright 2023 Jason Hazel (@jasonhazel)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next "mcuconf.h"

#undef RP_SPI_USE_SPI0
#define RP_SPI_USE_SPI0 TRUE
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE