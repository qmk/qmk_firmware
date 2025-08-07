// Copyright 2024 Filip Strzałka (@philvec)
// SPDX-License-Identifier: GPL-3.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM2
#define RP_PWM_USE_PWM2 TRUE
