// Copyright 2021 Nick Brassel (@tzarc)
// SPDX-License-Identifier: GPL-2.0-or-later
#pragma once


#define BACKLIGHT_PWM_DRIVER  PWMD4
#define BACKLIGHT_PWM_CHANNEL 3
#define BACKLIGHT_PAL_MODE    2

#define ADC_PIN A0

#define SOLENOID_PINS { B12, B13, B14, B15 }
#define SOLENOID_PINS_ACTIVE_STATE { high, high, low }
