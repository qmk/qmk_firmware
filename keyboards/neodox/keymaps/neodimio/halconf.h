// Copyright 2018-2022 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#undef HAL_USE_SERIAL

#define HAL_USE_SPI TRUE

#define HAL_USE_SIO TRUE

#define HAL_USE_PWM TRUE

#include_next <halconf.h>
