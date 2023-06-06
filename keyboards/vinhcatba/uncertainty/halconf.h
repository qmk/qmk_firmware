// Copyright 2023 Vinh Le (@vinhcatba)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#ifdef RGBLIGHT_ENABLE
    #undef HAL_USE_PWM
    #define HAL_USE_PWM TRUE
#endif

#undef HAL_USE_I2C
#define HAL_USE_I2C TRUE

#include_next <halconf.h>
