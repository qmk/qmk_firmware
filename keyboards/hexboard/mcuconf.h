// Copyright 2023 Zach DeCook
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE
#undef RP_I2C_USE_I2C1
#define RP_I2C_USE_I2C1 FALSE

// For audio, pin 23 is PWM3 B
#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE
