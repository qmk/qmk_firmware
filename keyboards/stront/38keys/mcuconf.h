// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM7
#define RP_PWM_USE_PWM7 TRUE
