// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE
#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
