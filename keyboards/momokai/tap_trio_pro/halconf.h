/* Copyright 2023 peepeetee (@peepeetee)
SPDX-License-Identifier: GPL-2.0-or-later */
#pragma once

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#undef HAL_USE_ADC
#define HAL_USE_ADC TRUE

#include_next <halconf.h>
