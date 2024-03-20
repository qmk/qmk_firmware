// Copyright 2022 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once


#define ADC_PIN A0

#define BACKLIGHT_PWM_DRIVER  PWMD4
#define BACKLIGHT_PWM_CHANNEL 3
#define BACKLIGHT_PAL_MODE    2

#define APA102_NOPS (100 / (1000000000L / (CPU_CLOCK / 4)))
#define RGB_CI_PIN B8

#define SOLENOID_PIN B12
#define SOLENOID_PINS { B12, B13, B14, B15 }
#define SOLENOID_PINS_ACTIVE_STATE { high, high, low }

#define I2C1_SDA_PIN B7
#define I2C1_SCL_PIN B6
#define I2C1_SCL_PAL_MODE 4
#define I2C1_OPMODE OPMODE_I2C
#define I2C1_CLOCK_SPEED 100000
