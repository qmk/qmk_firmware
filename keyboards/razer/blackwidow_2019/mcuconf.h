// Copyright 2026 AeroModes
// SPDX-License-Identifier: GPL-2.0-or-later

#pragma once

#include_next <mcuconf.h>

/* 12 MHz HSE x8 = 96 MHz VCO -> /3 = 32 MHz SYSCLK, VCO/2 = 48 MHz USB. */
#undef STM32_PLLMUL_VALUE
#define STM32_PLLMUL_VALUE 8

/* IS31FL3733 LED drivers on I2C1 (SCL PB6, SDA PB7). */
#undef STM32_I2C_USE_I2C1
#define STM32_I2C_USE_I2C1 TRUE
