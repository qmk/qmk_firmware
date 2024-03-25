// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include_next <halconf.h>

#undef HAL_USE_PWM
#define HAL_USE_PWM TRUE
