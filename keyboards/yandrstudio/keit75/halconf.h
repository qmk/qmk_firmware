// Copyright 2022 Y&R-Biu (@jiaxin96)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once
#include_next <halconf.h>

#undef HAL_USE_PWM
#define HAL_USE_PWM    TRUE
