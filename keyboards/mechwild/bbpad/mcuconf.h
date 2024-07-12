// Copyright 2023 QMK Contributors (@qmk)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

// WS2812
#undef STM32_PWM_USE_TIM4
#define STM32_PWM_USE_TIM4                  TRUE
