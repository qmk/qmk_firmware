// Copyright 2022 Stefan Kerkmann
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next "mcuconf.h"

#undef RP_PWM_USE_PWM0
#define RP_PWM_USE_PWM0 TRUE

#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

#undef RP_IRQ_ADC1_PRIORITY
#define RP_IRQ_ADC1_PRIORITY 2
