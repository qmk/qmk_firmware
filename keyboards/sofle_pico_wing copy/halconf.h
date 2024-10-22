// Copyright 2024 Ryan Neff (@JellyTitan)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include_next <halconf.h>

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE
#define HAL_USE_I2C TRUE
