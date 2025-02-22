// Copyright 2025 esplo
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <mcuconf.h>

#define RP2040_MCUCONF

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 FALSE
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 TRUE

#define RP_I2C_BUSY_TIMEOUT 50
#define RP_I2C_ADDRESS_MODE_10BIT FALSE
