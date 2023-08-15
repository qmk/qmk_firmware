// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#define HAL_USE_SIO TRUE

// For single-zone backlight
#define HAL_USE_PWM TRUE

#define HAL_USE_ADC TRUE

#include_next <halconf.h>
