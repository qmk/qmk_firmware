// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/*
 * see config.h for notes on the Keybow 2040 I2C setup
 */
#undef  RP_I2C_USE_I2C0
#undef  RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C0 TRUE
#define RP_I2C_USE_I2C1 FALSE
