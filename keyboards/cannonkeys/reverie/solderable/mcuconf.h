// Copyright 2024 Andrew Kannan
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE
