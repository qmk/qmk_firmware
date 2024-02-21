// Copyright 2023 ziptyze
// SPDX-License-Identifier: GPL-2.0-or-later#pragma once

#pragma once

#include_next <mcuconf.h>

#undef RP_I2C_USE_I2C1
#undef RP_ADC_USE_ADC1
#define RP_I2C_USE_I2C1 TRUE
#define RP_ADC_USE_ADC1 TRUE
