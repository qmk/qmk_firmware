/* Copyright 2024 QMK
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 */

#pragma once

/*
 * HAL driver enable switches for CH579M / KEY12-V02.
 * Only PAL (GPIO), ST (SysTick tick), and USB are needed for a basic QMK HID keyboard.
 */

#define HAL_USE_PAL TRUE
#define HAL_USE_ST TRUE
#define HAL_USE_USB TRUE

/* Everything else off */
#define HAL_USE_ADC FALSE
#define HAL_USE_CAN FALSE
#define HAL_USE_DAC FALSE
#define HAL_USE_EFL FALSE
#define HAL_USE_GPT FALSE
#define HAL_USE_I2C FALSE
#define HAL_USE_ICU FALSE
#define HAL_USE_MAC FALSE
#define HAL_USE_MMC_SPI FALSE
#define HAL_USE_PWM FALSE
#define HAL_USE_RTC FALSE
#define HAL_USE_SDC FALSE
#define HAL_USE_SERIAL FALSE
#define HAL_USE_SERIAL_USB FALSE
#define HAL_USE_SIO FALSE
#define HAL_USE_SPI FALSE
#define HAL_USE_TRNG FALSE
#define HAL_USE_UART FALSE
#define HAL_USE_USB TRUE
#define HAL_USE_WDG FALSE
#define HAL_USE_WSPI FALSE

#include_next <halconf.h>
