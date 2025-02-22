// Copyright 2024 Conor Burns (@Conor-Burns)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM2
#define RP_PWM_USE_PWM2 TRUE
