// Copyright 2024 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE

#include_next <halconf.h>
