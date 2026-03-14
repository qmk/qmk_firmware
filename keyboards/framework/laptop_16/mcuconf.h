// Copyright 2022-2023 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// For single-zone backlight
#undef RP_PWM_USE_PWM4
#define RP_PWM_USE_PWM4 TRUE

/*
 * IRQ system settings.
 */
#undef RP_IRQ_ADC1_PRIORITY
#define RP_IRQ_ADC1_PRIORITY 2
