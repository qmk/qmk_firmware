// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* MX40 overrides */
#undef LCD_DC_PIN
#define LCD_DC_PIN GP27
#undef LCD_RST_PIN
#define LCD_RST_PIN GP12
#undef BACKLIGHT_PWM_DRIVER
#define BACKLIGHT_PWM_DRIVER PWMD6
