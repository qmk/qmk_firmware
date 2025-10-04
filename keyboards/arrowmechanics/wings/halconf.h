// Copyright 2024 Filip Strzałka (@philvec)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <halconf.h>

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE
