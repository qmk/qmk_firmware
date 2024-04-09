// Copyright 2023 zzeneg (@zzeneg)
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

/* 40keys overrides */
#undef LCD_DC_PIN
#define LCD_DC_PIN GP27
#undef LCD_RST_PIN
#define LCD_RST_PIN GP12
#undef BACKLIGHT_PWM_DRIVER
#define BACKLIGHT_PWM_DRIVER PWMD6

/* Bootmagic on top outer pinky key */
#define BOOTMAGIC_ROW 3
#define BOOTMAGIC_COLUMN 0
