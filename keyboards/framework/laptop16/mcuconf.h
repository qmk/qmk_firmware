// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>


// For RGB backlight
#undef RP_ADC_USE_ADC1
#define RP_ADC_USE_ADC1 TRUE

// For single-zone backlight
#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

/*
 * IRQ system settings.

 * TODO: Default is 3, should it be 2?
 */
#undef RP_IRQ_ADC1_PRIORITY
#define RP_IRQ_ADC1_PRIORITY 2
