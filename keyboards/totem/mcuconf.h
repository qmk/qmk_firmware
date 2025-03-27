// Copyright 2022 GEIST <@geigigeist>
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_PWM_USE_TIM1
#define RP_PWM_USE_TIM1 TRUE
