// Copyright 2022 MatteoDM <matteodalmo@gmail.com>
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#undef HAL_USE_SERIAL
#define HAL_USE_SPI TRUE

#define HAL_USE_SIO TRUE

#define HAL_USE_PWM TRUE


#include_next <halconf.h>
