// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once

#include "config_common.h"

#define MATRIX_COL_PINS { A2 }
#define MATRIX_ROW_PINS { A1 }

#define BACKLIGHT_PIN         B8
#define BACKLIGHT_PWM_DRIVER  PWMD4
#define BACKLIGHT_PWM_CHANNEL 3
#define BACKLIGHT_PAL_MODE    2

#define RGB_DI_PIN A0
#define RGB_CI_PIN B13

#define ADC_PIN A0
