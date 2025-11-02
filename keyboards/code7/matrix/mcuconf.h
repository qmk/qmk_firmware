// Copyright 2023 Chris H <chris@zoid.com.au>
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM2
#define RP_PWM_USE_PWM2 TRUE

#undef RP_PWM_USE_PWM3
#define RP_PWM_USE_PWM3 TRUE

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_PWM_USE_PWM5
#define RP_PWM_USE_PWM5 TRUE

#undef RP_PWM_USE_PWM6
#define RP_PWM_USE_PWM6 TRUE

#undef RP_PWM_USE_PWM7
#define RP_PWM_USE_PWM7 TRUE
